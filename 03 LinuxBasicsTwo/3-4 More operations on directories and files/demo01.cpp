// 样例代码
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  if (argc != 2)  { cout << "Using:./demo 文件或目录名\n"; return -1; }

  if(access(argv[1],F_OK)!=0){
    cout << "文件或目录"<<argv[1]<<"不存在\n";
    return -1;
  }
  cout << "文件或目录"<<argv[1]<<"存在\n";
  return 0;
}

/*
编译运行：
➜  3-4 More operations on directories and files git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  3-4 More operations on directories and files git:(main) ✗ ls
demo01  demo01.cpp
➜  3-4 More operations on directories and files git:(main) ✗ ./demo01
Using:./demo 文件或目录名
➜  3-4 More operations on directories and files git:(main) ✗ ./demo01 /home
文件或目录/home存在
➜  3-4 More operations on directories and files git:(main) ✗ ./demo01 /file
文件或目录/file不存在
*/