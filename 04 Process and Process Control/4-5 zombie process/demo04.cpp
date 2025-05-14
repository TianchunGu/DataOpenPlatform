#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using  namespace std;

int main()
{
  if (fork()>0)
  { // 父进程的流程。
    int sts;
    pid_t pid=wait(&sts);

    cout << "已终止的子进程编号是：" << pid << endl;

    if (WIFEXITED(sts)) { cout << "子进程是正常退出的，退出状态是：" << WEXITSTATUS(sts) << endl; }
    else { cout << "子进程是异常退出的，终止它的信号是：" << WTERMSIG(sts) << endl; }
  }
  else
  { // 子进程的流程。
    //sleep(100);
    int *p=0; *p=10;
    exit(1);
  }
}