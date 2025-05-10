## <font style="color:black;">快速入门Linux</font>
<font style="color:black;background-color:#FFFFFF;">用两天的时间学习《程序员两天快速入门Linux》。</font>

## <font style="color:black;">安装软件包</font>
### 安装C和C++的编译器
```cpp
sudo apt update
sudo apt install build-essential
```

### 升级编译器
```cpp
sudo apt update
sudo apt install gcc g++
```

### 安装库函数的帮助文档
```cpp
sudo apt update
sudo apt install manpages manpages-dev manpages-posix manpages-posix-dev
```

#### <font style="color:black;background-color:#FFFFFF;">帮助文档的使用</font>
```cpp
man 级别 命令或函数
//显示帮助的界面可以用vi的命令，q退出。
```

#### <font style="color:black;">man的级别</font>
**<font style="color:#DF2A3F;background-color:#FFFFFF;">1-用户命令</font>**<font style="color:black;background-color:#FFFFFF;">；</font>

<font style="color:black;background-color:#FFFFFF;">2-系统接口；</font>

**<font style="color:#DF2A3F;background-color:#FFFFFF;">3-库函数</font>**<font style="color:black;background-color:#FFFFFF;">；</font>

<font style="color:black;background-color:#FFFFFF;">4-特殊文件，比如设备文件；</font>

<font style="color:black;background-color:#FFFFFF;">5-文件；</font>

<font style="color:black;background-color:#FFFFFF;">6-游戏；</font>

<font style="color:black;background-color:#FFFFFF;">7-系统的软件包；</font>

<font style="color:black;background-color:#FFFFFF;">8-系统管理命令；</font>

<font style="color:black;background-color:#FFFFFF;">9-内核。</font>

## <font style="color:black;">编译</font>
```cpp
gcc/g++ 选项 源代码文件1 源代码文件2 源代码文件
```

<font style="color:black;background-color:#FFFFFF;">常用选项：</font>

| -o | <font style="color:black;">指定输出的文件名，这个名称不能和源文件同名。如果不给出这个选项，则生成可执行文件a.out。</font> |
| --- | --- |
| -g | <font style="color:black;">如果想对源代码进行调试，必须加入这个选项。</font> |
| -On | <font style="color:black;">在编译、链接过程中进行优化处理，生成的</font>[可执行程序](https://baike.baidu.com/item/%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6?fromModule=lemma_inlink)<font style="color:black;">效率将更高。</font> |
| -c | <font style="color:black;">只</font>[编译](https://baike.baidu.com/item/%E7%BC%96%E8%AF%91?fromModule=lemma_inlink)<font style="color:black;">，不链接成为</font>[可执行文件](https://baike.baidu.com/item/%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6?fromModule=lemma_inlink)<font style="color:black;">，通常用于把源文件编译成静态库或动态库。</font> |
| -std=c++11 | <font style="color:black;">支持C++11标准。</font> |


优化选项：

| -O0 | <font style="color:black;">不做任何优化，这是默认的编译选项。</font> |
| --- | --- |
| -O或-O1 | <font style="color:black;">对程序做部分编译优化，对于大函数，优化编译占用稍微多的时间和相当大的内存。使用本项优化，编译器会尝试减小生成代码的尺寸，以及缩短执行时间，但并不执行需要占用大量编译时间的优化。</font> |
| -O2 | **<font style="color:black;">这是推荐的优化等级</font>**<font style="color:black;">。与</font><font style="color:#002060;background-color:#d9d9d9;">O1</font><font style="color:black;">比较而言，</font><font style="color:#002060;background-color:#d9d9d9;">O2</font><font style="color:black;">优化增加了编译时间的基础上，提高了生成代码的执行效率。</font> |
| -O3 | <font style="color:black;">这是最高最危险的优化等级。用这个选项会延长编译代码的时间，并且在使用gcc4.x的系统里不应全局启用。自从3.x版本以来gcc的行为已经有了极大地改变。在3.x，</font><font style="color:#002060;background-color:#d9d9d9;">-O3</font><font style="color:black;">生成的代码也只是比</font><font style="color:#002060;background-color:#d9d9d9;">-O2</font><font style="color:black;">快一点点而已，而gcc4.x中还未必更快。用</font><font style="color:#002060;background-color:#d9d9d9;">-O3</font><font style="color:black;">来编译所有的软件包将产生更大体积更耗</font>[内存](https://so.csdn.net/so/search?q=%E5%86%85%E5%AD%98&spm=1001.2101.3001.7020)<font style="color:black;">的二进制文件，大大增加编译失败的机会或不可预知的程序行为（包括错误）。这样做将得不偿失，记住过犹不及。在gcc 4.x.中使用</font><font style="color:#002060;background-color:#d9d9d9;">-O3</font><font style="color:black;">是不推荐的。</font> |


<font style="color:black;background-color:#FFFFFF;">如果使用了优化选项：</font>

<font style="color:black;background-color:#FFFFFF;">1）编译的时间将更长；</font>

<font style="color:black;background-color:#FFFFFF;">2）目标程序不可调试；</font>

<font style="color:black;background-color:#FFFFFF;">3）有效果，但是不可能显著提升程序的性能。</font>

## <font style="color:black;">静态库和动态库</font>
<font style="color:black;background-color:#FFFFFF;">在实际开发中，我们把通用的函数和类分文件编写，称之为</font><font style="color:#DF2A3F;background-color:#FFFFFF;">库</font><font style="color:black;background-color:#FFFFFF;">。在其它的程序中，可以使用库中的函数和类。</font>

<font style="color:black;background-color:#FFFFFF;">一般来说，通用的函数和类不提供源代码文件（安全性、商业机密），而是编译成二进制文件。</font>

<font style="color:#DF2A3F;background-color:#FBF5CB;">库的二进制文件有两种</font><font style="color:black;background-color:#FFFFFF;">：</font><font style="color:black;background-color:#E8F7CF;">静态库</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:black;background-color:#E8F7CF;">动态库</font><font style="color:black;background-color:#FFFFFF;">。</font>

### <font style="color:black;">静态库（.a）</font>
#### 制作静态库
```cpp
g++ -c -o lib库名.a 源代码文件清单
```

#### 使用静态库
<font style="color:black;background-color:#FFFFFF;">不规范的做法：</font>

```cpp
g++ 选项 源代码文件名清单 静态库文件名
```

<font style="color:black;background-color:#FFFFFF;">规范的做法：</font>

```cpp
g++ 选项 源代码文件名清单 -l库名 -L库文件所在的目录名
```

#### 静态库的概念
<font style="color:black;background-color:#FFFFFF;">程序在编译时会把库文件的二进制代码链接到目标程序中，这种方式称为静态链接。</font>

<font style="color:black;background-color:#FFFFFF;">如果多个程序中用到了同一静态库中的函数或类，就会存在多份拷贝。</font>

#### 静态库的特点
1. <font style="color:black;">静态库的链接是在编译时期完成的，</font><font style="color:#DF2A3F;">执行的时候代码加载速度快</font><font style="color:black;">。</font>
2. <font style="color:black;background-color:#FFFFFF;">目标程序的可执行文件比较大，浪费空间。</font>
3. <font style="color:black;background-color:#FFFFFF;">程序的更新和发布不方便，如果某一个静态库更新了，所有使用它的程序都需要重新编译。</font>

### <font style="color:black;">动态库(.so)</font>
#### 制作动态库
```cpp
g++ -fPIC -shared -o lib库名.so 源代码文件清单
```

#### 使用动态库
<font style="color:black;background-color:#FFFFFF;">不规范的做法：</font>

```cpp
g++ 选项 源代码文件名清单 动态库文件名
```

<font style="color:black;background-color:#FFFFFF;">规范的做法：</font>

```cpp
g++ 选项 源代码文件名清单 -l库名 -L库文件所在的目录名
```

<font style="color:#DF2A3F;background-color:#FFFFFF;">运行可执行程序的时候，需要提前设置</font>**<font style="color:#DF2A3F;background-color:#d9d9d9;">LD_LIBRARY_PATH</font>**<font style="color:#DF2A3F;background-color:#FFFFFF;">环境变量</font><font style="color:black;background-color:#FFFFFF;">。</font>

#### 动态库的概念
<font style="color:black;background-color:#FFFFFF;">程序在编译时不会把库文件的二进制代码链接到目标程序中，而是在运行时候才被载入。</font>

<font style="color:black;background-color:#FFFFFF;">如果多个进程中用到了同一动态库中的函数或类，那么在内存中只有一份，避免了空间浪费问题。</font>

#### 动态库的特点
1. <font style="color:black;background-color:#FFFFFF;">程序在运行的过程中，需要用到动态库的时候才把动态库的二进制代码载入内存。</font>
2. <font style="color:black;background-color:#FFFFFF;">可以实现进程之间的代码共享，因此动态库也称为共享库。</font>
3. <font style="color:black;background-color:#FFFFFF;">程序升级比较简单，不需要重新编译程序，只需要更新动态库就行了。</font>

### <font style="color:black;">优先使用动态库</font>
<font style="color:black;background-color:#FFFFFF;">如果动态库和静态库同时存在，编译器将优先使用动态库。</font>

## <font style="color:black;background-color:#FFFFFF;">源代码</font>
### tools/public.h
```cpp
// 通用函数和类的头文件。
#include <iostream>

// 声明一个通用的函数。
void func();

// 声明一个通用的类。
class AA
{
public:
  void show();
};
```

### tools/public.cpp
```cpp
// 通用函数和类的代码实现文件。
#include "public.h"
using namespace std;

// 通用函数的代码实现。
void func()
{
  cout << "升级了调用了func()函数。\n";
}

// 通用类的代码实现。
void AA::show()
{
  cout << "升级了我是一只傻傻鸟。\n";
}
```

### app/demo01.cpp
```cpp
#include "/home/wucz/tools/public.h"  // 包含通用函数和类的头文件。
using namespace std;

int main()
{
  func();    // 调用通用的函数。

  AA a;      // 用通用类声明对象。
  a.show();  // 调用对象的方法。
}
```

## <font style="color:black;">makefile</font>
<font style="color:black;background-color:#FFFFFF;">在实际开发中，项目的源代码文件比较多，按类型、功能、模块分别存放在不同的目录和文件中，哪些文件需要先编译，那些文件后编译，那些文件需要重新编译，还有更多更复杂的操作。</font>

<font style="color:black;background-color:#FFFFFF;">make是一个强大的实用工具，用于</font><font style="color:#DF2A3F;background-color:#FFFFFF;">管理项目的编译和链接</font><font style="color:black;background-color:#FFFFFF;">。make需要一个编译规则文件makefile，可实现自动化编译。</font>

### <font style="color:black;">app/demo01.cpp</font>
```cpp
#include "public.h"  // 包含通用函数和类的头文件。
#include "myapi.h"     // 包含另一个通用函数和类的头文件。
using namespace std;

int main()
{
  func();    // 调用通用的函数。

  func1();   // 调用另一个通用的函数。

  AA a;      // 用通用类声明对象。
  a.show();  // 调用对象的方法。

  BB b;      // 用另一个通用类声明对象。
  b.show();  // 调用对象的方法。
}
```

### <font style="color:black;">app/makefile</font>
```makefile
INCLUDEDIR=-I/home/wucz/tools -I/home/wucz/api
LIBDIR=-L/home/wucz/tools -L/home/wucz/api

all:demo01 demo02 demo03

demo01:demo01.cpp
        g++ -o demo01 demo01.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi
        cp demo01 /tmp/.

demo02:demo02.cpp
        g++ -o demo02 demo02.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi

demo03:demo03.cpp
        g++ -o demo03 demo03.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi

clean:
        rm -f demo01 demo02 demo03
```

### <font style="color:black;">tools/public.h</font>
```makefile
// 通用函数和类的头文件。
#include <iostream>

// 声明一个通用的函数。
void func();

// 声明一个通用的类。
class AA
{
public:
  void show();
};
```

### <font style="color:black;">tools/public.cpp</font>
```cpp
// 通用函数和类的代码实现文件。
#include "public.h"
using namespace std;

// 通用函数的代码实现。
void func()
{
    cout << "升级了调用了func()函数。\n";
}

// 通用类的代码实现。
void AA::show()
{
    cout << "升级了我是一只傻傻鸟。\n";
}
```

### <font style="color:black;">tools/makefile</font>
```makefile
# 指定编译的目标文件是libpublic.a和libpublic.so
all:libpublic.a \
    libpublic.so

# 编译libpublic.a需要依赖public.h和public.cpp
# 如果被依赖文件内容发生了变化，将重新编译libpublic.a
libpublic.a:public.h public.cpp
        g++ -c -o libpublic.a public.cpp

libpublic.so:public.h public.cpp
        g++ -fPIC -shared -o libpublic.so public.cpp

# clean用于清理编译目标文件，仅在make clean才会执行。
clean:
        rm -f libpublic.a libpublic.so

```

### <font style="color:black;">api/myapi.h</font>
```cpp
// 另一个通用函数和类的头文件。
#include <iostream>

// 声明一个通用的函数。
void func1();

// 声明一个通用的类。
class BB
{
public:
void show();
};
```

### <font style="color:black;">api/myapi.cpp</font>
```cpp
// 另一个通用函数和类的代码实现文件。
#include "myapi.h"
using namespace std;

// 通用函数的代码实现。
void func1()
{
  cout << "调用了func1()函数。\n";
}

// 通用类的代码实现。
void BB::show()
{
  cout << "你是一只傻傻鸟。\n";
}
```

### <font style="color:black;">api/makefile</font>
```makefile
# 指定编译的目标文件是libmyapi.a和libmyapi.so
all:libmyapi.a libmyapi.so

# 编译libmyapi.a需要依赖myapi.h和myapi.cpp
# 如果被依赖文件内容发生了变化，将重新编译libmyapi.a
libmyapi.a:myapi.h myapi.cpp
        g++ -c -o libmyapi.a myapi.cpp

libmyapi.so:myapi.h myapi.cpp
        g++ -fPIC -shared -o libmyapi.so myapi.cpp

# clean用于清理编译目标文件，仅在make clean才会执行。
clean:
        rm -f libmyapi.a libmyapi.so

```

## <font style="color:black;">main函数的参数</font>
### <font style="color:black;">main函数的参数</font>
<font style="color:#002060;background-color:#d9d9d9;">main</font><font style="color:black;background-color:#FFFFFF;">函数有三个参数，</font><font style="color:#002060;background-color:#d9d9d9;">argc</font><font style="color:black;background-color:#FFFFFF;">、</font><font style="color:#002060;background-color:#d9d9d9;">argv</font><font style="color:black;background-color:#FFFFFF;">和</font><font style="color:#002060;background-color:#d9d9d9;">envp</font><font style="color:black;background-color:#FFFFFF;">，它的标准写法如下：</font>

```cpp
int main(int argc,char *argv[],char *envp[])
{
    return 0;
}
```

| argc | <font style="color:black;">存放了程序参数的个数，包括程序本身。</font> |
| --- | --- |
| argv | <font style="color:black;">字符串的数组，存放了每个参数的值，包括程序本身。</font> |
| envp | <font style="color:black;">字符串的数组，存放了环境变量，数组的最后一个元素是空。</font> |


<font style="color:black;background-color:#FFFFFF;">在程序中，如果不关心</font><font style="color:#002060;background-color:#d9d9d9;">main()</font><font style="color:black;background-color:#FFFFFF;">函数的参数，可以省略不写。</font>

```cpp
#include<iostream>
using namespace std;
/*
    1. argc 表示命令行参数的个数
    2. argv 是一个指针数组，每个元素是一个字符指针，指向一个字符串
    3. argv[0] 是程序的名称
    4. argv[1] 是第一个命令行参数
    5. argv[2] 是第二个命令行参数
*/
int main(int argc, char *argv[], char *environ[]) {
    cout<<"一共有"<<argc<<"个参数"<<endl;
    // 显示全部的参数
    for(int i=0;i<argc;i++) {
        cout<<"第"<<i<<"个参数是"<<argv[i]<<endl;
    }
    // 显示全部环境变量
    for(int i=0;environ[i]!=NULL;i++) {// environ是一个全局变量，是一个指针数组，每个元素是一个字符指针，指向一个字符串.最后一个元素是NULL
        // 显示第i个环境变量
        // environ[i] 是一个字符指针，指向一个字符串
        // environ[i] 是一个字符串
        cout<<"第"<<i<<"个环境变量是"<<environ[i]<<endl;
    }
}
```

### <font style="color:black;">操作环境变量</font>
#### 设置环境变量
```makefile
int setenv(const char *name, const char *value, int overwrite);
```

<font style="color:#002060;background-color:#d9d9d9;">name</font><font style="color:black;background-color:#FFFFFF;">   </font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">环境变量名。</font>

<font style="color:#002060;background-color:#d9d9d9;">value</font><font style="color:black;background-color:#FFFFFF;">    </font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">环境变量的值。</font>

<font style="color:#002060;background-color:#d9d9d9;">overwrite</font><font style="color:black;background-color:#FFFFFF;">   </font><font style="color:black;background-color:#FFFFFF;">0-</font><font style="color:black;background-color:#FFFFFF;">如果环境不存在，增加新的环境变量，如果环境变量已存在，不替换其值；非</font><font style="color:black;background-color:#FFFFFF;">0-</font><font style="color:black;background-color:#FFFFFF;">如果环境不存在，增加新的环境变量，如果环境变量已存在，替换其值。</font>

<font style="color:black;background-color:#FFFFFF;">返回值：</font><font style="color:black;background-color:#FFFFFF;">0-</font><font style="color:black;background-color:#FFFFFF;">成功；</font><font style="color:black;background-color:#FFFFFF;">-1-</font><font style="color:black;background-color:#FFFFFF;">失败（失败的情况极少见）。</font>

<font style="color:#DF2A3F;background-color:#FBE4E7;">注意</font><font style="color:black;background-color:#FFFFFF;">：</font><font style="color:black;background-color:#E8F7CF;">此函数设置的环境变量只对本进程有效，不会影响shell的</font>[<font style="background-color:#E8F7CF;">环境变量</font>](https://baike.baidu.com/item/%E7%8E%AF%E5%A2%83%E5%8F%98%E9%87%8F?fromModule=lemma_inlink)<font style="color:black;background-color:#FFFFFF;">。如果在运行程序时执行了setenv()函数，进程终止后再次运行该程序，上次的设置是无效的。</font>

#### 获取环境变量的值
```makefile
char *getenv(const char *name);
```

### <font style="color:black;">示例</font>
```cpp
#include <iostream>
using namespace std;

int main(int argc,char *argv[],char *envp[])
{
  if (argc!=4)
  {
    cout << "表白神器程序的使用方法：./demo 追求者姓名 被追求者姓名 表白内容\n";
    return -1;
  }

  cout << argv[1] << "开始向" << argv[2] << "表白。\n";
  cout << argv[3] << endl;
  cout << argv[1] << "表白完成。\n";

  return 0;

  cout << "一共有" << argc << "个参数。\n";

  // 显示全部的参数。
  for (int ii=0;ii<argc;ii++)
  {
    cout << "第" << ii << "个参数：" << argv[ii] << endl;
  }
  // 显示全部的环境变量。
  for (int ii=0;envp[ii]!=0;ii++)  // 环境变量数组最后一个元素是0。
  {
    cout << envp[ii] << endl;
  }

  // 设置环境变量AA。
  setenv("AA","aaaa",0);

  // 显示环境变量AA的值。
  cout << "AA=" << getenv("AA") << endl;

  return 0;
}

```

## <font style="color:black;">gdb的常用命令</font>
<font style="color:black;">如果程序有问题，不要问别人为什么会这样，而是立即动手调试。</font>

### <font style="color:black;">安装gdb</font>
```cpp
sudo apt update
sudo apt install gdb
```

### <font style="color:black;">gdb常用命令</font>
<font style="color:black;background-color:#FFFFFF;">如果希望程序可调试，编译时需要加</font><font style="color:#002060;background-color:#d9d9d9;">-g</font><font style="color:black;background-color:#FFFFFF;">选项，并且，不能使用</font><font style="color:#002060;background-color:#d9d9d9;">-O</font><font style="color:black;background-color:#FFFFFF;">的优化选项。</font>

<font style="color:#002060;background-color:#d9d9d9;">gdb 目标程序</font>

| **<font style="color:black;background-color:#FFFFFF;">命令</font>** | **<font style="color:black;background-color:#FFFFFF;">简写</font>** | **<font style="color:black;background-color:#FFFFFF;">命令说明</font>** |
| --- | --- | --- |
| <font style="color:black;background-color:#FFFFFF;">set args</font> |  | <font style="color:black;background-color:#FFFFFF;">设置程序运行的参数。</font><br/><font style="color:black;background-color:#FFFFFF;">例如：</font><font style="color:black;background-color:#FFFFFF;">./demo </font><font style="color:black;background-color:#FFFFFF;">张三 西施 我是一只傻傻鸟</font><br/><font style="color:black;background-color:#FFFFFF;">设置参数的方法是：</font><br/><font style="color:black;background-color:#FFFFFF;">set args </font><font style="color:black;background-color:#FFFFFF;">张三 西施 我是一只傻傻鸟</font> |
| <font style="color:black;background-color:#FFFFFF;">break</font> | <font style="color:black;background-color:#FFFFFF;">b</font> | <font style="color:black;background-color:#FFFFFF;">设置断点，</font><font style="color:black;background-color:#FFFFFF;">b 20 </font><font style="color:black;background-color:#FFFFFF;">表示在第</font><font style="color:black;background-color:#FFFFFF;">20</font><font style="color:black;background-color:#FFFFFF;">行设置断点，可以设置多个断点。</font> |
| <font style="color:black;background-color:#FFFFFF;">run</font> | <font style="color:black;background-color:#FFFFFF;">r</font> | <font style="color:black;background-color:#FFFFFF;">开始运行程序</font><font style="color:black;background-color:#FFFFFF;">, </font><font style="color:black;background-color:#FFFFFF;">程序运行到断点的位置会停下来，如果没有遇到断点，程序一直运行下去。</font> |
| <font style="color:black;background-color:#FFFFFF;">next</font> | <font style="color:black;background-color:#FFFFFF;">n</font> | <font style="color:black;background-color:#FFFFFF;">执行当前行语句，如果该语句为函数调用，不会进入函数内部。 </font><font style="color:black;background-color:#E8F7CF;">VS的F10</font> |
| <font style="color:black;background-color:#FFFFFF;">step</font> | <font style="color:black;background-color:#FFFFFF;">s</font> | <font style="color:black;background-color:#FFFFFF;">执行当前行语句，如果该语句为函数调用，则进入函数内部。</font><font style="color:black;background-color:#E8F7CF;">VS的F11</font><br/><font style="color:black;background-color:#FFFFFF;">注意了，如果函数是库函数或第三方提供的函数，用</font><font style="color:black;background-color:#FFFFFF;">s</font><font style="color:black;background-color:#FFFFFF;">也是进不去的，因为没有源代码，如果是自定义的函数，只要有源码就可以进去。</font> |
| <font style="color:black;background-color:#FFFFFF;">print</font> | <font style="color:black;background-color:#FFFFFF;">p</font> | <font style="color:black;background-color:#FFFFFF;">显示变量或表达式的值，如果</font><font style="color:black;background-color:#FFFFFF;">p</font><font style="color:black;background-color:#FFFFFF;">后面是表达式，会执行这个表达式。</font> |
| <font style="color:black;background-color:#FFFFFF;">continue</font> | <font style="color:black;background-color:#FFFFFF;">c</font> | <font style="color:black;background-color:#FFFFFF;">继续运行程序，遇到下一个断点停止，如果没有遇到断点，程序将一直运行。</font><br/><font style="color:black;background-color:#E8F7CF;">VS的F5</font> |
| <font style="color:black;background-color:#FFFFFF;">set var</font> |  | <font style="color:black;background-color:#FFFFFF;">设置变量的值。</font><br/><font style="color:black;background-color:#FFFFFF;">假设程序中定义了两个变量：</font><br/><font style="color:black;background-color:#FFFFFF;">int ii; </font><br/><font style="color:black;background-color:#FFFFFF;">char name[21];</font><br/><font style="color:black;background-color:#FFFFFF;">set var ii=10 </font><font style="color:black;background-color:#FFFFFF;">把</font><font style="color:black;background-color:#FFFFFF;">ii</font><font style="color:black;background-color:#FFFFFF;">的值设置为</font><font style="color:black;background-color:#FFFFFF;">10</font><font style="color:black;background-color:#FFFFFF;">；</font><br/><font style="color:black;background-color:#FFFFFF;">set var name="</font><font style="color:black;background-color:#FFFFFF;">西施</font><font style="color:black;background-color:#FFFFFF;">"</font><font style="color:black;background-color:#FFFFFF;">。</font> |
| <font style="color:black;background-color:#FFFFFF;">quit</font> | <font style="color:black;background-color:#FFFFFF;">q</font> | <font style="color:black;background-color:#FFFFFF;">退出</font><font style="color:black;background-color:#FFFFFF;">gdb</font><font style="color:black;background-color:#FFFFFF;">。</font> |


<font style="color:black;background-color:#FFFFFF;">注意：在gdb中，用上下光标键可以选择执行过的gdb命令。</font>

### <font style="color:black;">示例</font>
```cpp
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
```

```cpp
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
```

## <font style="color:black;">gdb调试core文件</font>
<font style="color:black;background-color:#FFFFFF;">如果程序在运行的过程中发生了内存泄漏，会被内核强行终止，提示“段错误（吐核）”，内存的状态将保存在core文件中，方便程序员进一步分析。</font>

<font style="color:black;background-color:#FBF5CB;">Linux缺省不会生成core文件，需要修改系统参数</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">调试</font><font style="color:black;background-color:#FFFFFF;">core</font><font style="color:black;background-color:#FFFFFF;">文件的步骤如下：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）用</font><font style="color:#002060;background-color:#d9d9d9;">ulimit -a</font><font style="color:black;background-color:#FFFFFF;">查看当前用户的资源限制参数；</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）用</font><font style="color:#002060;background-color:#d9d9d9;">ulimit -c unlimited</font><font style="color:black;background-color:#FFFFFF;">把</font><font style="color:#002060;background-color:#d9d9d9;">core file size</font><font style="color:black;background-color:#FFFFFF;">改为</font><font style="color:#002060;background-color:#d9d9d9;">unlimited</font><font style="color:black;background-color:#FFFFFF;">；</font>

<font style="color:black;background-color:#FFFFFF;">3）运行程序，产生core文件；（core文件可能不会生成在当前目录）</font>

>  Linux 默认会将 core 文件保存在 `/var/lib/systemd/coredump` 或其他系统目录中。
>
> 你可以通过以下命令设置 core 文件直接生成在当前目录：  
>
> sudo sysctl -w kernel.core_pattern=core
>

<font style="color:black;background-color:#FFFFFF;">4</font><font style="color:black;background-color:#FFFFFF;">）运行</font><font style="color:#002060;background-color:#d9d9d9;">gdb </font><font style="color:#002060;background-color:#d9d9d9;">程序名 </font><font style="color:#002060;background-color:#d9d9d9;">core</font><font style="color:#002060;background-color:#d9d9d9;">文件名</font><font style="color:black;background-color:#FFFFFF;">；</font>

<font style="color:black;background-color:#FFFFFF;">5</font><font style="color:black;background-color:#FFFFFF;">）在</font><font style="color:#002060;background-color:#d9d9d9;">gdb</font><font style="color:black;background-color:#FFFFFF;">中，用</font><font style="color:#002060;background-color:#d9d9d9;">bt</font><font style="color:black;background-color:#FFFFFF;">查看函数调用栈。</font>

>  <font style="color:#DF2A3F;background-color:#FBF5CB;">函数调用栈</font>（**Call Stack**）是程序运行时用于管理**函数调用和返回**的一种内存结构，它是程序执行过程中最核心的数据结构之一。  
>

<font style="color:black;background-color:#FFFFFF;">示例：</font>

```cpp
#include <cstring>
#include <iostream>
using namespace std;

void bb(const int bh,const string xm)
{
  char *ptr=nullptr;
  *ptr=3;
  //strcpy(ptr,xm.c_str());
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

```

## <font style="color:black;">gdb调试正在运行中的程序</font>
```cpp
gdb 程序名 -p 进程编号
```

> ubuntu中前面需要添加sudo提高权限
>

示例：

```cpp
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
```