#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void func(int signal){
  cout<<"alarm"<<"执行了"<<signal<<"信号"<<endl;
  alarm(5);//5秒后发送SIGALRM信号（14的信号）
}

int main(){
  int num = 0;
  alarm(5);//5秒后发送SIGALRM信号（14的信号）
  signal(SIGALRM,func);//设置定时任务函数等价于signal(14,func);
  while (true){
    cout<<"执行了"<<++num<<"次任务"<<endl;
    sleep(1);
  }
  return 0;
}

/*
编译运行：
➜  4-1 Signals of Linux git:(main) ✗ g++ -o alarm alarm.cpp -g
➜  4-1 Signals of Linux git:(main) ✗ ls
alarm  alarm.cpp  demo01  demo01.cpp
➜  4-1 Signals of Linux git:(main) ✗ ./alarm 
执行了1次任务
执行了2次任务
执行了3次任务
执行了4次任务
执行了5次任务
alarm执行了14信号
执行了6次任务
执行了7次任务
执行了8次任务
执行了9次任务
执行了10次任务
alarm执行了14信号
执行了11次任务
执行了12次任务
执行了13次任务
执行了14次任务
执行了15次任务
[3]    449370 terminated  ./alarm
➜  4-1 Signals of Linux git:(main) ✗ 
*/