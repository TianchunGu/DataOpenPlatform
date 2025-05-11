#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstring>    // strerror()函数需要的头文件
#include <cerrno>     // errno全局变量的头文件
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  if (argc != 2)  { cout << "Using:./demo 文件或目录名\n"; return -1; }

  struct stat st;  // 存放目录或文件详细信息的结构体。

  // 获取目录或文件的详细信息
  if (stat(argv[1],&st) != 0)
  {
    cout << "stat(" << argv[1] << "):" << strerror(errno) << endl; return -1;
  }

  if (S_ISREG(st.st_mode))
    cout << argv[1] << "是一个文件(" << "mtime=" << st.st_mtime << ",size=" << st.st_size << ")\n";
  if (S_ISDIR(st.st_mode))
cout << argv[1] << "是一个目录(" << "mtime=" << st.st_mtime << ",size=" << st.st_size << ")\n";
}

/*
编译运行：
➜  3-4 More operations on directories and files git:(main) ✗ ls
demo01  demo01.cpp  demo02.cpp
➜  3-4 More operations on directories and files git:(main) ✗ g++ -o demo02 demo02.cpp -g
➜  3-4 More operations on directories and files git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  3-4 More operations on directories and files git:(main) ✗ ./demo02      
Using:./demo 文件或目录名
➜  3-4 More operations on directories and files git:(main) ✗ ./demo02 /home                   
/home是一个目录(mtime=1744536977,size=4096)
*/