#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  int bh=8;
  string message="我是一只傻傻鸟。";

  pid_t pid=fork();

  if (pid>0)
  { // 父进程将执行这段代码。
    sleep(1);// 等待子进程先执行。
    cout << "父：pid=" << pid << endl;
    cout << "父：亲爱的" << bh << "号：" << message << endl;
  }
  else
  { // 子进程将执行这段代码。
    bh=3; message="你是一只傻傻鸟。";
    cout << "子：pid=" << pid << endl;
    cout << "子：亲爱的" << bh << "号：" << message << endl;
  }
}

/*  
编译运行：
➜  4-4 Create process git:(main) ✗ ls
demo01.cpp
➜  4-4 Create process git:(main) ✗ g++ -o demo01 demo01.cpp   
➜  4-4 Create process git:(main) ✗ ./demo01      
子：pid=0
子：亲爱的3号：你是一只傻傻鸟。
父：pid=532013
父：亲爱的8号：我是一只傻傻鸟。
*/