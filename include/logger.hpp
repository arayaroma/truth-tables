#pragma once
#include <cstdlib>
#include <string>

class Logger {
  Logger();
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

public:
  static Logger &get_instance();
  void log(const std::string &message);
  void log_title();
  void log_menu();
  std::string get_user_input();
  void clear_console();
};