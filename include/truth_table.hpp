#pragma once
#include "logger.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

class LogicalOperators;

class TruthTable {

private:
  int i;
  int num_rows, num_vars;
  int max_expr_length, separator_width;
  std::vector<std::string> expressions;
  std::set<std::string> variables;
  std::vector<std::vector<int>> table;

public:
  TruthTable();
  TruthTable &parse_expression(const std::string &expression);
  void parse_variables();
  TruthTable &build_table();
  TruthTable &show_variables();
  void calculate_num_rows();
  void calculate_max_expr_length();
  void calculate_separator_width(int max_expr_length);
  void display_header(int max_expr_lenght, int separator_width);
  void display_variables_and_expressions();
  std::string format_header(const std::vector<std::string> &items,
                            int max_expr_length);
  std::string format_header(const std::set<std::string> &items,
                            int max_expr_length);
  std::string format_cell(bool value, int max_expr_length);
  bool evaluate_expression(const std::string &expr, int i);
  int get_value(int row, int var);
  int get_variable(const std::string &token);
  TruthTable &load_table(TruthTable &truth_table);
  int get_num_rows() const;
  int get_num_variables() const;
};