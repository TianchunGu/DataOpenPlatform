#include <iostream>
using namespace std;

int main(int argc,char *argv[],char *envp[])
{
  if (argc!=4)// 检查参数个数是否正确
  {
    cout << "表白神器程序的使用方法：./demo 追求者姓名 被追求者姓名 表白内容\n";
    return -1;
  }

  cout << argv[1] << "开始向" << argv[2] << "表白。\n";
  cout << argv[3] << endl;
  cout << argv[1] << "表白完成。\n";

  return 0;
}

/*  
编译运行：
➜  2-5 Parameters of the main function git:(main) ✗ ls
demo01  demo01.cpp  demo02.cpp
➜  2-5 Parameters of the main function git:(main) ✗ g++ demo02.cpp -o demo02                  
➜  2-5 Parameters of the main function git:(main) ✗ ./demo02                      
表白神器程序的使用方法：./demo 追求者姓名 被追求者姓名 表白内容
➜  2-5 Parameters of the main function git:(main) ✗ ./demo02 张三 西施 我是一只傻傻鸟
张三开始向西施表白。
我是一只傻傻鸟
张三表白完成。
*/