#include <iostream>
using namespace std;

void show(const char *name1,const char *name2,const char *message)
{
  cout << name1 << "开始表白。\n";
  cout << name2 << "：" << message << endl;
}

int main(int argc,char *argv[],char *envp[])
{
  if (argc!=4)
  {
    cout << "表白神器程序的使用方法：./demo 追求者姓名 被追求者姓名 表白内容\n"; return -1;
  }
  cout << "表白前的准备工作一。\n";
  cout << "表白前的准备工作二。\n";
  cout << "表白前的准备工作三。\n";
  cout << "表白前的准备工作四。\n";
  cout << "表白前的准备工作五。\n";

  show(argv[1],argv[2],argv[3]);

  cout << "表白完成。\n";

  for (int ii=0;ii<10;ii++)
  {
    string str="这是第"+to_string(ii)+"个超级女生。";
    cout << str << endl;
  }

  return 0;
}

/* 
编译运行：
➜  2-6 Common commands of gdb git:(main) ✗ ls
demo01.cpp
➜  2-6 Common commands of gdb git:(main) ✗ g++ -o demo demo01.cpp -g
➜  2-6 Common commands of gdb git:(main) ✗ ls
demo  demo01.cpp
➜  2-6 Common commands of gdb git:(main) ✗ ./demo 张三 西施 我是一只傻傻鸟
表白前的准备工作一。
表白前的准备工作二。
表白前的准备工作三。
表白前的准备工作四。
表白前的准备工作五。
张三开始表白。
西施：我是一只傻傻鸟
表白完成。
这是第0个超级女生。
这是第1个超级女生。
这是第2个超级女生。
这是第3个超级女生。
这是第4个超级女生。
这是第5个超级女生。
这是第6个超级女生。
这是第7个超级女生。
这是第8个超级女生。
这是第9个超级女生。
*/

/*
gdb调试
➜  2-6 Common commands of gdb git:(main) ✗ gdb demo  
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

--Type <RET> for more, q to quit, c to continue without paging--
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from demo...
(gdb) set args 张三 西施 我是一只傻傻鸟
(gdb) b 17
Breakpoint 1 at 0x1476: file demo01.cpp, line 17.
(gdb) r
Starting program: /home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-6 Common commands of gdb/demo 张三 西施 我是一只傻傻鸟
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
表白前的准备工作一。

Breakpoint 1, main (argc=4, argv=0x7fffffffd628, envp=0x7fffffffd650) at demo01.cpp:17
warning: Source file is more recent than executable.
17        cout << "表白前的准备工作二。\n";
(gdb) n
表白前的准备工作二。
18        cout << "表白前的准备工作三。\n";
(gdb) n
表白前的准备工作三。
19        cout << "表白前的准备工作四。\n";
(gdb) n
表白前的准备工作四。
20        cout << "表白前的准备工作五。\n";
(gdb) b 23
Breakpoint 2 at 0x55555555550f: file demo01.cpp, line 24.
(gdb) c
Continuing.
表白前的准备工作五。
张三开始表白。
西施：我是一只傻傻鸟

Breakpoint 2, main (argc=4, argv=0x7fffffffd628, envp=0x7fffffffd650) at demo01.cpp:24
24        cout << "表白完成。\n";
(gdb) s
表白完成。
26        for (int ii=0;ii<10;ii++)
(gdb) p name1
No symbol "name1" in current context.
(gdb) p name2
No symbol "name2" in current context.
(gdb) p ii
$1 = 0
*/