#include "../../include/databases/id_map.h"

IdMap::IdMap(const std::string map_file, int size, int key_size) {
  Init(map_file, size, key_size);
}

void IdMap::Init(const std::string map_file, int size, int key_size) {
  map_file_ = map_file;
  key_size_ = key_size;
  size_ = size;

  std::fstream fs;
  fs.open(map_file, std::ios::binary | std::ios::in | std::ios::out);

  if (fs.is_open() == 0) {
    fs.open(map_file, std::ios::binary | std::ios::out);

    int file_size = key_size * size + size * sizeof(int);

    char* empty = new char[file_size];
    memset(empty, 0, file_size);
    fs.write(empty, file_size);
  }

  fs.close();
}

int IdMap::Index(std::string key) {
  return std::hash<std::string>()(key) % size_;
}

int IdMap::Insert(std::string key, int id) {
  int index = Index(key);
  while (!ReadKey(index).empty()) {
    index++;
    index %= size_;
  }
  WriteKey(index, key);
  WriteId(index, id);
  return 0;
}

int IdMap::Get(std::string key) {
  int index = Index(key);

  std::string read_key = ReadKey(index);

  while (read_key != key) {
    if (read_key[0] == '\0') return -1;
    index++;
    index %= size_;
    read_key = ReadKey(index);
  }
  return ReadId(index);
}

int IdMap::WriteKey(int offset, std::string& key) {
  std::fstream fs;

  fs.open(map_file_, std::ios::binary | std::ios::in | std::ios::out);
  fs.seekp((long long)offset * key_size_);

  if (fs.is_open() == 0) {
    std::cout << "Cannot open file";
    return -1;
  }

  fs.write(key.c_str(), key_size_);
  fs.close();

  return 0;
}

std::string IdMap::ReadKey(int offset) {
  std::fstream fs;
  fs.open(map_file_, std::ios::binary | std::ios::in);
  fs.seekg((long long)key_size_ * offset);

  if (fs.is_open() == 0) {
    std::cout << "Cannot open file";
  }

  char* key_buffer = new char[key_size_];
  fs.read(key_buffer, key_size_);
  fs.close();

  std::string key = key_buffer;
  delete[] key_buffer;

  return key;
}

int IdMap::WriteId(int offset, int value) {
  std::fstream fs;

  fs.open(map_file_, std::ios::binary | std::ios::in | std::ios::out);
  fs.seekp((long long)size_ * key_size_ + (long long)offset * sizeof(int));

  if (fs.is_open() == 0) {
    std::cout << "Cannot open file";
    return -1;
  }

  fs.write((char*)&value, sizeof(int));
  fs.close();

  return 0;
}

int IdMap::ReadId(int offset) {
  std::fstream fs;
  fs.open(map_file_, std::ios::binary | std::ios::in);
  fs.seekp((long long)size_ * key_size_ + (long long)offset * sizeof(int));

  if (fs.is_open() == 0) {
    std::cout << "Cannot open file";
  }

  int id = 0;
  fs.read((char*)&id, sizeof(int));
  fs.close();

  return id;
}