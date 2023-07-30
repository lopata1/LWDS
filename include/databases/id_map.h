#pragma once

#include <fstream>
#include <iostream>
#include <string>

class IdMap {
 public:
  IdMap(){};
  IdMap(const std::string map_file, int size, int key_size);

  void Init(const std::string map_file, int size, int key_size);
  int Insert(std::string key, int id);
  int Get(std::string key);
  int Index(std::string key);

  std::string map_file_;
  int key_size_{};
  int size_{};

 protected:
  int WriteKey(int offset, std::string& key);
  std::string ReadKey(int offset);
  int WriteId(int offset, int value);
  int ReadId(int offset);
};