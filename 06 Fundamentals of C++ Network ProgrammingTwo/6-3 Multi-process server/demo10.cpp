/*
 * 程序名：demo10.cpp，此程序用于演示多进程的socket服务端
 */
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class ctcpserver  // TCP通讯的服务端类。
{
 private:
  int m_listenfd;         // 监听的socket，-1表示未初始化。
  int m_clientfd;         // 客户端连上来的socket，-1表示客户端未连接。
  string m_clientip;      // 客户端字符串格式的IP。
  unsigned short m_port;  // 服务端用于通讯的端口。
 public:
  ctcpserver() : m_listenfd(-1), m_clientfd(-1) {}

  // 初始化服务端用于监听的socket。
  bool initserver(const unsigned short in_port) {
    // 第1步：创建服务端的socket。
    if ((m_listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
      return false;

    m_port = in_port;

    // 第2步：把服务端用于通信的IP和端口绑定到socket上。
    struct sockaddr_in servaddr;  // 用于存放协议、端口和IP地址的结构体。
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;      // ①协议族，固定填AF_INET。
    servaddr.sin_port = htons(m_port);  // ②指定服务端的通信端口。
    servaddr.sin_addr.s_addr =
        htonl(INADDR_ANY);  // ③如果操作系统有多个IP，全部的IP都可以用于通讯。

    // 绑定服务端的IP和端口（为socket分配IP和端口）。
    if (bind(m_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
      close(m_listenfd);
      m_listenfd = -1;
      return false;
    }

    // 第3步：把socket设置为可连接（监听）的状态。
    if (listen(m_listenfd, 5) == -1) {
      close(m_listenfd);
      m_listenfd = -1;
      return false;
    }

    return true;
  }

  // 受理客户端的连接（从已连接的客户端中取出一个客户端），
  // 如果没有已连接的客户端，accept()函数将阻塞等待。
  bool accept() {
    struct sockaddr_in caddr;           // 客户端的地址信息。
    socklen_t addrlen = sizeof(caddr);  // struct sockaddr_in的大小。
    if ((m_clientfd =
             ::accept(m_listenfd, (struct sockaddr*)&caddr, &addrlen)) == -1)
      return false;

    m_clientip =
        inet_ntoa(caddr.sin_addr);  // 把客户端的地址从大端序转换成字符串。

    return true;
  }

  // 获取客户端的IP(字符串格式)。
  const string& clientip() const { return m_clientip; }

  // 向对端发送报文，成功返回true，失败返回false。
  bool send(const string& buffer) {
    if (m_clientfd == -1)
      return false;

    if ((::send(m_clientfd, buffer.data(), buffer.size(), 0)) <= 0)
      return false;

    return true;
  }

  // 接收对端的报文，成功返回true，失败返回false。
  // buffer-存放接收到的报文的内容，maxlen-本次接收报文的最大长度。
  bool recv(string& buffer, const size_t maxlen) {
    buffer.clear();         // 清空容器。
    buffer.resize(maxlen);  // 设置容器的大小为maxlen。
    int readn = ::recv(m_clientfd, &buffer[0], buffer.size(),
                       0);  // 直接操作buffer的内存。
    if (readn <= 0) {
      buffer.clear();
      return false;
    }
    buffer.resize(readn);  // 重置buffer的实际大小。

    return true;
  }

  // 关闭监听的socket。
  bool closelisten() {
    if (m_listenfd == -1)
      return false;

    ::close(m_listenfd);
    m_listenfd = -1;
    return true;
  }

  // 关闭客户端连上来的socket。
  bool closeclient() {
    if (m_clientfd == -1)
      return false;

    ::close(m_clientfd);
    m_clientfd = -1;
    return true;
  }

  ~ctcpserver() {
    closelisten();
    closeclient();
  }
};

void FathEXIT(int sig);  // 父进程的信号处理函数。
void ChldEXIT(int sig);  // 子进程的信号处理函数。

ctcpserver tcpserver;  // 设置为全局对象
int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout
        << "Using:./demo8 通讯端口\nExample:./demo8 5005\n\n";  // 端口大于1024，不与其它的重复。
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }

  // 忽略全部的信号，不希望被打扰。
  for (int ii = 1; ii <= 64; ii++)
    signal(ii, SIG_IGN);

  // 设置信号,在shell状态下可用 "kill 进程号" 或 "Ctrl+c" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  signal(SIGTERM, FathEXIT);
  signal(SIGINT, FathEXIT);  // SIGTERM 15 SIGINT 2

  if (tcpserver.initserver(atoi(argv[1])) ==
      false)  // 初始化服务端用于监听的socket。
  {
    perror("initserver()");
    return -1;
  }
  while (true) {
    // 受理客户端的连接（从已连接的客户端中取出一个客户端），
    // 如果没有已连接的客户端，accept()函数将阻塞等待。
    if (tcpserver.accept() == false) {
      perror("accept()");
      return -1;
    }
    int pid = fork();
    if (pid == -1) {
      perror("accept()");
      return -1;  // 系统资源不足。
    }
    if (pid > 0) {
      tcpserver.closeclient();  // 父进程关闭客户端连接的socket。
      continue;  // 父进程返回到循环开始的位置，继续受理客户端的连接。
    }

    tcpserver.closelisten();  // 子进程关闭监听的socket。
    // 子进程需要重新设置信号。
    signal(SIGTERM, ChldEXIT);  // 子进程的退出函数与父进程不一样。
    signal(SIGINT, SIG_IGN);    // 子进程不需要捕获SIGINT信号。

    // 子进程负责与客户端进行通讯。
    cout << "客户端已连接(" << tcpserver.clientip() << ")。\n";

    string buffer;
    while (true) {
      // 接收对端的报文，如果对端没有发送报文，recv()函数将阻塞等待。
      if (tcpserver.recv(buffer, 1024) == false) {
        perror("recv()");
        break;
      }
      cout << "接收：" << buffer << endl;

      buffer = "ok";
      if (tcpserver.send(buffer) == false)  // 向对端发送报文。
      {
        perror("send");
        break;
      }
      cout << "发送：" << buffer << endl;
    }
  }
}

// 父进程的信号处理函数。
void FathEXIT(int sig) {
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);

  cout << "父进程退出，sig=" << sig << endl;

  kill(0, SIGTERM);  // 向全部的子进程发送15的信号，通知它们退出。

  // 在这里增加释放资源的代码（全局的资源）。
  tcpserver.closelisten();  // 父进程关闭监听的socket。

  exit(0);
}

// 子进程的信号处理函数。
void ChldEXIT(int sig) {
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);

  cout << "子进程" << getpid() << "退出，sig=" << sig << endl;

  // 在这里增加释放资源的代码（只释放子进程的资源）。
  tcpserver.closeclient();  // 子进程关闭客户端连接的socket。
  exit(0);
}
