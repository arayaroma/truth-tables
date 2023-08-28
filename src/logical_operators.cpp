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

bool LogicalOperators::AND_OPERATOR(int index, std::string c, std::string d,
                                    TruthTable &truth_table) {
  bool value_c, value_d;

  if (is_variable(c)) {
    int variableIndex = truth_table.get_variable(c);
    value_c = truth_table.get_value(index, variableIndex);
  } else {
    value_c = (c == TRUE);
  }

  if (is_variable(d)) {
    int variableIndex = truth_table.get_variable(d);
    value_d = truth_table.get_value(index, variableIndex);
  } else {
    value_d = (d == TRUE);
  }

  return value_c && value_d;
}

bool LogicalOperators::OR_OPERATOR(int index, std::string c, std::string d,
                                   TruthTable &truth_table) {
  bool value_c, value_d;

  if (is_variable(c)) {
    int variableIndex = truth_table.get_variable(c);
    value_c = truth_table.get_value(index, variableIndex);
  } else {
    value_c = (c == TRUE);
  }

  if (is_variable(d)) {
    int variableIndex = truth_table.get_variable(d);
    value_d = truth_table.get_value(index, variableIndex);
  } else {
    value_d = (d == TRUE);
  }

  return value_c || value_d || (value_c && !value_d) || (!value_c && value_d);
}

bool LogicalOperators::NOT_OPERATOR(std::string c) { return c == FALSE; }

bool LogicalOperators::XOR_OPERATOR(int index, std::string c, std::string d,
                                    TruthTable &truth_table) {
  bool value_c, value_d;

  if (is_variable(c)) {
    int variableIndex = truth_table.get_variable(c);
    value_c = truth_table.get_value(index, variableIndex);
  } else {
    value_c = (c == TRUE);
  }

  if (is_variable(d)) {
    int variableIndex = truth_table.get_variable(d);
    value_d = truth_table.get_value(index, variableIndex);
  } else {
    value_d = (d == TRUE);
  }

  return (value_c && !value_d) || (!value_c && value_d);
}

bool LogicalOperators::apply_operator(int index, std::string operator_,
                                      std::string first_operand,
                                      std::string second_operand,
                                      TruthTable &truth_table) {
  if (operator_ == AND) {
    return AND_OPERATOR(index, first_operand, second_operand, truth_table);
  } else if (operator_ == OR) {
    return OR_OPERATOR(index, first_operand, second_operand, truth_table);
  } else if (operator_ == NOT) {
    return NOT_OPERATOR(first_operand);
  } else if (operator_ == XOR) {
    return XOR_OPERATOR(index, first_operand, second_operand, truth_table);
  } else {
    std::cerr << "Invalid operator\n";
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
