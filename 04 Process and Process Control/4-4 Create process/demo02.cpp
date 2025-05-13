#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  if (fork()>0)
  { // 父进程将执行这段代码。
    while (true)
    {
      sleep(1);
      cout << "父进程运行中...\n";
    }
  }
  else
  { // 子进程将执行这段代码。
    sleep(10);
    cout << "子进程开始执行任务...\n";
    execl("/bin/ls","/bin/ls","-lt","/tmp",nullptr);
    cout << "子进程执行任务结束，退出。\n";
  }
}

/*
编译运行：
➜  4-4 Create process git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-4 Create process git:(main) ✗ ./demo02
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
子进程开始执行任务...
/bin/ls: cannot access '/tmp/fuse': No such file or directory
total 88
-rw-rw-r-- 1 gtc  gtc   915  5月 13 20:18 dnscache.json
drwxrwxr-x 2 gtc  gtc  4096  5月 11 15:04 vscode-typescript1000
drwxr-xr-x 2 gtc  gtc  4096  5月 11 13:59 dd
drwxrwxr-x 2 gtc  gtc  4096  5月 11 11:37 gtc-code-zsh
drwxrwxr-x 2 gtc  gtc  4096  5月 10 20:21 gtc-trae-zsh
-rw-rw-r-- 1 gtc  gtc    32  5月 10 20:21 trae-region-detect.json
drwx------ 5 root root 4096  5月 10 20:19 snap-private-tmp
srw-rw-rw- 1 gtc  gtc     0  5月 10 20:18 2AACD8D5-F8BE-4993-AFE7-BADB52602FB7_slrc_plugin_manager_personal_gtc
-rw-rw-r-- 1 gtc  gtc     3  5月 10 20:18 sunlogin_run
-rw-r--r-- 1 root root  417  5月 10 20:18 sunlogin_rundaemon.log
-rw-rw-r-- 1 gtc  gtc    28  5月 10 20:18 sunlogin_variable
-rw-rw-r-- 1 gtc  gtc    18  5月 10 20:18 sunloginservertmp
drwx------ 2 root root 4096  5月 10 20:18 pulse-0A4x2EUmG78W
-rw------- 1 gtc  gtc     0  5月 10 20:18 gdm3-config-err-B1VE1G
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-colord.service-BtACAj
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-upower.service-tG8irV
-rw-rw-rw- 1 root root    0  5月 10 20:18 ToDesk_Service_HUIfj32hjjgq.lock
srw-rw-rw- 1 root root    0  5月 10 20:18 2AACD8D5-F8BE-4993-AFE7-BADB52602FB7_16308
srw-rw-rw- 1 root root    0  5月 10 20:18 2AACD8D5-F8BE-4993-AFE7-BADB52602FB7_16090
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-ModemManager.service-WqEq1E
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-systemd-logind.service-vpUhRi
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-switcheroo-control.service-zmvYPB
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-power-profiles-daemon.service-zKYvQs
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-bluetooth.service-cD2IXm
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-systemd-timesyncd.service-LhYiPK
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-systemd-resolved.service-RkC4Z4
drwx------ 3 root root 4096  5月 10 20:18 systemd-private-d66d082d97ff4deab43b64ad2f898f91-systemd-oomd.service-QJSAyL
d????????? ? ?    ?       ?             ? fuse
父进程运行中...
父进程运行中...
父进程运行中...
父进程运行中...
^Z
[4]  + 537864 suspended  ./demo02
➜  4-4 Create process git:(main) ✗ 
*/