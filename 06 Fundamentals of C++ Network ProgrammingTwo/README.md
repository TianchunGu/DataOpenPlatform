## <font style="color:black;">多进程的网络服务端</font>
![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1748408617899-6282ec8d-7c4e-4f8f-8761-2133d72c618d.png)

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1748410758285-55b9de1e-5867-4319-b251-60b286d8acce.png)

我们把服务端程序改为多进程。

父进程只受理客户端的连接，不与客户端通讯。

子进程负责与客户端通讯，不受理客户端的连接。

`fork`之后，父进程不需要`tcpserver.m_clientfd`,子进程不需要`tcpserver.m_listenfd`。

### <font style="color:black;">demo10.cpp</font>
```cpp
/*
 * 程序名：demo10.cpp，此程序用于演示多进程的socket服务端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

class ctcpserver         // TCP通讯的服务端类。
{
private:
  int    m_listenfd;        // 监听的socket，-1表示未初始化。
  int    m_clientfd;        // 客户端连上来的socket，-1表示客户端未连接。
  string m_clientip;        // 客户端字符串格式的IP。
  unsigned short m_port;    // 服务端用于通讯的端口。
public:
  ctcpserver():m_listenfd(-1),m_clientfd(-1) {}

  // 初始化服务端用于监听的socket。
  bool initserver(const unsigned short in_port)
  {
    // 第1步：创建服务端的socket。 
    if ( (m_listenfd=socket(AF_INET,SOCK_STREAM,0))==-1) return false;

    m_port=in_port;
  
    // 第2步：把服务端用于通信的IP和端口绑定到socket上。 
    struct sockaddr_in servaddr;                // 用于存放协议、端口和IP地址的结构体。
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;                // ①协议族，固定填AF_INET。
    servaddr.sin_port=htons(m_port);            // ②指定服务端的通信端口。
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY); // ③如果操作系统有多个IP，全部的IP都可以用于通讯。

    // 绑定服务端的IP和端口（为socket分配IP和端口）。
    if (bind(m_listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
    { 
      close(m_listenfd); m_listenfd=-1; return false; 
    }
 
    // 第3步：把socket设置为可连接（监听）的状态。
    if (listen(m_listenfd,5) == -1 ) 
    { 
      close(m_listenfd); m_listenfd=-1; return false;
    }

    return true;
  }

  // 受理客户端的连接（从已连接的客户端中取出一个客户端），
  // 如果没有已连接的客户端，accept()函数将阻塞等待。
  bool accept()
  {
    struct sockaddr_in caddr;        // 客户端的地址信息。  
    socklen_t addrlen=sizeof(caddr); // struct sockaddr_in的大小。
    if ((m_clientfd=::accept(m_listenfd,(struct sockaddr *)&caddr,&addrlen))==-1) return false;

    m_clientip=inet_ntoa(caddr.sin_addr);  // 把客户端的地址从大端序转换成字符串。

    return true;
  }

  // 获取客户端的IP(字符串格式)。
  const string & clientip() const
  {
    return m_clientip;
  }

  // 向对端发送报文，成功返回true，失败返回false。
  bool send(const string &buffer)   
  {
    if (m_clientfd==-1) return false;

    if ( (::send(m_clientfd,buffer.data(),buffer.size(),0))<=0) return false;
   
    return true;
  }

  // 接收对端的报文，成功返回true，失败返回false。
  // buffer-存放接收到的报文的内容，maxlen-本次接收报文的最大长度。
  bool recv(string &buffer,const size_t maxlen)
  { 
    buffer.clear();         // 清空容器。
    buffer.resize(maxlen);  // 设置容器的大小为maxlen。
    int readn=::recv(m_clientfd,&buffer[0],buffer.size(),0);  // 直接操作buffer的内存。
    if (readn<=0) { buffer.clear(); return false; }
    buffer.resize(readn);   // 重置buffer的实际大小。

    return true;
  }
  
  // 关闭监听的socket。
  bool closelisten()
  {
    if (m_listenfd==-1) return false; 

    ::close(m_listenfd);
    m_listenfd=-1;
    return true;
  }

  // 关闭客户端连上来的socket。
  bool closeclient()
  {
    if (m_clientfd==-1) return false;

    ::close(m_clientfd);
    m_clientfd=-1;
    return true;
  }

 ~ctcpserver() { closelisten(); closeclient(); }
};

ctcpserver tcpserver;

void FathEXIT(int sig);  // 父进程的信号处理函数。
void ChldEXIT(int sig);  // 子进程的信号处理函数。
 
int main(int argc,char *argv[])
{
  if (argc!=2)
  {
    cout << "Using:./demo10 通讯端口\nExample:./demo10 5005\n\n";
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }

  // 忽略全部的信号，不希望被打扰。顺便解决了僵尸进程的问题。
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);

  // 设置信号,在shell状态下可用 "kill 进程号" 或 "Ctrl+c" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  signal(SIGTERM,FathEXIT); signal(SIGINT,FathEXIT);  // SIGTERM 15 SIGINT 2

  if (tcpserver.initserver(atoi(argv[1]))==false) // 初始化服务端用于监听的socket。
  {
    perror("initserver()"); return -1;
  }

  while (true)
  {
    // 受理客户端的连接（从已连接的客户端中取出一个客户端），  
    // 如果没有已连接的客户端，accept()函数将阻塞等待。
    if (tcpserver.accept()==false)
    {
      perror("accept()"); return -1;
    }
	
    int pid=fork();
    if (pid==-1) { perror("fork()"); return -1; }  // 系统资源不足。
    if (pid>  0) 
    { // 父进程。
      tcpserver.closeclient();  // 父进程关闭客户端连接的socket。
      continue;                 // 父进程返回到循环开始的位置，继续受理客户端的连接。
    }
	
    tcpserver.closelisten();    // 子进程关闭监听的socket。
	
    // 子进程需要重新设置信号。
    signal(SIGTERM,ChldEXIT);   // 子进程的退出函数与父进程不一样。
    signal(SIGINT ,SIG_IGN);    // 子进程不需要捕获SIGINT信号。
	
    // 子进程负责与客户端进行通讯。
    cout << "客户端已连接(" << tcpserver.clientip() << ")。\n";
	
    string buffer;
    while (true)
    {
      // 接收对端的报文，如果对端没有发送报文，recv()函数将阻塞等待。
      if (tcpserver.recv(buffer,1024)==false)
      {
        perror("recv()"); break;
      }
      cout << "接收：" << buffer << endl;
 	
      buffer="ok";  
      if (tcpserver.send(buffer)==false)  // 向对端发送报文。
      {
        perror("send"); break;
      }
      cout << "发送：" << buffer << endl;
    }
	
    return 0;  // 子进程一定要退出，否则又会回到accept()函数的位置。
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
  tcpserver.closelisten();       // 父进程关闭监听的socket。

  exit(0);
}

// 子进程的信号处理函数。
void ChldEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

  cout << "子进程" << getpid() << "退出，sig=" << sig << endl;

  // 在这里增加释放资源的代码（只释放子进程的资源）。
  tcpserver.closeclient();       // 子进程关闭客户端连上来的socket。

  exit(0);
}
```

## <font style="color:black;">实现文件传输功能（不难，只是流程繁琐）</font>
+ 熟悉网络编程
+ 演示网络编程的常用技巧
+ 功能需求：采用socket通讯，客户端把指定文件传输给服务端（支持文本文件和二进制文件）

### 客户端与服务端的流程
#### 客户端
1. 发送待传输文件名和文件大小。
2. 等待服务端的确认报文（文件名和文件的大小的确认）。
3. 发送文件内容。
4. 等待服务端的确认报文（文件内容的确认）。

#### 服务端
1. 接收文件名和文件大小信息。
2. 给客户端回复确认报文，表示客户端可以发送文件了。
3. 接收文件内容。
4. 给客户端回复确认报文，表示文件已经接收完毕。

### <font style="color:black;">demo11.cpp--客户端</font>
```cpp
/* 
 * 程序名：demo11.cpp，此程序用于演示文件传输的客户端。
*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

class ctcpclient         // TCP通讯的客户端类。
{
private:
  int m_clientfd;        // 客户端的socket，-1表示未连接或连接已断开；>=0表示有效的socket。
  string m_ip;           // 服务端的IP/域名。
  unsigned short m_port; // 通讯端口。
public:
  ctcpclient():m_clientfd(-1) {}
  
  // 向服务端发起连接请求，成功返回true，失败返回false。
  bool connect(const string &in_ip,const unsigned short in_port)
  {
    if (m_clientfd!=-1) return false; // 如果socket已连接，直接返回失败。

    m_ip=in_ip; m_port=in_port;       // 把服务端的IP和端口保存到成员变量中。

    // 第1步：创建客户端的socket。
    if ( (m_clientfd = socket(AF_INET,SOCK_STREAM,0))==-1) return false;

    // 第2步：向服务器发起连接请求。
    struct sockaddr_in servaddr;               // 用于存放协议、端口和IP地址的结构体。
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;             // ①协议族，固定填AF_INET。
    servaddr.sin_port = htons(m_port);         // ②指定服务端的通信端口。

    struct hostent* h;                         // 用于存放服务端IP地址(大端序)的结构体的指针。
    if ((h=gethostbyname(m_ip.c_str()))==nullptr ) // 把域名/主机名/字符串格式的IP转换成结构体。
    {
      ::close(m_clientfd); m_clientfd=-1; return false;
    }
    memcpy(&servaddr.sin_addr,h->h_addr,h->h_length); // ③指定服务端的IP(大端序)。
    
    // 向服务端发起连接清求。
    if (::connect(m_clientfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)  
    {
      ::close(m_clientfd); m_clientfd=-1; return false;
    }

    return true;
  }

  // 向服务端发送报文（字符串），成功返回true，失败返回false。
  bool send(const string &buffer)   // buffer不要用const char *
  {
    if (m_clientfd==-1) return false; // 如果socket的状态是未连接，直接返回失败。

    if ((::send(m_clientfd,buffer.data(),buffer.size(),0))<=0) return false;
    
    return true;
  }

  // 向服务端发送报文（二进制数据），成功返回true，失败返回false。      
  bool send(void *buffer,const size_t size)   
  {
    if (m_clientfd==-1) return false; // 如果socket的状态是未连接，直接返回失败。

    if ((::send(m_clientfd,buffer,size,0))<=0) return false;

    return true;
  }

  // 接收服务端的报文，成功返回true，失败返回false。
  // buffer-存放接收到的报文的内容，maxlen-本次接收报文的最大长度。
  bool recv(string &buffer,const size_t maxlen)
  { // 如果直接操作string对象的内存，必须保证：1)不能越界；2）操作后手动设置数据的大小。
    buffer.clear();         // 清空容器。
    buffer.resize(maxlen);  // 设置容器的大小为maxlen。
    int readn=::recv(m_clientfd,&buffer[0],buffer.size(),0);  // 直接操作buffer的内存。
    if (readn<=0) { buffer.clear(); return false; }
    buffer.resize(readn);   // 重置buffer的实际大小。

    return true;
  }

  // 断开与服务端的连接。
  bool close()
  {
    if (m_clientfd==-1) return false; // 如果socket的状态是未连接，直接返回失败。

    ::close(m_clientfd);
    m_clientfd=-1;
    return true;
  }

  // 向服务端发送文件内容。
  bool sendfile(const string &filename,const size_t filesize)
  {
    // 以二进制的方式打开文件。
    ifstream fin(filename,ios::binary);
    if (fin.is_open() == false) { cout << "打开文件" << filename << "失败。\n";  return false; }

    int  onread=0;        // 每次调用fin.read()时打算读取的字节数。  每次应搬砖头数。
    int  totalbytes=0;    // 从文件中已读取的字节总数。 已搬砖头数。
    char buffer[4096];       // 存放读取数据的buffer。     每次搬七块砖头。

    while (true)
    {
      memset(buffer,0,sizeof(buffer));

      // 计算本次应该读取的字节数，如果剩余的数据超过4096字节，就读4096字节。
      if (filesize-totalbytes>4096) onread=4096;
      else onread=filesize-totalbytes;

      // 从文件中读取数据。
      fin.read(buffer,onread);

      // 把读取到的数据发送给对端。
      if (send(buffer,onread)==false) return false;

      // 计算文件已读取的字节总数，如果文件已读完，跳出循环。
      totalbytes=totalbytes+onread;

      if (totalbytes==filesize) break;
    }

    return true;
  }

 ~ctcpclient(){ close(); }
};
 
int main(int argc,char *argv[])
{
  if (argc!=5)
  {
    cout << "Using:./demo11 服务端的IP 服务端的端口 文件名 文件大小\n";
    cout << "Example:./demo11 192.168.101.138 5005 aaa.txt 2424\n\n";
    return -1;
  }

  ctcpclient tcpclient;
  if (tcpclient.connect(argv[1],atoi(argv[2]))==false)  // 向服务端发起连接请求。
  {
    perror("connect()"); return -1;
  }

  // 以下是发送文件的流程。
  // 1）把待传输文件名和文件的大小告诉服务端。
  // 定义文件信息的结构体。
  struct st_fileinfo{
    char filename[256];  // 文件名。
    int  filesize;       // 文件大小。
  }fileinfo;
  memset(&fileinfo,0,sizeof(fileinfo));
  strcpy(fileinfo.filename,argv[3]);     // 文件名。
  fileinfo.filesize=atoi(argv[4]);       // 文件大小。
  // 把文件信息的结构体发送给服务端。
  if (tcpclient.send(&fileinfo,sizeof(fileinfo))==false) { perror("send"); return -1; }
  cout << "发送文件信息的结构体" << fileinfo.filename << "(" << fileinfo.filesize <<")。"<< endl;

  // 2）等待服务端的确认报文（文件名和文件的大小的确认）。
  string buffer;
  if (tcpclient.recv(buffer,2)==false) { perror("recv()"); return -1; }
  if (buffer!="ok") { cout << "服务端没有回复ok。\n"; return -1; }

  // 3）发送文件内容。
  if (tcpclient.sendfile(fileinfo.filename,fileinfo.filesize)==false)
  { 
    perror("sendfile()"); return -1;
  }
  
  // 4）等待服务端的确认报文（服务端已接收完文件）。
  if (tcpclient.recv(buffer,2)==false) { perror("recv()"); return -1; }
  if (buffer!="ok") { cout << "发送文件内容失败。\n"; return -1; }

  cout << "发送文件内容成功。\n";
}
```

### <font style="color:black;">demo12.cpp--服务端</font>
```cpp
/*
 * 程序名：demo12.cpp，此程序用于演示文件传输的服务端。
*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

class ctcpserver         // TCP通讯的服务端类。
{
private:
  int    m_listenfd;        // 监听的socket，-1表示未初始化。
  int    m_clientfd;        // 客户端连上来的socket，-1表示客户端未连接。
  string m_clientip;        // 客户端字符串格式的IP。
  unsigned short m_port;    // 服务端用于通讯的端口。
public:
  ctcpserver():m_listenfd(-1),m_clientfd(-1) {}

  // 初始化服务端用于监听的socket。
  bool initserver(const unsigned short in_port)
  {
    // 第1步：创建服务端的socket。 
    if ( (m_listenfd=socket(AF_INET,SOCK_STREAM,0))==-1) return false;

    m_port=in_port;
  
    // 第2步：把服务端用于通信的IP和端口绑定到socket上。 
    struct sockaddr_in servaddr;                // 用于存放协议、端口和IP地址的结构体。
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;                // ①协议族，固定填AF_INET。
    servaddr.sin_port=htons(m_port);            // ②指定服务端的通信端口。
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY); // ③如果操作系统有多个IP，全部的IP都可以用于通讯。

    // 绑定服务端的IP和端口（为socket分配IP和端口）。
    if (bind(m_listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
    { 
      close(m_listenfd); m_listenfd=-1; return false; 
    }
 
    // 第3步：把socket设置为可连接（监听）的状态。
    if (listen(m_listenfd,5) == -1 ) 
    { 
      close(m_listenfd); m_listenfd=-1; return false;
    }

    return true;
  }

  // 受理客户端的连接（从已连接的客户端中取出一个客户端），
  // 如果没有已连接的客户端，accept()函数将阻塞等待。
  bool accept()
  {
    struct sockaddr_in caddr;        // 客户端的地址信息。  
    socklen_t addrlen=sizeof(caddr); // struct sockaddr_in的大小。
    if ((m_clientfd=::accept(m_listenfd,(struct sockaddr *)&caddr,&addrlen))==-1) return false;

    m_clientip=inet_ntoa(caddr.sin_addr);  // 把客户端的地址从大端序转换成字符串。

    return true;
  }

  // 获取客户端的IP(字符串格式)。
  const string & clientip() const
  {
    return m_clientip;
  }

  // 向对端发送报文，成功返回true，失败返回false。
  bool send(const string &buffer)   
  {
    if (m_clientfd==-1) return false;

    if ( (::send(m_clientfd,buffer.data(),buffer.size(),0))<=0) return false;
   
    return true;
  }

  // 接收对端的报文（字符串），成功返回true，失败返回false。
  // buffer-存放接收到的报文的内容，maxlen-本次接收报文的最大长度。
  bool recv(string &buffer,const size_t maxlen)
  { 
    buffer.clear();         // 清空容器。
    buffer.resize(maxlen);  // 设置容器的大小为maxlen。
    int readn=::recv(m_clientfd,&buffer[0],buffer.size(),0);  // 直接操作buffer的内存。
    if (readn<=0) { buffer.clear(); return false; }
    buffer.resize(readn);   // 重置buffer的实际大小。

    return true;
  }

  // 接收客户端的报文（二进制数据），成功返回true，失败返回false。
  // buffer-存放接收到的报文的内容，size-本次接收报文的最大长度。
  bool recv(void *buffer,const size_t size)
  {
    if (::recv(m_clientfd,buffer,size,0)<=0) return false;

    return true;
  }
  
  // 关闭监听的socket。
  bool closelisten()
  {
    if (m_listenfd==-1) return false; 

    ::close(m_listenfd);
    m_listenfd=-1;
    return true;
  }

  // 关闭客户端连上来的socket。
  bool closeclient()
  {
    if (m_clientfd==-1) return false;

    ::close(m_clientfd);
    m_clientfd=-1;
    return true;
  }

  // 接收文件内容。
  bool recvfile(const string &filename,const size_t filesize)
  {
    ofstream fout;
    fout.open(filename,ios::binary);
    if (fout.is_open() == false) { cout << "打开文件" << filename << "失败。\n";  return false; }

    int  totalbytes=0;        // 已接收文件的总字节数。
    int  onread=0;            // 本次打算接收的字节数。
    char buffer[4096];           // 接收文件内容的缓冲区。

    while (true)
    {
      // 计算本次应该接收的字节数。
      if (filesize-totalbytes>4096) onread=4096;
      else onread=filesize-totalbytes;

      // 接收文件内容。
      if (recv(buffer,onread)==false) return false;

      // 把接收到的内容写入文件。
      fout.write(buffer,onread);

      // 计算已接收文件的总字节数，如果文件接收完，跳出循环。
      totalbytes=totalbytes+onread;

      if (totalbytes==filesize) break;
    }

    return true;
  }

 ~ctcpserver() { closelisten(); closeclient(); }
};

ctcpserver tcpserver;

void FathEXIT(int sig);  // 父进程的信号处理函数。
void ChldEXIT(int sig);  // 子进程的信号处理函数。
 
int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    cout << "Using:./demo12 通讯端口 文件存放的目录\n";
    cout << "Example:./demo12 5005 /tmp\n\n";
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }

  // 忽略全部的信号，不希望被打扰。顺便解决了僵尸进程的问题。
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);

  // 设置信号,在shell状态下可用 "kill 进程号" 或 "Ctrl+c" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  signal(SIGTERM,FathEXIT); signal(SIGINT,FathEXIT);  // SIGTERM 15 SIGINT 2

  if (tcpserver.initserver(atoi(argv[1]))==false) // 初始化服务端用于监听的socket。
  {
    perror("initserver()"); return -1;
  }

  while (true)
  {
    // 受理客户端的连接（从已连接的客户端中取出一个客户端），  
    // 如果没有已连接的客户端，accept()函数将阻塞等待。
    if (tcpserver.accept()==false)
    {
      perror("accept()"); return -1;
    }

    int pid=fork();
    if (pid==-1) { perror("fork()"); return -1; }  // 系统资源不足。
    if (pid>  0) 
    { // 父进程。
      tcpserver.closeclient();  // 父进程关闭客户端连接的socket。
      continue;                 // 父进程返回到循环开始的位置，继续受理客户端的连接。
    }

    tcpserver.closelisten();    // 子进程关闭监听的socket。

    // 子进程需要重新设置信号。
    signal(SIGTERM,ChldEXIT);   // 子进程的退出函数与父进程不一样。
    signal(SIGINT ,SIG_IGN);    // 子进程不需要捕获SIGINT信号。

    // 子进程负责与客户端进行通讯。
    cout << "客户端已连接(" << tcpserver.clientip() << ")。\n";

    // 以下是接收文件的流程。
    // 1）接收文件名和文件大小信息。
    // 定义文件信息的结构体。
    struct st_fileinfo{
      char filename[256];  // 文件名。
      int  filesize;       // 文件大小。
    }fileinfo;
    memset(&fileinfo,0,sizeof(fileinfo));
    // 用结构体存放接收报文的内容。
    if (tcpserver.recv(&fileinfo,sizeof(fileinfo))==false) { perror("recv()"); return -1; }
    cout << "文件信息结构体" << fileinfo.filename << "(" << fileinfo.filesize <<")。"<< endl;

    // 2）给客户端回复确认报文，表示客户端可以发送文件了。
    if (tcpserver.send("ok")==false)  { perror("send"); break; }

    // 3）接收文件内容。  string   char * + const char * + char *
    if (tcpserver.recvfile(string(argv[2])+"/"+fileinfo.filename,fileinfo.filesize)==false)
    { 
      cout << "接收文件内容失败。\n"; return -1; 
    }

    cout << "接收文件内容成功。\n";

    // 4）给客户端回复确认报文，表示文件已接收成功。
    tcpserver.send("ok");

    return 0;  // 子进程一定要退出，否则又会回到accept()函数的位置。
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
  tcpserver.closelisten();       // 父进程关闭监听的socket。

  exit(0);
}

// 子进程的信号处理函数。
void ChldEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

  cout << "子进程" << getpid() << "退出，sig=" << sig << endl;

  // 在这里增加释放资源的代码（只释放子进程的资源）。
  tcpserver.closeclient();       // 子进程关闭客户端连上来的socket。

  exit(0);
}
```

## <font style="color:black;">三次握手与四次挥手</font>
<font style="color:black;background-color:#FFFFFF;">TCP是面向连接的、可靠的协议，建立TCP连接需要三次对话（三次握手），拆除TCP连接需要四次对话（四次握/挥手）。</font>

### <font style="color:black;">三次握手</font>
<font style="color:black;background-color:#FFFFFF;">服务端调用</font><font style="color:#002060;background-color:#d9d9d9;">listen()</font><font style="color:black;background-color:#FFFFFF;">函数后进入监听（等待连接）状态，这时候，客户端就可以调用</font><font style="color:#002060;background-color:#d9d9d9;">connect()</font><font style="color:black;background-color:#FFFFFF;">函数发起TCP连接请求，</font><font style="color:#002060;background-color:#d9d9d9;">connect()</font><font style="color:black;background-color:#FFFFFF;">函数会触发三次握手，三次握手完成后，客户端和服务端将建立一个双向的传输通道。</font>

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747714968488-1e7ad054-7acd-432c-baa4-900ed03310d1.png)

<font style="color:black;background-color:#FFFFFF;">情景类似：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">、客户端对服务端说：我可以给你发送数据吗？</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">、服务端回复：</font><font style="color:black;background-color:#FFFFFF;">ok</font><font style="color:black;background-color:#FFFFFF;">，不过，我也要给你发送数据。（这时候，客户端至服务端的单向传输通道已建立）</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">、客户端回复：</font><font style="color:black;background-color:#FFFFFF;">ok</font><font style="color:black;background-color:#FFFFFF;">。（这时候，服务端至客户端的单向传输通道已建立）</font>

**<font style="color:black;background-color:#FFFFFF;">细节：</font>**

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）客户端的</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">也有端口号，对程序员来说，不必关心客户端</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">的端口号，所以系统随机分配。（</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">通讯中的地址包括</font><font style="color:black;background-color:#FFFFFF;">ip</font><font style="color:black;background-color:#FFFFFF;">和端口号，但是，习惯中的地址仅指</font><font style="color:black;background-color:#FFFFFF;">ip</font><font style="color:black;background-color:#FFFFFF;">地址）</font>

<font style="color:black;background-color:#FFFFFF;">2）服务端的</font><font style="color:#002060;background-color:#d9d9d9;">bind()</font><font style="color:black;background-color:#FFFFFF;">函数，</font><font style="color:#DF2A3F;background-color:#FFFFFF;">普通用户</font><font style="color:black;background-color:#E8F7CF;">只能使用1024以上的端口</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#DF2A3F;background-color:#FFFFFF;">root用户</font><font style="color:black;background-color:#E8F7CF;">可以使用任意端口</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:#002060;background-color:#d9d9d9;">listen()</font><font style="color:black;background-color:#FFFFFF;">函数的第二个参数</font><font style="color:black;background-color:#FFFFFF;">+1</font><font style="color:black;background-color:#FFFFFF;">为已连接队列（</font><font style="color:#002060;background-color:#d9d9d9;">ESTABLISHED</font><font style="color:black;background-color:#FFFFFF;">状态，三次握手已完成但是没有被</font><font style="color:#002060;background-color:#d9d9d9;">accept()</font><font style="color:black;background-color:#FFFFFF;">的</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">，只存在于服务端）的大小。（在高并发的服务程序中，该参数应该调大一些）</font>

<font style="color:black;background-color:#FFFFFF;">4</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:#002060;background-color:#d9d9d9;">SYN_RECV</font><font style="color:black;background-color:#FFFFFF;">状态的连接也称为半连接。</font>

<font style="color:black;background-color:#FFFFFF;">5）</font><font style="color:#002060;background-color:#d9d9d9;">CLOSED</font><font style="color:black;background-color:#FFFFFF;">是假想状态，实际上不存在。</font>

### <font style="color:black;">四次挥手（握手）</font>
<font style="color:black;background-color:#FFFFFF;">断开一个TCP连接时，客户端和服务端需要相互总共发送四个包以确认连接的断开。在socket编程中，这一过程由客户端或服务端任一方执行</font><font style="color:#002060;background-color:#d9d9d9;">close()</font><font style="color:black;background-color:#FFFFFF;">函数触发。</font>

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747715006033-e72d8012-2458-4284-aaaf-9561da8c4003.png)

<font style="color:black;background-color:#FFFFFF;">情景类似：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）一端（</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">）对另一端（</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">）说：我不会给你发数据了，断开连接吧。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">回复：</font><font style="color:black;background-color:#FFFFFF;">ok</font><font style="color:black;background-color:#FFFFFF;">。（这时候</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">不能对</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">发数据了，但是，</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">仍可以对</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">发数据）</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">发完数据了，对</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">说：我也不会给你发数据了。（这时候</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">也不能对</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">发数据了）。</font>

<font style="color:black;background-color:#FFFFFF;">4</font><font style="color:black;background-color:#FFFFFF;">、</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">回复：</font><font style="color:black;background-color:#FFFFFF;">ok</font><font style="color:black;background-color:#FFFFFF;">。</font>

**<font style="color:black;background-color:#FFFFFF;">细节：</font>**

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）主动断开的端在四次挥手后，</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">的状态为</font><font style="color:black;background-color:#FFFFFF;">TIME_WAIT</font><font style="color:black;background-color:#FFFFFF;">，该状态将持续</font><font style="color:black;background-color:#FFFFFF;">2MSL</font><font style="color:black;background-color:#FFFFFF;">（</font><font style="color:black;background-color:#FFFFFF;">30</font><font style="color:black;background-color:#FFFFFF;">秒</font><font style="color:black;background-color:#FFFFFF;">/1</font><font style="color:black;background-color:#FFFFFF;">分钟</font><font style="color:black;background-color:#FFFFFF;">/</font>**<font style="color:black;background-color:#FFFFFF;">2</font>****<font style="color:black;background-color:#FFFFFF;">分钟</font>**<font style="color:black;background-color:#FFFFFF;">）。</font><font style="color:black;background-color:#FFFFFF;"> MSL</font><font style="color:black;background-color:#FFFFFF;">（</font><font style="color:black;background-color:#FFFFFF;">Maximum Segment Lifetime</font><font style="color:black;background-color:#FFFFFF;">）报文在网络上存在的最长时间，超过这个时间报文将被丢弃。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）如果是客户端主动断开，</font><font style="color:black;background-color:#FFFFFF;">TIME_WAIT</font><font style="color:black;background-color:#FFFFFF;">状态的</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">几乎不会造成危害。</font>

<font style="color:black;background-color:#FFFFFF;">a）客户端程序的socket很少，服务端程序的socket很多（成千上万）；</font>

<font style="color:black;background-color:#FFFFFF;">b）客户端的端口是随机分配的，不存在重用的问题。</font>

<font style="color:black;background-color:#FFFFFF;">3</font><font style="color:black;background-color:#FFFFFF;">）如果是服务端主动断开，有两方面的危害：</font>

<font style="color:black;background-color:#FFFFFF;">a）socket没有立即释放；</font>

<font style="color:black;background-color:#FFFFFF;">b）端口号只能在2MSL后才能重用。</font>

<font style="color:black;background-color:#FFFFFF;">在服务端程序中，用</font><font style="color:#002060;background-color:#d9d9d9;">setsockopt()</font><font style="color:black;background-color:#FFFFFF;">函数设置socket的属性（一定要放在</font><font style="color:#002060;background-color:#d9d9d9;">bind()</font><font style="color:black;background-color:#FFFFFF;">之前）。</font>

```cpp
int opt = 1;   
setsockopt(m_listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
```

## <font style="color:black;">TCP缓存</font>
<font style="color:black;background-color:#FFFFFF;">系统为每个</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">创建了发送缓冲区和接收缓冲区，应用程序调用</font><font style="color:#002060;background-color:#d9d9d9;">send()</font><font style="color:black;background-color:#FFFFFF;">/</font><font style="color:#002060;background-color:#d9d9d9;">write()</font><font style="color:black;background-color:#FFFFFF;">函数发送数据的时候，内核把数据从应用进程拷贝</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">的发送缓冲区中；应用程序调用</font><font style="color:#002060;background-color:#d9d9d9;">recv()</font><font style="color:black;background-color:#FFFFFF;">/</font><font style="color:#002060;background-color:#d9d9d9;">read()</font><font style="color:black;background-color:#FFFFFF;">函数接收数据的时候，内核把数据从</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">的接收缓冲区拷贝应用进程中。</font>

<font style="color:black;background-color:#FFFFFF;">发送数据即把数据放入发送缓冲区中。</font>

<font style="color:black;background-color:#FFFFFF;">接收数据即从接收缓冲区中取数据。</font>

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747715104036-630f2340-848a-4132-a9f9-a5df3cc36830.png)

<font style="color:black;background-color:#FFFFFF;">查看socket缓存的大小：</font>

```cpp
int bufsize = 0;
socklen_t optlen = sizeof(bufsize);     

getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &bufsize, &optlen); // 获取发送缓冲区的大小。
cout << "send bufsize=" << bufsize << endl;

getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &bufsize, &optlen); // 获取接收缓冲区的大小。
cout << "recv bufsize=" << bufsize << endl;
```

<font style="color:black;background-color:#FFFFFF;">问题：</font>

<font style="color:black;background-color:#FFFFFF;">1</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:#002060;background-color:#d9d9d9;">send()</font><font style="color:black;background-color:#FFFFFF;">函数有可能会阻塞吗？ </font>

<font style="color:black;background-color:#FFFFFF;">如果自己的发送缓冲区和对端的接收缓冲区都满了，会阻塞。</font>

<font style="color:black;background-color:#FFFFFF;">2</font><font style="color:black;background-color:#FFFFFF;">）向</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">中写入数据后，如果关闭了</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">，对端还能接收到数据吗？</font>

<font style="color:black;background-color:#FFFFFF;"></font>

**<font style="color:black;background-color:#FFFFFF;">Nagle</font>****<font style="color:black;background-color:#FFFFFF;">算法</font>**

<font style="color:black;background-color:#FFFFFF;">在</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">协议中，无论发送多少数据，都要在数据前面加上协议头，同时，对方收到数据后，也需要回复</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">表示确认。为了尽可能的利用网络带宽，</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">希望每次都能够以</font><font style="color:black;background-color:#FFFFFF;">MSS</font><font style="color:black;background-color:#FFFFFF;">（</font><font style="color:black;background-color:#FFFFFF;">Maximum Segment Size</font><font style="color:black;background-color:#FFFFFF;">，最大报文长度）的数据块来发送数据。</font>

<font style="color:black;background-color:#FFFFFF;">Nagle</font><font style="color:black;background-color:#FFFFFF;">算法就是为了尽可能发送大块的数据，避免网络中充斥着小数据块。</font>

<font style="color:black;background-color:#FFFFFF;">Nagle</font><font style="color:black;background-color:#FFFFFF;">算法的定义是：任意时刻，最多只能有一个未被确认的小段，小段是指小于</font><font style="color:black;background-color:#FFFFFF;">MSS</font><font style="color:black;background-color:#FFFFFF;">的数据块，未被确认是指一个数据块发送出去后，没有收到对端回复的</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">举个例子：发送端调用</font><font style="color:#002060;background-color:#d9d9d9;">send()</font><font style="color:black;background-color:#FFFFFF;">函数将一个</font><font style="color:black;background-color:#FFFFFF;">int</font><font style="color:black;background-color:#FFFFFF;">型数据（称之为</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">数据块）写入到</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">中，</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">数据块会被马上发送到接收端，接着，发送端又调用</font><font style="color:#002060;background-color:#d9d9d9;">send()</font><font style="color:black;background-color:#FFFFFF;">函数写入一个</font><font style="color:black;background-color:#FFFFFF;">int</font><font style="color:black;background-color:#FFFFFF;">型数据（称之为</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">数据块），这时候，</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">块的</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">没有返回（已经存在了一个未被确认的小段），所以</font><font style="color:black;background-color:#FFFFFF;">B</font><font style="color:black;background-color:#FFFFFF;">块不会立即被发送，而是等</font><font style="color:black;background-color:#FFFFFF;">A</font><font style="color:black;background-color:#FFFFFF;">块的</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">返回之后（大概</font><font style="color:black;background-color:#FFFFFF;">40ms</font><font style="color:black;background-color:#FFFFFF;">）才发送。</font>

<font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">协议中不仅仅有</font><font style="color:black;background-color:#FFFFFF;">Nagle</font><font style="color:black;background-color:#FFFFFF;">算法，还有一个</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">延迟机制：当接收端收到数据之后，并不会马上向发送端回复</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">，而是延迟</font><font style="color:black;background-color:#FFFFFF;">40ms</font><font style="color:black;background-color:#FFFFFF;">后再回复，它希望在</font><font style="color:black;background-color:#FFFFFF;">40ms</font><font style="color:black;background-color:#FFFFFF;">内接收端会向发送端回复应答数据，这样</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">就可以和应答数据一起发送，把</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">捎带过去。</font>

<font style="color:black;background-color:#FFFFFF;">如果</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">连接的一端启用了</font><font style="color:black;background-color:#FFFFFF;">Nagle</font><font style="color:black;background-color:#FFFFFF;">算法，另一端启用了</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">延时机制，而发送的数据包又比较小，则可能会出现这样的情况：发送端在等待上一个包的</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">，而接收端正好延迟了此</font><font style="color:black;background-color:#FFFFFF;">ACK</font><font style="color:black;background-color:#FFFFFF;">，那么这个正要被发送的包就会延迟</font><font style="color:black;background-color:#FFFFFF;">40ms</font><font style="color:black;background-color:#FFFFFF;">。</font>

**<font style="color:black;background-color:#FFFFFF;">解决方案</font>**

<font style="color:black;background-color:#FFFFFF;">开启TCP_NODELAY选项，这个选项的作用就是禁用Nagle算法。</font>

```cpp
#include <netinet/tcp.h>   // 注意，要包含这个头文件。
int opt = 1;   
setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY,&opt,sizeof(opt));
```

<font style="color:black;background-color:#FFFFFF;">对时效要求很高的系统，例如联机游戏、证券交易，一般会禁用Nagle算法。</font>

