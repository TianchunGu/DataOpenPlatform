#include <iostream>
using namespace std;

int main()
{
  close(0);//关闭标准输入
  close(1);//关闭标准输出
  close(2);//关闭标准错误输出
  int i=0;
  cout << "cout i="<<i<< endl;//标准输出
  cerr << "cerr i="<<i<< endl;//标准错误输出
  return 0;
}