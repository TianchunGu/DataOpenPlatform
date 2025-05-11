#include <iostream>
#include <dirent.h>
using namespace std;

int main(int argc,char *argv[])
{
  if (argc != 2) { cout << "Using ./demo 目录名\n"; return -1; }

  DIR *dir;   // 定义目录指针。

  // 打开目录。
  if ( (dir=opendir(argv[1])) == nullptr ) return -1;

  // 用于存放从目录中读取到的内容。
  struct dirent *stdinfo=nullptr;

  while (1)
  {
    // 读取一项内容并显示出来。
    if ((stdinfo=readdir(dir)) == nullptr) break;

    cout << "文件名=" << stdinfo->d_name << "，文件类型=" << (int)stdinfo->d_type << endl;
  }

  closedir(dir);   // 关闭目录指针。
}

/*
编译运行：
➜  3-2 Linux's directory operations git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  3-2 Linux's directory operations git:(main) ✗ ls
demo01  demo01.cpp
➜  3-2 Linux's directory operations git:(main) ✗ ./demo01 "/home/gtc/GitHub/DataOpenPlatform/03 LinuxBasicsTwo/3-1 Linux's time-related operations"
文件名=demo02.cpp，文件类型=8
文件名=demo02，文件类型=8
文件名=demo03，文件类型=8
文件名=..，文件类型=4
文件名=demo03.cpp，文件类型=8
文件名=.，文件类型=4
文件名=demo01，文件类型=8
文件名=demo01.cpp，文件类型=8
*/