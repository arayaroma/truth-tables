#include "file_loader.hpp"
#include "logger.hpp"

int main() {
  Logger::get_instance().log_menu();
  FileLoader fileLoader;
  fileLoader.handle_user_input(Logger::get_instance().get_user_input());

  return EXIT_SUCCESS;
}