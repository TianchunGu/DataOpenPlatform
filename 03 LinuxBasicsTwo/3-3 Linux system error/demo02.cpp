#include <iostream>
#include <cstring>    // strerror()函数需要的头文件。
#include <cerrno>     // errno全局变量的头文件。
#include <sys/stat.h> // mkdir()函数需要的头文件。
using namespace std;

int main()
{
  int iret=mkdir("/tmp/aaa/bb/cc/dd",0755);
  if (iret!=0)
  {
    cout << "iret=" << iret << endl;
    cout << errno << ":" << strerror(errno) << endl;
    cout<<"是这里输出的"<<endl;
    perror("调用mkdir(/tmp/aaa/bb/cc/dd)失败");
  }

  iret=mkdir("/tmp/dd",0755);//成功创建目录
  if (iret!=0)
  {
    cout << "iret=" << iret << endl;
    cout << errno << ":" << strerror(errno) << endl;
    perror("调用mkdir(/tmp/dd)失败");
  }
}

/*
编译运行：
➜  3-3 Linux system error git:(main) ✗ g++ -o demo02 demo02.cpp -g
➜  3-3 Linux system error git:(main) ✗ ./demo0 
zsh: no such file or directory: ./demo0
➜  3-3 Linux system error git:(main) ✗ ./demo02
iret=-1
2:No such file or directory
是这里输出的
调用mkdir(/tmp/aaa/bb/cc/dd)失败: No such file or directory
*/