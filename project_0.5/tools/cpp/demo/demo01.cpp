#include "_public.h"
using namespace idc;

// 进程心跳信息的结构体
struct stprocinfo {
  int pid = 0;             // 进程的PID。
  char pnameme[51] = {0};  // 进程名称，可以为空
  int timeout = 0;         // 进程心跳超时时间。
  time_t atime = 0;        // 进程最近一次心跳的时间,用整数表示。
  // 有了自定义的构造函数，编译器将不提供默认构造函数，所以启用默认构造函数
  stprocinfo() = default;
  stprocinfo(const int in_pid,
             const string& in_pname,
             const int in_timeout,
             const time_t in_atime)
      : pid(in_pid), timeout(in_timeout), atime(in_atime) {
    strncpy(pnameme, in_pname.c_str(), 50);
  }
};

int m_shmid = -1;             // 共享内存的id
stprocinfo* m_shm = nullptr;  // 指向共享内存的地址空间
void EXIT(int sig);
int m_pos = -1;  // 用于存放当前进程在数组中的下标。

int main() {
  // 处理程序的退出信号。
  signal(SIGINT, EXIT);
  signal(SIGTERM, EXIT);
  // 创建/获取共享内存。
  if ((m_shmid = shmget((key_t)0x5095, 1000 * sizeof(struct stprocinfo),
                        0666 | IPC_CREAT)) == -1) {
    printf("创建/获取共享内存（%x）失败\n", 0x5095);
    return -1;
  }
  // 将共享内存连接到当前进程的地址空间。
  m_shm = (struct stprocinfo*)shmat(m_shmid, 0, 0);
  // 把共享内存中全部进程的信息显示出来，用于调试
  for (int ii = 0; ii < 1000; ii++) {
    if (m_shm[ii].pid != 0) {  // 只显示进程已使用的位置，空位置不显示
      printf("pid=%d,pname=%s,timeout=%d,atime=%s\n", m_shm[ii].pid,
             m_shm[ii].pnameme, m_shm[ii].timeout, ctime(&m_shm[ii].atime));
    }
  }
  // 把当前进程的信息填充到结构体中。
  stprocinfo procinfo(getpid(), "server1", 30, time(0));

  csemp semlock;                        // 用于给共享内存加锁的信号量id
  if (semlock.init(0x5095) == false) {  // 初始化信号量，失败则退出程序
    printf("初始化信号量(%x)失败\n", 0x5095);
    return -1;
  }
  semlock.wait();  // 给共享内存加锁，等待信号量
  // 进程id是循环使用的，如果曾经有一个进程异常退出，没有清理自己的心跳信息，他的进程信息将残留在共享内存中，
  // 不巧的是如果当前进程重用了它的id，所以，如果共享内存中已存在当前进程编号，一定是其他进程残留的信息，
  // 当前进程应该重用这个位置。
  for (int ii = 0; ii < 1000; ii++) {
    if (m_shm[ii].pid == procinfo.pid) {  // 如果pid是空的，表示这是一个空位置
      m_pos = ii;
      printf("找到旧位置=%d\n", m_pos);
      break;
    }
  }
  if (m_pos == -1) {
    // 在共享内存中寻找一个空的位置，把当前进程的结构体保存到共享内存中。
    for (int ii = 0; ii < 1000; ii++) {
      if (m_shm[ii].pid == 0) {  // 如果pid是空的，表示这是一个空位置
        m_pos = ii;
        printf("找到新位置=%d\n", m_pos);
        break;
      }
    }
  }
  // 如果m_pos=-1，表示没有空位置（说明共享空间已用完），程序退出。
  if (m_pos == -1) {
    semlock.post();
    printf("共享内存已用完，程序退出\n");
    EXIT(-1);
  }
  // 把当前进程的结构体保存到共享内存中
  memcpy(&m_shm[m_pos], &procinfo, sizeof(struct stprocinfo));  // 数组表示法

  // 指针表示法
  // memcpy(m_shm + m_pos,  q&procinfo, sizeof(struct stprocinfo));
  semlock.post();  //  解锁
  while (1) {
    printf("服务程序在运行中...\n");
    sleep(1);
    // 更新进程的心跳信息。
    m_shm[m_pos].atime = time(0);
  }
  return 0;
}

void EXIT(int sig) {
  printf("程序退出，sig=%d\n", sig);
  // 从共享内存中删除当前进程的心跳信息。
  if (m_pos != -1)
    memset(m_shm + m_pos, 0, sizeof(struct stprocinfo));
  // 把共享内存从当前进程分离
  if (m_shmid != 0)
    shmdt(m_shm);
  exit(0);
}

/*
编译指令：
g++ -g -o server1 server.cpp
/home/gtc/GitHub/DataOpenPlatform/project_0.5/public/_public.cpp
-I/home/gtc/GitHub/DataOpenPlatform/project_0.5/public
*/
