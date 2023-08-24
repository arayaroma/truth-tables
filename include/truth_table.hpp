#pragma once
#include "logger.hpp"
#include <iostream>

class TruthTable {
private:
  int num_rows;

public:
  TruthTable();
  TruthTable &generate_truth_table(int num_vars);
};