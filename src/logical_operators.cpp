#include "logical_operators.hpp"

const char LogicalOperators::AND = '*';
const char LogicalOperators::OR = '+';
const char LogicalOperators::NOT = '\'';
const char LogicalOperators::XOR = '#';
const char LogicalOperators::WHITE_SPACE = ' ';
const char LogicalOperators::LEFT_PARENTHESIS = '(';
const char LogicalOperators::RIGHT_PARENTHESIS = ')';
const char LogicalOperators::COMMA = ',';
const char LogicalOperators::TRUE = '1';
const char LogicalOperators::FALSE = '0';

bool LogicalOperators::AND_OPERATOR(char c, char d) {
  return (c == TRUE && d == TRUE);
}

bool LogicalOperators::OR_OPERATOR(char c, char d) {
  return (c == TRUE || d == TRUE || c == TRUE && d == FALSE ||
          c == FALSE && d == TRUE);
}

bool LogicalOperators::NOT_OPERATOR(char c) { return c == FALSE; }

bool LogicalOperators::XOR_OPERATOR(char c, char d) {
  return (c == TRUE && d == FALSE || c == FALSE && d == TRUE);
}

bool LogicalOperators::is_variable(char c) {
  return c != LogicalOperators::WHITE_SPACE &&
         c != LogicalOperators::LEFT_PARENTHESIS &&
         c != LogicalOperators::COMMA &&
         c != LogicalOperators::RIGHT_PARENTHESIS &&
         c != LogicalOperators::AND && c != LogicalOperators::OR &&
         c != LogicalOperators::XOR && c != LogicalOperators::TRUE &&
         c != LogicalOperators::FALSE;
}

bool LogicalOperators::is_operator(char c) {
  return c == AND || c == OR || c == NOT || c == XOR;
}

bool LogicalOperators::apply_operator(char operator_, bool first_operand,
                                      bool second_operand) {
  if (operator_ == AND) {
    return AND_OPERATOR(first_operand, second_operand);
  } else if (operator_ == OR) {
    return OR_OPERATOR(first_operand, second_operand);
  } else if (operator_ == NOT) {
    return NOT_OPERATOR(first_operand);
  } else if (operator_ == XOR) {
    return XOR_OPERATOR(first_operand, second_operand);
  } else {
    std::cerr << "Invalid operator\n";
    return false;
  }
}
int LogicalOperators::precedence(char op) {
  if (op == NOT) {
    return 3;
  } else if (op == AND) {
    return 2;
  } else if (op == XOR) {
    return 1;
  } else if (op == OR) {
    return 0;
  } else {
    return -1; // Invalid operator or operand
  }
}
