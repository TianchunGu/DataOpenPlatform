## <font style="color:black;">Linux的信号</font>
### <font style="color:black;">信号的基本概念 </font>
<font style="color:black;background-color:#FFFFFF;">信号（signal）是软件中断，是进程之间相互传递消息的一种方法，用于通知进程发生了事件，但是，不能给进程传递任何数据。</font>

<font style="color:black;background-color:#FFFFFF;">信号产生的原因有很多，在Shell中，可以用</font><font style="color:#002060;background-color:#d9d9d9;">kill</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">killall</font><font style="color:black;background-color:#FFFFFF;">命令发送信号：</font>

```cpp
kill -信号的类型 进程编号
killall -信号的类型 进程名
```

```cpp
//案例
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  int num = 0;
  while (true){
    cout<<"执行了"<<++num<<"次任务"<<endl;
    sleep(1);
  }
  return 0;
}

/*
第一个窗口编译运行：
➜  4-1 Signals of Linux git:(main) ✗ ls
demo01.cpp
➜  4-1 Signals of Linux git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  4-1 Signals of Linux git:(main) ✗ ls
demo01  demo01.cpp
➜  4-1 Signals of Linux git:(main) ✗ ./demo01      
执行了1次任务
执行了2次任务
执行了3次任务
执行了4次任务
执行了5次任务
执行了6次任务
执行了7次任务
执行了8次任务
执行了9次任务
执行了10次任务
执行了11次任务
执行了12次任务
执行了13次任务
执行了14次任务
执行了15次任务
执行了16次任务
执行了17次任务
执行了18次任务
执行了19次任务
执行了20次任务
执行了21次任务
执行了22次任务
[3]    430507 terminated  ./demo01

第二个窗口杀死进程：
➜  DataOpenPlatform git:(main) ✗ killall demo01

可以使用-指定信号种类
➜  DataOpenPlatform git:(main) ✗ killall -15 demo01 

*/
```

![](https://cdn.nlark.com/yuque/0/2025/gif/33636091/1747142782152-13f842f1-6dbc-42b9-adde-33cc8c1a5161.gif)

### <font style="color:black;">信号的类型 </font>
| <font style="color:black;background-color:#FFFFFF;">信号名</font> | <font style="color:black;background-color:#FFFFFF;">信号值</font> | <font style="color:black;background-color:#FFFFFF;">默认处理动作</font> | <font style="color:black;background-color:#FFFFFF;">发出信号的原因</font> |
| :--- | --- | --- | :--- |
| <font style="color:black;background-color:#FFFFFF;">SIGHUP</font> | <font style="color:black;background-color:#FFFFFF;">1</font> | <font style="color:black;background-color:#FFFFFF;">A</font> | <font style="color:black;background-color:#FFFFFF;">终端挂起或者控制进程终止</font> |
| **<font style="color:black;background-color:#FFFFFF;">SIGINT</font>** | **<font style="color:black;background-color:#FFFFFF;">2</font>** | **<font style="color:black;background-color:#FFFFFF;">A</font>** | **<font style="color:black;background-color:#FFFFFF;">键盘中断</font>****<font style="color:black;background-color:#FFFFFF;">Ctrl+c</font>** |
| <font style="color:black;background-color:#FFFFFF;">SIGQUIT</font> | <font style="color:black;background-color:#FFFFFF;">3</font> | <font style="color:black;background-color:#FFFFFF;">C</font> | <font style="color:black;background-color:#FFFFFF;">键盘的退出键被按下</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGILL</font> | <font style="color:black;background-color:#FFFFFF;">4</font> | <font style="color:black;background-color:#FFFFFF;">C</font> | <font style="color:black;background-color:#FFFFFF;">非法指令</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGABRT</font> | <font style="color:black;background-color:#FFFFFF;">6</font> | <font style="color:black;background-color:#FFFFFF;">C</font> | <font style="color:black;background-color:#FFFFFF;">由</font><font style="color:black;background-color:#FFFFFF;">abort(3)</font><font style="color:black;background-color:#FFFFFF;">发出的退出指令</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGFPE</font> | <font style="color:black;background-color:#FFFFFF;">8</font> | <font style="color:black;background-color:#FFFFFF;">C</font> | <font style="color:black;background-color:#FFFFFF;">浮点异常</font> |
| **<font style="color:black;background-color:#FFFFFF;">SIGKILL</font>** | **<font style="color:black;background-color:#FFFFFF;">9</font>** | **<font style="color:black;background-color:#FFFFFF;">AEF</font>** | **<font style="color:black;background-color:#FFFFFF;">采用</font>****<font style="color:black;background-color:#FFFFFF;">kill -9 </font>****<font style="color:black;background-color:#FFFFFF;">进程编号 强制杀死程序。</font>** |
| **<font style="color:black;background-color:#FFFFFF;">SIGSEGV</font>** | **<font style="color:black;background-color:#FFFFFF;">11</font>** | **<font style="color:black;background-color:#FFFFFF;">CEF</font>** | **<font style="color:black;background-color:#FFFFFF;">无效的内存引用（数组越界、操作空指针和野指针等）。</font>** |
| <font style="color:black;background-color:#FFFFFF;">SIGPIPE</font> | <font style="color:black;background-color:#FFFFFF;">13</font> | <font style="color:black;background-color:#FFFFFF;">A</font> | <font style="color:black;background-color:#FFFFFF;">管道破裂，写一个没有读端口的管道。</font> |
| **<font style="color:black;background-color:#FFFFFF;">SIGALRM</font>** | **<font style="color:black;background-color:#FFFFFF;">14</font>** | **<font style="color:black;background-color:#FFFFFF;">A</font>** | **<font style="color:black;background-color:#FFFFFF;">由闹钟</font>****<font style="color:black;background-color:#FFFFFF;">alarm()</font>****<font style="color:black;background-color:#FFFFFF;">函数发出的信号。</font>** |
| **<font style="color:black;background-color:#FFFFFF;">SIGTERM</font>** | **<font style="color:black;background-color:#FFFFFF;">15</font>** | **<font style="color:black;background-color:#FFFFFF;">A</font>** | **<font style="color:black;background-color:#FFFFFF;">采用“</font>****<font style="color:black;background-color:#FFFFFF;">kill </font>****<font style="color:black;background-color:#FFFFFF;">进程编号”或“</font>****<font style="color:black;background-color:#FFFFFF;">killall </font>****<font style="color:black;background-color:#FFFFFF;">程序名”通知程序。</font>** |
| <font style="color:black;background-color:#FFFFFF;">SIGUSR1</font> | <font style="color:black;background-color:#FFFFFF;">10</font> | <font style="color:black;background-color:#FFFFFF;">A</font> | <font style="color:black;background-color:#FFFFFF;">用户自定义信号</font><font style="color:black;background-color:#FFFFFF;">1</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGUSR2</font> | <font style="color:black;background-color:#FFFFFF;">12</font> | <font style="color:black;background-color:#FFFFFF;">A</font> | <font style="color:black;background-color:#FFFFFF;">用户自定义信号</font><font style="color:black;background-color:#FFFFFF;">2</font> |
| **<font style="color:black;background-color:#FFFFFF;">SIGCHLD</font>** | **<font style="color:black;background-color:#FFFFFF;">17</font>** | **<font style="color:black;background-color:#FFFFFF;">B</font>** | **<font style="color:black;background-color:#FFFFFF;">子进程结束信号</font>** |
| <font style="color:black;background-color:#FFFFFF;">SIGCONT</font> | <font style="color:black;background-color:#FFFFFF;">18</font> |  | <font style="color:black;background-color:#FFFFFF;">进程继续（曾被停止的进程）</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGSTOP</font> | <font style="color:black;background-color:#FFFFFF;">19</font> | <font style="color:black;background-color:#FFFFFF;">DEF</font> | <font style="color:black;background-color:#FFFFFF;">终止进程</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGTSTP</font> | <font style="color:black;background-color:#FFFFFF;">20</font> | <font style="color:black;background-color:#FFFFFF;">D</font> | <font style="color:black;background-color:#FFFFFF;">控制终端（</font><font style="color:black;background-color:#FFFFFF;">tty</font><font style="color:black;background-color:#FFFFFF;">）上按下停止键</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGTTIN</font> | <font style="color:black;background-color:#FFFFFF;">21</font> | <font style="color:black;background-color:#FFFFFF;">D</font> | <font style="color:black;background-color:#FFFFFF;">后台进程企图从控制终端读</font> |
| <font style="color:black;background-color:#FFFFFF;">SIGTTOU</font> | <font style="color:black;background-color:#FFFFFF;">22</font> | <font style="color:black;background-color:#FFFFFF;">D</font> | <font style="color:black;background-color:#FFFFFF;">后台进程企图从控制终端写</font> |
| <font style="color:black;background-color:#FFFFFF;">其它</font> | <font style="color:black;background-color:#FFFFFF;"><=64</font> | <font style="color:black;background-color:#FFFFFF;">A</font> | <font style="color:black;background-color:#FFFFFF;">自定义信号</font> |


<font style="color:black;background-color:#FFFFFF;">处理动作一项中的字母含义如下：</font>

<font style="color:black;background-color:#FFFFFF;">A </font><font style="color:black;background-color:#FFFFFF;">缺省的动作是终止进程。</font>

<font style="color:black;background-color:#FFFFFF;">B </font><font style="color:black;background-color:#FFFFFF;">缺省的动作是忽略此信号，将该信号丢弃，不做处理。</font>

<font style="color:black;background-color:#FFFFFF;">C </font><font style="color:black;background-color:#FFFFFF;">缺省的动作是终止进程并进行内核映像转储（</font><font style="color:black;background-color:#FFFFFF;">core dump</font><font style="color:black;background-color:#FFFFFF;">）。</font>

<font style="color:black;background-color:#FFFFFF;">D </font><font style="color:black;background-color:#FFFFFF;">缺省的动作是停止进程，进入停止状态的程序还能重新继续，一般是在调试的过程中。</font>

<font style="color:black;background-color:#FFFFFF;">E </font><font style="color:black;background-color:#FFFFFF;">信号不能被捕获。</font>

<font style="color:black;background-color:#FFFFFF;">F 信号不能被忽略。</font>

### <font style="color:black;">信号的处理</font>
<font style="color:black;background-color:#FFFFFF;">进程对信号的处理方法有三种：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）对该信号的处理采用系统的默认操作，大部分的信号的默认操作是终止进程。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）设置信号的处理函数，收到信号后，由该函数来处理。</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）忽略某个信号，对该信号不做任何处理，就像未发生过一样。</font>

<font style="color:#002060;background-color:#d9d9d9;">signal()</font><font style="color:black;background-color:#FFFFFF;">函数可以设置程序对信号的处理方式。</font>

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
sighandler_t signal(int signum, sighandler_t handler);
```

<font style="color:black;background-color:#FFFFFF;">参数</font><font style="color:#002060;background-color:#d9d9d9;">signum</font><font style="color:black;background-color:#FFFFFF;">表示信号的编号（信号的值）。</font>

<font style="color:black;background-color:#FFFFFF;">参数</font><font style="color:#002060;background-color:#d9d9d9;">handler</font><font style="color:black;background-color:#FFFFFF;">表示信号的处理方式，有三种情况：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">SIG_DFL</font><font style="color:black;background-color:#FFFFFF;">：恢复参数</font><font style="color:black;background-color:#FFFFFF;">signum</font><font style="color:black;background-color:#FFFFFF;">信号的处理方法为默认行为。</font><font style="color:black;background-color:#FFFFFF;"> </font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）一个自定义的处理信号的函数，函数的形参是信号的编号。</font>

<font style="color:black;background-color:#FFFFFF;">3）SIG_IGN：忽略参数signum所指的信号。</font>

### <font style="color:black;">信号有什么用</font>
<font style="color:black;background-color:#FFFFFF;">服务程序运行在后台，如果想让中止它，杀掉不是个好办法，因为进程被杀的时候，是突然死亡，没有安排善后工作。</font>

<font style="color:black;background-color:#FFFFFF;">如果向服务程序发送一个信号，服务程序收到信号后，调用一个函数，在函数中编写善后的代码，程序就可以有计划的退出。</font>

<font style="color:black;background-color:#FFFFFF;">如果向服务程序发送0的信号，可以检测程序是否存活。</font>

### <font style="color:black;">信号应用示例</font>
```cpp
// 闹钟信号
#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void func(int signal){
  cout<<"alarm"<<"执行了"<<signal<<"信号"<<endl;
  alarm(5);//5秒后发送SIGALRM信号（14的信号），若不添加该行代码，闹钟只会响一次
}

int main(){
  int num = 0;
  alarm(5);//5秒后发送SIGALRM信号（14的信号）
  signal(SIGALRM,func);//设置定时任务函数等价于signal(14,func);
  while (true){
    cout<<"执行了"<<++num<<"次任务"<<endl;
    sleep(1);
  }
  return 0;
}

/*
编译运行：
➜  4-1 Signals of Linux git:(main) ✗ g++ -o alarm alarm.cpp -g
➜  4-1 Signals of Linux git:(main) ✗ ls
alarm  alarm.cpp  demo01  demo01.cpp
➜  4-1 Signals of Linux git:(main) ✗ ./alarm 
执行了1次任务
执行了2次任务
执行了3次任务
执行了4次任务
执行了5次任务
alarm执行了14信号
执行了6次任务
执行了7次任务
执行了8次任务
执行了9次任务
执行了10次任务
alarm执行了14信号
执行了11次任务
执行了12次任务
执行了13次任务
执行了14次任务
执行了15次任务
[3]    449370 terminated  ./alarm
➜  4-1 Signals of Linux git:(main) ✗ 
*/
```

![](https://cdn.nlark.com/yuque/0/2025/gif/33636091/1747143825787-709f1194-63f3-48a1-867a-cc6ab5985abf.gif)

```cpp
#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void EXIT(int sig)
{
  cout << "收到了信号：" << sig << endl;
  cout << "正在释放资源，程序将退出......\n";

  // 以下是释放资源的代码。

  cout << "程序退出。\n";
  exit(0);  // 进程退出。
}

int main(int argc,char *argv[])
{
  // 忽略全部的信号，防止程序被信号异常中止。
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);

  // 如果收到2和15的信号（Ctrl+c和kill、killall），本程序将主动退出。
  signal(2,EXIT);  signal(15,EXIT);

  while (true)
  {
    cout << "执行了一次任务。\n";
    sleep(1);
  }
}

/*
编译运行：
➜  4-1 Signals of Linux git:(main) ✗ g++ -o theFunctionOfTheSignal theFunctionOfTheSignal.cpp -g
➜  4-1 Signals of Linux git:(main) ✗ ls
alarm  alarm.cpp  demo01  demo01.cpp  theFunctionOfTheSignal  theFunctionOfTheSignal.cpp
➜  4-1 Signals of Linux git:(main) ✗ ./theFunctionOfTheSignal
执行了一次任务。
执行了一次任务。
执行了一次任务。
执行了一次任务。
执行了一次任务。
执行了一次任务。
收到了信号：15
正在释放资源，程序将退出......
程序退出。
*/
```

![](https://cdn.nlark.com/yuque/0/2025/gif/33636091/1747144182053-861be20d-d80c-46da-866b-8119c102bc81.gif)

### <font style="color:black;">发送信号</font>
<font style="color:black;background-color:#FFFFFF;">Linux操作系统提供了</font><font style="color:#002060;background-color:#d9d9d9;">kill</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">killall</font><font style="color:black;background-color:#FFFFFF;">命令向进程发送信号，在程序中，可以用</font><font style="color:#002060;background-color:#d9d9d9;">kill()</font><font style="color:black;background-color:#FFFFFF;">函数向其它进程发送信号。</font>

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int kill(pid_t pid, int sig);
```

<font style="color:#002060;background-color:#d9d9d9;">kill()</font><font style="color:black;background-color:#FFFFFF;">函数将参数</font><font style="color:#002060;background-color:#d9d9d9;">sig</font><font style="color:black;background-color:#FFFFFF;">指定的信号给参数</font><font style="color:#002060;background-color:#d9d9d9;">pid</font><font style="color:black;background-color:#FFFFFF;">指定的进程。</font>

<font style="color:black;background-color:#FFFFFF;">参数</font><font style="color:#002060;background-color:#d9d9d9;">pid</font><font style="color:black;background-color:#FFFFFF;">有几种情况：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">pid>0 </font><font style="color:black;background-color:#FFFFFF;">将信号传给进程号为</font><font style="color:black;background-color:#FFFFFF;">pid </font><font style="color:black;background-color:#FFFFFF;">的进程。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">pid=0 </font><font style="color:black;background-color:#FFFFFF;">将信号传给和当前进程相同进程组的所有进程，常用于父进程给子进程发送信号，注意，发送信号者进程也会收到自己发出的信号。</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">pid=-1 </font><font style="color:black;background-color:#FFFFFF;">将信号广播传送给系统内所有的进程，例如系统关机时，会向所有的登录窗口广播关机信息。</font>

<font style="color:black;background-color:#FFFFFF;">sig</font><font style="color:black;background-color:#FFFFFF;">：准备发送的信号代码，假如其值为</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">则没有任何信号送出，但是系统会执行错误检查，通常会利用</font><font style="color:black;background-color:#FFFFFF;">sig</font><font style="color:black;background-color:#FFFFFF;">值为零来检验某个进程是否仍在运行。</font>

<font style="color:black;background-color:#FFFFFF;">返回值说明： 成功执行时，返回0；失败返回-1，errno被设置。</font>

### <font style="color:black;">进程终止</font>
<font style="color:black;background-color:#FFFFFF;">有</font><font style="color:black;background-color:#FFFFFF;">8</font><font style="color:black;background-color:#FFFFFF;">种方式可以中止进程，其中</font><font style="color:black;background-color:#FFFFFF;">5</font><font style="color:black;background-color:#FFFFFF;">种为正常终止，它们是：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）在</font><font style="color:#002060;background-color:#d9d9d9;">main()</font><font style="color:black;background-color:#FFFFFF;">函数用</font><font style="color:#002060;background-color:#d9d9d9;">return</font><font style="color:black;background-color:#FFFFFF;">返回；</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）在任意函数中调用</font><font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">函数；</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）在任意函数中调用</font><font style="color:#002060;background-color:#d9d9d9;">_exit()</font><font style="color:black;background-color:#FFFFFF;">或</font><font style="color:#002060;background-color:#d9d9d9;">_Exit()</font><font style="color:black;background-color:#FFFFFF;">函数；</font>

<font style="color:black;background-color:#FFFFFF;">4</font><font style="color:black;background-color:#FFFFFF;">）最后一个线程从其启动例程（线程主函数）用</font><font style="color:#002060;background-color:#d9d9d9;">return</font><font style="color:black;background-color:#FFFFFF;">返回；</font>

<font style="color:black;background-color:#FFFFFF;">5</font><font style="color:black;background-color:#FFFFFF;">）在最后一个线程中调用</font><font style="color:#002060;background-color:#d9d9d9;">pthread_exit()</font><font style="color:black;background-color:#FFFFFF;">返回；</font>

<font style="color:black;background-color:#FFFFFF;">异常终止有</font><font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">种方式，它们是：</font>

<font style="color:black;background-color:#FFFFFF;">6</font><font style="color:black;background-color:#FFFFFF;">）调用</font><font style="color:#002060;background-color:#d9d9d9;">abort()</font><font style="color:black;background-color:#FFFFFF;">函数中止；</font>

<font style="color:black;background-color:#FFFFFF;">7</font><font style="color:black;background-color:#FFFFFF;">）接收到一个信号；</font>

<font style="color:black;background-color:#FFFFFF;">8）最后一个线程对取消请求做出响应。</font>

```cpp
// 案例
#include <iostream>
using namespace std;

void func2(){
  cout<<"调用了func2"<<endl;
  // exit(0);
  return;
}

void func1(){
  cout<<"调用了func1"<<endl;
  func2();
  cout<<"回到了func1函数"<<endl;
}
int main(){
  func1();
  cout<<"回到了main函数"<<endl;
  return 0;
}

/*
编译运行：
1. func2中调用exit(0);
➜  4-2 Process termination git:(main) ✗ ls
demo01.cpp
➜  4-2 Process termination git:(main) ✗ g++ -o demo01 demo01.cpp                                   
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp
➜  4-2 Process termination git:(main) ✗ ./demo01                
调用了func1
调用了func2
2. func2中调用return;
➜  4-2 Process termination git:(main) ✗ ls
demo01.cpp
➜  4-2 Process termination git:(main) ✗ g++ -o demo01 demo01.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp
➜  4-2 Process termination git:(main) ✗ ./demo01      
调用了func1
调用了func2
回到了func1函数
回到了main函数
*/
```

#### <font style="color:black;">进程终止的状态</font>
<font style="color:black;background-color:#FFFFFF;">在</font><font style="color:#002060;background-color:#d9d9d9;">main()</font><font style="color:black;background-color:#FFFFFF;">函数中，</font><font style="color:#002060;background-color:#d9d9d9;">return</font><font style="color:black;background-color:#FFFFFF;">的返回值即终止状态，如果没有</font><font style="color:#002060;background-color:#d9d9d9;">return</font><font style="color:black;background-color:#FFFFFF;">语句或调用</font><font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">，那么该进程的终止状态是</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">在</font><font style="color:black;background-color:#FFFFFF;">Shell</font><font style="color:black;background-color:#FFFFFF;">中，查看进程终止的状态：</font><font style="color:#002060;background-color:#d9d9d9;">echo $?</font>

<font style="color:black;background-color:#FFFFFF;">正常终止进程的3个函数（</font><font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">_Exit()</font><font style="color:black;background-color:#FFFFFF;">是由ISO C说明的，</font><font style="color:#002060;background-color:#d9d9d9;">_exit()</font><font style="color:black;background-color:#FFFFFF;">是由POSIX说明的）。</font>

```cpp
void exit(int status);
void _exit(int status);
void _Exit(int status);
```

<font style="color:#002060;background-color:#d9d9d9;">status</font><font style="color:black;background-color:#FFFFFF;">也是进程终止的状态。</font>

<font style="color:black;background-color:#FFFFFF;">如果进程被异常终止，终止状态为非0。  服务程序的调度、日志和监控。</font>

```cpp
// 该代码展示进程终止的状态
#include <iostream>
using namespace std;

int main(){

  // return 0;
  // return 1;
  exit(2);
}

/*
编译运行：
1. main函数中return 0;
➜  4-2 Process termination git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-2 Process termination git:(main) ✗ ./demo02      
➜  4-2 Process termination git:(main) ✗ echo $?
0
2.main函数中return 1;
➜  4-2 Process termination git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-2 Process termination git:(main) ✗ ./demo02
➜  4-2 Process termination git:(main) ✗ echo $?                 
1
3.main函数中调用exit(2);
➜  4-2 Process termination git:(main) ✗ g++ -o demo02 demo02.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  4-2 Process termination git:(main) ✗ ./demo02
➜  4-2 Process termination git:(main) ✗ echo $?                 
2
*/
```

#### <font style="color:black;">资源释放的问题</font>
<font style="color:#002060;background-color:#d9d9d9;">retun</font><font style="color:black;background-color:#FFFFFF;">表示函数返回，会调用局部对象的析构函数，</font><font style="color:#002060;background-color:#d9d9d9;">main()</font><font style="color:black;background-color:#FFFFFF;">函数中的</font><font style="color:#002060;background-color:#d9d9d9;">return</font><font style="color:black;background-color:#FFFFFF;">还会调用全局对象的析构函数。</font>

**<font style="color:#002060;background-color:#d9d9d9;">exit()</font>****<font style="color:black;background-color:#FFFFFF;">表示终止进程，不会调用局部对象的</font>**[<font style="background-color:#FFFFFF;">析构函数</font>](https://so.csdn.net/so/search?q=%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0&spm=1001.2101.3001.7020)**<font style="color:black;background-color:#FFFFFF;">，只调用全局对象的析构函数。</font>**

<font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">会执行清理工作，然后退出，</font><font style="color:#002060;background-color:#d9d9d9;">_exit()</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">_Exit()</font><font style="color:black;background-color:#FFFFFF;">直接退出，不会执行任何清理工作。</font>

```cpp
#include <iostream>
#include <unistd.h>
using namespace std;

struct AA{
  string name;//用于区分不同的对象
  AA(const string &name):name(name){}
  ~AA(){
    cout<<name<<"调用了析构函数"<<endl;
  }
};

AA a1("全局对象a1");

int main(){
  AA a2("局部对象a2");
  // return 0;
  // exit(0);
  _exit(0);
}

/*
编译运行：
1. main函数中return 0;
➜  4-2 Process termination git:(main) ✗ g++ -o resourceRelease resourceRelease.cpp 
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  resourceRelease  resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ./resourceRelease 
局部对象a2调用了析构函数
全局对象a1调用了析构函数
2. main函数中exit(0);
➜  4-2 Process termination git:(main) ✗ g++ -o resourceRelease resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  resourceRelease  resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ./resourceRelease 
全局对象a1调用了析构函数
3. main函数中_exit(0);
➜  4-2 Process termination git:(main) ✗ g++ -o resourceRelease resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp  resourceRelease  resourceRelease.cpp
➜  4-2 Process termination git:(main) ✗ ./resourceRelease
➜  4-2 Process termination git:(main) ✗ 
*/
```

#### <font style="color:black;">进程的终止函数</font>
<font style="color:black;background-color:#FFFFFF;">进程可以用</font><font style="color:#002060;background-color:#d9d9d9;">atexit()</font><font style="color:black;background-color:#FFFFFF;">函数登记终止函数（最多32个），这些函数将由</font><font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">自动调用。</font>

```cpp
int atexit(void (*function)(void));
```

<font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">调用终止函数的顺序与登记时相反。 进程退出前的收尾工作</font>

## <font style="color:black;">调用可执行程序</font>
<font style="color:black;background-color:#FFFFFF;">Linux提供了</font><font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数和</font><font style="color:#002060;background-color:#d9d9d9;">exec</font><font style="color:black;background-color:#FFFFFF;">函数族，在C++程序中，可以执行其它的程序（二进制文件、操作系统命令或Shell脚本）。</font>

### <font style="color:black;">system()函数</font>
<font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数提供了一种简单的执行程序的方法，把需要执行的程序和参数用一个字符串传给</font><font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数就行了。</font>

<font style="color:black;background-color:#FFFFFF;">函数的声明：</font>

```cpp
int system(const char * string);
```

<font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数的返回值比较麻烦。</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）如果执行的程序不存在，</font><font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数返回非</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">；</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）如果执行程序成功，并且被执行的程序终止状态是</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数返回</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">；</font>

<font style="color:black;background-color:#FFFFFF;">3）如果执行程序成功，并且被执行的程序终止状态不是0，</font><font style="color:#002060;background-color:#d9d9d9;">system()</font><font style="color:black;background-color:#FFFFFF;">函数返回非0。</font>

```cpp
// 案例
#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  // int ret=system("/bin/ls -| /temp");//使用全路径可避免环境变量的问题
  // 在路径两侧添加引号，解决路径中空格的问题
  int ret=system("\"/home/gtc/GitHub/DataOpenPlatform/04 Process and Process Control/4-2 Process termination/demo01\"");
  cout << "ret=" << ret << endl;
  perror("system");
}

/*
编译运行：
1.int ret=system("/bin/ls -| /temp");
➜  4-3 Call the executable program git:(main) ✗ g++ -o demo01 demo01.cpp   
➜  4-3 Call the executable program git:(main) ✗ ls
demo01  demo01.cpp
➜  4-3 Call the executable program git:(main) ✗ ./demo01      
sh: 1: /temp: not found
/bin/ls: cannot access '-': No such file or directory
ret=32512
system: Success
2.int ret=system("/home/gtc/GitHub/DataOpenPlatform/04 Process and Process Control/4-2 Process termination/demo01");
➜  4-3 Call the executable program git:(main) ✗ g++ -o demo01 demo01.cpp
➜  4-3 Call the executable program git:(main) ✗ ./demo01
调用了func1
调用了func2
回到了func1函数
回到了main函数
ret=0
system: Success
*/
```

### <font style="color:black;">exec函数族</font>
<font style="color:black;background-color:#FFFFFF;">exec</font><font style="color:black;background-color:#FFFFFF;">函数族提供了另一种在进程中调用程序（二进制文件或</font><font style="color:black;background-color:#FFFFFF;">Shell</font><font style="color:black;background-color:#FFFFFF;">脚本）的方法。</font>

<font style="color:black;background-color:#FFFFFF;">exec函数族的声明如下：</font>

```cpp
int execl(const char *path, const char *arg, ...);//重点
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg,...,char * const envp[]);
int execv(const char *path, char *const argv[]);//重点
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],char *const envp[]);
```

<font style="color:black;background-color:#FFFFFF;">注意：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）如果执行程序失败则直接返回</font><font style="color:black;background-color:#FFFFFF;">-1</font><font style="color:black;background-color:#FFFFFF;">，失败原因存于</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">中。</font>

<font style="color:black;background-color:#FFFFFF;">2）</font><font style="color:black;background-color:#E8F7CF;">新进程的进程编号与原进程相同</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:black;background-color:#FBF5CB;">但是，新进程取代了原进程的代码段、数据段和堆栈</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">3）如果执行成功则函数不会返回，当在主程序中成功调用exec后，被调用的程序将取代调用者程序，也就是说，</font><font style="color:#DF2A3F;background-color:#FBF5CB;">exec函数之后的代码都不会被执行</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">4</font><font style="color:black;background-color:#FFFFFF;">）在实际开发中，最常用的是</font><font style="color:#002060;background-color:#d9d9d9;">execl()</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">execv()</font><font style="color:black;background-color:#FFFFFF;">，其它的极少使用。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  int ret=execl("/bin/ls","/bin/ls","-lt","/tmp",nullptr);  // 最后一个参数0不能省略。使用全路径可避免环境变量的问题
  cout << "ret=" << ret << endl;
  perror("execl");

  /*
  char *args[10];
  args[0]=(char *)"/bin/ls";
  args[1]=(char *)"-lt";
  args[2]=(char *)"/tmp";
  args[3]=0;     // 这行代码不能省略。

  int ret=execv("/bin/ls",args);
  cout << "ret=" << ret << endl;
  perror("execv");
  */
}

/*
编译 运行：
➜  4-3 Call the executable program git:(main) ✗ g++ -o execl execl.cpp
➜  4-3 Call the executable program git:(main) ✗ ./execl 
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
➜  4-3 Call the executable program git:(main) ✗ 
*/
```

## <font style="color:black;">创建进程</font>
### <font style="color:black;">Linux的0、1和2号进程</font>
<font style="color:black;background-color:#FFFFFF;">整个</font><font style="color:black;background-color:#FFFFFF;">linux</font><font style="color:black;background-color:#FFFFFF;">系统全部的进程是一个树形结构。</font>

<font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">号进程（系统进程）是所有进程的祖先，它创建了</font><font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">号和</font><font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">号进程。</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">号进程（</font><font style="color:black;background-color:#FFFFFF;">systemd</font><font style="color:black;background-color:#FFFFFF;">）负责执行内核的初始化工作和进行系统配置。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">号进程（</font><font style="color:black;background-color:#FFFFFF;">kthreadd</font><font style="color:black;background-color:#FFFFFF;">）负责所有内核线程的调度和管理。</font>

<font style="color:black;background-color:#FFFFFF;">用</font><font style="color:#002060;background-color:#d9d9d9;">pstree</font><font style="color:black;background-color:#FFFFFF;">命令可以查看进程树（</font><font style="color:#002060;background-color:#d9d9d9;">yum -y install psmisc</font><font style="color:black;background-color:#FFFFFF;">）。</font>

<font style="color:#002060;background-color:#d9d9d9;">pstree -p 进程编号</font>

### <font style="color:black;">进程标识</font>
<font style="color:black;background-color:#FFFFFF;">每个进程都有一个非负整数表示的唯一的进程ID。虽然是唯一的，但是进程ID可以复用。当一个进程终止后，其进程ID就成了复用的候选者。Linux采用延迟复用算法，让新建进程的ID不同于最近终止的进程所使用的ID。这样防止了新进程被误认为是使用了同一ID的某个已终止的进程。</font>

```cpp
pid_t getpid(void);     // 获取当前进程的ID。
pid_t getppid(void);    // 获取父进程的ID。
```

### <font style="color:black;">fork()函数</font>
<font style="color:black;background-color:#FFFFFF;">一个现有的进程可以调用</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">函数创建一个新的进程。</font>

```cpp
pid_t fork(void);
```

<font style="color:black;background-color:#FFFFFF;">由</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">创建的新进程被称为子进程。子进是父进程的副本，父进程和子进程都从调用</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">之后的代码开始执行。</font>

<font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">函数被调用一次，但返回两次。两次返回的区别是子进程的返回值是</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">，而父进程的返回值则是子进程的进程</font><font style="color:black;background-color:#FFFFFF;">ID</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">子进程获得了父进程数据空间、堆和栈的副本（</font>**<font style="color:black;background-color:#FFFFFF;">注意：子进程拥有的是副本，不是和父进程共享</font>**<font style="color:black;background-color:#FFFFFF;">）。</font>

<font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">之后，父进程和子进程的执行顺序是不确定的。</font>

```cpp
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  int bh=8;
  string message="我是一只傻傻鸟。";

  pid_t pid=fork();

  if (pid>0)
  { // 父进程将执行这段代码。
    sleep(1);// 等待子进程先执行。
    cout << "父：pid=" << pid << endl;
    cout << "父：亲爱的" << bh << "号：" << message << endl;
  }
  else
  { // 子进程将执行这段代码。
    bh=3; message="你是一只傻傻鸟。";
    cout << "子：pid=" << pid << endl;
    cout << "子：亲爱的" << bh << "号：" << message << endl;
  }
}

/*  
编译运行：
➜  4-4 Create process git:(main) ✗ ls
demo01.cpp
➜  4-4 Create process git:(main) ✗ g++ -o demo01 demo01.cpp   
➜  4-4 Create process git:(main) ✗ ./demo01      
子：pid=0
子：亲爱的3号：你是一只傻傻鸟。
父：pid=532013
父：亲爱的8号：我是一只傻傻鸟。
*/
```

### <font style="color:black;">fork()的两种用法</font>
<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）父进程复制自己，然后，父进程和子进程分别执行不同的代码。这种用法在网络服务程序中很常见，父进程等待客户端的连接请求，当请求到达时，父进程调用</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">，让子进程处理些请求，而父进程则继续等待下一个连接请求。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）进程要执行另一个程序。这种用法在</font><font style="color:black;background-color:#FFFFFF;">Shell</font><font style="color:black;background-color:#FFFFFF;">中很常见，子进程从</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">返回后立即调用</font><font style="color:#002060;background-color:#d9d9d9;">exec</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
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
```

### <font style="color:black;">共享文件</font>
<font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">的一个特性是在父进程中打开的文件描述符都会被复制到子进程中，父进程和子进程共享同一个文件偏移量。</font>

<font style="color:black;background-color:#FFFFFF;">如果父进程和子进程写同一描述符指向的文件，但又没有任何形式的同步，那么它们的输出可能会相互混合。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <fstream>
#include <unistd.h>
using  namespace std;

int main()
{
  ofstream fout;
  fout.open("/tmp/tmp.txt");  // 打开文件。
  fork();
  for (int ii=0;ii<10000000;ii++) // 向文件中写入一千万行数据。
  {
    fout << "进程" << getpid() << "西施" << ii << "极漂亮" << "\n";   // 写入的内容无所谓。
  }
 
 fout.close();    // 关闭文件。
}

/*
编译运行并查看结果：
➜  4-4 Create process git:(main) ✗ g++ -o demo03 demo03.cpp
➜  4-4 Create process git:(main) ✗ ./demo03
➜  4-4 Create process git:(main) ✗ wc /tmp/tmp.txt 
 20000000  19997948 697777780 /tmp/tmp.txt
➜  4-4 Create process git:(main) ✗ 
*/
```

### <font style="color:black;">vfork()函数</font>
<font style="color:#002060;background-color:#d9d9d9;">vfork()</font><font style="color:black;background-color:#FFFFFF;">函数的调用和返回值与</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">相同，但两者的语义不同。</font>

<font style="color:#002060;background-color:#d9d9d9;">vfork()</font><font style="color:black;background-color:#FFFFFF;">函数用于创建一个新进程，而该新进程的目的是</font><font style="color:black;background-color:#FFFFFF;">exec</font><font style="color:black;background-color:#FFFFFF;">一个新程序，它不复制父进程的地址空间，因为子进程会立即调用</font><font style="color:black;background-color:#FFFFFF;">exec</font><font style="color:black;background-color:#FFFFFF;">，于是也就不会使用父进程的地址空间。如果子进程使用了父进程的地址空间，可能会带来未知的结果。</font>

<font style="color:#002060;background-color:#d9d9d9;">vfork()</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">fork()</font><font style="color:black;background-color:#FFFFFF;">的另一个区别是：</font><font style="color:#002060;background-color:#d9d9d9;">vfork()</font><font style="color:black;background-color:#FFFFFF;">保证子进程先运行，在子进程调用exec或</font><font style="color:#002060;background-color:#d9d9d9;">exit()</font><font style="color:black;background-color:#FFFFFF;">之后父进程才恢复运行。</font>

## <font style="color:black;">僵尸进程</font>
<font style="color:black;background-color:#FFFFFF;">如果父进程比子进程先退出，子进程将被</font><font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">号进程托管（这也是一种让程序在后台运行的方法）。</font>

```cpp
// 案例
#include <iostream>
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
```

<font style="color:black;background-color:#FFFFFF;">如果子进程比父进程先退出，而父进程没有处理子进程退出的信息，那么，子进程将成为</font><font style="color:#DF2A3F;background-color:#FBF5CB;">僵尸进程</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">僵尸进程有什么危害？内核为每个子进程保留了一个数据结构，包括进程编号、终止状态、使用CPU时间等。父进程如果处理了子进程退出的信息，内核就会释放这个数据结构，父进程如果没有处理子进程退出的信息，内核就不会释放这个数据结构，子进程的进程编号将一直被占用。系统可用的进程编号是有限的，</font><font style="color:black;background-color:#FBF5CB;">如果产生了大量的僵尸进程，将因为没有可用的进程编号而导致系统不能产生新的进程</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">僵尸进程的避免：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）子进程退出的时候，内核会向父进程发头</font><font style="color:#002060;background-color:#d9d9d9;">SIGCHLD</font><font style="color:black;background-color:#FFFFFF;">信号，如果父进程用</font><font style="color:#002060;background-color:#d9d9d9;">signal(SIGCHLD,SIG_IGN)</font><font style="color:black;background-color:#FFFFFF;">通知</font>[<font style="background-color:#FFFFFF;">内核</font>](https://baike.baidu.com/item/%E5%86%85%E6%A0%B8?fromModule=lemma_inlink)<font style="color:black;background-color:#FFFFFF;">，表示自己对子进程的退出不感兴趣，那么子进程退出后会立即释放数据结构。</font>

<font style="color:black;background-color:#FFFFFF;">2）父进程通过</font><font style="color:#002060;background-color:#d9d9d9;">wait()/waitpid()</font><font style="color:black;background-color:#FFFFFF;">等函数等待子进程结束，在子进程退出之前，父进程将被阻塞待。</font>

```cpp
pid_t wait(int *stat_loc);//用的最多
pid_t waitpid(pid_t pid, int *stat_loc, int options);
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

<font style="color:black;background-color:#FFFFFF;">返回值是子进程的编号。</font>

<font style="color:#002060;background-color:#d9d9d9;">stat_loc</font><font style="color:black;background-color:#FFFFFF;">是子进程终止的信息：</font><font style="color:black;background-color:#FFFFFF;">a</font><font style="color:black;background-color:#FFFFFF;">）如果是正常终止，宏</font><font style="color:#002060;background-color:#d9d9d9;">WIFEXITED(stat_loc)</font><font style="color:black;background-color:#FFFFFF;">返回真，宏</font><font style="color:#002060;background-color:#d9d9d9;">WEXITSTATUS(stat_loc)</font><font style="color:black;background-color:#FFFFFF;">可获取终止状态；</font><font style="color:black;background-color:#FFFFFF;">b</font><font style="color:black;background-color:#FFFFFF;">）如果是异常终止，宏</font><font style="color:#002060;background-color:#d9d9d9;">WTERMSIG(stat_loc)</font><font style="color:black;background-color:#FFFFFF;">可获取终止进程的信号。</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）如果父进程很忙，可以捕获</font><font style="color:#002060;background-color:#d9d9d9;">SIGCHLD</font><font style="color:black;background-color:#FFFFFF;">信号，在信号处理函数中调用</font><font style="color:#002060;background-color:#d9d9d9;">wait()/waitpid()</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">示例一：</font>

```cpp
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
```

<font style="color:black;background-color:#FFFFFF;">示例二：</font>

```cpp
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using  namespace std;

void func(int sig)   // 子进程退出的信号处理函数。
{
  int sts;
  pid_t pid=wait(&sts);

  cout << "已终止的子进程编号是：" << pid << endl;

  if (WIFEXITED(sts)) { cout << "子进程是正常退出的，退出状态是：" << WEXITSTATUS(sts) << endl; }
  else { cout << "子进程是异常退出的，终止它的信号是：" << WTERMSIG(sts) << endl; }
}

int main()
{
  signal(SIGCHLD,func);  // 捕获子进程退出的信号。

  if (fork()>0)
  { // 父进程的流程。
    while (true)
    {
      cout << "父进程忙着执行任务。\n";
      sleep(1);
    }
  }
  else
  { // 子进程的流程。
    sleep(5);
    // int *p=0; *p=10;
    exit(1);
  }
}
```

### 程序运行在后台的方法
#### 添加`&`符号
```cpp
// 案例
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
```

![](https://cdn.nlark.com/yuque/0/2025/gif/33636091/1747191074455-c8f0a4b4-bc1d-42b7-9475-8bd7607882b9.gif)

#### 在main函数中修改
```cpp
// 案例
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
```

## <font style="color:black;">多进程与信</font><font style="color:black;">号</font>
<font style="color:black;background-color:#FFFFFF;">在多进程的服务程序中，如果子进程收到退出信号，子进程自行退出，如果父进程收到退出信号，则应该先向全部的子进程发送退出信号，然后自己再退出。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <unistd.h>
#include <signal.h>
using  namespace std;

void FathEXIT(int sig);  // 父进程的信号处理函数。
void ChldEXIT(int sig);  // 子进程的信号处理函数。

int main()
{
  // 忽略全部的信号，不希望被打扰。
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);

  // 设置信号,在shell状态下可用 "kill 进程号" 或 "Ctrl+c" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  signal(SIGTERM,FathEXIT); signal(SIGINT,FathEXIT);  // SIGTERM 15 SIGINT 2

  while (true)
  {
    if (fork()>0) // 父进程的流程。
    {
      sleep(5); continue;
    }
    else          // 子进程的流程。
    {
      // 子进程需要重新设置信号。
      signal(SIGTERM,ChldEXIT);   // 子进程的退出函数与父进程不一样。
      signal(SIGINT ,SIG_IGN);    // 子进程不需要捕获SIGINT信号。

      while (true)
      {
        cout << "子进程" << getpid() << "正在运行中。\n"; sleep(3); continue;
      }
    }
  }
}

// 父进程的信号处理函数。
void FathEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

  cout << "父进程退出，sig=" << sig << endl;

  kill(0,SIGTERM);     // 向全部的子进程发送15的信号，通知它们退出。

  // 在这里增加释放资源的代码（全局的资源）。

  exit(0);
}

// 子进程的信号处理函数。
void ChldEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

  cout << "子进程" << getpid() << "退出，sig=" << sig << endl;

  // 在这里增加释放资源的代码（只释放子进程的资源）。

  exit(0);
}
```

## <font style="color:black;">共享内存</font>
<font style="color:black;background-color:#FFFFFF;">多线程共享进程的地址空间，如果多个线程需要访问同一块内存，用全局变量就可以了。</font>

<font style="color:black;background-color:#FFFFFF;">在多进程中，每个进程的地址空间是独立的，不共享的，如果多个进程需要访问同一块内存，不能用全局变量，只能用共享内存。</font>

<font style="color:black;background-color:#FFFFFF;">共享内存（</font><font style="color:black;background-color:#FFFFFF;">Shared Memory</font><font style="color:black;background-color:#FFFFFF;">）允许多个进程（不要求进程之间有血缘关系）访问同一块内存空间，是多个进程之间共享和传递数据最高效的方式。进程可以将共享内存连接到它们自己的地址空间中，如果某个进程修改了共享内存中的数据，其它的进程读到的数据也会改变。</font>

<font style="color:#DF2A3F;background-color:#FBF5CB;">共享内存没有提供锁机制</font><font style="color:black;background-color:#FFFFFF;">，也就是说，在某一个进程对共享内存进行读/写的时候，不会阻止其它进程对它的读/写。如果要对共享内存的读/写加锁，可以使用信号量。</font>

<font style="color:black;">Linux中提供了一组函数用于操作共享内存。</font>

### <font style="color:black;">shmget函数</font>
<font style="color:black;background-color:#FFFFFF;">该函数用于创建/获取共享内存。</font>

```cpp
int shmget(key_t key, size_t size, int shmflg);
```

<font style="color:#002060;background-color:#d9d9d9;">key</font><font style="color:black;background-color:#FFFFFF;">    </font><font style="color:black;background-color:#FFFFFF;">共享内存的键值，是一个整数（</font><font style="color:#002060;background-color:#d9d9d9;">typedef unsigned int key_t</font><font style="color:black;background-color:#FFFFFF;">），一般采用十六进制，例如</font><font style="color:#002060;background-color:#d9d9d9;">0x5005</font><font style="color:black;background-color:#FFFFFF;">，不同共享内存的</font><font style="color:#002060;background-color:#d9d9d9;">key</font><font style="color:black;background-color:#FFFFFF;">不能相同。</font>

<font style="color:#002060;background-color:#d9d9d9;">size</font><font style="color:black;background-color:#FFFFFF;">    </font><font style="color:black;background-color:#FFFFFF;">共享内存的大小，以字节为单位。</font>

<font style="color:#002060;background-color:#d9d9d9;">shmflg</font><font style="color:black;background-color:#FFFFFF;">共享内存的访问权限，与文件的权限一样，例如</font><font style="color:#002060;background-color:#d9d9d9;">0666|IPC_CREAT</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#002060;background-color:#d9d9d9;">0666</font><font style="color:black;background-color:#FFFFFF;">表示全部用户对它可读写，</font><font style="color:#002060;background-color:#d9d9d9;">IPC_CREAT</font><font style="color:black;background-color:#FFFFFF;">表示如果共享内存不存在，就创建它。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：成功返回共享内存的</font><font style="color:black;background-color:#FFFFFF;">id</font><font style="color:black;background-color:#FFFFFF;">（一个非负的整数），失败返回</font><font style="color:black;background-color:#FFFFFF;">-1</font><font style="color:black;background-color:#FFFFFF;">（系统内存不足、没有权限）</font>

<font style="color:black;background-color:#FFFFFF;">用</font><font style="color:#DF2A3F;background-color:#d9d9d9;">ipcs -m</font><font style="color:black;background-color:#FFFFFF;">可以查看系统的共享内存，包括：键值（</font><font style="color:#002060;background-color:#d9d9d9;">key</font><font style="color:black;background-color:#FFFFFF;">），共享内存id（</font><font style="color:#002060;background-color:#d9d9d9;">shmid</font><font style="color:black;background-color:#FFFFFF;">），拥有者（</font><font style="color:#002060;background-color:#d9d9d9;">owner</font><font style="color:black;background-color:#FFFFFF;">），权限（</font><font style="color:#002060;background-color:#d9d9d9;">perms</font><font style="color:black;background-color:#FFFFFF;">），大小（</font><font style="color:#002060;background-color:#d9d9d9;">bytes</font><font style="color:black;background-color:#FFFFFF;">）。</font>

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1746877076376-899e5d0d-6421-498b-8474-20118e6cdc87.png)

<font style="color:black;background-color:#FFFFFF;">用</font><font style="color:#DF2A3F;background-color:#d9d9d9;">ipcrm -m 共享内存id</font><font style="color:black;background-color:#FFFFFF;">可以手工删除共享内存，如下：</font>

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1746877087576-dc7f3a3f-50bf-4cb8-acf7-e738c4517983.png)

### <font style="color:black;">shmat函数</font>
<font style="color:black;background-color:#FFFFFF;">该函数用于把共享内存连接到当前进程的地址空间。</font>

<font style="color:#002060;background-color:#d9d9d9;">void *shmat(int shmid, const void *shmaddr, int shmflg);</font>

<font style="color:#002060;background-color:#d9d9d9;">shmid</font><font style="color:black;background-color:#FFFFFF;">        </font><font style="color:black;background-color:#FFFFFF;">由</font><font style="color:#002060;background-color:#d9d9d9;">shmget()</font><font style="color:black;background-color:#FFFFFF;">函数返回的共享内存标识。</font>

<font style="color:#002060;background-color:#d9d9d9;">shmaddr</font><font style="color:black;background-color:#FFFFFF;">  </font><font style="color:black;background-color:#FFFFFF;">指定共享内存连接到当前进程中的地址位置，通常填</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">，表示让系统来选择共享内存的地址。</font>

<font style="color:#002060;background-color:#d9d9d9;">shmflg</font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">标志位，通常填</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">调用成功时返回共享内存起始地址，失败返回</font><font style="color:#002060;background-color:#d9d9d9;">(void*)-1</font><font style="color:black;background-color:#FFFFFF;">。</font>

### <font style="color:black;">shmdt函数</font>
<font style="color:black;background-color:#FFFFFF;">该函数用于将共享内存从当前进程中分离，相当于</font><font style="color:#002060;background-color:#d9d9d9;">shmat()</font><font style="color:black;background-color:#FFFFFF;">函数的反操作。</font>

```cpp
int shmdt(const void *shmaddr);
```

<font style="color:#002060;background-color:#d9d9d9;">shmaddr</font><font style="color:black;background-color:#FFFFFF;">    </font><font style="color:#002060;background-color:#d9d9d9;">shmat()</font><font style="color:black;background-color:#FFFFFF;">函数返回的地址。</font>

<font style="color:black;background-color:#FFFFFF;">调用成功时返回0，失败时返回-1。</font>

### <font style="color:black;">shmctl函数</font>
<font style="color:black;background-color:#FFFFFF;">该函数用于操作共享内存，最常用的操作是删除共享内存。</font>

```cpp
int shmctl(int shmid, int command, struct shmid_ds *buf);
```

<font style="color:#002060;background-color:#d9d9d9;">shmid</font><font style="color:black;background-color:#FFFFFF;">        </font><font style="color:#002060;background-color:#d9d9d9;">shmget()</font><font style="color:black;background-color:#FFFFFF;">函数返回的共享内存</font><font style="color:black;background-color:#FFFFFF;">id</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:#002060;background-color:#d9d9d9;">command</font><font style="color:black;background-color:#FFFFFF;">  </font><font style="color:black;background-color:#FFFFFF;">操作共享内存的指令，如果要删除共享内存，填</font><font style="color:black;background-color:#FFFFFF;">IPC_RMID</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:#002060;background-color:#d9d9d9;">buf</font><font style="color:black;background-color:#FFFFFF;">            </font><font style="color:black;background-color:#FFFFFF;">操作共享内存的数据结构的地址，如果要删除共享内存，填</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">调用成功时返回</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">，失败时返回</font><font style="color:black;background-color:#FFFFFF;">-1</font><font style="color:black;background-color:#FFFFFF;">。</font>

**<font style="color:black;background-color:#FFFFFF;">注意，用root创建的共享内存，不管创建的权限是什么，普通用户无法删除。</font>**

### <font style="color:black;">示例</font>
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using  namespace std;

struct stgirl     // 超女结构体。
{
  int  no;        // 编号。
  char name[51];  // 姓名，注意，不能用string。
};

int main(int argc,char *argv[])
{
  if (argc!=3) { cout << "Using:./demo no name\n"; return -1; }

  // 第1步：创建/获取共享内存，键值key为0x5005，也可以用其它的值。
  int shmid=shmget(0x5005, sizeof(stgirl), 0640|IPC_CREAT);
  if ( shmid ==-1 )
  {
    cout << "shmget(0x5005) failed.\n"; return -1;
  }

  cout << "shmid=" << shmid << endl;

  // 第2步：把共享内存连接到当前进程的地址空间。
  stgirl *ptr=(stgirl *)shmat(shmid,0,0);
  if ( ptr==(void *)-1 )
  {
    cout << "shmat() failed\n"; return -1;
  }

  // 第3步：使用共享内存，对共享内存进行读/写。
  cout << "原值：no=" << ptr->no << ",name=" << ptr->name << endl;  // 显示共享内存中的原值。
  ptr->no=atoi(argv[1]);        // 对超女结构体的no成员赋值。
  //strcpy(ptr->name,argv[2]);    // 对超女结构体的name成员赋值。
  ptr->name=argv[2];
  cout << "新值：no=" << ptr->no << ",name=" << ptr->name << endl;  // 显示共享内存中的当前值。

  // 第4步：把共享内存从当前进程中分离。
  shmdt(ptr);

  // 第5步：删除共享内存。
  //if (shmctl(shmid,IPC_RMID,0)==-1)
  //{
   // cout << "shmctl failed\n"; return -1;
  //}
}
```

## <font style="color:black;">循环队列、信号量、生产/消费者模型的源代码</font>
+ 共享内存不能自动扩展，只能采用C++内置的数据类型
+ 共享内存不能采用STL容器，也不能使用移动语义
+ 如果要实现多进程的生产/消费者模型，只能采用循环队列

### 信号量
#### 信号量的基本概念
+ 信号量本质上是一个非负数（>=0）的计数器
+ 同于给共享资源建立一个标志，表示该资源被占用情况

#### 信号量的两种操作
+ P操作（wait）将信号量的值减1，如果信号量的值为0，将阻塞等待，直到信号量的值大于0。
+ V操作（post）将信号量的值加1，任何时候都不会阻塞。

#### 信号量的应用场景
+ 如果约定信号量的取值只是0和1（0-资源不可用；1-资源可用），可以实现互斥锁。
+ 如果约定信号量的取值表示可用资源的数量，可以实现生产/消费者模型。

```cpp
//查看系统中的信号量
ipcs -s
// 删除信号量
ipcrm sem 信号量id
```

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747229987628-8bc062fb-a58e-4016-b047-e684a65c48ae.png)

### <font style="color:black;">demo1.cpp</font>
```cpp
// demo1.cpp，本程序演示循环队列的使用。
#include "_public.h"

int main()
{
  using ElemType=int;

  squeue<ElemType,5> QQ;

  ElemType ee;      // 创建一个数据元素。

  cout << "元素（1、2、3）入队。\n";
  ee=1;  QQ.push(ee);
  ee=2;  QQ.push(ee);
  ee=3;  QQ.push(ee);

  cout << "队列的长度是" << QQ.size() << endl;
  QQ.printqueue();

  ee=QQ.front(); QQ.pop(); cout << "出队的元素值为" << ee << endl;
  ee=QQ.front(); QQ.pop(); cout << "出队的元素值为" << ee << endl;

  cout << "队列的长度是" << QQ.size() << endl;
  QQ.printqueue();

  cout << "元素（11、12、13、14、15）入队。\n";
  ee=11;  QQ.push(ee);
  ee=12;  QQ.push(ee);
  ee=13;  QQ.push(ee);
  ee=14;  QQ.push(ee);
  ee=15;  QQ.push(ee);

  cout << "队列的长度是" << QQ.size() << endl;
  QQ.printqueue();
}
```

### <font style="color:black;">demo2.cpp</font>
```cpp
// demo2.cpp，本程序演示基于共享内存的循环队列。
#include "_public.h"

int main()
{
  using ElemType=int;

  // 初始化共享内存。
  int shmid=shmget(0x5005, sizeof(squeue<ElemType,5>), 0640|IPC_CREAT);
  if ( shmid ==-1 )
  {
    cout << "shmget(0x5005) failed.\n"; return -1;
  }

  // 把共享内存连接到当前进程的地址空间。
  squeue<ElemType,5> *QQ=(squeue<ElemType,5> *)shmat(shmid,0,0);
  if ( QQ==(void *)-1 )
  {
    cout << "shmat() failed\n"; return -1;
  }

  QQ->init();       // 初始化循环队列。

  ElemType ee;      // 创建一个数据元素。

  cout << "元素（1、2、3）入队。\n";
  ee=1;  QQ->push(ee);
  ee=2;  QQ->push(ee);
  ee=3;  QQ->push(ee);

  cout << "队列的长度是" << QQ->size() << endl;
  QQ->printqueue();

  ee=QQ->front(); QQ->pop(); cout << "出队的元素值为" << ee << endl;
  ee=QQ->front(); QQ->pop(); cout << "出队的元素值为" << ee << endl;

  cout << "队列的长度是" << QQ->size() << endl;
  QQ->printqueue();

  cout << "元素（11、12、13、14、15）入队。\n";
  ee=11;  QQ->push(ee);
  ee=12;  QQ->push(ee);
  ee=13;  QQ->push(ee);
  ee=14;  QQ->push(ee);
  ee=15;  QQ->push(ee);

  cout << "队列的长度是" << QQ->size() << endl;
  QQ->printqueue();

  shmdt(QQ);  // 把共享内存从当前进程中分离。
}
```

### <font style="color:black;">demo3.cpp</font>
```cpp
// demo3.cpp，本程序演示用信号量给共享内存加锁。
#include "_public.h"

struct stgirl     // 超女结构体。
{
  int  no;        // 编号。
  char name[51];  // 姓名，注意，不能用string。
};

int main(int argc,char *argv[])
{
  if (argc!=3) { cout << "Using:./demo no name\n"; return -1; }

  // 第1步：创建/获取共享内存，键值key为0x5005，也可以用其它的值。
  int shmid=shmget(0x5005, sizeof(stgirl), 0640|IPC_CREAT);
  if ( shmid ==-1 )
  { 
    cout << "shmget(0x5005) failed.\n"; return -1; 
  }

  cout << "shmid=" << shmid << endl;

  // 第2步：把共享内存连接到当前进程的地址空间。
  stgirl *ptr=(stgirl *)shmat(shmid,0,0);
  if ( ptr==(void *)-1 )
  { 
    cout << "shmat() failed\n"; return -1; 
  }

  // 创建、初始化二元信号量。
  csemp mutex;
  if (mutex.init(0x5005)==false)
  {
    cout << "mutex.init(0x5005) failed.\n"; return -1;
  }

  cout << "申请加锁...\n";
  mutex.wait(); // 申请加锁。
  cout << "申请加锁成功。\n";

  // 第3步：使用共享内存，对共享内存进行读/写。
  cout << "原值：no=" << ptr->no << ",name=" << ptr->name << endl;  // 显示共享内存中的原值。
  ptr->no=atoi(argv[1]);        // 对超女结构体的no成员赋值。
  strcpy(ptr->name,argv[2]);    // 对超女结构体的name成员赋值。
  cout << "新值：no=" << ptr->no << ",name=" << ptr->name << endl;  // 显示共享内存中的当前值。
  sleep(10);

  mutex.post(); // 解锁。
  cout << "解锁。\n";

  // 查看信号量  ：ipcs -s    // 删除信号量  ：ipcrm sem 信号量id
  // 查看共享内存：ipcs -m    // 删除共享内存：ipcrm -m  共享内存id

  // 第4步：把共享内存从当前进程中分离。
  shmdt(ptr);

  // 第5步：删除共享内存。
  //if (shmctl(shmid,IPC_RMID,0)==-1)
  //{ 
   // cout << "shmctl failed\n"; return -1; 
  //}
}
```

### <font style="color:black;">incache.cpp</font>
```cpp
// 多进程的生产消费者模型的生产者程序
#include "_public.h"

int main()
{
  struct stgirl  // 循环队列的数据元素是超女结构体。
  {
    int no;
    char name[51];
  };

  using ElemType=stgirl;

  // 初始化共享内存。
  int shmid=shmget(0x5005, sizeof(squeue<ElemType,5>), 0640|IPC_CREAT);
  if ( shmid ==-1 )
  {
    cout << "shmget(0x5005) failed.\n"; return -1;
  }

  // 把共享内存连接到当前进程的地址空间。
  squeue<ElemType,5> *QQ=(squeue<ElemType,5> *)shmat(shmid,0,0);
  if ( QQ==(void *)-1 )
  {
    cout << "shmat() failed\n"; return -1;
  }

  QQ->init();       // 初始化循环队列。

  ElemType ee;      // 创建一个数据元素。

  csemp mutex; mutex.init(0x5001);     // 用于给共享内存加锁。
  csemp cond;  cond.init(0x5002,0,0);  // 信号量的值用于表示队列中数据元素的个数。

  mutex.wait();  // 加锁。
  // 生产3个数据。
  ee.no=3; strcpy(ee.name,"西施"); QQ->push(ee);
  ee.no=7; strcpy(ee.name,"冰冰"); QQ->push(ee);
  ee.no=8; strcpy(ee.name,"幂幂"); QQ->push(ee);
  mutex.post();  // 解锁。
  cond.post(3);  // 实参是3，表示生产了3个数据。

  shmdt(QQ);  // 把共享内存从当前进程中分离。
}
```

### <font style="color:black;">outcache.cpp</font>
```cpp
// 多进程的生产消费者模型的消费者程序
#include "_public.h"

int main()
{
  struct stgirl  // 循环队列的数据元素是超女结构体。
  {
    int no;
    char name[51];
  };

  using ElemType=stgirl;

  // 初始化共享内存。
  int shmid=shmget(0x5005, sizeof(squeue<ElemType,5>), 0640|IPC_CREAT);
  if ( shmid ==-1 )
  {
    cout << "shmget(0x5005) failed.\n"; return -1;
  }

  // 把共享内存连接到当前进程的地址空间。
  squeue<ElemType,5> *QQ=(squeue<ElemType,5> *)shmat(shmid,0,0);
  if ( QQ==(void *)-1 )
  {
    cout << "shmat() failed\n"; return -1;
  }

  QQ->init();       // 初始化循环队列。

  ElemType ee;      // 创建一个数据元素。

  csemp mutex; mutex.init(0x5001);     // 用于给共享内存加锁。
  csemp cond;  cond.init(0x5002,0,0);  // 信号量的值用于表示队列中数据元素的个数。

  while (true)
  {
    mutex.wait();  // 加锁。

    while (QQ->empty())    // 如果队列空，进入循环，否则直接处理数据。必须用循环，不能用if
    {
      mutex.post();   // 解锁。
      cond.wait();    // 等待生产者的唤醒信号。
      mutex.wait();   // 加锁。
    }

    // 数据元素出队。
    ee = QQ->front();  QQ->pop();
    mutex.post(); // 解锁。

    // 处理出队的数据（把数据消费掉）。
    cout << "no=" << ee.no << ",name=" << ee.name << endl;
    usleep(100);    // 假设处理数据需要时间，方便演示。
  }

  shmdt(QQ);
}
```

### <font style="color:black;">_public.h</font>
```cpp
#ifndef __PUBLIC_HH
#define __PUBLIC_HH 1

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
using namespace std;

// 循环队列。
template <class TT, int MaxLength>
class squeue
{
private:
  bool m_inited;              // 队列被初始化标志，true-已初始化；false-未初始化。
  TT   m_data[MaxLength];     // 用数组存储循环队列中的元素。
  int  m_head;                // 队列的头指针。
  int  m_tail;                // 队列的尾指针，指向队尾元素。
  int  m_length;              // 队列的实际长度。    
  squeue(const squeue &) = delete;             // 禁用拷贝构造函数。
  squeue &operator=(const squeue &) = delete;  // 禁用赋值函数。
public:

  squeue() { init(); }  // 构造函数。

  // 循环队列的初始化操作。
  // 注意：如果用于共享内存的队列，不会调用构造函数，必须调用此函数初始化。
  void init()  
  { 
    if (m_inited!=true)      // 循环队列的初始化只能执行一次。
    { 
      m_head=0;              // 头指针。
      m_tail=MaxLength-1;    // 为了方便写代码，初始化时，尾指针指向队列的最后一个位置。
      m_length=0;            // 队列的实际长度。
      memset(m_data,0,sizeof(m_data));  // 数组元素清零。
      m_inited=true; 
    }
  }

  // 元素入队，返回值：false-失败；true-成功。
  bool push(const TT &ee)
  {
    if (full() == true)
    {
      cout << "循环队列已满，入队失败。\n"; return false;
    }

    // 先移动队尾指针，然后再拷贝数据。
    m_tail=(m_tail+1)%MaxLength;  // 队尾指针后移。
    m_data[m_tail]=ee;
    m_length++;    

    return true;
  }

  // 求循环队列的长度，返回值：>=0-队列中元素的个数。
  int  size()                   
  {
    return m_length;    
  }

  // 判断循环队列是否为空，返回值：true-空，false-非空。
  bool empty()                    
  {
    if (m_length == 0) return true;    

    return false;
  }

  // 判断循环队列是否已满，返回值：true-已满，false-未满。
  bool full()
  {
    if (m_length == MaxLength) return true;    

    return false;
  }

  // 查看队头元素的值，元素不出队。
  TT& front()
  {
    return m_data[m_head];
  }

  // 元素出队，返回值：false-失败；true-成功。
  bool pop()
  {
    if (empty() == true) return false;

    m_head=(m_head+1)%MaxLength;  // 队列头指针后移。
    m_length--;    

    return true;
  }

  // 显示循环队列中全部的元素。
  // 这是一个临时的用于调试的函数，队列中元素的数据类型支持cout输出才可用。
  void printqueue()                    
  {
    for (int ii = 0; ii < size(); ii++)
    {
      cout << "m_data[" << (m_head+ii)%MaxLength << "],value=" \
           << m_data[(m_head+ii)%MaxLength] << endl;
    }
  }
};

// 信号量。
class csemp
{
private:
  union semun  // 用于信号量操作的共同体。
  {
    int val;
    struct semid_ds *buf;
    unsigned short  *arry;
  };

  int   m_semid;         // 信号量id（描述符）。

  // 如果把sem_flg设置为SEM_UNDO，操作系统将跟踪进程对信号量的修改情况，
  // 在全部修改过信号量的进程（正常或异常）终止后，操作系统将把信号量恢复为初始值。
  // 如果信号量用于互斥锁，设置为SEM_UNDO。
  // 如果信号量用于生产消费者模型，设置为0。
  short m_sem_flg;

  csemp(const csemp &) = delete;             // 禁用拷贝构造函数。
  csemp &operator=(const csemp &) = delete;  // 禁用赋值函数。
public:
  csemp():m_semid(-1){}
  // 如果信号量已存在，获取信号量；如果信号量不存在，则创建它并初始化为value。
  // 如果用于互斥锁，value填1，sem_flg填SEM_UNDO。
  // 如果用于生产消费者模型，value填0，sem_flg填0。
  bool init(key_t key,unsigned short value=1,short sem_flg=SEM_UNDO);
  bool wait(short value=-1);// 信号量的P操作，如果信号量的值是0，将阻塞等待，直到信号量的值大于0。
  bool post(short value=1); // 信号量的V操作。
  int  getvalue();           // 获取信号量的值，成功返回信号量的值，失败返回-1。
  bool destroy();            // 销毁信号量。
 ~csemp();
};

#endif
```

### <font style="color:black;">_public.cpp</font>
```cpp
#include "_public.h"

// 如果信号量已存在，获取信号量；如果信号量不存在，则创建它并初始化为value。
// 如果用于互斥锁，value填1，sem_flg填SEM_UNDO。
// 如果用于生产消费者模型，value填0，sem_flg填0。
bool csemp::init(key_t key,unsigned short value,short sem_flg)
{
  if (m_semid!=-1) return false; // 如果已经初始化了，不必再次初始化。

  m_sem_flg=sem_flg;

  // 信号量的初始化不能直接用semget(key,1,0666|IPC_CREAT)
  // 因为信号量创建后，初始值是0，如果用于互斥锁，需要把它的初始值设置为1，
  // 而获取信号量则不需要设置初始值，所以，创建信号量和获取信号量的流程不同。

  // 信号量的初始化分三个步骤：
  // 1）获取信号量，如果成功，函数返回。
  // 2）如果失败，则创建信号量。
  // 3) 设置信号量的初始值。

  // 获取信号量。
  if ( (m_semid=semget(key,1,0666)) == -1)
  {
    // 如果信号量不存在，创建它。
    if (errno==ENOENT)
    {
      // 用IPC_EXCL标志确保只有一个进程创建并初始化信号量，其它进程只能获取。
      if ( (m_semid=semget(key,1,0666|IPC_CREAT|IPC_EXCL)) == -1)
      {
        if (errno==EEXIST) // 如果错误代码是信号量已存在，则再次获取信号量。
        {
          if ( (m_semid=semget(key,1,0666)) == -1)
          { 
            perror("init 1 semget()"); return false; 
          }
          return true;
        }
        else  // 如果是其它错误，返回失败。
        {
          perror("init 2 semget()"); return false;
        }
      }

      // 信号量创建成功后，还需要把它初始化成value。
      union semun sem_union;
      sem_union.val = value;   // 设置信号量的初始值。
      if (semctl(m_semid,0,SETVAL,sem_union) <  0) 
      { 
        perror("init semctl()"); return false; 
      }
    }
    else
    { perror("init 3 semget()"); return false; }
  }

  return true;
}

// 信号量的P操作（把信号量的值减value），如果信号量的值是0，将阻塞等待，直到信号量的值大于0。
bool csemp::wait(short value)
{
  if (m_semid==-1) return false;

  struct sembuf sem_b;
  sem_b.sem_num = 0;      // 信号量编号，0代表第一个信号量。
  sem_b.sem_op = value;   // P操作的value必须小于0。
  sem_b.sem_flg = m_sem_flg;
  if (semop(m_semid,&sem_b,1) == -1) { perror("p semop()"); return false; }

  return true;
}

// 信号量的V操作（把信号量的值减value）。
bool csemp::post(short value)
{
  if (m_semid==-1) return false;

  struct sembuf sem_b;
  sem_b.sem_num = 0;     // 信号量编号，0代表第一个信号量。
  sem_b.sem_op = value;  // V操作的value必须大于0。
  sem_b.sem_flg = m_sem_flg;
  if (semop(m_semid,&sem_b,1) == -1) { perror("V semop()"); return false; }

  return true;
}

// 获取信号量的值，成功返回信号量的值，失败返回-1。
int csemp::getvalue()
{
  return semctl(m_semid,0,GETVAL);
}

// 销毁信号量。
bool csemp::destroy()
{
  if (m_semid==-1) return false;

  if (semctl(m_semid,0,IPC_RMID) == -1) { perror("destroy semctl()"); return false; }

  return true;
}

csemp::~csemp()
{
}
```

### <font style="color:black;">makefile</font>
```makefile
all:demo1 demo2 demo3 incache outcache

demo1:demo1.cpp _public.h _public.cpp
	g++ -g -o demo1 demo1.cpp _public.cpp

demo2:demo2.cpp _public.h _public.cpp
	g++ -g -o demo2 demo2.cpp _public.cpp

demo3:demo3.cpp _public.h _public.cpp
	g++ -g -o demo3 demo3.cpp _public.cpp

incache:incache.cpp _public.h _public.cpp
	g++ -g -o incache incache.cpp _public.cpp

outcache:outcache.cpp _public.h _public.cpp
	g++ -g -o outcache outcache.cpp _public.cpp

clean:
	rm -f demo1 demo2 demo3 incache outcache
```

