#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(){
  while(true){
    cout<<"服务运行中~~"<<endl;
    sleep(1);
  }
}

/*
编译运行：
➜  4-5 zombie process git:(main) ✗ ls
demo01  demo01.cpp  demo02.cpp
➜  4-5 zombie process git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-5 zombie process git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-5 zombie process git:(main) ✗ ./demo02 &    
[5] 589519
服务运行中~~                                                                                                                  
➜  4-5 zombie process git:(main) ✗ 服务运行中~~
服务运行中~~
服务运行中~~
服务运行中~~
ls
服务运行中~~
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-5 zombie process git:(main) ✗ 服务运行中~~
服务运行中~~
ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-5 zombie process git:(main) ✗ 服务运行中~~
服务运行中~~
服务运行中~~
ls服务运行中~~

demo01  demo01.cpp  demo02  demo02.cpp
➜  4-5 zombie process git:(main) ✗ 服务运行中~~
服务运行中~~
服务运行中~~
服务运行中~~
*/