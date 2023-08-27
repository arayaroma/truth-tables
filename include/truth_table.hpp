#pragma once
#include "logger.hpp"
#include "logical_operators.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

class TruthTable {
private:
  int num_rows;
  int num_vars;
  std::vector<std::string> expressions;
  std::set<char> variables;

public:
  TruthTable();
  TruthTable &get_rows(int num_vars);
  TruthTable &generate_table(const std::string &expression);
  TruthTable &parse_expression(const std::string &expression);
  bool is_variable(char c);
  TruthTable &show_variables();
};