#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  // int ret=system("/bin/ls -| /temp");//使用全路径可避免环境变量的问题
  // 在路径两侧添加引号，解决路径中空格的问题
  int ret=system("\"/home/gtc/GitHub/DataOpenPlatform/04 Process and Process Control/4-2 Process termination/demo01\"");
  cout << "ret=" << ret << endl;
  perror("system");
}

/*
编译运行：
1.int ret=system("/bin/ls -| /temp");
➜  4-3 Call the executable program git:(main) ✗ g++ -o demo01 demo01.cpp   
➜  4-3 Call the executable program git:(main) ✗ ls
demo01  demo01.cpp
➜  4-3 Call the executable program git:(main) ✗ ./demo01      
sh: 1: /temp: not found
/bin/ls: cannot access '-': No such file or directory
ret=32512
system: Success
2.int ret=system("/home/gtc/GitHub/DataOpenPlatform/04 Process and Process Control/4-2 Process termination/demo01");
➜  4-3 Call the executable program git:(main) ✗ g++ -o demo01 demo01.cpp
➜  4-3 Call the executable program git:(main) ✗ ./demo01
调用了func1
调用了func2
回到了func1函数
回到了main函数
ret=0
system: Success
*/