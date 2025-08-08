#pragma once

#include "../include/buffer.hpp"

// Вставка в конец
template <typename T>
void Buffer<T>::insert(T value) {
  this->data.push_back(value);

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Вставка по индексу
template <typename T>
void Buffer<T>::insert(int index, T value) {
  this->data.insert(this->data.begin() + index, value);

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Удаление последнего элемента
template <typename T>
void Buffer<T>::remove() {
  this->data.pop_back();

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Удаление по индексу
template <typename T>
void Buffer<T>::remove(int index) {
  this->data.erase(this->data.begin() + index);

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Удаление всех элементов
template <typename T>
void Buffer<T>::remove_all() {
  this->data.clear();

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Сортировка от большего к меньшему
template <typename T>
void Buffer<T>::sort_ascending() {
  std::sort(this->data.begin(), this->data.end());

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Сортировка от меньшего к большему
template <typename T>
void Buffer<T>::sort_descending() {
  std::sort(this->data.rbegin(), this->data.rend());

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

// Изменение порядка элементов на обратный
template <typename T>
void Buffer<T>::reverse() {
  std::reverse(this->data.begin(), this->data.end());

  std::lock_guard<std::mutex> lock(this->mtxBuff);
  this->data_copy = this->data;
};

/*
 * Подсчёт элементов на чётных позициях.
 * Можно было бы использовать формулу, для болле быстрого вычисления:
 * (this->data.size() / 2) + this->data.size() % 2
 * но в задании написано подсчитать а не вычислить,
 * поэтому я использовал такой метод.
 */
template <typename T>
int Buffer<T>::count_even_positioned() {
  int count = 0;
  for (auto i = 0LU; i < this->data.size(); i += 2) count++;
  return count;
};

/*
 * Подсчёт элементов на нечётных позициях.
 * Тут ситуация такая же как с подсчётом чётных индексов.
 * Можно было бы использовать формулу, для болле быстрого вычисления:
 * (this->data.size() / 2)
 * но в задании написано подсчитать а не вычислить,
 * поэтому я использовал такой метод.
 */
template <typename T>
int Buffer<T>::count_odd_positioned() {
  int count = 0;
  for (auto i = 1LU; i < this->data.size(); i += 2) count++;
  return count;
};

// Чтение содержимого буффера
template <typename T>
void Buffer<T>::read() {
  int count = 0;
  std::unique_lock<std::mutex> lock(mtxBuff);

  for (auto i = this->data_copy.begin(); i != this->data_copy.end();
       i++, count++);
  std::cout << count << " elements in buffer now\n";
}