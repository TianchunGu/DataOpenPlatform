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

/*
运行输出：
➜  4-8 round-robin queue git:(main) ✗ ./demo01
元素（1、2、3）入队。
队列的长度是3
m_data[0],value=1
m_data[1],value=2
m_data[2],value=3
出队的元素值为1
出队的元素值为2
队列的长度是1
m_data[2],value=3
元素（11、12、13、14、15）入队。
循环队列已满，入队失败。
队列的长度是5
m_data[2],value=3
m_data[3],value=11
m_data[4],value=12
m_data[0],value=13
m_data[1],value=14
*/