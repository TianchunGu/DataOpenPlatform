#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void EXIT(int sig)
{
  cout << "收到了信号：" << sig << endl;
  cout << "正在释放资源，程序将退出......\n";

  // 以下是释放资源的代码。

  cout << "程序退出。\n";
  exit(0);  // 进程退出。
}

int main(int argc,char *argv[])
{
  // 忽略全部的信号，防止程序被信号异常中止。
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);

  // 如果收到2和15的信号（Ctrl+c和kill、killall），本程序将主动退出。
  signal(2,EXIT);  signal(15,EXIT);

  while (true)
  {
    cout << "执行了一次任务。\n";
    sleep(1);
  }
}

/*
编译运行：
➜  4-1 Signals of Linux git:(main) ✗ g++ -o theFunctionOfTheSignal theFunctionOfTheSignal.cpp -g
➜  4-1 Signals of Linux git:(main) ✗ ls
alarm  alarm.cpp  demo01  demo01.cpp  theFunctionOfTheSignal  theFunctionOfTheSignal.cpp
➜  4-1 Signals of Linux git:(main) ✗ ./theFunctionOfTheSignal
执行了一次任务。
执行了一次任务。
执行了一次任务。
执行了一次任务。
执行了一次任务。
执行了一次任务。
收到了信号：15
正在释放资源，程序将退出......
程序退出。
*/