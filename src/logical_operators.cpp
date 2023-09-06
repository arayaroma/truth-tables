#include "logical_operators.hpp"
#include "truth_table.hpp"

const std::string LogicalOperators::AND = "";
const std::string LogicalOperators::OR = "+";
const std::string LogicalOperators::NOT = "\'";
const std::string LogicalOperators::XOR = "#";
const std::string LogicalOperators::WHITE_SPACE = " ";
const std::string LogicalOperators::LEFT_PARENTHESIS = "(";
const std::string LogicalOperators::RIGHT_PARENTHESIS = ")";
const std::string LogicalOperators::COMMA = ",";
const std::string LogicalOperators::TRUE = "1";
const std::string LogicalOperators::FALSE = "0";

bool LogicalOperators::is_operator(std::string c) {
  return c == AND || c == OR || c == XOR;
}

bool LogicalOperators::is_variable(std::string c) {
  return c != AND && c != OR && c != NOT && c != XOR && c != TRUE && c != FALSE;
}

bool LogicalOperators::apply_negation(bool first_operand) {
  return first_operand ? false : true;
}

bool LogicalOperators::apply_and(bool first_operand, bool second_operand) {
  return (first_operand == true && second_operand == true);
}

bool LogicalOperators::apply_or(bool first_operand, bool second_operand) {
  return (first_operand == true || second_operand == true);
}

bool LogicalOperators::apply_xor(bool first_operand, bool second_operand) {
  return (first_operand == true ^ second_operand == false);
}

bool LogicalOperators::apply_operator(std::string operator_, bool first_operand,
                                      bool second_operand) {
  if (operator_ == AND)
    return apply_and(first_operand, second_operand);
  if (operator_ == OR)
    return apply_or(first_operand, second_operand);
  if (operator_ == XOR)
    return apply_xor(first_operand, second_operand);
  return false;
}

int LogicalOperators::precedence(std::string token) {
  if (token == NOT)
    return 3;
  if (token == AND)
    return 2;
  if (token == OR)
    return 1;
  if (token == XOR)
    return 1;
  return 0;
}
