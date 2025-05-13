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