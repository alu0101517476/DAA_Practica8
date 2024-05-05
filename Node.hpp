#ifndef NODE_H
#define NODE_H

#include <vector>

#include "Solution.hpp"

class Node {
 private:
  Solution partial_solution_;
  float value_;
  float upper_bound_;
  bool is_expanded_;
  bool is_pruned_;
  bool is_solution_;

 public:
  Node() {}
  Node(float value, float upper_bound);
  ~Node() {}

  void add_point(Point point);
  void set_solution(Solution solution);
  void set_is_expanded(bool expanded);
  void set_is_pruned(bool pruned);
  void set_is_solution(bool solution);

  float get_value();
  Solution get_solution();
  float get_upper_bound();
  bool get_is_pruned();
  bool get_is_expanded();
  bool get_is_solution();
};
#endif  // NODE_H