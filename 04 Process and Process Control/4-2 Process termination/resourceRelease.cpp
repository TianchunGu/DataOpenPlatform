#include <iostream>
#include <unistd.h>
using namespace std;

struct AA{
  string name;//用于区分不同的对象
  AA(const string &name):name(name){}
  ~AA(){
    cout<<name<<"调用了析构函数"<<endl;
  }
};

AA a1("全局对象a1");

int main(){
  AA a2("局部对象a2");
  // return 0;
  // exit(0);
  _exit(0);
}

/*
编译运行：
1. main函数中return 0;
➜  4-2 Process termination git:(main) ✗ g++ -o resourceRelease resourceRelease.cpp 
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  resourceRelease  resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ./resourceRelease 
局部对象a2调用了析构函数
全局对象a1调用了析构函数
2. main函数中exit(0);
➜  4-2 Process termination git:(main) ✗ g++ -o resourceRelease resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  resourceRelease  resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ./resourceRelease 
全局对象a1调用了析构函数
3. main函数中_exit(0);
➜  4-2 Process termination git:(main) ✗ g++ -o resourceRelease resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  resourceRelease  resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ./resourceRelease
➜  4-2 Process termination git:(main) ✗ 
*/