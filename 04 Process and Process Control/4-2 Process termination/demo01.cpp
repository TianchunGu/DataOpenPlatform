#include <iostream>
using namespace std;

void func2(){
  cout<<"调用了func2"<<endl;
  // exit(0);
  return;
}

void func1(){
  cout<<"调用了func1"<<endl;
  func2();
  cout<<"回到了func1函数"<<endl;
}
int main(){
  func1();
  cout<<"回到了main函数"<<endl;
  return 0;
}

/*
编译运行：
1. func2中调用exit(0);
➜  4-2 Process termination git:(main) ✗ ls
demo01.cpp
➜  4-2 Process termination git:(main) ✗ g++ -o demo01 demo01.cpp                                   
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp
➜  4-2 Process termination git:(main) ✗ ./demo01                
调用了func1
调用了func2
2. func2中调用return;
➜  4-2 Process termination git:(main) ✗ ls
demo01.cpp
➜  4-2 Process termination git:(main) ✗ g++ -o demo01 demo01.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp
➜  4-2 Process termination git:(main) ✗ ./demo01      
调用了func1
调用了func2
回到了func1函数
回到了main函数
*/