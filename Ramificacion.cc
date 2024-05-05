#include <algorithm>

BranchBound::BranchBound(int size_solution, Solution initial_solution,
                         int expansion_strategy) {
  size_solution_ = size_solution;
  initial_solution_ = initial_solution;
  lower_bound_ = initial_solution.calculate_objetive_function();
}

// Método que ejecuta el algoritmo

Solution BranchBound::execute(Problem &problem) {
  Solution best_solution;
  generate_first_level_tree(problem, problem.get_points_size());
  std::vector<int> active_nodes;
  for (size_t i = 0; i < tree_.size(); i++) {
    active_nodes.push_back(i);
  }

  while (active_nodes.size()) {
    prune(active_nodes);
    int node_position = minimum_expandend_node();
    if (node_position != -1) {
      expand_node(node_position, active_nodes, problem);
      for (auto &&node : tree_) {
        if (node.get_solution().get_list_points().size() == size_solution_) {
          node.set_is_solution(true);

          Solution solution = node.get_solution();
          if (is_greater_equal(solution.calculate_objetive_function(),
                               lower_bound_)) {
            lower_bound_ = solution.calculate_objetive_function();
            best_solution = solution;
          }
        }
      }
    } else {
      break;
    }
  }
  return best_solution;
}

void BranchBound::generate_first_level_tree(Problem &problem, int total_nodes) {
  for (size_t i = 0; i < (total_nodes - (size_solution_ - 1)); i++) {
    std::vector<Point> list_points = {problem.get_point(i)};
    Node node(0, calculate_upper_bound(problem, list_points));
    node.set_solution(Solution(list_points));
    tree_.push_back(node);
  }
}

void BranchBound::prune(std::vector<int> &active_nodes) {
  int index = 0;
  for (auto &&node : tree_) {
    if (node.get_value() + node.get_upper_bound() < lower_bound_) {
      node.set_is_pruned(true);
      if (std::find(active_nodes.begin(), active_nodes.end(), index) !=
          active_nodes.end()) {
        active_nodes.erase(
            std::find(active_nodes.begin(), active_nodes.end(), index));
      }
    }
    index++;
  }
}

// Métodos importantes: /////
void BranchBound::expand_node(int node_position, std::vector<int> &active_nodes,
                              Problem &problem) {
  tree_[node_position].set_is_expanded(true);
  active_nodes.erase(
      std::find(active_nodes.begin(), active_nodes.end(), node_position));
  int current_deep_level =
      tree_[node_position].get_solution().get_list_points().size();
  int last_point =
      tree_[node_position].get_solution().get_list_points().back().get_id() + 1;
  int number_of_points = problem.get_points_size();
  Solution partial_solution = tree_[node_position].get_solution();

  for (size_t i = last_point;
       i < (number_of_points - (size_solution_ - current_deep_level)); i++) {
    Solution solution = partial_solution;
    solution.add_point(problem.get_point(i));
    float node_value = solution.calculate_objetive_function();
    Node node(node_value,
              calculate_upper_bound(problem, solution.get_list_points()));
    node.set_solution(solution);
    tree_.push_back(node);
    active_nodes.push_back(tree_.size() - 1);
  }
}

float BranchBound::calculate_upper_bound(Problem &problem,
                                         std::vector<Point> proccesed_points) {
  std::vector<Point> unprocessed_points =
      problem.unproccessed_points(proccesed_points);

  std::vector<float> upper_bound_2;
  std::vector<float> upper_bound_3;

  for (auto &&point : proccesed_points) {
    for (auto &&unprocessed_point : unprocessed_points) {
      float distance =
          problem.calculate_euclidean_distance(point, unprocessed_point);

      // Insert distance in upperB2 of orderly fashion
      int position = 0;
      for (int k = 0; k < upper_bound_2.size(); k++) {
        if (distance < upper_bound_2[k]) {
          position++;
        }
      }
      upper_bound_2.insert(upper_bound_2.begin() + position, distance);
    }
  }

  float upper_bound_2_value =
      upper_bound_value(proccesed_points.size(), upper_bound_2, 2);

  for (int i = 0; i < unprocessed_points.size(); i++) {
    for (int j = i + 1; j < unprocessed_points.size(); j++) {
      float distance = problem.calculate_euclidean_distance(
          unprocessed_points[i], unprocessed_points[j]);

      int position = 0;
      for (int k = 0; k < upper_bound_3.size(); k++) {
        if (distance < upper_bound_3[k]) {
          position++;
        }
      }
      upper_bound_3.insert(upper_bound_3.begin() + position, distance);
    }
  }

  float upper_bound_3_value =
      upper_bound_value(proccesed_points.size(), upper_bound_3, 3);

  return upper_bound_2_value + upper_bound_3_value;
}

int BranchBound::minimum_expandend_node() {
  int node_position = -1;
  if (expansion_strategy_ == MINIMUM_LEVEL_STRATEGY) {
    float min_distance = std::numeric_limits<float>::max();
    int index = 0;
    for (auto &&node : tree_) {
      if (!node.get_is_pruned() && !node.get_is_expanded() &&
          !node.get_is_solution()) {
        float distance = node.get_upper_bound();
        if (distance < min_distance) {
          min_distance = distance;
          node_position = index;
        }
      }
      index++;
    }
  } else if (expansion_strategy_ == DEEP_STRATEGY) {
    int max_deep_level = -1;
    int index = 0;
    for (auto &&node : tree_) {
      if (!node.get_is_pruned() && !node.get_is_expanded() &&
          !node.get_is_solution()) {
        int deep_level = node.get_solution().get_list_points().size();
        if (deep_level > max_deep_level) {
          max_deep_level = deep_level;
          node_position = index;
        }
      }
      index++;
    }
  }
  return node_position;
}

///////////////////////////

float BranchBound::upper_bound_value(int proccesed_points_size,
                                     std::vector<float> upper_bound,
                                     int number_of_upper_bound) {
  float upper_bound_value = 0;
  if (number_of_upper_bound == 2) {
    int size = proccesed_points_size * (size_solution_ - proccesed_points_size);
    for (int i = 0; i < size; i++) {
      upper_bound_value += upper_bound[i];
    }
  } else if (number_of_upper_bound == 3) {
    int size = 0;
    for (int i = size_solution_ - proccesed_points_size - 1; i > 0; i--) {
      size += i;
    }

    for (int i = 0; i < size; i++) {
      upper_bound_value += upper_bound[i];
    }
  }
  return upper_bound_value;
}

bool BranchBound::is_greater_equal(float num, float other_num) {
  return (num - other_num) >= -0.001;
}