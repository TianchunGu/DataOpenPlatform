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

/*
运行代码：
➜  4-8 round-robin queue git:(main) ✗ ./demo02  
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
➜  4-8 round-robin queue git:(main) ✗ ipcs -m 

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00000000 4          gtc        777        4000       2          dest         
0x00000000 5          gtc        777        640000     2          dest         
0x00000000 6          gtc        777        640000     2          dest         
0x00000000 7          gtc        777        640000     2          dest         
0x00000000 8          gtc        777        640000     2          dest         
0x00000000 9          gtc        777        640000     2          dest         
0x00000000 10         gtc        777        640000     2          dest         
0x00000000 11         gtc        777        640000     2          dest         
0x00000000 12         gtc        777        640000     2          dest         
0x00000000 13         gtc        777        640000     2          dest         
0x00000000 14         gtc        777        640000     2          dest         
0x00000000 15         gtc        777        640000     2          dest         
0x00000000 16         gtc        777        640000     2          dest         
0x00000000 17         gtc        777        640000     2          dest         
0x00000000 18         gtc        777        640000     2          dest         
0x00000000 19         gtc        777        640000     2          dest         
0x00000000 20         gtc        777        640000     2          dest         
0x00000000 21         gtc        777        640000     2          dest         
0x00000000 22         gtc        777        640000     2          dest         
0x00000000 23         gtc        777        640000     2          dest         
0x00000000 24         gtc        777        640000     2          dest         
0x00000000 25         gtc        777        640000     2          dest         
0x00000000 26         gtc        777        640000     2          dest         
0x00000000 27         gtc        777        640000     2          dest         
0x00000000 28         gtc        777        640000     2          dest         
0x00000000 29         gtc        777        640000     2          dest         
0x00000000 30         gtc        777        640000     2          dest         
0x00000000 31         gtc        777        640000     2          dest         
0x00000000 32         gtc        777        640000     2          dest         
0x00000000 33         gtc        777        640000     2          dest         
0x00000000 34         gtc        777        640000     2          dest         
0x00000000 35         gtc        777        640000     2          dest         
0x00000000 37         gtc        777        1753600    2          dest         
0x00000000 38         gtc        777        28800      2          dest         
0x00000000 42         gtc        777        28800      2          dest         
0x00000000 43         gtc        777        89600      2          dest         
0x00000000 44         gtc        777        77000      2          dest         
0x00000000 45         gtc        777        640000     2          dest         
0x00000000 46         gtc        777        640000     2          dest         
0x00000000 47         gtc        777        640000     2          dest         
0x00000000 48         gtc        777        640000     2          dest         
0x00000000 49         gtc        777        640000     2          dest         
0x00000000 50         gtc        777        640000     2          dest         
0x00000000 51         gtc        777        640000     2          dest         
0x00000000 52         gtc        777        640000     2          dest         
0x00000000 53         gtc        777        640000     2          dest         
0x00000000 54         gtc        777        640000     2          dest         
0x00000000 55         gtc        777        640000     2          dest         
0x00000000 56         gtc        777        640000     2          dest         
0x00000000 57         gtc        777        640000     2          dest         
0x00000000 58         gtc        777        640000     2          dest         
0x00000000 59         gtc        777        640000     2          dest         
0x00000000 60         gtc        777        640000     2          dest         
0x00000000 61         gtc        777        640000     2          dest         
0x00000000 62         gtc        777        640000     2          dest         
0x00000000 32831      gtc        600        524288     2          dest         
0x00000000 64         gtc        777        1012800    2          dest         
0x00000000 65         gtc        777        1079680    2          dest         
0x00000000 67         gtc        777        1079680    2          dest         
0x00000000 68         gtc        777        288800     2          dest         
0x00000000 70         gtc        777        288800     2          dest         
0x00000000 32839      gtc        600        524288     2          dest         
0x00000000 74         gtc        777        1079680    2          dest         
0x00000000 32843      gtc        600        4194304    2          dest         
0x00000000 76         gtc        777        1236000    2          dest         
0x00000000 77         gtc        777        50384      2          dest         
0x00000000 78         gtc        777        69144      2          dest         
0x00000000 79         gtc        777        69144      2          dest         
0x00000000 80         gtc        777        69144      2          dest         
0x00000000 81         gtc        777        69144      2          dest         
0x00000000 82         gtc        777        640000     2          dest         
0x00000000 83         gtc        777        640000     2          dest         
0x00000000 84         gtc        777        876800     2          dest         
0x00000000 32853      gtc        600        524288     2          dest         
0x00000000 86         gtc        777        4          2          dest         
0x00005005 32855      gtc        640        36         0                       
0x00000000 90         gtc        600        8388608    2          dest         
0x00000000 93         gtc        600        524288     2          dest         
0x00000000 105        gtc        600        524288     2          dest         
0x00000000 106        gtc        600        4194304    2          dest         
0x00000000 110        gtc        600        524288     2          dest         

➜  4-8 round-robin queue git:(main) ✗ ./demo02
元素（1、2、3）入队。
循环队列已满，入队失败。
循环队列已满，入队失败。
循环队列已满，入队失败。
队列的长度是5
m_data[2],value=3
m_data[3],value=11
m_data[4],value=12
m_data[0],value=13
m_data[1],value=14
出队的元素值为3
出队的元素值为11
队列的长度是3
m_data[4],value=12
m_data[0],value=13
m_data[1],value=14
元素（11、12、13、14、15）入队。
循环队列已满，入队失败。
循环队列已满，入队失败。
循环队列已满，入队失败。
队列的长度是5
m_data[4],value=12
m_data[0],value=13
m_data[1],value=14
m_data[2],value=11
m_data[3],value=12
*/