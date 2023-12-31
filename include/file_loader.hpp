#pragma once
#include "logger.hpp"
#include "truth_table.hpp"
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class FileLoader {
private:
  std::vector<std::string> files;
  const std::filesystem::path directoryPath = "../include/data";
  std::unordered_map<std::string, std::function<void()>> function_map;

public:
  FileLoader();
  void setup_function_map();
  void handle_user_input(const std::string &user_option);
  void load_file(const std::string &file);
  FileLoader &load_existing_files();
  void display_files();
  void select_existing_file();
  void clear_files() { files.clear(); }
  void create_file(const std::string &file, const std::string &expression);
};