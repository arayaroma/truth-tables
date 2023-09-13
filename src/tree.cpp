#include "tree.hpp"
#include <string>

Tree::Tree() { this->root = nullptr; }

Tree::Node *Tree::create_node(char c) { return new Node(c); }

Tree::Node *Tree::create_node(char c, bool is_negated) {
  return new Node(c, is_negated);
}

bool Tree::is_empty(Node *root) const { return root == nullptr; }

/**
 * @bug Is not inserting the negated variables.
 */
Tree::Node * ::Tree::insert(Node *root, const std::string &expr) {
  std::stack<Node *> node_stack;

  for (char c : expr) {
    if (isalnum(c)) {
      bool is_negated = false;
      if (c == '\'') {
        is_negated = true;
        c = expr[expr.find(c) - 1];
        node_stack.push(create_node(c, is_negated));
      }
      node_stack.push(create_node(c, is_negated));
    } else {
      Node *right_operand = node_stack.top();
      node_stack.pop();
      Node *left_operand = node_stack.top();
      node_stack.pop();

      Node *operator_node = create_node(c);
      operator_node->left = left_operand;
      operator_node->right = right_operand;

      node_stack.push(operator_node);
    }
  }
  return node_stack.top();
}

void Tree::insert(const std::string &expr) {
  this->root = insert(this->root, expr);
}

void Tree::show(Node *root) {
  if (is_empty(root))
    return;
  root->show();
}