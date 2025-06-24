## 业务需求
### 服务程序会僵死
+ 不管是操作系统还是应用软件，都会出现僵死的情况，为什么？
+ 是程序员的水平不够高？原因说不清楚。通讯程序更容易死。
+ 不管什么原因，重启可以解决99%的问题。重装系统或软件。
+ 使用电脑和手机软件的时候，有问题可以人工重启。
+ 服务程序运行在后台，无人值守，难以发现，如何重启？
+ 人工干预不现实。

### 服务程序的监控和调度
+ 周期性的运行服务程序。
+ 检查服务程序是否活着，如果死了，终止它。
+ 如果服务程序已终止，重启它。

## 调度模块
复习课程<font style="background-color:#E8F7CF;">314.调用可执行程序</font>

> [程序路径](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/tools/cpp/procctl.cpp)：
>
> /home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/procctl
>

### 服务程序的运行方式
+ 周期性运行的服务程序。生成测试数据的程序。
+ 常驻内存中的服务程序。网络通讯的服务端程序。

### 服务程序的调度方法
+ 周期性运行的服务程序。周期性的启动它。
+ 常驻内存中的服务程序。在正常/异常终止后，重新运行它。
+ 在服务程序正常/异常终止后，重新运行它。周期性/立即。

### 完整代码
```cpp
// 本程序不需要包含_public.h，没必要依赖那么多头文件。
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Using:./procctl timetvl program argv ...\n");
    printf(
        "Example:/project/tools/bin/procctl 10 /usr/bin/tar zcvf /tmp/tmp.tgz "
        "/usr/include\n");
    printf(
        "Example:/project/tools/bin/procctl 60 /project/idc/bin/crtsurfdata "
        "/project/idc/ini/stcode.ini /tmp/idc/surfdata "
        "/log/idc/crtsurfdata.log csv,xml,json\n");

    printf("本程序是服务程序的调度程序，周期性启动服务程序或shell脚本。\n");
    printf("timetvl 运行周期，单位：秒。\n");
    printf(
        "        被调度的程序运行结束后，在timetvl秒后会被procctl重新启动。\n");
    printf("        如果被调度的程序是周期性的任务，timetvl设置为运行周期。\n");
    printf(
        "        如果被调度的程序是常驻内存的服务程序，timetvl设置小于5秒。\n");
    printf("program 被调度的程序名，必须使用全路径。\n");
    printf("...     被调度的程序的参数。\n");
    printf("注意，本程序不会被kill杀死，但可以用kill -9强行杀死。\n\n\n");

    return -1;
  }

  // 关闭信号和I/O，本程序不希望被打扰。
  // 注意：1）为了防调度程序被误杀，不处理退出信号；
  //           2）如果忽略和信号和关闭了I/O，将影响被调度的程序（也会忽略和信号和关闭了I/O）。
  //           why？因为被调度的程序取代了子进程，子进程会继承父进程的信号处理方式和I/O。
  for (int ii = 0; ii < 64; ii++) {
    signal(ii, SIG_IGN);
    close(ii);
  }

  // 生成子进程，父进程退出，让程序运行在后台，由系统1号进程托管，不受shell的控制。
  if (fork() != 0)
    exit(0);

  // 把子进程退出的信号SIGCHLD恢复为默认行为，让父进程可以调用wait()函数等待子进程退出。
  signal(SIGCHLD, SIG_DFL);

  // 定义一个和argv一样大的指针数组，存放被调度程序名及其参数。
  char* pargv[argc];
  for (int ii = 2; ii < argc; ii++)
    pargv[ii - 2] = argv[ii];

  pargv[argc - 2] = nullptr;  // 空表示参数已结束。

  while (true) {
    if (fork() == 0) {
      // 子进程运行被调度的程序。
      execv(argv[2], pargv);
      exit(0);  // 如果被调度的程序运行失败，才会执行这行代码。
    } else {
      // 父进程等待子进程终止（被调度的程序运行结束）。
      // int status;
      // wait(&status);           // wait()函数会阻塞，直到被调度的程序终止。
      wait(nullptr);         // wait()函数会阻塞，直到被调度的程序终止。
      sleep(atoi(argv[1]));  // 休眠timetvl秒，然后回到循环。
    }
  }
}

/*
使用程序：
./procctl 60 /home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/cpp/crtsurfdata
/home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/ini/stcode.ini
/tmp/idc/surfdata
/home/gtc/GitHub/DataOpenPlatform/project_0.5/log/idc/crtsurfdata.log
csv,xml,json
查看进程信息 ps -ef |grep procctl
停止调度程序 killall -9 procctl
*/
```

## 进程的心跳
### 注意事项
+ 为保证系统的稳定运行，调度模块、进程心跳、进程监控协同工作。
+ 暂时不要想太多，先实现部分功能。

### 进程心跳
```cpp
struct st_procinfo
{
    int     pid=0;      // 进程id。
    char    pname[51];  // 进程名称，可以为空。
    int     timeout=0;  // 超时时间，单位：秒。
    time_t  atime=0;    // 最后一次心跳的时间。
};
```

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1749177147637-19a4ea73-913f-4dd0-93bf-13425f8546b7.png)

进程心跳的设计：用结构体数组，开辟一块[共享内存](https://www.yuque.com/tianchungu/dw0i8t/guc5las0hihwv6h9#gNIBu)。服务程序启动时，在数组中查找一个空的位置，把自己的进程信息写进去。服务程序在运行的过程中，要定时更新自己的信息。退出时，删除自己的信息。 

### 核心流程
1. 处理程序的退出信号
2. 创建/获取共享内存
3. 将共享内存连接到当前进程的地址空间
4. 将当前进程的信息填充到结构体中
5. 把当前进程的结构体保存到共享内存中
6. 循环更新

### 注意事项
#### 异常退出处理
<font style="color:#DF2A3F;">正常退出</font>：调用`EXIT`函数清理共享内存中的进程信息。

<font style="color:#DF2A3F;">异常退出</font>：可能导致信息残留（如kill -9 强制终止）

##### 解决方式
<font style="color:#DF2A3F;">进程启动时检查并重用相同PID的残留位置</font>。

进程id是循环使用的，如果曾经有一个进程异常退出，没有清理自己的心跳信息，他的进程信息将残留在共享内存中，不巧的是如果当前进程重用了它的id。

即，<font style="background-color:#E8F7CF;">如果共享内存中已存在当前进程编号，一定是其他进程残留的信息，当前进程应该重用这个位置</font>。

#### 多进程锁机制
[采用信号量实现](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/public/_public.h#L814)。

程序对共享内存有三个操作：

1. 在共享内存中寻找一个空的位置，将当前进程的结构体写入共享内存。
2. 更新自己在共享内存中的结构体的心跳时间
3. 从共享内存中删除自己

在这三个操作中，只有第一步需要加锁。

### 完整代码
进程心跳类实现：

1. [头文件](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/public/_public.h#L877)
2. [CPP](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/public/_public.cpp#L1697)

```cpp
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
```

## 守护模块
+ 检查共享内存中进程的心跳，如果超时，则终止进程（<font style="color:#DF2A3F;background-color:#FBF5CB;">核心功能</font>）。
+ 超时被终止的进程将由[调度模块(procctl)](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/tools/cpp/procctl.cpp)重启

### 核心流程
1. 打开日志文件
2. 创建/获取[共享内存](https://www.yuque.com/tianchungu/dw0i8t/guc5las0hihwv6h9#gNIBu)
3. 链接共享内存到进程地址空间
4. 遍历检查进程心跳记录，如果进程已超时，终止它
5. 把共享内存从当前进程中分离

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1749373526934-f2947b88-101c-480b-bea8-a2c58d68cd33.png)

### 完整代码
```cpp
// 守护程序：检查共享内存中进程的心跳，如果超时，则终止进程。
#include "_public.h"
using namespace idc;

int main(int argc, char* argv[]) {
  // 程序的帮助。
  if (argc != 2) {
    printf("\n");
    printf("Using:./checkproc logfilename\n");

    printf(
        "Example:/project/tools/bin/procctl 10 /project/tools/bin/checkproc "
        "/tmp/log/checkproc.log\n\n");

    printf("本程序用于检查后台服务程序是否超时，如果已超时，就终止它。\n");
    printf("注意：\n");
    printf("  1）本程序由procctl启动，运行周期建议为10秒。\n");
    printf("  2）为了避免被普通用户误杀，本程序应该用root用户启动。\n");
    printf("  3）如果要停止本程序，只能用killall -9 终止。\n\n\n");

    return 0;
  }

  // 忽略全部的信号和IO，不处理程序的退出信号。
  closeioandsignal(true);

  // 打开日志文件。
  clogfile logfile;  // 程序运行的日志。
  if (logfile.open(argv[1]) == false) {
    printf("logfile.open(%s) failed.\n", argv[1]);
    return -1;
  }

  // 创建/获取共享内存，键值为SHMKEYP，大小为MAXNUMP个st_procinfo结构体的大小。
  int shmid = 0;
  if ((shmid = shmget((key_t)SHMKEYP, MAXNUMP * sizeof(struct st_procinfo),
                      0666 | IPC_CREAT)) == -1) {
    logfile.write("创建/获取共享内存(%x)失败。\n", SHMKEYP);
    return false;
  }

  // 将共享内存连接到当前进程的地址空间。
  struct st_procinfo* shm = (struct st_procinfo*)shmat(shmid, 0, 0);

  // 遍历共享内存中全部的记录，如果进程已超时，终止它。
  for (int ii = 0; ii < MAXNUMP; ii++) {
    // 如果记录的pid==0，表示空记录，continue;
    if (shm[ii].pid == 0)
      continue;

    // 如果记录的pid!=0，表示是服务程序的心跳记录。

    // 显示进程信息，程序稳定运行后，以下两行代码可以注释掉。
    // logfile.write("ii=%d,pid=%d,pname=%s,timeout=%d,atime=%d\n",\
        //               ii,shm[ii].pid,shm[ii].pname,shm[ii].timeout,shm[ii].atime);

    // 如果进程已经不存在了，共享内存中是残留的心跳信息。
    // 向进程发送信号0，判断它是否还存在，如果不存在，从共享内存中删除该记录，continue;
    int iret = kill(shm[ii].pid, 0);
    if (iret == -1) {
      logfile.write("进程pid=%d(%s)已经不存在。\n", shm[ii].pid, shm[ii].pname);
      memset(&shm[ii], 0,
             sizeof(struct st_procinfo));  // 从共享内存中删除该记录。
      continue;
    }

    // 判断进程的心跳是否超时，如果超时了，就终止它。

    time_t now = time(0);  // 获取当前时间。

    // 如果进程未超时，continue;
    if (now - shm[ii].atime < shm[ii].timeout)
      continue;

    // 一定要把进程的结构体备份出来，不能直接用共享内存中的值。
    struct st_procinfo tmp = shm[ii];
    if (tmp.pid == 0)
      continue;

    // 如果已超时。
    logfile.write("进程pid=%d(%s)已经超时。\n", tmp.pid, tmp.pname);

    // 发送信号15，尝试正常终止已超时的进程。
    kill(tmp.pid, 15);

    // 每隔1秒判断一次进程是否存在，累计5秒，一般来说，5秒的时间足够让进程退出。
    for (int jj = 0; jj < 5; jj++) {
      sleep(1);
      iret = kill(tmp.pid, 0);  // 向进程发送信号0，判断它是否还存在。
      if (iret == -1)
        break;  // 进程已退出。
    }

    if (iret == -1)
      logfile.write("进程pid=%d(%s)已经正常终止。\n", tmp.pid, tmp.pname);
    else {
      // 如果进程仍存在，就发送信号9，强制终止它。
      kill(tmp.pid, 9);
      logfile.write("进程pid=%d(%s)已经强制终止。\n", tmp.pid, tmp.pname);

      // 从共享内存中删除已超时进程的心跳记录。
      memset(shm + ii, 0, sizeof(struct st_procinfo));
    }
  }

  // 把共享内存从当前进程中分离。
  shmdt(shm);

  return 0;
}
```

[测试demo](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/tools/cpp/demo/demo02.cpp)

```cpp
#include "_public.h"
using namespace idc;

cpactive pactive;  // 进程心跳，用全局对象（保证析构函数会被调用）。

void EXIT(int sig)  // 程序退出和信号2、15的处理函数。
{
  printf("sig=%d\n", sig);

  exit(0);
}

int main(int argc, char* argv[]) {
  // 处理程序的退出信号。
  signal(SIGINT, EXIT);
  signal(SIGTERM, EXIT);
  // closeioandsignal(true);

  pactive.addpinfo(atoi(argv[1]),
                   "demo02");  // 把当前进程的信息加入共享内存进程组中。

  while (1) {
    sleep(atoi(argv[2]));
    pactive.uptatime();  // 更新进程的心跳。
  }

  return 0;
}

/*
运行代码
// 进程心跳不会超时
./demo02 30 10
// 进程心跳会超时
./demo02 10 100
*/
```

## 运行策略
### 服务程序的运行策略
+ 心跳机制: 除调度模块和手动模块外，所有服务程序都应启用心跳机制
+ 统一启动: 所有服务程序由[调度模块（procctl）](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/tools/cpp/procctl.cpp)统一启动
+ 守护机制: 启动[守护模块（checkproc）](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/tools/cpp/checkproc.cpp)监控服务程序，超时则终止并由调度模块重启

### 完善文件`crtsurfdata.cpp`
#### 修改前
```cpp
/*
 * 程序名：crtsurfdata.cpp
 * 功能：本程序用于生成气象站点的分钟数据
 * 使用方法：程序每分钟运行一次，由调度模块启动
 */

#include "_public.h"
using namespace idc;

// 省   站号  站名 纬度   经度  海拔高度
//  安徽,58015,砀山,34.27,116.2,44.2
struct st_stcode {  // 站点参数结构体
  // string 操作方便、自动扩容 操作数据库时 string没有优势，所以用char[]
  char provname[31];  // 省
  char obtid[11];     // 站号
  char obtname[31];   // 站名
  double lat;         // 纬度
  double lon;         // 经度
  double height;      // 海拔高度
};

// 气象站观测数据的结构体
struct st_surfdata {
  char obtid[11];      // 站点代码
  char ddatetime[15];  // 数据时间：格式yyyymmddhh24miss，精确到分钟，秒固定填00
  int t;               // 气温：单位，0.1摄氏度
  int p;               // 气压：单位，0.1百帕
  int u;               // 相对湿度：0-100之间的值
  int wd;              // 风向：0-360之间的值
  int wf;              // 风速：单位，0.1米/秒
  int r;               // 降雨量：单位，0.1毫米
  int vis;             // 能见度：单位，0.1米
};
list<struct st_surfdata> datalist;  // 存放观测数据的容器
void crtsurfdata();  // 根据stlist容器中的站点参数，生成站点的观测数据，存放在datalist中·

list<st_stcode> stlist;                  // 存放全部的站点参数
bool loadstcode(const string& inifile);  // 把站点参数文件加载到stlist容器中

char strddatetime[15];  // yyyymmddhh24miss格式的当前时间

// 把容器datalist中的气象观测数据写入文件，outpath-数据文件存放的目录；datafmt-数据文件的格式，取值：csv、xml、json
bool crtsurffile(const string& outpath, const string& datafmt);

clogfile logfile;  // 本程序运行的日志

// 程序退出和信号2,15的处理函数
void EXIT(int sig);

int main(int argc, char* argv[]) {
  // 检查参数数量是否正确
  // 站点参数文件 生成的测试数据存放的目录 本程序运行的日志 输出数据文件的格式
  if (argc != 5) {
    // 如果参数数量不正确，输出帮助信息
    cout << "Using:./crtsurfdata inifile outpath logfile datafmt\n";
    cout << "Examples:/project/tools/bin/procctl 60 "
            "/project/idc/bin/crtsurfdata /project/idc/ini/stcode.ini "
            "/tmp/idc/surfdata /log/idc/crtsurfdata.log csv,xml,json\n\n";

    cout << "本程序用于生成气象站点观测的分钟数据，程序每分钟运行一次，由调度模"
            "块启动。\n";
    cout << "inifile  气象站点参数文件名。\n";
    cout << "outpath  气象站点数据文件存放的目录。\n";
    cout << "logfile  本程序运行的日志文件名。\n";
    cout << "datafmt  "
            "输出数据文件的格式，支持csv、xml和json，中间用逗号分隔。\n\n";

    return -1;
  }

  // 设置信号处理函数，确保程序可以正常退出
  closeioandsignal(true);  // 关闭0,1,2和忽略全部的信号
  signal(SIGINT, EXIT);
  signal(SIGTERM, EXIT);

  // 打开日志文件
  if (logfile.open(argv[3]) == false) {
    cout << "logfile.open(" << argv[3] << ") failed!\n";
    return -1;
  }

  // 记录程序开始运行的日志
  logfile.write("crtsurfdata 开始运行\n");

  // TODO: 实现生成气象站点数据的逻辑
  // 1. 从站点参数文件中加载站点参数，存放于容器中；
  if (loadstcode(argv[1]) == false) {
    EXIT(-1);
  }
  // 获取时间的代码
  memset(strddatetime, 0, sizeof(strddatetime));
  ltime(strddatetime, "yyyymmddhh24miss");  // 获取系统当前时间
  strncpy(strddatetime + 12, "00", 2);      // 把时间数据中的秒固定填00
  // 2. 根据站点参数，生成站点观测数据（随机数）；
  crtsurfdata();
  // 3.
  // 把站点观测数据保存到文件中。把容器datalist中的气象观测数据写入文件，outpath-数据文件存放的目录；datafmt-数据文件的格式，取值：csv、xml、json
  if (strstr(argv[4], "csv") != 0)
    crtsurffile(argv[2], "csv");
  if (strstr(argv[4], "xml") != 0)
    crtsurffile(argv[2], "xml");
  if (strstr(argv[4], "json") != 0)
    crtsurffile(argv[2], "json");

  // 记录程序运行结束的日志
  logfile.write("crtsurfdata 运行结束\n");

  return 0;
}

// 程序退出和信号2,15的处理函数
void EXIT(int sig) {
  // 记录程序退出的日志
  logfile.write("程序退出，sig=%d\n\n", sig);

  exit(0);
}

// 把站点参数文件加载到stlist容器中
bool loadstcode(const string& inifile) {
  cifile ifile;  // 读取文件的对象
  if (ifile.open(inifile) == false) {
    logfile.write("ifile.open(%s) failed.\n", inifile.c_str());
    return false;
  }
  string strbuffer;           // 存放从文件中读取的每一行。
  ifile.readline(strbuffer);  // 读取站点参数文件的第一行,他是标题，扔掉
  ccmdstr cmdstr;             // 用于拆分从文件中读取的行。
  st_stcode stcode;           // 站点参数的结构体

  while (ifile.readline(strbuffer)) {
    // logfile.write("strbuffer=%s\n",
    // strbuffer.c_str());//输出读取的行到日志文件。
    // 拆分从文件中读取的行，例如：安徽,58015,砀山,34.27,116.2,44.2
    cmdstr.splittocmd(strbuffer, ",");             // 拆分字符串
    memset(&stcode, 0, sizeof(struct st_stcode));  // 初始化结构体

    cmdstr.getvalue(0, stcode.provname, 30);  // 省
    cmdstr.getvalue(1, stcode.obtid, 10);     // 站点代码
    cmdstr.getvalue(2, stcode.obtname, 30);   // 站点名称
    cmdstr.getvalue(3, stcode.lat);           // 纬度
    cmdstr.getvalue(4, stcode.lon);           // 经度
    cmdstr.getvalue(5, stcode.height);        // 海拔高度

    stlist.push_back(stcode);  // 将站点数据添加到列表中
  }
  // 这里不需要手工关闭文件，cifile析构函数会自动关闭文件。

  // 把容器中全部数据写入日志中。
  // logfile.write("站点数:%d\n", stlist.size());
  // for (auto& aa : stlist) {
  //   logfile.write("%s %s %s %.2f %.2f %.2f\n\n", aa.provname, aa.obtname,
  //                 aa.obtid, aa.lat, aa.lon, aa.height);
  // }
  return true;
}

// 根据stlist容器中的站点参数，生成站点的观测数据，存放在datalist中·
void crtsurfdata() {
  srand(time(0));          //  设置随机数种子。
  st_surfdata stsurfdata;  // 存放观测数据的结构体
  // 遍历气象站点的参数的stlist容器，生成每个站点的观测数据，存放在datalist容器中。
  for (auto& aa : stlist) {
    memset(&stsurfdata, 0, sizeof(stsurfdata));  // 初始化stsurfdata结构体。

    // 填充观测数据的结构体的成员
    strcpy(stsurfdata.obtid, aa.obtid);          // 站点代码
    strcpy(stsurfdata.ddatetime, strddatetime);  // 数据时间
    stsurfdata.t =
        rand() % 350;  // 气温：单位0.1摄氏度。0-350之间。可犯可不犯的错误不要犯
    stsurfdata.p = rand() % 265 + 10000;      // 气压：单位0.1百帕。0-1000之间。
    stsurfdata.u = rand() % 101;              // 相对湿度：0-100之间。
    stsurfdata.wd = rand() % 360;             // 风向：0-360之间。
    stsurfdata.wf = rand() % 150;             // 风速：单位0.1m/s。
    stsurfdata.r = rand() % 16;               // 降雨量：0.1mm
    stsurfdata.vis = rand() % 5001 + 100000;  // 能见度：0.1米

    datalist.push_back(stsurfdata);  // 把观测数据的结构体放入datalist容器
  }

  for (auto& aa : datalist) {
    logfile.write("%s %s %.1f %.1f %d %.1f %.1f %.1f %.1f\n", aa.obtid,
                  aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
                  aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);
  }
}

// 把容器datalist中的气象观测数据写入文件，outpath-数据文件存放的目录；datafmt-数据文件的格式，取值：csv、xml、json
bool crtsurffile(const string& outpath, const string& datafmt) {
  // 加进程编号是一种常见的方法，这样，不同进程的输出文件不会冲突。
  // 拼接生成数据的文件名，例如：/tmp/idc/surfdata/SURF_ZH_20210629092200_2254.csv
  string strfilename = outpath + "/" + "SURF_ZH_" + strddatetime + "_" +
                       to_string(getpid()) + "." + datafmt;

  cofile ofile;  // 写入数据文件的对象。

  if (ofile.open(strfilename) == false) {
    logfile.write("ofile.open(%s) failed.\n", strfilename.c_str());
    return false;
  }

  // 把datalist容器中的观测数据写入文件，支持csv、xml和json三种格式。
  if (datafmt == "csv")
    ofile.writeline(
        "站点代码,数据时间,气温,气压,相对湿度,风向,风速,降雨量,能见度\n");
  if (datafmt == "xml")
    ofile.writeline("<data>\n");
  if (datafmt == "json")
    ofile.writeline("{\"data\":[\n");

  // 遍历存放观测数据的datalist容器。
  for (auto& aa : datalist) {
    // 把每行数据写入文件。
    if (datafmt == "csv")
      ofile.writeline("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n", aa.obtid,
                      aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
                      aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);

    if (datafmt == "xml")
      ofile.writeline(
          "<obtid>%s</obtid><ddatetime>%s</ddatetime><t>%.1f</t><p>%.1f</"
          "p><u>%d</u>"
          "<wd>%d</wd><wf>%.1f</wf><r>%.1f</r><vis>%.1f</vis><endl/>\n",
          aa.obtid, aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
          aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);

    if (datafmt == "json") {
      ofile.writeline(
          "{\"obtid\":\"%s\",\"ddatetime\":\"%s\",\"t\":\"%.1f\",\"p\":\"%."
          "1f\","
          "\"u\":\"%d\",\"wd\":\"%d\",\"wf\":\"%.1f\",\"r\":\"%.1f\",\"vis\":"
          "\"%.1f\"}",
          aa.obtid, aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
          aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);
      // 注意，json文件的最后一条记录不需要逗号，用以下代码特殊处理。
      static int ii = 0;               // 已写入数据行数的计数器。
      if (ii < datalist.size() - 1) {  // 如果不是最后一行。
        ofile.writeline(",\n");
        ii++;
      } else
        ofile.writeline("\n");
    }
  }

  if (datafmt == "xml")
    ofile.writeline("</data>\n");
  if (datafmt == "json")
    ofile.writeline("]}\n");

  ofile.closeandrename();  // 关闭临时文件，并改名为正式的文件。

  logfile.write("生成数据文件%s成功，数据时间%s，记录数%d。\n",
                strfilename.c_str(), strddatetime, datalist.size());

  return true;
}

/*
./crtsurfdata ../ini/stcode.ini
/home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/output logfile xml
*/
```

#### 修改
1. 添加进程心跳



### 启动和停止服务的方法
#### 启动
编写[脚本start.sh](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/idc/cpp/start.sh)

```bash
#此脚本用于启动数据共享平台全部的服务程序。

#启动守护模块
/home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/procctl 10 /home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/bin/checkproc /tmp/log/checkproc.log
#启动气象站点观测的分钟数据，程序每分钟运行一次
/home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/procctl 60 /home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/cpp/crtsurfdata /home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/ini/stcode.ini /tmp/idc/surfdata /home/gtc/GitHub/DataOpenPlatform/project_0.5/log/idc/crtsurfdata.log csv,xml,json
```

```bash
# 给脚本增加可执行权限
chmod +x start.sh
```

#### 停止
编写[脚本stop.sh](https://github.com/TianchunGu/DataOpenPlatform/blob/main/project_max/idc/cpp/stop.sh)

```bash
# 此脚本用于停止数据共享平台全部的服务程序

# 停止调度程序
killall -9 procctl

#停止其他的服务程序
#尝试让其他服务程序正常终止
killall crtsurfdata

#让其他服务程序有足够的时间退出
sleep 5

#不管服务程序有没有限制，都强制杀死
killall -9 crtsurfdata

```

```bash
# 给脚本增加可执行权限
chmod +x stop.sh
```

### 设置开机自启动
在文件`/etc/rc.local`下添加脚本。

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1749465779000-d0e24845-4ca6-4710-9e62-e445970cbfd4.png)

守护模块在`start.sh`中的内容需要删除。

重要性: <font style="color:#DF2A3F;">守护进程极其重要且只需运行一个实例</font>

### 调度程序和守护进程死掉了怎么办？
+ 越复杂的程序越容易死，特别是用到网络通讯的程序。
+ 简单的程序不会死。个人经验。
+ 在实际开发中，把系统分解成简单的模块是明智的选择。

## 清理文件`deletefiles.cpp`
+ 清理文件：删除指定目录中的历史数据文件。
+ 压缩文件：压缩指定目录中的历史数据文件。

### 程序流程
1. 程序的帮助文档
2. 忽略全部的信号和关闭`I/O`，设置信号处理函数
3. 获取被定义为历史数据文件的时间点
4. 打开目录
5. 遍历目录中的文件，如果是历史数据文件，删除它。

---

代码完成具体功能后，需要添加进程心跳`cpactive`，并且在脚本中`start.sh`、`stop.sh`中启用。

### 完整代码
```cpp
#include "_public.h"
using namespace idc;

cpactive pactive;  // 进程的心跳

// 程序退出和信号2、15的处理函数。
void EXIT(int sig);

int main(int argc, char* argv[]) {
  // 1. 程序的帮助文档
  if (argc != 4) {
    printf("\n");
    // pathname 目录中子目录的文件也会被清理掉。
    printf(
        "Using:/project/tools/bin/deletefiles pathname matchstr timeout\n\n");

    printf(
        "Example:/project/tools/bin/deletefiles /tmp/idc/surfdata "
        "\"*.xml,*.json\" 0.01\n");
    cout
        << R"(        /project/tools/bin/deletefiles /log/idc "*.log.20*" 0.02)"
        << endl;
    printf(
        "        /project/tools/bin/procctl 300 /project/tools/bin/deletefiles "
        "/log/idc \"*.log.20*\" 0.02\n");
    printf(
        "        /project/tools/bin/procctl 300 /project/tools/bin/deletefiles "
        "/tmp/idc/surfdata \"*.xml,*.json\" 0.01\n\n");

    printf("这是一个工具程序，用于删除历史的数据文件或日志文件。\n");
    printf(
        "本程序把pathname目录及子目录中timeout天之前的匹配matchstr文件全部删除"
        "，timeout可以是小数。\n");
    printf("本程序不写日志文件，也不会在控制台输出任何信息。\n\n\n");

    return -1;
  }
  // 2. 忽略全部的信号和关闭I/O，设置信号处理函数
  closeioandsignal(true);  // 在开发测试阶段，这行代码不启用，方便显示调试信息。
  signal(2, EXIT);
  signal(15, EXIT);
  pactive.addpinfo(30, "deletefiles");  // 把当前进程的心跳加入共享内存。
  // 3. 获取被定义为历史数据文件的时间点
  string strtimeout =
      ltime1("yyyymmddhh24miss", 0 - (int)(atof(argv[3]) * 24 * 60 * 60));
  // cout << "strtimeout=" << strtimeout << endl;
  // 4. 打开目录
  cdir dir;
  if (dir.opendir(argv[1], argv[2], 10000, true) == false) {
    printf("dir.opendir(%s) failed.\n", argv[1]);
    return -1;
  }
  // 5. 遍历目录中的文件，如果是历史数据文件，删除它。
  while (dir.readdir() == true) {
    // 把文件的时间与历史文件的时间点比较，如果更早，就需要删除
    if (dir.m_mtime < strtimeout) {
      if (remove(dir.m_ffilename.c_str()) == 0) {
        cout << "删除文件成功：" << dir.m_ffilename << "\n";
      } else {
        cout << "删除文件失败：" << dir.m_ffilename << "\n";
      }
    }
  }
  return 0;
}

void EXIT(int sig) {
  printf("程序退出，sig=%d\n", sig);
  exit(0);
}
```

## 压缩文件
```cpp
#include "_public.h"
using namespace idc;

cpactive pactive;  // 进程的心跳

// 程序退出和信号2、15的处理函数。
void EXIT(int sig);

int main(int argc, char* argv[]) {
    // 1. 程序的帮助文档
    if (argc != 4) {
        printf("\n");
        // pathname 目录中子目录的文件也会被清理掉。
        printf("Using:/project/tools/bin/gzipfiles pathname matchstr timeout\n\n");

        printf(
            "Example:/project/tools/bin/gzipfiles /tmp/idc/surfdata "
            "\"*.xml,*.json\" 0.01\n");
        cout << R"(        /project/tools/bin/gzipfiles /log/idc "*.log.20*" 0.02)"
            << endl;
        printf(
            "        /project/tools/bin/procctl 300 /project/tools/bin/gzipfiles "
            "/log/idc \"*.log.20*\" 0.02\n");
        printf(
            "        /project/tools/bin/procctl 300 /project/tools/bin/gzipfiles "
            "/tmp/idc/surfdata \"*.xml,*.json\" 0.01\n\n");

        printf("这是一个工具程序，用于压缩历史的数据文件或日志文件。\n");
        printf(
            "本程序把pathname目录及子目录中timeout天之前的匹配matchstr文件全部压缩"
            "，timeout可以是小数。\n");
        printf("本程序调用/usr/bin/gzip命令压缩文件。\n\n\n");

        return -1;
    }
    // 2. 忽略全部的信号和关闭I/O，设置信号处理函数
    // closeioandsignal(true);  //
    // 在开发测试阶段，这行代码不启用，方便显示调试信息。
    signal(2, EXIT);
    signal(15, EXIT);
    pactive.addpinfo(120, "gzipfiles");  // 把当前进程的心跳加入共享内存。
    // 3. 获取被定义为历史数据文件的时间点
    string strtimeout =
    ltime1("yyyymmddhh24miss", 0 - (int)(atof(argv[3]) * 24 * 60 * 60));
    // cout << "strtimeout=" << strtimeout << endl;
    // 4. 打开目录
    cdir dir;
    if (dir.opendir(argv[1], argv[2], 10000, true) == false) {
        printf("dir.opendir(%s) failed.\n", argv[1]);
        return -1;
    }
    // 5. 遍历目录中的文件，如果是历史数据文件，压缩它。
    while (dir.readdir() == true) {
        // 把文件的时间与历史文件的时间点比较，如果更早，并且不是压缩文件，就需要压缩。
        if ((dir.m_mtime < strtimeout) &&
            (matchstr(dir.m_filename, "*.gz") == false)) {
            // 压缩文件，调用操作系统的gzip命令。
            // 该句代码需要注意空格
            string strcmd =
            "/usr/bin/gzip -f " + dir.m_ffilename + " 1>/dev/null 2>/dev/null";
            if (system(strcmd.c_str()) == 0) {
                cout << "压缩文件成功：" << dir.m_ffilename << "\n";
            } else {
                cout << "压缩文件失败：" << dir.m_ffilename << "\n";
            }
            // 如果压缩的文件比较大，有几个G，需要时间可能比较长，所以，增加更新心跳的代码
            pactive.uptatime();
        }
    }
    return 0;
}

void EXIT(int sig) {
    printf("程序退出，sig=%d\n", sig);
    exit(0);
}
```

