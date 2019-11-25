#ifndef QUEUE_WITH_PRIORITY_B2
#define QUEUE_WITH_PRIORITY_B2

#include <list>
#include <iostream>

template<typename T>
class QueueWithPriority
{
public:

  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  QueueWithPriority();

  QueueWithPriority(const QueueWithPriority &queue) = default;
  QueueWithPriority(QueueWithPriority &&queue) noexcept = default;
  ~QueueWithPriority() = default;
  QueueWithPriority &operator=(const QueueWithPriority<T> &queue) = default;
  QueueWithPriority &operator=(QueueWithPriority<T> &&queue) noexcept = default;

  void putElement(const T &element, ElementPriority priority);
  T getElement();
  void accelerate();
  bool empty() const;

private:
  std::list <T> low;
  std::list <T> normal;
  std::list <T> high;
};

template<typename T>
QueueWithPriority<T>::QueueWithPriority() :
  low(),
  normal(),
  high()
{}

template<typename T>
void QueueWithPriority<T>::putElement(const T &element, ElementPriority priority)
{
  switch (priority)
  {
    case ElementPriority::LOW:
    {
      low.push_back(element);
      break;
    }
    case ElementPriority::NORMAL:
    {
      normal.push_back(element);
      break;
    }
    case ElementPriority::HIGH:
    {
      high.push_back(element);
      break;
    }
  }
}

template<typename T>
bool QueueWithPriority<T>::empty() const
{
  return (low.empty() && normal.empty() && high.empty());
}

template<typename T>
T QueueWithPriority<T>::getElement()
{
  if (!high.empty())
  {
    T temp = high.front();
    high.pop_front();
    return temp;
  }
  else if (!normal.empty())
  {
    T temp = normal.front();
    normal.pop_front();
    return temp;
  }
  else
  {
    T temp = low.front();
    low.pop_front();
    return temp;
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  high.splice(high.end(), low);
}

#endif //QUEUE_WITH_PRIORITY_B2
