#include "Node.hpp"

Node::Node(float value, float upper_bound) {
  value_ = value;
  upper_bound_ = upper_bound;
  is_pruned_ = false;
  is_solution_ = false;
  is_expanded_ = false;
}

void Node::add_point(Point point) { partial_solution_.add_point(point); }

void Node::set_solution(Solution solution) { partial_solution_ = solution; }

void Node::set_is_expanded(bool expanded) { is_expanded_ = expanded; }

void Node::set_is_pruned(bool pruned) { is_pruned_ = pruned; }

void Node::set_is_solution(bool solution) { is_solution_ = solution; }

float Node::get_value() { return value_; }

Solution Node::get_solution() { return partial_solution_; }

float Node::get_upper_bound() { return upper_bound_; }

bool Node::get_is_pruned() { return is_pruned_; }

bool Node::get_is_expanded() { return is_expanded_; }

bool Node::get_is_solution() { return is_solution_; }