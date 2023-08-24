#include "file_loader.hpp"

FileLoader::FileLoader() { setup_function_map(); }

void FileLoader::setup_function_map() {
  function_map["1"] = std::bind(&FileLoader::select_existing_file, this);
  function_map["2"] = std::bind(&FileLoader::load_from_file, this);
}

void FileLoader::handle_user_input(const std::string &user_option) {
  auto function = function_map.find(user_option);
  if (function != function_map.end()) {
    function->second();
  } else {
    Logger::get_instance().log("[!] Invalid option.");
  }
}

FileLoader &FileLoader::load_from_file() { return *this; }

FileLoader &FileLoader::load_existing_files() {
  for (const auto &entry : std::filesystem::directory_iterator{directoryPath}) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
      files.push_back(entry.path().filename().string());
    }
  }
  return *this;
}

void FileLoader::display_files() {
  Logger::get_instance().clear_console();
  Logger::get_instance().log("Available files:");
  int number = 1;
  for (const std::string &filename : files) {
    Logger::get_instance().log("[" + std::to_string(number) + "] " + filename);
    number++;
  }
}

void FileLoader::select_existing_file() {
  load_existing_files().display_files();
}
