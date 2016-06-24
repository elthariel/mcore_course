#include <thread>
#include <chrono>
#include <iostream>

#include "waitqueue.hh"

waitqueue<int> q;

void consumer()
{
  while(true)
    {
      auto v = q.pop();

      std::cout << "Consumer " << std::this_thread::get_id()
                << " popped " << v << std::endl;
    }
}

int main(int ac, char **av)
{
  std::chrono::milliseconds sleep_time(250);
  std::thread t1(consumer), t2(consumer), t3(consumer);
  int i = 1;

  while(true)
    {
      q.push(i);
      ++i;
      std::this_thread::sleep_for(sleep_time);
    }
}
