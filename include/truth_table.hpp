#pragma once
#include "logger.hpp"
#include "logical_operators.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

class TruthTable {
private:
  int i;
  int num_rows, num_vars;
  int max_expr_length, separator_width;
  std::vector<std::string> expressions;
  std::set<char> variables;

public:
  TruthTable();
  TruthTable &parse_expression(const std::string &expression);
  void parse_variables();
  TruthTable &build_table();
  TruthTable &show_variables();
  void calculate_num_rows();
  void calculate_max_expr_length();
  void calculate_separator_width(int maxExprLenght);
  void display_header(int maxExprLenght, int separatorWidth);
  void display_variables_and_expressions();
  std::string format_header(const std::vector<std::string> &items,
                            int maxExprLenght);
  std::string format_header(const std::set<char> &items, int maxExprLenght);
  std::string format_cell(bool value, int maxExprLenght);
  bool evaluate_expression(const std::string &expr, int i);
  bool get_value(int row, char var);
};