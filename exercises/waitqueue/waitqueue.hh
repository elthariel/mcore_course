#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <cstdint>

template <class T>
class waitqueue
{
public:
  typedef T data_type;
  typedef std::queue<data_type> queue_type;

  waitqueue() {}
  waitqueue(const waitqueue<T> &) = delete;

  bool empty()
  {
    std::lock_guard<std::mutex> lock(_mutex);

    return _q.empty();
  }

  size_t size()
  {
    std::lock_guard<std::mutex> lock(_mutex);

    return _q.size();
  }

  data_type pop()
  {
    std::unique_lock<std::mutex> lock(_mutex);
    data_type result;

    while(true)
      {
        if(!_q.empty())
          {
            result = _q.front();
            _q.pop();
            return result;
          }

        _cond.wait(lock);
      }
  }

  void push(data_type new_element)
  {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      _q.push(new_element);
    }
    _cond.notify_one();
  }

protected:
  queue_type _q;
  std::mutex _mutex;
  std::condition_variable _cond;
};
