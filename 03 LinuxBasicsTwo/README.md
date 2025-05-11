## <font style="color:black;">Linux的时间操作</font>
+ C++11提供了操作时间的chrono库，从语言级别提供了支持
+ chrono库屏蔽了时间操作的很多细节，简化了时间操作
+ 如果对Linux原生的时间操作不熟悉，很难用好chrono库

<font style="color:black;background-color:#FFFFFF;">UNIX操作系统根据计算机产生的年代把1970年1月1日作为UNIX的纪元时间，1970年1月1日是时间的中间点，将从1970年1月1日起经过的</font><font style="color:#DF2A3F;background-color:#FFFFFF;">秒数</font><font style="color:black;background-color:#FFFFFF;">用一个</font><font style="color:#DF2A3F;background-color:#FFFFFF;">整数存放</font><font style="color:black;background-color:#FFFFFF;">。</font>

### <font style="color:black;">time_t别名</font>
<font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">用于表示时间类型，它是一个</font><font style="color:#002060;background-color:#d9d9d9;">long</font><font style="color:black;background-color:#FFFFFF;">类型的别名，在</font><font style="color:#002060;background-color:#d9d9d9;"><time.h></font><font style="color:black;background-color:#FFFFFF;">文件中定义，表示从1970年1月1日0时0分0秒到现在的秒数。</font>

```cpp
typedef long time_t; //可读性高
/////////////////////////////////////////////
long tt;
time_t tt; //这两行代码与上面一行代码等价
```

### <font style="color:black;">time()库函数</font>
<font style="color:black;background-color:#FFFFFF;">time()</font><font style="color:black;background-color:#FFFFFF;">库函数用于获取操作系统的当前时间。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><time.h></font>

<font style="color:black;">声明：</font>

```cpp
time_t time(time_t *tloc);
```

<font style="color:black;background-color:#FFFFFF;">有两种调用方法：</font>

```cpp
time_t now=time(0);// 将空地址传递给time()函数，并将time()返回值赋给变量now。
```

或

```cpp
time_t now; time(&now);   // 将变量now的地址作为参数传递给time()函数。
```

```cpp
//示例代码
#include <iostream>
#include <time.h>      // 时间操作的头文件。
using namespace std;

int main()
{
  time_t now1 = time(0);             // 获取当前时间，存放在now1中。
  long now2;  
  time(&now2);                       //获取当前时间，存放在now2中。
  
  cout << "now1 = " << now1 << endl;  // 显示当前时间，1970年1月1日到现在的秒数。
  cout << "now2 = " << now2 << endl;  // 显示当前时间，1970年1月1日到现在的秒数。

  return 0;
}

/*
➜  3-1 Linux's time-related operations git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  3-1 Linux's time-related operations git:(main) ✗ ls
demo01  demo01.cpp
➜  3-1 Linux's time-related operations git:(main) ✗ ./demo01                      
now1 = 1746934247
now2 = 1746934247
*/
```

### <font style="color:black;">tm结构体</font>
<font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">是一个长整数，不符合人类的使用习惯，需要转换成</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体，</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体在</font><font style="color:#002060;background-color:#d9d9d9;"><time.h></font><font style="color:black;background-color:#FFFFFF;">中声明，如下：                 2022-10-01 15:30:25   Oct 1,2022 15:30:25</font>

```cpp
struct tm
{
  int tm_year;	// 年份：其值等于实际年份减去1900
  int tm_mon;	// 月份：取值区间为[0,11]，其中0代表一月，11代表12月
  int tm_mday;	// 日期：一个月中的日期，取值区间为[1,31]
  int tm_hour; 	// 时：取值区间为[0,23]
  int tm_min;	// 分：取值区间为[0,59]
  int tm_sec;     	// 秒：取值区间为[0,59]
  int tm_wday;	// 星期：取值区间为[0,6]，其中0代表星期天，6代表星期六
  int tm_yday;	// 从每年的1月1日开始算起的天数：取值区间为[0,365] 
  int tm_isdst;   // 夏令时标识符，该字段意义不大
};
```

### <font style="color:black;">localtime()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">localtime()</font><font style="color:black;background-color:#FFFFFF;">函数用于把</font><font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">表示的时间转换为</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体表示的时间。</font>

<font style="color:#002060;background-color:#d9d9d9;">localtime()</font><font style="color:black;background-color:#FFFFFF;">函数</font><font style="color:black;background-color:#E8F7CF;">不是线程安全的</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#002060;background-color:#d9d9d9;">localtime_r()</font><font style="color:black;background-color:#FFFFFF;">是</font><font style="color:black;background-color:#FBF5CB;">线程安全的</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><time.h></font>

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t *timep, struct tm *result);
```

<font style="color:#002060;background-color:#d9d9d9;">示例：</font>

```cpp
#include <iostream>
#include <time.h>      // 时间操作的头文件。
using namespace std;

int main()
{
  time_t now=time(0);             // 获取当前时间，存放在now中。

  cout << "now=" << now << endl;  // 显示当前时间，1970年1月1日到现在的秒数。

  tm tmnow;
  localtime_r(&now,&tmnow);       // 把整数的时间转换成tm结构体。

  // 根据tm结构体拼接成中国人习惯的字符串格式。
  string stime = to_string(tmnow.tm_year+1900)+"-"
               + to_string(tmnow.tm_mon+1)+"-"
               + to_string(tmnow.tm_mday)+" "
               + to_string(tmnow.tm_hour)+":"
               + to_string(tmnow.tm_min)+":"
               + to_string(tmnow.tm_sec);

  cout << "stime=" << stime << endl;
}
```

### <font style="color:black;">mktime()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">mktime()</font><font style="color:black;background-color:#FFFFFF;">函数的功能与</font><font style="color:#002060;background-color:#d9d9d9;">localtime()</font><font style="color:black;background-color:#FFFFFF;">函数相反，用于把</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体时间转换为</font><font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">时间。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><time.h></font>

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
time_t mktime(struct tm *tm);
```

<font style="color:black;background-color:#FFFFFF;">该函数</font><font style="color:#DF2A3F;background-color:#FBF5CB;">主要用于时间的运算</font><font style="color:black;background-color:#FFFFFF;">，例如：把2022-03-01 00:00:25加30分钟。</font>

<font style="color:black;background-color:#FFFFFF;">思路：</font>

<font style="color:black;background-color:#FFFFFF;">1）解析字符串格式的时间，转换成</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体；</font>

<font style="color:black;background-color:#FFFFFF;">2）用</font><font style="color:#002060;background-color:#d9d9d9;">mktime()</font><font style="color:black;background-color:#FFFFFF;">函数把tm结构体转换成</font><font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">时间；</font>

<font style="color:black;background-color:#FFFFFF;">3）把</font><font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">时间加30*60秒；</font>

<font style="color:black;background-color:#FFFFFF;">4）用</font><font style="color:#002060;background-color:#d9d9d9;">localtime_r()</font><font style="color:black;background-color:#FFFFFF;">函数把</font><font style="color:#002060;background-color:#d9d9d9;">time_t</font><font style="color:black;background-color:#FFFFFF;">时间转换成</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体；</font>

<font style="color:black;background-color:#FFFFFF;">5）把</font><font style="color:#002060;background-color:#d9d9d9;">tm</font><font style="color:black;background-color:#FFFFFF;">结构体转换成字符串。</font>

### `<font style="color:black;">gettimeofday()</font>`<font style="color:black;">库函数</font>
<font style="color:black;background-color:#FFFFFF;">用于获取1970年1月1日到现在的秒和当前秒中已逝去的</font><font style="color:black;background-color:#FBF5CB;">微秒数</font><font style="color:black;background-color:#FFFFFF;">，可以</font><font style="color:#DF2A3F;background-color:#FFFFFF;">用于程序的计时</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><sys/time.h></font>

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int gettimeofday(struct timeval *tv, struct timezone *tz);

struct timeval {
  time_t      tv_sec;    	/* 1970-1-1到现在的秒数 */
  suseconds_t tv_usec;   	/* 当前秒中，已逝去的微秒数 */
}; 

struct timezone {         /* 在实际开发中，派不上用场 */
  int tz_minuteswest;   	/* minutes west of Greenwich */ 
  int tz_dsttime;         	/* type of DST correction */
}; 
```

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <sys/time.h>  // gettimeofday()需要的头文件。
using namespace std;

int main()
{
  timeval start,end;

  gettimeofday(&start, 0 ); // 计时开始。

  for (int ii=0;ii<1000000000;ii++)
    ;

  gettimeofday(&end, 0 );   // 计时结束。

  // 计算消耗的时长。
  timeval tv;
  tv.tv_usec=end.tv_usec-start.tv_usec;
  tv.tv_sec=end.tv_sec-start.tv_sec;
  if (tv.tv_usec<0)
  {
    tv.tv_usec=1000000-tv.tv_usec;
    tv.tv_sec--;
  }

  cout << "耗时：" << tv.tv_sec << "秒和" << tv.tv_usec << "微秒。\n";
}
```

### <font style="color:black;">程序睡眠</font>
<font style="color:black;background-color:#FFFFFF;">如果需要把程序挂起一段时间，可以使用</font><font style="color:#002060;background-color:#d9d9d9;">sleep()</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">usleep()</font><font style="color:black;background-color:#FFFFFF;">两个库函数。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><unistd.h></font>

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);
```

## <font style="color:black;">Linux的目录操作</font>
### <font style="color:black;">几个简单的目录操作函数</font>
#### 获取当前工作目录
<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><unistd.h></font>

```cpp
char *getcwd(char *buf, size_t size); 
char *get_current_dir_name(void);
```

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  char path1[256];   // linux系统目录的最大长度是255。
  getcwd(path1,256);
  cout << "path1=" << path1 << endl;

  char *path2=get_current_dir_name();
  cout << "path2=" << path2 << endl;
  free(path2);   // 注意释放内存。malloc() new delete
}
```

#### 切换工作目录
<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><unistd.h></font>

```cpp
int chdir(const char *path);
```

<font style="color:black;background-color:#FFFFFF;">返回值：0-成功；其它-失败（目录不存在或没有权限）。</font>

#### 创建目录
<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"><sys/stat.h></font>

```cpp
int mkdir(const char *pathname, mode_t mode);
```

<font style="color:#002060;background-color:#d9d9d9;">pathname</font><font style="color:black;background-color:#FFFFFF;">-</font><font style="color:black;background-color:#FFFFFF;">目录名。</font>

<font style="color:#002060;background-color:#d9d9d9;">mode</font><font style="color:black;background-color:#FFFFFF;">-</font><font style="color:black;background-color:#FFFFFF;">访问权限，如</font><font style="color:black;background-color:#FFFFFF;">0755</font><font style="color:black;background-color:#FFFFFF;">，不要省略前置的</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：0-成功；其它-失败（上级目录不存在或没有权限）。 /tmp/aaa  /tmp/aaa/bbb </font>

#### 删除目录
<font style="color:black;background-color:#FFFFFF;">包含头文件：</font><font style="color:#002060;background-color:#d9d9d9;"> <unistd.h></font>

```cpp
int rmdir(const char *path);
```

<font style="color:#002060;background-color:#d9d9d9;">path</font><font style="color:black;background-color:#FFFFFF;">-</font><font style="color:black;background-color:#FFFFFF;">目录名。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：0-成功；其它-失败（目录不存在或没有权限）。</font>

### <font style="color:black;">获取目录中文件的列表</font>
<font style="color:black;background-color:#FFFFFF;">文件存放在目录中，在处理文件之前，必须先知道目录中有哪些文件，所以要获取目录中文件的列表。</font>

#### 包含头文件
```cpp
#include <dirent.h>
```

#### 相关的库函数
**<font style="color:black;background-color:#FFFFFF;">步骤一：用</font>****<font style="color:#002060;background-color:#d9d9d9;">opendir()</font>****<font style="color:black;background-color:#FFFFFF;">函数打开目录。</font>**

```cpp
DIR *opendir(const char *pathname);
```

<font style="color:black;background-color:#FFFFFF;">成功-返回目录的地址，失败-返回空地址。</font>

**<font style="color:black;background-color:#FFFFFF;">步骤二：用</font>****<font style="color:#002060;background-color:#d9d9d9;">readdir()</font>****<font style="color:black;background-color:#FFFFFF;">函数循环的读取目录。</font>**

```cpp
struct dirent *readdir(DIR *dirp);
```

<font style="color:black;background-color:#FFFFFF;">成功-返回</font><font style="color:#002060;background-color:#d9d9d9;">struct dirent</font><font style="color:black;background-color:#FFFFFF;">结构体的地址，失败-返回空地址。</font>

**<font style="color:black;background-color:#FFFFFF;">步骤三：用</font>****<font style="color:#002060;background-color:#d9d9d9;">closedir()</font>****<font style="color:black;background-color:#FFFFFF;">关闭目录。</font>**

```cpp
int closedir(DIR *dirp);
```

#### 数据结构
<font style="color:black;background-color:#FFFFFF;">目录指针：</font>

```cpp
DIR *目录指针变量名;
```

<font style="color:black;background-color:#FFFFFF;">每次调用</font><font style="color:#002060;background-color:#d9d9d9;">readdir()</font><font style="color:black;background-color:#FFFFFF;">，函数返回</font><font style="color:#002060;background-color:#d9d9d9;">struct dirent</font><font style="color:black;background-color:#FFFFFF;">的地址，存放了本次读取到的内容。</font>

```cpp
struct dirent
{
   long d_ino;                  // inode number 索引节点号。
   off_t d_off;                 // offset to this dirent 在目录文件中的偏移。
   unsigned short d_reclen;     // length of this d_name 文件名长度。
   unsigned char d_type;        // the type of d_name 文件类型。
   char d_name [NAME_MAX+1];    // file name文件名，最长255字符。
};
```

<font style="color:black;background-color:#FFFFFF;">重点关注结构体的</font><font style="color:#002060;background-color:#d9d9d9;">d_name</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">d_type</font><font style="color:black;background-color:#FFFFFF;">成员。</font>

<font style="color:#002060;background-color:#d9d9d9;">d_name</font><font style="color:black;background-color:#FFFFFF;">-</font><font style="color:black;background-color:#FFFFFF;">文件名或目录名。</font>

<font style="color:#002060;background-color:#d9d9d9;">d_type-</font><font style="color:black;background-color:#FFFFFF;">文件的类型，有多种取值，最重要的是</font><font style="color:black;background-color:#FFFFFF;">8</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:black;background-color:#FFFFFF;">4</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:black;background-color:#FFFFFF;">8-</font><font style="color:black;background-color:#FFFFFF;">常规文件（</font><font style="color:black;background-color:#FFFFFF;">A regular file</font><font style="color:black;background-color:#FFFFFF;">）；</font><font style="color:black;background-color:#FFFFFF;">4-</font><font style="color:black;background-color:#FFFFFF;">子目录（</font><font style="color:black;background-color:#FFFFFF;">A directory</font><font style="color:black;background-color:#FFFFFF;">），其它的暂时不关心。注意，</font><font style="color:#002060;background-color:#d9d9d9;">d_name</font><font style="color:black;background-color:#FFFFFF;">的数据类型是字符，不可直接显示。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <dirent.h>
using namespace std;

int main(int argc,char *argv[])
{
  if (argc != 2) { cout << "Using ./demo 目录名\n"; return -1; }

  DIR *dir;   // 定义目录指针。

  // 打开目录。
  if ( (dir=opendir(argv[1])) == nullptr ) return -1;

  // 用于存放从目录中读取到的内容。
  struct dirent *stdinfo=nullptr;

  while (1)
  {
    // 读取一项内容并显示出来。
    if ((stdinfo=readdir(dir)) == nullptr) break;

    cout << "文件名=" << stdinfo->d_name << "，文件类型=" << (int)stdinfo->d_type << endl;
  }

  closedir(dir);   // 关闭目录指针。
}
```

## <font style="color:black;">Linux的系统错误</font>
<font style="color:black;background-color:#FFFFFF;">在C++程序中，如果调用了库函数，可以通过函数的返回值判断调用是否成功。其实，还有一个整型的全局变量</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:black;background-color:#FBF5CB;">存放了函数调用过程中产生的错误代码</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">如果调用库函数失败，可以通过</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">的值来查找原因，这也是调试程序的一个重要方法。</font>

<font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">在</font><font style="color:#002060;background-color:#d9d9d9;"><errno.h></font><font style="color:black;background-color:#FFFFFF;">中声明。</font>

<font style="color:black;background-color:#FFFFFF;">配合 </font><font style="color:#002060;background-color:#d9d9d9;">strerror()</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">perror()</font><font style="color:black;background-color:#FFFFFF;">两个库函数，可以查看出错的详细信息。</font>

### <font style="color:black;">strerror()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">strerror() </font><font style="color:black;background-color:#FFFFFF;">在</font><font style="color:#002060;background-color:#d9d9d9;"><string.h></font><font style="color:black;background-color:#FFFFFF;">中声明，用于获取错误代码对应的详细信息。</font>

```cpp
char *strerror(int errnum);                       		// 非线程安全。
int strerror_r(int errnum, char *buf, size_t buflen);	// 线程安全。
```

<font style="color:black;background-color:#FFFFFF;">gcc8.3.1</font><font style="color:black;background-color:#FFFFFF;">一共有</font><font style="color:black;background-color:#FFFFFF;">133</font><font style="color:black;background-color:#FFFFFF;">个错误代码。</font>

<font style="color:black;background-color:#FFFFFF;">示例一：</font>

```cpp
#include <iostream>
#include <cstring>
using namespace std;
 
int main()
{
  int ii;
 
  for(ii=0;ii<150;ii++)		// gcc8.3.1一共有133个错误代码。
  {
    cout << ii << ":" << strerror(ii) << endl;
  }
}
```

<font style="color:black;background-color:#FFFFFF;">示例二：</font>

```cpp
#include <iostream>
#include <cstring>
#include <cerrno>
#include <sys/stat.h>
using namespace std;

int main()
{
  int iret=mkdir("/tmp/aaa",0755);

  cout << "iret=" << iret << endl;
  cout << errno << ":" << strerror(errno) << endl;
}
```

### <font style="color:black;">perror()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">perror() </font><font style="color:black;background-color:#FFFFFF;">在</font><font style="color:#002060;background-color:#d9d9d9;"><stdio.h></font><font style="color:black;background-color:#FFFFFF;">中声明，用于在控制台显示最近一次系统错误的详细信息，在实际开发中，服务程序在后台运行，通过控制台显示错误信息意义不大。（对调试程序略有帮助）</font>

```cpp
void perror(const char *s);
```

### <font style="color:black;">注意事项</font>
#### 调用库函数失败不一定会设置errno
<font style="color:black;background-color:#E8F7CF;">并不是全部的库函数在调用失败时都会设置errno的值</font><font style="color:black;background-color:#FFFFFF;">，以man手册为准（一般来说，不属于系统调用的函数不会设置errno，属于系统调用的函数才会设置errno）。什么是系统调用？百度“库函数和系统调用的区别”。</font>

| <font style="color:black;background-color:#FFFFFF;">特性</font> | <font style="color:black;background-color:#FFFFFF;">库函数 (Library Function)</font> | <font style="color:black;background-color:#FFFFFF;">系统调用 (System Call)</font> |
| --- | --- | --- |
| **定义** | <font style="color:black;background-color:#FFFFFF;">可重用的代码块，提供常用功能</font> | <font style="color:black;background-color:#FFFFFF;">操作系统提供给应用程序的接口，请求内核服务</font> |
| **目的** | <font style="color:black;background-color:#FFFFFF;">简化开发，提供便捷功能</font> | <font style="color:black;background-color:#FFFFFF;">访问操作系统核心功能，执行特权操作</font> |
| **执行环境** | <font style="color:black;background-color:#FFFFFF;">主要在用户空间，可能封装系统调用</font> | <font style="color:black;background-color:#FFFFFF;">从用户态切换到内核态执行</font> |
| **开销** | <font style="color:black;background-color:#FFFFFF;">较低（若不涉及系统调用），较高（若封装系统调用）</font> | <font style="color:black;background-color:#FFFFFF;">较高（涉及上下文切换和模式切换）</font> |
| **可移植性** | <font style="color:black;background-color:#FFFFFF;">较高（尤其是标准库）</font> | <font style="color:black;background-color:#FFFFFF;">较低（操作系统特定）</font> |
| **与OS关系** | <font style="color:black;background-color:#FFFFFF;">应用程序的一部分，可能间接与OS交互</font> | <font style="color:black;background-color:#FFFFFF;">应用程序与操作系统内核交互的直接通道</font> |
| **抽象级别** | <font style="color:black;background-color:#FFFFFF;">较高，更接近用户</font> | <font style="color:black;background-color:#FFFFFF;">较低，更接近硬件和操作系统内核</font> |


#### errno不能作为调用库函数失败的标志
<font style="color:#002060;background-color:#E8F7CF;">errno</font><font style="color:black;background-color:#E8F7CF;">的值只有在库函数调用发生错误时才会被设置</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#DF2A3F;background-color:#FFFFFF;">当库函数调用成功时，</font><font style="color:#DF2A3F;background-color:#d9d9d9;">errno</font><font style="color:#DF2A3F;background-color:#FFFFFF;">的值不会被修改，不会主动的置为 0</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:#DF2A3F;background-color:#FBF5CB;">在实际开发中，判断函数执行是否成功还得靠函数的返回值，只有在返回值是失败的情况下，才需要关注errno的值</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <iostream>
#include <cstring>    // strerror()函数需要的头文件。
#include <cerrno>     // errno全局变量的头文件。
#include <sys/stat.h> // mkdir()函数需要的头文件。
using namespace std;

int main()
{
  int iret=mkdir("/tmp/aaa/bb/cc/dd",0755);
  if (iret!=0)
  {
    cout << "iret=" << iret << endl;
    cout << errno << ":" << strerror(errno) << endl;
    cout<<"是这里输出的"<<endl;
    perror("调用mkdir(/tmp/aaa/bb/cc/dd)失败");
  }

  iret=mkdir("/tmp/dd",0755);//成功创建目录
  if (iret!=0)
  {
    cout << "iret=" << iret << endl;
    cout << errno << ":" << strerror(errno) << endl;
    perror("调用mkdir(/tmp/dd)失败");
  }
}
```

## <font style="color:black;">目录和文件的更多操作</font>
### <font style="color:black;">access()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">access()</font><font style="color:black;background-color:#FFFFFF;">函数用于</font><font style="color:black;background-color:#E8F7CF;">判断当前用户对目录或文件的存取权限</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font>

```cpp
#include <unistd.h>
```

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int access(const char *pathname, int mode);
```

<font style="color:black;background-color:#FFFFFF;">参数说明：</font>

<font style="color:#002060;background-color:#d9d9d9;">pathname</font><font style="color:black;background-color:#FFFFFF;">  </font><font style="color:black;background-color:#FFFFFF;">目录或文件名。</font>

<font style="color:#002060;background-color:#d9d9d9;">mode</font><font style="color:black;background-color:#FFFFFF;">         需要判断的存取权限。在头文件</font><font style="color:#002060;background-color:#d9d9d9;"><unistd.h></font><font style="color:black;background-color:#FFFFFF;">中的预定义如下：</font>

```cpp
#define R_OK 	4 	// 判断是否有读权限。
#define W_OK	2 	// 判断是否有写权限。
#define X_OK 	1 	// 判断是否有执行权限。
#define F_OK 	0  	// 判断是否存在。
```

<font style="color:black;background-color:#FFFFFF;">返回值：</font>

<font style="color:black;background-color:#FFFFFF;">当</font><font style="color:#002060;background-color:#d9d9d9;">pathname</font><font style="color:black;background-color:#FFFFFF;">满足</font><font style="color:#002060;background-color:#d9d9d9;">mode</font><font style="color:black;background-color:#FFFFFF;">权限返回</font><font style="color:black;background-color:#FFFFFF;">0</font><font style="color:black;background-color:#FFFFFF;">，不满足返回</font><font style="color:black;background-color:#FFFFFF;">-1</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>

<font style="color:black;background-color:#FFFFFF;">在实际开发中，</font><font style="color:#002060;background-color:#d9d9d9;">access()</font><font style="color:black;background-color:#FFFFFF;">函数</font><font style="color:black;background-color:#FBF5CB;">主要用于判断目录或文件是否存在</font><font style="color:black;background-color:#FFFFFF;">。</font>

```cpp
// 样例代码
// 样例代码
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  if (argc != 2)  { cout << "Using:./demo 文件或目录名\n"; return -1; }

  if(access(argv[1],F_OK)!=0){
    cout << "文件或目录"<<argv[1]<<"不存在\n";
    return -1;
  }
  cout << "文件或目录"<<argv[1]<<"存在\n";
  return 0;
}

/*
编译运行：
➜  3-4 More operations on directories and files git:(main) ✗ g++ -o demo01 demo01.cpp -g
➜  3-4 More operations on directories and files git:(main) ✗ ls
demo01  demo01.cpp
➜  3-4 More operations on directories and files git:(main) ✗ ./demo01
Using:./demo 文件或目录名
➜  3-4 More operations on directories and files git:(main) ✗ ./demo01 /home
文件或目录/home存在
➜  3-4 More operations on directories and files git:(main) ✗ ./demo01 /file
文件或目录/file不存在
*/
```

### <font style="color:black;">stat()库函数</font>
#### stat结构体
<font style="color:#002060;background-color:#d9d9d9;">struct stat</font><font style="color:black;background-color:#FFFFFF;">结构体用于存放目录或文件的详细信息，如下：</font>

```cpp
struct stat
{
  dev_t st_dev;   	// 文件的设备编号。
  ino_t st_ino;   		// 文件的i-node。
  mode_t st_mode; 	// 文件的类型和存取的权限。
  nlink_t st_nlink;   	// 连到该文件的硬连接数目，刚建立的文件值为1。
  uid_t st_uid;   		// 文件所有者的用户识别码。
  gid_t st_gid;   		// 文件所有者的组识别码。
  dev_t st_rdev;  	// 若此文件为设备文件，则为其设备编号。
  off_t st_size;  		// 文件的大小，以字节计算。
  size_t st_blksize;	// I/O 文件系统的I/O 缓冲区大小。
  size_t st_blocks;  	// 占用文件区块的个数。
  time_t st_atime;  	// 文件最近一次被存取或被执行的时间，
 					// 在用mknod、 utime、read、write 与tructate 时改变。
  time_t st_mtime;  	// 文件最后一次被修改的时间，
					// 在用mknod、 utime 和write 时才会改变。
  time_t st_ctime;  	// 最近一次被更改的时间，在文件所有者、组、 权限被更改时更新。
};
```

<font style="color:#002060;background-color:#d9d9d9;">struct stat</font><font style="color:black;background-color:#FFFFFF;">结构体的成员变量比较多，</font><font style="color:#DF2A3F;background-color:#FBF5CB;">重点关注</font><font style="color:#002060;background-color:#d9d9d9;">st_mode</font><font style="color:black;background-color:#FFFFFF;">、</font><font style="color:#002060;background-color:#d9d9d9;">st_size</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">st_mtime</font><font style="color:black;background-color:#FFFFFF;">成员。</font>

<font style="color:black;background-color:#FFFFFF;">注意：</font><font style="color:#002060;background-color:#d9d9d9;">st_mtime</font><font style="color:black;background-color:#FFFFFF;">是一个整数表示的时间，需要程序员自己写代码转换格式。</font>

<font style="color:#002060;background-color:#d9d9d9;">st_mode</font><font style="color:black;background-color:#FFFFFF;">成员的取值很多，用以下两个宏来判断：</font>

```cpp
S_ISREG(st_mode)  // 是否为普通文件，如果是，返回真。 
S_ISDIR(st_mode)  // 是否为目录，如果是，返回真。
```

#### stat()库函数
<font style="color:black;background-color:#FFFFFF;">包含头文件：</font>

```cpp
#include <sys/stat.h>
```

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int stat(const char *path, struct stat *buf);
```

<font style="color:#002060;background-color:#d9d9d9;">stat()</font><font style="color:black;background-color:#FFFFFF;">函数获取</font><font style="color:#002060;background-color:#d9d9d9;">path</font><font style="color:black;background-color:#FFFFFF;">参数</font><font style="color:#DF2A3F;background-color:#FFFFFF;">指定目录或文件的详细信息</font><font style="color:black;background-color:#FFFFFF;">，保存到</font><font style="color:#002060;background-color:#d9d9d9;">buf</font><font style="color:black;background-color:#FFFFFF;">结构体中。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：</font><font style="color:black;background-color:#FFFFFF;">0-</font><font style="color:black;background-color:#FFFFFF;">成功，</font><font style="color:black;background-color:#FFFFFF;">-1-</font><font style="color:black;background-color:#FFFFFF;">失败，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstring>    // strerror()函数需要的头文件
#include <cerrno>     // errno全局变量的头文件
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
  if (argc != 2)  { cout << "Using:./demo 文件或目录名\n"; return -1; }

  struct stat st;  // 存放目录或文件详细信息的结构体。

  // 获取目录或文件的详细信息
  if (stat(argv[1],&st) != 0)
  {
    cout << "stat(" << argv[1] << "):" << strerror(errno) << endl; return -1;
  }

  if (S_ISREG(st.st_mode))
    cout << argv[1] << "是一个文件(" << "mtime=" << st.st_mtime << ",size=" << st.st_size << ")\n";
  if (S_ISDIR(st.st_mode))
cout << argv[1] << "是一个目录(" << "mtime=" << st.st_mtime << ",size=" << st.st_size << ")\n";
}

/*
编译运行：
➜  3-4 More operations on directories and files git:(main) ✗ ls
demo01  demo01.cpp  demo02.cpp
➜  3-4 More operations on directories and files git:(main) ✗ g++ -o demo02 demo02.cpp -g
➜  3-4 More operations on directories and files git:(main) ✗ ls
demo01  demo01.cpp  demo02  demo02.cpp
➜  3-4 More operations on directories and files git:(main) ✗ ./demo02      
Using:./demo 文件或目录名
➜  3-4 More operations on directories and files git:(main) ✗ ./demo02 /home                   
/home是一个目录(mtime=1744536977,size=4096)
*/
```

### <font style="color:black;">utime()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">utime()</font><font style="color:black;background-color:#FFFFFF;">函数用于修改目录或文件的时间。</font>

<font style="color:black;">包含头文件：</font>

```cpp
#include <sys/types.h>
#include <utime.h>
```

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int utime(const char *filename, const struct utimbuf *times);
```

<font style="color:#002060;background-color:#d9d9d9;">utime()</font><font style="color:black;background-color:#FFFFFF;">函数用来修改参数</font><font style="color:#002060;background-color:#d9d9d9;">filename</font><font style="color:black;background-color:#FFFFFF;">的</font><font style="color:#002060;background-color:#d9d9d9;">st_atime</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">st_mtime</font><font style="color:black;background-color:#FFFFFF;">。如果参数</font><font style="color:#002060;background-color:#d9d9d9;">times</font><font style="color:black;background-color:#FFFFFF;">为空地址，则设置为当前时间。结构</font><font style="color:#002060;background-color:#d9d9d9;">utimbuf</font><font style="color:black;background-color:#FFFFFF;">声明如下：</font>

```cpp
struct utimbuf
{
  time_t actime;
  time_t modtime;
};
```

<font style="color:black;background-color:#FFFFFF;">返回值：0-成功，-1-失败，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>

### <font style="color:black;">rename()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">rename()</font><font style="color:black;background-color:#FFFFFF;">函数用于</font><font style="color:#DF2A3F;background-color:#FBF5CB;">重命名目录或文件</font><font style="color:black;background-color:#FFFFFF;">，相当于操作系统的</font><font style="color:#002060;background-color:#d9d9d9;">mv</font><font style="color:black;background-color:#FFFFFF;">命令。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font>

```cpp
#include <stdio.h>
```

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int rename(const char *oldpath, const char *newpath);
```

<font style="color:black;background-color:#FFFFFF;">参数说明：</font>

<font style="color:#002060;background-color:#d9d9d9;">oldpath</font><font style="color:black;background-color:#FFFFFF;"> </font><font style="color:black;background-color:#FFFFFF;">     </font><font style="color:black;background-color:#FFFFFF;">原目录或文件名。</font>

<font style="color:#002060;background-color:#d9d9d9;">newpath</font><font style="color:black;background-color:#FFFFFF;"> </font><font style="color:black;background-color:#FFFFFF;">   </font><font style="color:black;background-color:#FFFFFF;">目标目录或文件名。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：0-成功，-1-失败，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>

### <font style="color:black;">remove()库函数</font>
<font style="color:#002060;background-color:#d9d9d9;">remove()</font><font style="color:black;background-color:#FFFFFF;">函数</font><font style="color:#DF2A3F;background-color:#FBF5CB;">用于删除目录或文件</font><font style="color:black;background-color:#FFFFFF;">，相当于操作系统的</font><font style="color:#002060;background-color:#d9d9d9;">rm</font><font style="color:black;background-color:#FFFFFF;">命令。</font>

<font style="color:black;background-color:#FFFFFF;">包含头文件：</font>

```cpp
#include <stdio.h>
```

<font style="color:black;background-color:#FFFFFF;">函数声明：</font>

```cpp
int remove(const char *pathname);
```

<font style="color:black;background-color:#FFFFFF;">参数说明：</font>

<font style="color:#002060;background-color:#d9d9d9;">pathname</font><font style="color:black;background-color:#FFFFFF;"> </font><font style="color:black;background-color:#FFFFFF;">待删除的目录或文件名。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：0-成功，-1-失败，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>