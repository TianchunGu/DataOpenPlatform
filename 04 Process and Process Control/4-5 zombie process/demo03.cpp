#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(){
  if(fork()>0) return 0;
  while(true){
    cout<<"服务运行中~~"<<endl;
    sleep(1);
  }
}

/*
编译运行：
➜  4-5 zombie process git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  demo03.cpp
➜  4-5 zombie process git:(main) ✗ g++ -o demo03 demo03.cpp
➜  4-5 zombie process git:(main) ✗ ./demo03  
服务运行中~~
➜  4-5 zombie process git:(main) ✗ 服务运行中~~
服务运行中~~
服务运行中~~
服务运行中~~
*/