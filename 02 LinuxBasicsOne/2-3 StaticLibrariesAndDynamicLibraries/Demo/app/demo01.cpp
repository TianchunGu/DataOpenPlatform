#include "/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-3 StaticLibrariesAndDynamicLibraries/Demo/tools/public.h"  // 包含通用函数和类的头文件,注意替换为实际路径再运行代码
using namespace std;

int main()
{
  func();    // 调用通用的函数。

  AA a;      // 用通用类声明对象。
  a.show();  // 调用对象的方法。
}