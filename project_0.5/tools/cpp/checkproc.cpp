// 守护程序：检查共享内存中进程的心跳，如果超时，则终止进程
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

  // 打开日志文件
  clogfile logfile;  // 程序运行的日志
  if (logfile.open(argv[1]) == false) {
    printf("logfile.open(%s) failed.\n", argv[1]);
    return -1;
  }

  // 创建/获取共享内存，键值为SHMKEYP，大小为MAXNUMP个st_procinfo结构体的大小
  int shmid = 0;
  if ((shmid = shmget((key_t)SHMKEYP, MAXNUMP * sizeof(struct st_procinfo),
                      0666 | IPC_CREAT)) == -1) {
    logfile.write("创建/获取共享内存（%x）失败。\n", SHMKEYP);
    return false;
  }
  // 讲共享内存连接到当前进程的地址空间
  struct st_procinfo* shm = (struct st_procinfo*)shmat(shmid, 0, 0);

  // 遍历共享内存中全部的记录，如果进程已超时，终止它
  for (int ii = 0; ii < MAXNUMP; ii++) {
    // 如果记录的pid==0，表示空记录，continue；
    if (shm[ii].pid == 0)
      continue;
    // 如果记录的pid！=0表示是服务程序的心跳记录

    // 显示进程信息，程序稳定后，以下两行代码可以注释掉
    logfile.write("ii=%d,pid=%d,pname=%s,timeout=%d,atime=%d\n", ii,
                  shm[ii].pid, shm[ii].pname, shm[ii].timeout, shm[ii].atime);

    // 判断进程的心跳是否超时，如果超时了，就终止它
    time_t now = time(0);  // 获取当前时间
    // 如果进程未超时，continue
    if (now - shm[ii].atime < shm[ii].timeout)
      continue;
    // 如果已超时
    logfile.write("进程pid=%d（%s）已超时，将被杀死！\n", shm[ii].pid,
                  shm[ii].pname);
    // 发送信号15，终止已超时的进程
    kill(shm[ii].pid, 15);
  }
  // 把共享内存从当前进程中分离
  shmdt(shm);
  return 0;
}

/*
程序运行：
./checkproc
/home/gtc/GitHub/DataOpenPlatform/project_0.5/log/checkproc/checkproc.log
*/