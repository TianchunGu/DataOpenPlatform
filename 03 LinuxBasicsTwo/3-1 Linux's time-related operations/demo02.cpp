#include <iostream>
#include <time.h>      // 时间操作的头文件。
using namespace std;

int main()
{
  time_t now=time(0);             // 获取当前时间，存放在now中。

  cout << "now=" << now << endl;  // 显示当前时间，1970年1月1日到现在的秒数。

  tm tmnow;
  localtime_r(&now,&tmnow);       // 把整数的时间转换成tm结构体。

  // 根据tm结构体拼接成中国人习惯的字符串格式。
  string stime = to_string(tmnow.tm_year+1900)+"-"
               + to_string(tmnow.tm_mon+1)+"-"
               + to_string(tmnow.tm_mday)+" "
               + to_string(tmnow.tm_hour)+":"
               + to_string(tmnow.tm_min)+":"
               + to_string(tmnow.tm_sec);

  cout << "stime=" << stime << endl;
}

/*  
编译运行：
➜  3-1 Linux's time-related operations git:(main) ✗ g++ -o demo02 demo02.cpp -g
➜  3-1 Linux's time-related operations git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  3-1 Linux's time-related operations git:(main) ✗ ./demo02                         
now=1746934465
stime=2025-5-11 11:34:25
*/