#pragma once
#include <cstdlib>
#include <string>

class Logger {
  Logger();
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

public:
  void log(const std::string &message);
  void log_title();
  void log_menu();
  void clear_console();
  std::string get_user_input();
  static Logger &get_instance();
};