// 该代码展示进程终止的状态
#include <iostream>
using namespace std;

int main(){

  // return 0;
  // return 1;
  exit(2);
}

/*
编译运行：
1. main函数中return 0;
➜  4-2 Process termination git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-2 Process termination git:(main) ✗ ./demo02      
➜  4-2 Process termination git:(main) ✗ echo $?
0
2.main函数中return 1;
➜  4-2 Process termination git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-2 Process termination git:(main) ✗ ./demo02
➜  4-2 Process termination git:(main) ✗ echo $?                 
1
3.main函数中调用exit(2);
➜  4-2 Process termination git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-2 Process termination git:(main) ✗ ./demo02
➜  4-2 Process termination git:(main) ✗ echo $?                 
2
*/