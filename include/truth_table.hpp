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
  std::set<std::string> literals;
  bool **table;
  bool **resolved_table;

public:
  TruthTable();
  TruthTable &parse_expression(const std::string &expression);
  void parse_variables();
  void parse_literals();
  std::vector<std::string> separate_expressions();
  TruthTable &build_table();
  TruthTable &show_variables();

  void calculate_table();

  void calculate_variables_truth_values();
  void calculate_expressions_truth_values();
  void calculate_num_rows();
  void calculate_max_expr_length();
  void calculate_separator_width(int max_expr_length);
  void display_header(int max_expr_lenght, int separator_width);
  std::string format_header(const std::vector<std::string> &items,
                            int max_expr_length);
  std::string format_header(const std::set<std::string> &items,
                            int max_expr_length);
  std::string format_cell(bool value, int max_expr_length);
  bool evaluate_expression(std::string const &expr, int row);
  int get_num_rows() const;
  int get_num_variables() const;
  std::string get_expression(int index) const;
  void clean_resolved_table();
  void clean_table();
  bool get_variable_value(int row, char col) const;
  int get_column_by_variable(char variable) const;
};