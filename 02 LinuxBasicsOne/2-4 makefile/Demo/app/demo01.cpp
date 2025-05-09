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