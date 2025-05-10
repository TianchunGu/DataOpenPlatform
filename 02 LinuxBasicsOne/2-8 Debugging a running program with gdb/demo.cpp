#include <unistd.h>
#include <iostream>
using namespace std;

void bb(const int bh,const string xm)
{
  for (int ii=0;ii<1000000;ii++)
  {
    sleep(1);
    cout << "ii=" << ii << endl;
  }
}

void aa(const int no,const string name)
{
  bb(3,"冰冰");
}

int main()
{
  aa(8,"西施");

  return 0;
}

/*获取进程编号
➜  DataOpenPlatform git:(main) ✗ ps -ef |grep demo
gtc        71148   16323  0 21:40 pts/0    00:00:00 ./demo
gtc        71869   71268  0 21:41 pts/2    00:00:00 grep --color=auto --exclude-dir=.bzr --exclude-dir=CVS --exclude-dir=.git --exclude-dir=.hg --exclude-dir=.svn --exclude-dir=.idea --exclude-dir=.tox --exclude-dir=.venv --exclude-dir=venv demo
➜  DataOpenPlatform git:(main) ✗ gdb demo -p 71148  
*/

//被调试的程序将会自动停止

/*
调试需要提高权限
➜  DataOpenPlatform git:(main) ✗ sudo gdb demo -p 71148
Alias tip: _ gdb demo -p 71148
[sudo] password for gtc: 
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
demo: No such file or directory.
Attaching to process 71148
Reading symbols from /home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-8 Debugging a running program with gdb/demo...
Reading symbols from /lib/x86_64-linux-gnu/libstdc++.so.6...
(No debugging symbols found in /lib/x86_64-linux-gnu/libstdc++.so.6)
Reading symbols from /lib/x86_64-linux-gnu/libgcc_s.so.1...
(No debugging symbols found in /lib/x86_64-linux-gnu/libgcc_s.so.1)
Reading symbols from /lib/x86_64-linux-gnu/libc.so.6...
Reading symbols from /usr/lib/debug/.build-id/cd/410b710f0f094c6832edd95931006d883af48e.debug...
Reading symbols from /lib/x86_64-linux-gnu/libm.so.6...
Reading symbols from /usr/lib/debug/.build-id/7d/8778fca8ea4621b268cc03662855d0cd983439.debug...
Reading symbols from /lib64/ld-linux-x86-64.so.2...
Reading symbols from /usr/lib/debug/.build-id/e4/de036b19e4768e7591b596c4be9f9015f2d28a.debug...
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGTSTP, Stopped (user).
0x00007fc4d5ce578a in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=req@entry=0x7ffd3c7351c0, rem=rem@entry=0x7ffd3c7351c0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
78      ../sysdeps/unix/sysv/linux/clock_nanosleep.c: No such file or directory.
(gdb) bt
#0  0x00007fc4d5ce578a in __GI___clock_nanosleep (clock_id=clock_id@entry=0, 
    flags=flags@entry=0, req=req@entry=0x7ffd3c7351c0, 
    rem=rem@entry=0x7ffd3c7351c0)
    at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007fc4d5cea677 in __GI___nanosleep (req=req@entry=0x7ffd3c7351c0, 
    rem=rem@entry=0x7ffd3c7351c0) at ../sysdeps/unix/sysv/linux/nanosleep.c:25
#2  0x00007fc4d5cea5ae in __sleep (seconds=0) at ../sysdeps/posix/sleep.c:55
#3  0x000060694653448f in bb (bh=3, xm="冰冰") at demo.cpp:9
#4  0x0000606946534535 in aa (no=8, name="西施") at demo.cpp:16
#5  0x00006069465345f0 in main () at demo.cpp:21
*/