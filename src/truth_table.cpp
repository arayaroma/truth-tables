#include "truth_table.hpp"
#include <cmath>

TruthTable::TruthTable() {}

TruthTable &TruthTable::generate_truth_table(int num_vars) {

  num_rows = pow(2, num_vars);

  for (int i = 0; i < num_rows; i++) {
    for (int j = num_vars - 1; j >= 0; j--) {
      std::cout << ((i >> j) & 1);
    }
    std::cout << std::endl;
  }

  return *this;
}