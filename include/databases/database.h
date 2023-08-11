#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "id_map.h"
#include "data.h"

#ifndef _WIN32
static const auto strncpy_s = strncpy;
#endif

struct DbData {
  char title[50];
  char description[100];
  unsigned int records;
};

template <typename Data>
class Database {
 public:
  Database(const std::string& db_file, const DbData& db_data);
  std::vector<Data> GetAllDataWhere(const std::function<bool(Data*)>& lambda);
  int Init(std::string db_file);
  int Insert(Data* data);
  Data GetDataByID(int id);
  void MakeSecondaryKey(std::string map_file, int key_size, int size);
  int GetIdBySecondaryKey(std::string key);

  std::string db_file_;
  IdMap id_map_;

 protected:
  int Write(Data* data, int offset);
  int Read(int offset, Data* data);

  int WriteDbData();

  DbData db_data_;
};

template <typename Data>
Database<Data>::Database(const std::string& db_file, const DbData& db_data) {
  db_data_ = {"Users Database", "Database used for storing data about users.",
              0};
  Init(db_file);
}

template <typename Data>
int Database<Data>::Init(std::string db_file) {
  db_file_ = db_file;

  std::fstream fs;
  fs.open(db_file, std::ios::binary | std::ios::in | std::ios::out);

  if (fs.is_open() == 0) {
    fs.open(db_file, std::ios::binary | std::ios::out);
    fs.write((char*)&db_data_, sizeof(DbData));
  } else {
    fs.read((char*)&db_data_, sizeof(DbData));
  }

  fs.close();
  return 0;
}

template <typename Data>
int Database<Data>::Write(Data* data, int offset) {
  std::fstream fs;

  fs.open(db_file_, std::ios::binary | std::ios::in | std::ios::out);
  fs.seekp(sizeof(DbData) + offset * sizeof(Data));

  if (fs.is_open() == 0) {
    std::cout << "Cannot open database for writting\n";
    return -1;
  }

  fs.write((char*)data, sizeof(Data));
  fs.close();

  return 0;
}

template <typename Data>
int Database<Data>::Read(int offset, Data* data) {
  std::fstream fs;
  fs.open(db_file_, std::ios::binary | std::ios::in);
  fs.seekg(sizeof(DbData) + offset * sizeof(Data));

  if (fs.is_open() == 0) {
    std::cout << "Cannot open database for reading\n";
    return -1;
  }

  fs.read((char*)data, sizeof(Data));
  fs.close();

  return 0;
}

template <typename Data>
std::vector<Data> Database<Data>::GetAllDataWhere(
    const std::function<bool(Data*)>& lambda) {
  std::vector<Data> result;

  Data data;
  for (unsigned int i = 0; i < db_data_.records; i++) {
    Read(i, &data);
    if (lambda(&data)) result.push_back(data);
  }

  return result;
}

template <typename Data>
Data Database<Data>::GetDataByID(int id) {
  Data data;
  Read(id, &data);
  return data;
}

template <typename Data>
int Database<Data>::Insert(Data* data) {
  data->id = db_data_.records;
  Write(data, db_data_.records++);
  WriteDbData();
  return 0;
}

template <typename Data>
int Database<Data>::WriteDbData() {
  std::fstream fs;
  fs.open(db_file_, std::ios::binary | std::ios::in | std::ios::out);

  if (!fs.is_open()) {
    std::cout << "Failed to open\n";
    return -1;
  }

  fs.write((char*)&db_data_, sizeof(DbData));
  return 0;
}

template <typename Data>
void Database<Data>::MakeSecondaryKey(std::string map_file, int key_size,
                                      int size) {
  id_map_.Init(map_file, size, key_size);
}

template <typename Data>
int Database<Data>::GetIdBySecondaryKey(std::string key) {
  return id_map_.Get(key);
}
