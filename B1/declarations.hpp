#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP
#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>

enum sortOrder
{
  ascending,
  descending
};

template<typename T>
struct bracketsImplementation
{
  typedef std::size_t indexType;

  static typename T::value_type &getElement(T &container, size_t ind)
  {
    return container[ind];
  }

  static size_t getBegin(const T &)
  {
    return 0;
  }

  static size_t getEnd(const T &container)
  {
    return container.size();
  }

  static size_t getNextIndex(size_t ind)
  {
    return ind + 1;
  }
};

template<typename T>
struct atImplementation
{
  typedef std::size_t indexType;

  static typename T::value_type &getElement(T &container, size_t ind)
  {
    return container.at(ind);
  }

  static size_t getBegin(const T &)
  {
    return 0;
  }

  static size_t getEnd(const T &container)
  {
    return container.size();
  }

  static size_t getNextIndex(size_t ind)
  {
    return ind + 1;
  }
};

template<typename T>
struct iteratorImplementation
{
  typedef typename T::iterator indexType;

  static typename T::value_type &getElement(T &, typename T::iterator &iter)
  {
    return *iter;
  }

  static typename T::iterator getBegin(T &container)
  {
    return container.begin();
  }

  static typename T::iterator getEnd(T &container)
  {
    return container.end();
  }

  static typename T::iterator getNextIndex(typename T::iterator &iter)
  {
    return std::next(iter);
  }
};

template<template<class T> class Traits, typename T>
void sort(T &container, sortOrder order)
{
  std::function<bool(typename T::value_type, typename T::value_type)> comp;
  if (order == ascending)
  {
    comp = std::greater<typename T::value_type>();
  }
  else
  {
    comp = std::less<typename T::value_type>();
  }

  using indexType = typename Traits<T>::indexType;
  const indexType containerEnd = Traits<T>::getEnd(container);
  for (indexType i = Traits<T>::getBegin(container); i != containerEnd; i++)
  {
    for (indexType j = Traits<T>::getNextIndex(i); j != containerEnd; j++)
    {
      typename T::value_type &a = Traits<T>::getElement(container, i);
      typename T::value_type &b = Traits<T>::getElement(container, j);
      if (comp(a, b))
      {
        std::swap(a, b);
      }
    }
  }
}

template<typename T>
void printContainerValues(const T &collection)
{
  if (collection.empty()) {
    return;
  }

  for (typename T::const_iterator iter = collection.cbegin(); iter != collection.cend(); iter++)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}

sortOrder getSortOrder(const std::string &param);

void runTask1(const char *direction);
void runTask2(const char *filename);
void runTask3();
void runTask4(const char *numbers, const char *direction);

#endif
