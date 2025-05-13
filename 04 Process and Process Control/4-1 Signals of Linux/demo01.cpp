#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  int num = 0;
  while (true){
    cout<<"执行了"<<++num<<"次任务"<<endl;
    sleep(1);
  }
  return 0;
}

/*
第一个窗口编译运行：
➜  4-1 Signals of Linux git:(main) ✗ ls
demo01.cpp
➜  4-1 Signals of Linux git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  4-1 Signals of Linux git:(main) ✗ ls
demo01  demo01.cpp
➜  4-1 Signals of Linux git:(main) ✗ ./demo01      
执行了1次任务
执行了2次任务
执行了3次任务
执行了4次任务
执行了5次任务
执行了6次任务
执行了7次任务
执行了8次任务
执行了9次任务
执行了10次任务
执行了11次任务
执行了12次任务
执行了13次任务
执行了14次任务
执行了15次任务
执行了16次任务
执行了17次任务
执行了18次任务
执行了19次任务
执行了20次任务
执行了21次任务
执行了22次任务
[3]    430507 terminated  ./demo01

第二个窗口杀死进程：
➜  DataOpenPlatform git:(main) ✗ killall demo01

可以使用-指定信号种类
➜  DataOpenPlatform git:(main) ✗ killall -15 demo01 

*/