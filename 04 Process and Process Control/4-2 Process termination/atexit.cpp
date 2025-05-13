#include <iostream>
#include <unistd.h>
using namespace std;

void func1(){
  cout<<"调用了func1"<<endl;
}
void func2(){
  cout<<"调用了func2"<<endl;
}

int main(){
  atexit(func1);//登记第一个进程终止函数
  atexit(func2);//登记第二个进程终止函数
  // return 0;
  // exit(1);
  _exit(1);
}

/*
编译运行：
1. main函数中return 0;
➜  4-2 Process termination git:(main) ✗ g++ -o atexit atexit.cpp
➜  4-2 Process termination git:(main) ✗ ./atexit         
调用了func2
调用了func1
2. main函数中exit(1);
➜  4-2 Process termination git:(main) ✗ g++ -o atexit atexit.cpp
➜  4-2 Process termination git:(main) ✗ ./atexit
调用了func2
调用了func1
3.main函数中_exit(1);
➜  4-2 Process termination git:(main) ✗ g++ -o atexit atexit.cpp
➜  4-2 Process termination git:(main) ✗ ./atexit
➜  4-2 Process termination git:(main) ✗ 
*/