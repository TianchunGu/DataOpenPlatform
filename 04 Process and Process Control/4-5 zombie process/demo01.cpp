#include <>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(){
  if(fork()>0){
    //父进程的流程
    sleep(20);
    cout<<"父进程将退出。"<<endl;
    return 0;
  }else{
    //子进程的流程
    for(int i=0;i<100;i++){
      cout<<"子进程继续运行中。"<<endl;
      sleep(1);
    }
  }
}

/*
编译运行：
➜  4-5 zombie process git:(main) ✗ g++ -o demo01 demo01.cpp
➜  4-5 zombie process git:(main) ✗ ./demo01
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
父进程将退出。
子进程继续运行中。                                                                                                            
➜  4-5 zombie process git:(main) ✗ 子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。
子进程继续运行中。

父进程被杀死后，子进程将被1号进程托管
➜  DataOpenPlatform git:(main) ✗ ps -ef | grep demo01
gtc       387260  385277  0 5月13 pts/2   00:00:00 ./demo01
gtc       388316  385277  0 5月13 pts/2   00:00:00 ./demo01
gtc       582632  385277  0 10:43 pts/2    00:00:00 ./demo01
gtc       582633  582632  0 10:43 pts/2    00:00:00 ./demo01
gtc       582904  430563  0 10:44 pts/4    00:00:00 grep --color=auto --exclude-dir=.bzr --exclude-dir=CVS --exclude-dir=.git --exclude-dir=.hg --exclude-dir=.svn --exclude-dir=.idea --exclude-dir=.tox --exclude-dir=.venv --exclude-dir=venv demo01
➜  DataOpenPlatform git:(main) ✗ ps -ef | grep demo01
gtc       387260  385277  0 5月13 pts/2   00:00:00 ./demo01
gtc       388316  385277  0 5月13 pts/2   00:00:00 ./demo01
gtc       582633       1  0 10:43 pts/2    00:00:00 ./demo01
gtc       583488  430563  0 10:44 pts/4    00:00:00 grep --color=auto --exclude-dir=.bzr --exclude-dir=CVS --exclude-dir=.git --exclude-dir=.hg --exclude-dir=.svn --exclude-dir=.idea --exclude-dir=.tox --exclude-dir=.venv --exclude-dir=venv demo01
*/