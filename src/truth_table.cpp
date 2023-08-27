#include "truth_table.hpp"
#include "logical_operators.hpp"

TruthTable::TruthTable() {}

TruthTable &TruthTable::get_rows(int num_vars) {
  num_rows = pow(2, num_vars);
  return *this;
}

TruthTable &TruthTable::parse_expression(const std::string &expression) {
  expressions.clear();

  for (std::size_t i = 0; i < expression.length(); ++i) {
    char c = expression[i];
    if (is_variable(c)) {
      variables.insert(c);
      if (i + 1 < expression.length() &&
          expression[i + 1] == LogicalOperators::NOT) {
        ++i;
      }
    }
  }
  for (char var : variables) {
    expressions.push_back(std::string(1, var));
  }
  show_variables();
  return *this;
}

bool TruthTable::is_variable(char c) {
  return c != LogicalOperators::WHITE_SPACE &&
         c != LogicalOperators::LEFT_PARENTHESIS &&
         c != LogicalOperators::COMMA &&
         c != LogicalOperators::RIGHT_PARENTHESIS &&
         c != LogicalOperators::AND && c != LogicalOperators::OR &&
         c != LogicalOperators::XOR;
}

TruthTable &TruthTable::show_variables() {
  Logger::get_instance().log("Variables: ");
  for (const char &var : variables) {
    Logger::get_instance().log(std::string(1, var));
  }
  return *this;
}

TruthTable &TruthTable::generate_table(const std::string &expression) {
  parse_expression(expression);

  return *this;
}