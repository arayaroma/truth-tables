#include "truth_table.hpp"
#include "logical_operators.hpp"

TruthTable::TruthTable() {}

TruthTable &TruthTable::parse_expression(const std::string &expression) {
  expressions.clear();
  size_t start = 0;
  size_t end = expression.find(LogicalOperators::COMMA);
  while (end != std::string::npos) {
    expressions.push_back(expression.substr(start, end - start));
    start = end + 1;
    end = expression.find(LogicalOperators::COMMA, start);
  }
  expressions.push_back(expression.substr(start));
  expressions = separate_expressions();
  final_expression = expression;
  show_tree();
  parse_variables();
  return *this;
}

std::vector<std::string> TruthTable::separate_expressions() {
  std::vector<std::string> separated_expressions;
  for (const std::string &expression : expressions) {
    size_t start = 0;
    size_t end = expression.find(LogicalOperators::OR);

    while (end != std::string::npos) {
      separated_expressions.push_back(expression.substr(start, end - start));
      start = end + 1;
      end = expression.find(LogicalOperators::OR, start);
    }
    if (start < expression.length()) {
      separated_expressions.push_back(expression.substr(start));
    }
  }
  return separated_expressions;
}

std::string TruthTable::infix_to_postfix(const std::string &expr) {
  std::string postfix;
  std::stack<std::string> operator_stack;

  for (char c : expr) {
    if (isalnum(c)) {
      postfix += c;
    } else if (c == '(') {
      operator_stack.push(std::string(1, c));
    } else if (c == ')') {
      while (!operator_stack.empty() && operator_stack.top() != "(") {
        postfix += operator_stack.top();
        operator_stack.pop();
      }
      if (!operator_stack.empty() && operator_stack.top() == "(") {
        operator_stack.pop();
      }
    } else {
      while (!operator_stack.empty() && operator_stack.top() != "(" &&
             LogicalOperators::precedence(std::string(1, c)) <=
                 LogicalOperators::precedence(operator_stack.top())) {
        postfix += operator_stack.top();
        operator_stack.pop();
      }
      operator_stack.push(std::string(1, c));
    }
  }
  while (!operator_stack.empty()) {
    postfix += operator_stack.top();
    operator_stack.pop();
  }

  return postfix;
}

void TruthTable::show_tree() {
  tree = new Tree();
  Logger::get_instance().log("Tree:");
  for (const std::string &expression : this->expressions) {
    tree->insert(infix_to_postfix(expression));
    Logger::get_instance().log_not_jump(expression + " -> ");
    tree->show(tree->root);
  }
  Logger::get_instance().line_jump();
}

void TruthTable::parse_variables() {
  for (const std::string &expr : expressions) {
    for (char c : expr) {
      std::string token(1, c);
      if (token != LogicalOperators::NOT &&
          LogicalOperators::is_variable(token)) {
        variables.insert(token);
      }
    }
  }
}

TruthTable &TruthTable::show_variables() {
  Logger::get_instance().log_not_jump("Variables: ");
  for (const std::string &var : variables) {
    Logger::get_instance().log_not_jump(var);
  }
  Logger::get_instance().line_jump();
  return *this;
}

void TruthTable::display_header(int max_expr_length, int separator_width) {
  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");
  Logger::get_instance().log_not_jump("|");
  Logger::get_instance().log_not_jump(
      format_header(variables, max_expr_length));
  Logger::get_instance().log_not_jump(
      format_header(expressions, max_expr_length));
  Logger::get_instance().log_not_jump(
      format_header(final_expression, max_expr_length));
  Logger::get_instance().line_jump();
  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");
}

void TruthTable::calculate_num_rows() {
  num_rows = static_cast<int>(std::pow(2, variables.size()));
}

void TruthTable::calculate_separator_width(int max_expr_length) {
  separator_width =
      (variables.size() + expressions.size()) * (max_expr_length + 6) - 3;
}

void TruthTable::calculate_max_expr_length() {
  max_expr_length = 0;
  max_expr_length =
      std::max(max_expr_length, static_cast<int>(final_expression.length()));
}

TruthTable &TruthTable::build_table() {
  calculate_num_rows();
  calculate_max_expr_length();
  calculate_separator_width(max_expr_length);
  display_header(max_expr_length, separator_width);
  calculate_table();
  return *this;
}

void TruthTable::calculate_table() {
  clean_table();
  calculate_variables_truth_values();
  clean_resolved_table();
  for (int i = 0; i < num_rows; ++i) {
    Logger::get_instance().log_not_jump(
        "|" + format_cell(table[i][0], max_expr_length) + "|");
    for (int j = 1; j < variables.size(); ++j) {
      Logger::get_instance().log_not_jump(
          format_cell(table[i][j], max_expr_length) + "|");
    }
    for (int j = variables.size(); j < variables.size() + expressions.size();
         ++j) {
      resolved_table[i][j - variables.size()] =
          evaluate_expression(expressions[j - variables.size()], i);
      Logger::get_instance().log_not_jump(
          format_cell(resolved_table[i][j - variables.size()],
                      max_expr_length) +
          "|");
    }
    Logger::get_instance().log_not_jump(
        format_cell(evaluate_expression(final_expression, i) ? true : false,
                    max_expr_length) +
        "|");
    Logger::get_instance().line_jump();
  }
  Logger::get_instance().log("+" + std::string(separator_width, '-') + "+");
}

void TruthTable::clean_table() {
  table = new bool *[num_rows];
  for (int i = 0; i < num_rows; ++i) {
    table[i] = new bool[num_rows];
    for (int j = 0; j < variables.size(); ++j) {
      table[i][j] = false;
    }
  }
}

void TruthTable::clean_resolved_table() {
  resolved_table = new bool *[num_rows];
  for (int i = 0; i < num_rows; ++i) {
    resolved_table[i] = new bool[num_rows];
    for (int j = 0; j < expressions.size(); ++j) {
      resolved_table[i][j] = false;
    }
  }
}

void TruthTable::calculate_variables_truth_values() {
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < variables.size(); ++j) {
      int position = variables.size() - j - 1;
      table[i][j] = (i & (1 << position)) ? true : false;
    }
  }
}

std::string TruthTable::format_header(const std::string &item,
                                      int max_expr_length) {
  return " " + item + std::string(max_expr_length - item.length(), ' ') + " |";
}

std::string TruthTable::format_header(const std::vector<std::string> &items,
                                      int max_expr_length) {
  std::string formatted = "";
  for (const std::string &item : items) {
    formatted +=
        " " + item + std::string(max_expr_length - item.length(), ' ') + " |";
  }
  return formatted;
}

std::string TruthTable::format_header(const std::set<std::string> &items,
                                      int max_expr_length) {
  std::string formatted = "";
  for (std::string item : items) {
    formatted += " " + item + std::string(max_expr_length - 1, ' ') + " |";
  }
  return formatted;
}

std::string TruthTable::format_cell(bool value, int max_expr_length) {
  return " " + std::to_string(value) + std::string(max_expr_length - 1, ' ') +
         " ";
}

bool TruthTable::evaluate_expression(const std::string &expr, int row) {
  return false;
}

int TruthTable::get_num_rows() const { return num_rows; }
int TruthTable::get_num_variables() const { return variables.size(); }
std::string TruthTable::get_expression(int index) const {
  return expressions[index];
}

bool TruthTable::get_variable_value(int row, char c) const {
  return table[row][get_column_by_variable(c)];
}

int TruthTable::get_column_by_variable(char variable) const {
  int column = 0;
  for (const std::string &var : variables) {
    if (var[0] == variable) {
      return column;
    }
    ++column;
  }
  return -1;
}