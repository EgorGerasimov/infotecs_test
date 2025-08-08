#pragma once

#include <algorithm>
#include <iostream>
#include <mutex>
#include <vector>

template <typename T>
class Buffer {
 private:
  std::vector<T> data;
  std::vector<T> data_copy;
  std::mutex mtxBuff;

 public:
  Buffer() = default;
  explicit Buffer(int size) : data(size), data_copy(size) {}
  Buffer(int size, T value) : data(size, value), data_copy(size, value) {}

  void insert(T value);
  void insert(int index, T value);
  void remove();
  void remove(int index);
  void remove_all();
  void sort_ascending();
  void sort_descending();
  void reverse();
  int count_even_positioned();
  int count_odd_positioned();
  void read();
};

#include "../buffer_lib/buffer_method.hpp"