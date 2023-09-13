#pragma once
#include "logical_operators.hpp"
#include <stack>
#include <string>

class Tree {
private:
  struct Node {
    char data;
    bool is_negated;
    Node *left;
    Node *right;

    Node(char data) {
      this->data = data;
      this->is_negated = false;
      left = nullptr;
      right = nullptr;
    }

    Node(char data, bool is_negated) {
      this->data = data;
      this->is_negated = is_negated;
      left = nullptr;
      right = nullptr;
    }

    ~Node() {
      if (left != nullptr)
        delete left;
      if (right != nullptr)
        delete right;
    }

    void show() {
      if (left != nullptr)
        left->show();
      if (right != nullptr)
        right->show();
      std::cout << data << " " << is_negated << " ";
    }
  };

public:
  Node *root;
  Tree();
  Node *create_node(char c);
  Node *create_node(char c, bool is_negated);
  bool is_empty(Node *root) const;
  Node *insert(Node *root, const std::string &expr);
  void insert(const std::string &expr);
  void show(Node *root);
};