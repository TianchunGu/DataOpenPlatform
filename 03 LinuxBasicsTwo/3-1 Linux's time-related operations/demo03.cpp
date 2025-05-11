#include <iostream>
#include <sys/time.h>  // gettimeofday()需要的头文件。
using namespace std;

int main()
{
  timeval start,end;

  gettimeofday(&start, 0 ); // 计时开始。

  for (int ii=0;ii<1000000000;ii++)
    ;

  gettimeofday(&end, 0 );   // 计时结束。

  // 计算消耗的时长。
  timeval tv;
  tv.tv_usec=end.tv_usec-start.tv_usec;
  tv.tv_sec=end.tv_sec-start.tv_sec;
  if (tv.tv_usec<0)
  {
    tv.tv_usec=1000000-tv.tv_usec;
    tv.tv_sec--;
  }

  cout << "耗时：" << tv.tv_sec << "秒和" << tv.tv_usec << "微秒。\n";
}

/*
编译运行：
➜  3-1 Linux's time-related operations git:(main) ✗ g++ -o demo03 demo03.cpp -g
➜  3-1 Linux's time-related operations git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  demo03  demo03.cpp
➜  3-1 Linux's time-related operations git:(main) ✗ ./demo03
耗时：0秒和1624961微秒。
*/