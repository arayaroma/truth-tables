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
  return c == AND || c == OR || c == NOT || c == XOR;
}

bool LogicalOperators::is_variable(std::string c) {
  return c != AND && c != OR && c != NOT && c != XOR && c != WHITE_SPACE &&
         c != LEFT_PARENTHESIS && c != RIGHT_PARENTHESIS && c != COMMA &&
         c != TRUE && c != FALSE;
}

bool LogicalOperators::AND_OPERATOR(std::string value_c, std::string value_d) {
  return (value_c == TRUE) && (value_d == TRUE);
}

bool LogicalOperators::OR_OPERATOR(std::string value_c, std::string value_d) {
  return (value_c == TRUE) || (value_d == TRUE);
}

bool LogicalOperators::NOT_OPERATOR(std::string value) {
  return (value == TRUE) ? false : true;
}

bool LogicalOperators::XOR_OPERATOR(std::string value_c, std::string value_d) {
  return (value_c == FALSE) ^ (value_d == TRUE) ||
         (value_c == TRUE) ^ (value_d == FALSE);
}

bool LogicalOperators::apply_operator(std::string operator_,
                                      std::string first_operand,
                                      std::string second_operand) {
  if (operator_ == AND) {
    return AND_OPERATOR(first_operand, second_operand);
  } else if (operator_ == OR) {
    return OR_OPERATOR(first_operand, second_operand);
  } else if (operator_ == NOT) {
    return NOT_OPERATOR(first_operand);
  } else if (operator_ == XOR) {
    return XOR_OPERATOR(first_operand, second_operand);
  } else {
    return false;
  }
}

int LogicalOperators::precedence(std::string op) {
  if (op == NOT) {
    return 3;
  } else if (op == AND) {
    return 2;
  } else if (op == OR) {
    return 1;
  } else if (op == XOR) {
    return 0;
  } else {
    return -1;
  }
}
