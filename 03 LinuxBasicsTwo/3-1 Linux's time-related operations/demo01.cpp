#include <iostream>
#include <time.h>      // 时间操作的头文件。
using namespace std;

int main()
{
  time_t now1 = time(0);             // 获取当前时间，存放在now1中。
  long now2;  
  time(&now2);                       //获取当前时间，存放在now2中。
  
  cout << "now1 = " << now1 << endl;  // 显示当前时间，1970年1月1日到现在的秒数。
  cout << "now2 = " << now2 << endl;  // 显示当前时间，1970年1月1日到现在的秒数。

  return 0;
}

/*
➜  3-1 Linux's time-related operations git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  3-1 Linux's time-related operations git:(main) ✗ ls
demo01  demo01.cpp
➜  3-1 Linux's time-related operations git:(main) ✗ ./demo01                      
now1 = 1746934247
now2 = 1746934247
*/