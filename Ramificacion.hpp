#ifndef BRANCHBOUND_H
#define BRANCHBOUND_H

#include "Algorithm.hpp"
#include "Node.hpp"

class BranchBound : public Algorithm {
 private:
  int size_solution_;
  float lower_bound_;
  Solution initial_solution_;
  std::vector<Node> tree_;
  const int DEEP_STRATEGY = 1;
  const int MINIMUM_LEVEL_STRATEGY = 0;
  int expansion_strategy_;

 public:
  BranchBound() {}
  BranchBound(int size_solution, Solution initial_solution,
              int expansion_strategy = 0);
  ~BranchBound() {}

  // Métodos importantes:
  void expand_node(int node_position, std::vector<int> &active_nodes,
                   Problem &problem);
  float calculate_upper_bound(Problem &problem,
                              std::vector<Point> proccesed_points);
  int minimum_expandend_node();
  ///////////
  Solution execute(Problem &problem);
  void generate_first_level_tree(Problem &problem, int total_nodes);
  void prune(std::vector<int> &active_nodes);
  float upper_bound_value(int proccesed_points_size,
                          std::vector<float> upper_bound,
                          int number_of_upper_bound);

  bool is_greater_equal(float num, float other_num);
};
#endif  // BRANCHBOUND_H