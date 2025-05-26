## <font style="color:black;">第一个网络通讯程序</font>
![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1746933195844-4612595f-1ed6-4fe0-ac12-91353d8157ad.png)

+ 网络通讯是指两台计算机中的程序进行传输数据的过程。
+ 客户程序（端）：指主动发起通讯的程序。
+ 服务程序（端/器）：指被动的等待，然后为向它发起通讯的客户端提供服务。

---

+ 客户端必须提前知道服务端的IP地址和通讯端口。
+ 服务端不需要知道客户端的IP地址

示例：

+ 上网：客户端时电脑或手机上的浏览器软件，服务端时WEB软件。
+ QQ：客户端时电脑或手机上的QQ软件，服务端时腾讯的后台服务程序。
+ 远程登陆Linux：客户端时SecureCRT或其它的软件，服务端时Linux的ssh服务程序

### <font style="color:black;">demo1.cpp</font>
```cpp
/*
 * 程序名：demo1.cpp，此程序用于演示socket的客户端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;
 
int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    cout << "Using:./demo1 服务端的IP 服务端的端口\nExample:./demo1 192.168.101.139 5005\n\n"; 
    return -1;
  }

  // 第1步：创建客户端的socket。  
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if (sockfd==-1)
  {
    perror("socket"); return -1;
  }
 
  // 第2步：向服务器发起连接请求。 
  struct hostent* h;    // 用于存放服务端IP的结构体。
  if ( (h = gethostbyname(argv[1])) == 0 )  // 把字符串格式的IP转换成结构体。
  { 
    cout << "gethostbyname failed.\n" << endl; close(sockfd); return -1;
  }
  struct sockaddr_in servaddr;              // 用于存放服务端IP和端口的结构体。
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  memcpy(&servaddr.sin_addr,h->h_addr,h->h_length); // 指定服务端的IP地址。
  servaddr.sin_port = htons(atoi(argv[2]));         // 指定服务端的通信端口。
  
  if (connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)  // 向服务端发起连接清求。
  { 
    perror("connect"); close(sockfd); return -1; 
  }
  
  // 第3步：与服务端通讯，客户发送一个请求报文后等待服务端的回复，收到回复后，再发下一个请求报文。
  char buffer[1024];
  for (int ii=0;ii<3;ii++)  // 循环3次，将与服务端进行三次通讯。
  {
    int iret;
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"这是第%d个超级女生，编号%03d。",ii+1,ii+1);  // 生成请求报文内容。
    // 向服务端发送请求报文。
    if ( (iret=send(sockfd,buffer,strlen(buffer),0))<=0)
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;

    memset(buffer,0,sizeof(buffer));
    // 接收服务端的回应报文，如果服务端没有发送回应报文，recv()函数将阻塞等待。
    if ( (iret=recv(sockfd,buffer,sizeof(buffer),0))<=0)
    {
       cout << "iret=" << iret << endl; break;
    }
    cout << "接收：" << buffer << endl;

    sleep(1);
  }
 
  // 第4步：关闭socket，释放资源。
  close(sockfd);
}
```

### <font style="color:black;">demo2.cpp</font>
```cpp
/*
 * 程序名：demo2.cpp，此程序用于演示socket通信的服务端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;
 
int main(int argc,char *argv[])
{
  if (argc!=2)
  {
    cout << "Using:./demo2 通讯端口\nExample:./demo2 5005\n\n";   // 端口大于1024，不与其它的重复。
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }

  // 第1步：创建服务端的socket。 
  int listenfd = socket(AF_INET,SOCK_STREAM,0);
  if (listenfd==-1) 
  { 
    perror("socket"); return -1; 
  }
  
  // 第2步：把服务端用于通信的IP和端口绑定到socket上。 
  struct sockaddr_in servaddr;          // 用于存放服务端IP和端口的数据结构。
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;        // 指定协议。
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 服务端任意网卡的IP都可以用于通讯。
  servaddr.sin_port = htons(atoi(argv[1]));     // 指定通信端口，普通用户只能用1024以上的端口。
  // 绑定服务端的IP和端口。
  if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0 )
  { 
    perror("bind"); close(listenfd); return -1; 
  }
 
  // 第3步：把socket设置为可连接（监听）的状态。
  if (listen(listenfd,5) != 0 ) 
  { 
    perror("listen"); close(listenfd); return -1; 
  }
 
  // 第4步：受理客户端的连接请求，如果没有客户端连上来，accept()函数将阻塞等待。
  int clientfd=accept(listenfd,0,0);
  if (clientfd==-1)
  {
    perror("accept"); close(listenfd); return -1; 
  }

  cout << "客户端已连接。\n";
 
  // 第5步：与客户端通信，接收客户端发过来的报文后，回复ok。
  char buffer[1024];
  while (true)
  {
    int iret;
    memset(buffer,0,sizeof(buffer));
    // 接收客户端的请求报文，如果客户端没有发送请求报文，recv()函数将阻塞等待。
    // 如果客户端已断开连接，recv()函数将返回0。
    if ( (iret=recv(clientfd,buffer,sizeof(buffer),0))<=0) 
    {
       cout << "iret=" << iret << endl;  break;   
    }
    cout << "接收：" << buffer << endl;
 
    strcpy(buffer,"ok");  // 生成回应报文内容。
    // 向客户端发送回应报文。
    if ( (iret=send(clientfd,buffer,strlen(buffer),0))<=0) 
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;
  }
 
  // 第6步：关闭socket，释放资源。
  close(listenfd);   // 关闭服务端用于监听的socket。
  close(clientfd);   // 关闭客户端连上来的socket。
}
```

## <font style="color:black;">基于Linux的文件操作</font>
+ 对Linux来说，socket操作与文件操作没有区别。
+ 在网络传输数据的过程中，可以使用文件的I/O函数。

### <font style="color:black;">demo3.cpp</font>
```cpp
// demo3.cpp，本程序演示了Linux底层文件的操作-创建文件并写入数据。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main()
{
  int fd;    // 定义一个文件描述符/文件句柄。

  // 打开文件，注意，如果创建后的文件没有权限，可以手工授权chmod 777 data.txt。
  fd=open("data.txt",O_CREAT|O_RDWR|O_TRUNC);
  if (fd==-1)
  {
    perror("open(data.txt)"); return -1;
  }

  printf("文件描述符fd=%d\n",fd);

  char buffer[1024];
  strcpy(buffer,"我是一只傻傻鸟。\n");

  if (write(fd,buffer,strlen(buffer))==-1)    // 把数据写入文件。
  {
    perror("write()"); return -1;
  }

  close(fd);  // 关闭文件。
}
```

### <font style="color:black;">demo4.cpp</font>
```cpp
// demo4.cpp，本程序演示了Linux底层文件的操作-读取文件。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int fd;    // 定义一个文件描述符/文件句柄。

  fd=open("data.txt",O_RDONLY); // 打开文件。
  if (fd==-1)
  {
    perror("open(data.txt)"); return -1;
  }

  printf("文件描述符fd=%d\n",fd);

  char buffer[1024];
  memset(buffer,0,sizeof(buffer));
  if (read(fd,buffer,sizeof(buffer))==-1)    // 从文件中读取数据。
  {
    perror("write()"); return -1;
  }

  printf("%s",buffer);

  close(fd);  // 关闭文件。
}
```

![](https://cdn.nlark.com/yuque/0/2025/gif/33636091/1747664787373-b3bb41bb-46a1-4b2f-b1b8-3c7c48811658.gif)

### 文件描述符的分配规则
+ `/proc/进程id/fd`目录中，存放了每个进程打开的fd
+ Linux进程默认打开了三个文件描述符：
    - 0-标准输入（键盘）
    - 1-标准输出（显示器）
    - 2-标准错误（显示器）
    - `cin`、`cout`、`cerr`
+ 文件描述符的分配规则是：找到最小的，没有被占用的文件描述符。

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747664896743-c67b4fc3-199f-408d-aed9-875fae5bfb1f.png)

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747664925718-7e578842-905c-449e-b967-862a598966f5.png)

## <font style="color:black;">socket函数详解</font>
+ 网络编程的每个细节都很重要，不能一知半解。
+ 不可能学一遍就能搞清楚全部的细节，要慢慢的体会
+ 课程内容可能会比较沉闷，一定要静下心来。

### <font style="color:black;">什么是协议</font>
<font style="color:black;background-color:#FFFFFF;">人与人沟通的方式有很多种：书信、电话、</font><font style="color:black;background-color:#FFFFFF;">QQ</font><font style="color:black;background-color:#FFFFFF;">、微信。如果两个人想沟通，必须先选择一种沟通的方式，如果一方使用电话，另一方也应该使用电话，而不是书信。</font>

<font style="color:black;background-color:#FFFFFF;">协议是网络通讯的规则，是约定。</font>

### <font style="color:black;">创建socket</font>
```cpp
int socket(int domain, int type, int protocol);
```

<font style="color:black;background-color:#FFFFFF;">成功返回一个有效的</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">，失败返回</font><font style="color:black;background-color:#FFFFFF;">-1</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>

<font style="color:black;background-color:#FFFFFF;">全部网络编程的函数，失败时基本上都是返回</font><font style="color:black;background-color:#FFFFFF;">-1</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:#002060;background-color:#d9d9d9;">errno</font><font style="color:black;background-color:#FFFFFF;">被设置。</font>

<font style="color:black;background-color:#FFFFFF;"></font><font style="color:black;background-color:#FFFFFF;">只要参数没填错，基本上不会失败。</font>

<font style="color:black;background-color:#FFFFFF;">不过，单个进程中创建的socket数量与受系统参数</font><font style="color:#002060;background-color:#d9d9d9;">open files</font><font style="color:black;background-color:#FFFFFF;">的限制。（</font><font style="color:#002060;background-color:#d9d9d9;">ulimit -a</font><font style="color:black;background-color:#FFFFFF;">）</font>

#### domain <font style="color:black;">通讯的协议家族</font>
**<font style="color:#002060;background-color:#d9d9d9;">PF_INET</font>****<font style="color:black;background-color:#FFFFFF;">     </font>****<font style="color:black;background-color:#FFFFFF;">      </font>****<font style="color:black;background-color:#FFFFFF;">IPv4</font>****<font style="color:black;background-color:#FFFFFF;">互联网协议族。</font>**

<font style="color:#002060;background-color:#d9d9d9;">PF_INET6</font><font style="color:black;background-color:#FFFFFF;">    </font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">IPv6</font><font style="color:black;background-color:#FFFFFF;">互联网协议族。</font>

<font style="color:#002060;background-color:#d9d9d9;">PF_LOCAL</font><font style="color:black;background-color:#FFFFFF;">  </font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">本地通信的协议族。</font>

<font style="color:#002060;background-color:#d9d9d9;">PF_PACKET</font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">内核底层的协议族。</font>

<font style="color:#002060;background-color:#d9d9d9;">PF_IPX</font><font style="color:black;background-color:#FFFFFF;">             </font><font style="color:black;background-color:#FFFFFF;">IPX Novell</font><font style="color:black;background-color:#FFFFFF;">协议族。</font>

<font style="color:black;background-color:#FFFFFF;">IPv6尚未普及，其它的不常用。</font>

#### type <font style="color:black;">数据传输的类型</font>
![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747665768514-723bad9f-ec5b-467b-8b98-41dc4016b676.png)

<font style="color:#002060;background-color:#d9d9d9;">SOCK_STREAM</font><font style="color:black;background-color:#FFFFFF;">      面向连接的socket：1）数据不会丢失；2）数据的顺序不会错乱；3）双向通道。</font>

<font style="color:#002060;background-color:#d9d9d9;">SOCK_DGRAM</font><font style="color:black;background-color:#FFFFFF;">       无连接的socket：1）数据可能会丢失；2）数据的顺序可能会错乱；3）传输的效率更高。</font>

#### protocol 最终使用的协议
<font style="color:black;background-color:#FFFFFF;">在</font><font style="color:black;background-color:#FFFFFF;">IPv4</font><font style="color:black;background-color:#FFFFFF;">网络协议家族中，数据传输方式为</font><font style="color:#002060;background-color:#d9d9d9;">SOCK_STREAM</font><font style="color:black;background-color:#FFFFFF;">的协议只有</font><font style="color:#002060;background-color:#d9d9d9;">IPPROTO_TCP</font><font style="color:black;background-color:#FFFFFF;">，数据传输方式为</font><font style="color:#002060;background-color:#d9d9d9;">SOCK_DGRAM</font><font style="color:black;background-color:#FFFFFF;">的协议只有</font><font style="color:#002060;background-color:#d9d9d9;">IPPROTO_UDP</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">本参数也可以填0。</font>

```cpp
socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);    // 创建tcp的sock
socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);    // 创建udp的sock
```

## <font style="color:black;">TCP和UPD </font>
### TCP和UDP的区别
#### <font style="color:black;background-color:#FFFFFF;">TCP</font>
<font style="color:black;background-color:#FFFFFF;">a</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">面向连接，通过三次握手建立连接，四次挥手断开连接； </font><font style="color:black;background-color:#FFFFFF;"> </font>**<font style="color:black;background-color:#FFFFFF;">面试的重点</font>**

<font style="color:black;background-color:#FFFFFF;">b</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">是可靠的通信方式，通过超时重传、数据校验等方式来确保数据无差错，不丢失，不重复，并且按序到达；</font>

<font style="color:black;background-color:#FFFFFF;">c</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">把数据当成字节流，当网络出现波动时，连接可能出现响应延迟的问题；</font>

<font style="color:black;background-color:#FFFFFF;">d</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">只支持点对点通信；</font>

<font style="color:black;background-color:#FFFFFF;">e</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">报文的首部较大，为</font><font style="color:black;background-color:#FFFFFF;">20</font><font style="color:black;background-color:#FFFFFF;">字节；</font>

<font style="color:black;background-color:#FFFFFF;">f）TCP是全双工的可靠信道。</font>

#### <font style="color:black;background-color:#FFFFFF;">UDP</font>
<font style="color:black;background-color:#FFFFFF;">a</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">UDP</font><font style="color:black;background-color:#FFFFFF;">是无连接的，即发送数据之前不需要建立连接，这种方式为</font><font style="color:black;background-color:#FFFFFF;">UDP</font><font style="color:black;background-color:#FFFFFF;">带来了高效的传输效率，但也导致无法确保数据的发送成功；</font>

<font style="color:black;background-color:#FFFFFF;">b</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">UDP</font><font style="color:black;background-color:#FFFFFF;">以最大的速率进行传输，但不保证可靠交付，会出现丢失、重复等等问题；</font>

<font style="color:black;background-color:#FFFFFF;">c</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">UDP</font><font style="color:black;background-color:#FFFFFF;">没有拥塞控制，当网络出现拥塞时，发送方不会降低发送速率；</font>

<font style="color:black;background-color:#FFFFFF;">d</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">UDP</font><font style="color:black;background-color:#FFFFFF;">支持一对一，一对多，多对一和多对多的通信；</font>

<font style="color:black;background-color:#FFFFFF;">e</font><font style="color:black;background-color:#FFFFFF;">）</font><font style="color:black;background-color:#FFFFFF;">UDP</font><font style="color:black;background-color:#FFFFFF;">报文的首部比较小，只有</font><font style="color:black;background-color:#FFFFFF;">8</font><font style="color:black;background-color:#FFFFFF;">字节；</font>

<font style="color:black;background-color:#FFFFFF;">f）UDP是不可靠信道。</font>

### TCP保证自身可靠的方式
<font style="color:black;background-color:#FFFFFF;">a</font><font style="color:black;background-color:#FFFFFF;">）数据分片：在发送端对用户数据进行分片，在接收端进行重组，由</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">确定分片的大小并控制分片和重组；</font>

<font style="color:black;background-color:#FFFFFF;">b</font><font style="color:black;background-color:#FFFFFF;">）到达确认：接收端接收到分片数据时，根据分片的序号向对端回复一个确认包；</font>

<font style="color:black;background-color:#FFFFFF;">c</font><font style="color:black;background-color:#FFFFFF;">）超时重发：发送方在发送分片后开始计时，若超时却没有收到对端的确认包，将会重发分片；</font>

<font style="color:black;background-color:#FFFFFF;">d</font><font style="color:black;background-color:#FFFFFF;">）滑动窗口：</font><font style="color:black;background-color:#FFFFFF;">TCP </font><font style="color:black;background-color:#FFFFFF;">中采用滑动窗口来进行传输控制，发送方可以通过滑动窗口的大小来确定应该发送多少字节的数据。当滑动窗口为</font><font style="color:black;background-color:#FFFFFF;"> 0 </font><font style="color:black;background-color:#FFFFFF;">时，发送方不会再发送数据；</font>

<font style="color:black;background-color:#FFFFFF;">e</font><font style="color:black;background-color:#FFFFFF;">）失序处理：</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">的接收端会把接收到的数据重新排序；</font>

<font style="color:black;background-color:#FFFFFF;">f</font><font style="color:black;background-color:#FFFFFF;">）重复处理：如果传输的分片出现重复，</font><font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">的接收端会丢弃重复的数据；</font>

<font style="color:black;background-color:#FFFFFF;">g）数据校验：TCP通过数据的检验和来判断数据在传输过程中是否正确。</font>

### UDP不可靠的原因
<font style="color:black;background-color:#FFFFFF;">没有上述TCP的机制，如果校验和出错，UDP会将该报文丢弃。</font>

### TCP和UDP使用场景
**<font style="color:black;background-color:#FFFFFF;">TCP </font>****<font style="color:black;background-color:#FFFFFF;">使用场景</font>**

<font style="color:black;background-color:#FFFFFF;">TCP</font><font style="color:black;background-color:#FFFFFF;">实现了数据传输过程中的各种控制，适合对可靠性有要求的场景。</font>

**<font style="color:black;background-color:#FFFFFF;">UDP </font>****<font style="color:black;background-color:#FFFFFF;">使用场景</font>**

<font style="color:black;background-color:#FFFFFF;">可以容忍数据丢失的场景：</font>

+ **<font style="color:black;background-color:#FFFFFF;">视频、音频等多媒体通信（即时通信）；</font>**
+ <font style="color:black;background-color:#FFFFFF;">广播信息。</font>

### UDP能实现可靠传输吗？ 
<font style="color:black;background-color:#FFFFFF;">这是个伪命题，如果用UDP实现可靠传输，那么，应用程序必须实现重传和排序等功能，非常麻烦，还不如直接用TCP。谁能保证自己写的算法比写TCP协议的人更牛？</font>

## <font style="color:black;">主机字节序与网络字节序</font>
### <font style="color:black;">大端序/小端序</font>
<font style="color:black;background-color:#FFFFFF;">如果数据类型占用的内存空间大于1字节，CPU把数据存放在内存中的方式有两种：</font>

+ <font style="color:black;background-color:#FFFFFF;">大端序（Big Endian）：低位字节存放在高位，高位字节存放在低位。</font>
+ <font style="color:black;background-color:#FFFFFF;">小端序（Little Endia）：低位字节存放在低位，高位字节存放在高位。</font>

<font style="color:black;background-color:#FFFFFF;">假设从内存地址0x00000001处开始存储十六进制数0x12345678，那么：</font>

<font style="color:black;background-color:#FFFFFF;">Bit-endian（按原来顺序存储）</font>

```cpp
0x00000001           0x12 
0x00000002           0x34
0x00000003           0x56
0x00000004           0x78
```

<font style="color:black;background-color:#FFFFFF;">Little-endian（颠倒顺序储存）</font>

```cpp
0x00000001           0x78
0x00000002           0x56
0x00000003           0x34
0x00000004           0x12
```

<font style="color:black;background-color:#FFFFFF;">Intel</font><font style="color:black;background-color:#FFFFFF;">系列的</font><font style="color:black;background-color:#FFFFFF;">CPU</font><font style="color:black;background-color:#FFFFFF;">以小端序方式保存数据，其它型号的</font><font style="color:black;background-color:#FFFFFF;">CPU</font><font style="color:black;background-color:#FFFFFF;">不一定。</font>

<font style="color:black;background-color:#FFFFFF;">操作文件的本质是把内存中的数据写入磁盘，在网络编程中，传输数据的本质也是把数据写入文件（</font><font style="color:black;background-color:#FFFFFF;">socket</font><font style="color:black;background-color:#FFFFFF;">也是文件描述符）。</font>

<font style="color:black;background-color:#FFFFFF;">这样的话，字节序不同的计算机之间传输数据，可能会出现问题。</font>

![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1747711084145-527af558-1dd0-4ccb-865d-636537cccf25.png)

### <font style="color:black;">网络字节序</font>
<font style="color:black;background-color:#FFFFFF;">为了解决不同字节序的计算机之间传输数据的问题，约定采用网络字节序（大端序）。</font>

<font style="color:black;background-color:#FFFFFF;">C语言提供了四个库函数，用于在主机字节序和网络字节序之间转换：</font>

```cpp
uint16_t h to n s(uint16_t hostshort);   // uint16_t  2字节的整数 unsigned short
uint32_t htonl(uint32_t hostlong);    // uint32_t  4字节的整数 unsigned int
uint16_t ntohs(uint16_t netshort);
uint32_t n to h l(uint32_t netlong);
/*
h	host（主机）；
to  转换；
n	network（网络）；
s	short（2字节，16位的整数）；
l	long（4字节，32位的整数）；
*/
```

### <font style="color:black;">IP地址和通讯端口</font>
<font style="color:black;background-color:#FFFFFF;">在计算机中，</font><font style="color:black;background-color:#FBF5CB;">IPv4的地址</font><font style="color:black;background-color:#FFFFFF;">用</font><font style="color:black;background-color:#E8F7CF;">4字节的整数存放</font><font style="color:black;background-color:#FFFFFF;">，</font><font style="color:black;background-color:#FBF5CB;">通讯端口</font><font style="color:black;background-color:#FFFFFF;">用</font><font style="color:black;background-color:#E8F7CF;">2字节的整数（0-65535）存放</font><font style="color:black;background-color:#FFFFFF;">。</font>

<font style="color:black;background-color:#FFFFFF;">例如：</font><font style="color:black;background-color:#FFFFFF;">192.168.190.134</font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">3232284294</font><font style="color:black;background-color:#FFFFFF;">    </font><font style="color:black;background-color:#FFFFFF;">255.255.255.255</font>

<font style="color:black;background-color:#FFFFFF;">192</font><font style="color:black;background-color:#FFFFFF;">     </font><font style="color:black;background-color:#FFFFFF;">168</font><font style="color:black;background-color:#FFFFFF;">       </font><font style="color:black;background-color:#FFFFFF;">190</font><font style="color:black;background-color:#FFFFFF;">      </font><font style="color:black;background-color:#FFFFFF;">134</font>

<font style="color:black;background-color:#FFFFFF;">大端：</font><font style="color:black;background-color:#FFFFFF;">11000000 10101000 10111110 10000110</font>

<font style="color:black;background-color:#FFFFFF;">小端：10000110 10111110 10101000 11000000</font>

### <font style="color:black;">如何处理大小端序</font>
<font style="color:black;background-color:#FFFFFF;">在网络编程中，数据收发的时候有自动转换机制，不需要程序员手动转换，只有向</font><font style="color:#002060;background-color:#d9d9d9;">sockaddr_in</font><font style="color:black;background-color:#FFFFFF;">结体成员变量填充数据时，才需要考虑字节序的问题。</font>

## <font style="color:black;">万恶的结构体</font>
### <font style="color:black;">sockaddr结构体</font>
<font style="color:black;background-color:#FFFFFF;">存放协议族、端口和地址信息，客户端和</font><font style="color:#002060;background-color:#d9d9d9;">connect()</font><font style="color:black;background-color:#FFFFFF;">函数和服务端的</font><font style="color:#002060;background-color:#d9d9d9;">bind()</font><font style="color:black;background-color:#FFFFFF;">函数需要这个结构体。</font>

```cpp
struct sockaddr {
  unsigned short sa_family;	// 协议族，与socket()函数的第一个参数相同，填AF_INET。
  unsigned char sa_data[14];	// 14字节的端口和地址。
};
```

### <font style="color:black;">sockaddr_in结构体</font>
<font style="color:#002060;background-color:#d9d9d9;">sockaddr</font><font style="color:black;background-color:#FFFFFF;">结构体是为了统一地址结构的表示方法，统一接口函数，但是，操作不方便，所以定义了等价的</font><font style="color:#002060;background-color:#d9d9d9;">sockaddr_in</font><font style="color:black;background-color:#FFFFFF;">结构体，它的大小与</font><font style="color:#002060;background-color:#d9d9d9;">sockaddr</font><font style="color:black;background-color:#FFFFFF;">相同，可以强制转换成</font><font style="color:#002060;background-color:#d9d9d9;">sockaddr</font><font style="color:black;background-color:#FFFFFF;">。</font>

```cpp
struct sockaddr_in {  
  unsigned short sin_family;	// 协议族，与socket()函数的第一个参数相同，填AF_INET。
  unsigned short sin_port;		// 16位端口号，大端序。用htons(整数的端口)转换。
  struct in_addr sin_addr;		// IP地址的结构体。192.168.101.138
  unsigned char sin_zero[8];	// 未使用，为了保持与struct sockaddr一样的长度而添加。
};
struct in_addr {				// IP地址的结构体。
  unsigned int s_addr;		// 32位的IP地址，大端序。
};
```

### <font style="color:black;">gethostbyname函数</font>
<font style="color:black;background-color:#FFFFFF;">根据域名/主机名/字符串IP获取大端序IP，用于网络通讯的客户端程序中。</font>

```cpp
struct hostent *gethostbyname(const char *name);
struct hostent { 
  char *h_name;     	// 主机名。
  char **h_aliases;    	// 主机所有别名构成的字符串数组，同一IP可绑定多个域名。 
  short h_addrtype; 	// 主机IP地址的类型，例如IPV4（AF_INET）还是IPV6。
  short h_length;     	// 主机IP地址长度，IPV4地址为4，IPV6地址则为16。
  char **h_addr_list; 	// 主机的ip地址，以网络字节序存储。 
};
#define h_addr h_addr_list[0] 	// for backward compatibility.
```

<font style="color:black;background-color:#FFFFFF;">转换后，用以下代码把大端序的地址复制到</font><font style="color:#002060;background-color:#d9d9d9;">sockaddr_in</font><font style="color:black;background-color:#FFFFFF;">结构体的</font><font style="color:#002060;background-color:#d9d9d9;">sin_addr</font><font style="color:black;background-color:#FFFFFF;">成员中。</font>

```cpp
memcpy(&servaddr.sin_addr,h->h_addr,h->h_length);
```

### <font style="color:black;">字符串IP与大端序IP的转换</font>
<font style="color:black;background-color:#FFFFFF;">C语言提供了几个库函数，用于字符串格式的IP和大端序IP的互相转换，用于网络通讯的服务端程序中。</font>

```cpp
typedef unsigned int in_addr_t;    // 32位大端序的IP地址。

// 把字符串格式的IP转换成大端序的IP，转换后的IP赋给sockaddr_in.in_addr.s_addr。
in_addr_t inet_addr(const char *cp); 

// 把字符串格式的IP转换成大端序的IP，转换后的IP将填充到sockaddr_in.in_addr成员。
int inet_aton(const char *cp, struct in_addr *inp);	

// 把大端序IP转换成字符串格式的IP，用于在服务端程序中解析客户端的IP地址。
char *inet_ntoa(struct in_addr in);
```

### <font style="color:black;">demo5.cpp</font>
```cpp
/*
 * 程序名：demo5.cpp，此程序用于演示socket的客户端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;
 
int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    cout << "Using:./demo5 服务端的IP 服务端的端口\nExample:./demo5 192.168.101.138 5005\n\n"; 
    return -1;
  }

  // 第1步：创建客户端的socket。  
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if (sockfd==-1)
  {
    perror("socket"); return -1;
  }
 
  // 第2步：向服务器发起连接请求。 
  struct sockaddr_in servaddr;               // 用于存放协议、端口和IP地址的结构体。
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;             // ①协议族，固定填AF_INET。
  servaddr.sin_port = htons(atoi(argv[2]));  // ②指定服务端的通信端口。

  struct hostent* h;                         // 用于存放服务端IP地址(大端序)的结构体的指针。
  if ( (h = gethostbyname(argv[1])) == nullptr )  // 把域名/主机名/字符串格式的IP转换成结构体。
  { 
    cout << "gethostbyname failed.\n" << endl; close(sockfd); return -1;
  }
  memcpy(&servaddr.sin_addr,h->h_addr,h->h_length); // ③指定服务端的IP(大端序)。
  
  //servaddr.sin_addr.s_addr=inet_addr(argv[1]); // ③指定服务端的IP，只能用IP，不能用域名和主机名。
  if (connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)  // 向服务端发起连接清求。
  { 
    perror("connect"); close(sockfd); return -1; 
  }
  
  // 第3步：与服务端通讯，客户发送一个请求报文后等待服务端的回复，收到回复后，再发下一个请求报文。
  char buffer[1024];
  for (int ii=0;ii<10;ii++)  // 循环3次，将与服务端进行三次通讯。
  {
    int iret;
    memset(buffer,0,sizeof(buffer));
    sprintf(buffer,"这是第%d个超级女生，编号%03d。",ii+1,ii+1);  // 生成请求报文内容。
    // 向服务端发送请求报文。
    if ( (iret=send(sockfd,buffer,strlen(buffer),0))<=0)
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;

    memset(buffer,0,sizeof(buffer));
    // 接收服务端的回应报文，如果服务端没有发送回应报文，recv()函数将阻塞等待。
    if ( (iret=recv(sockfd,buffer,sizeof(buffer),0))<=0)
    {
       cout << "iret=" << iret << endl; break;
    }
    cout << "接收：" << buffer << endl;

    sleep(1);
  }
 
  // 第4步：关闭socket，释放资源。
  close(sockfd);
}
```

### <font style="color:black;">demo6.cpp</font>
```cpp
/*
 * 程序名：demo6.cpp，此程序用于演示socket通信的服务端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;
 
int main(int argc,char *argv[])
{
  if (argc!=2)
  {
    cout << "Using:./demo6 通讯端口\nExample:./demo6 5005\n\n";   // 端口大于1024，不与其它的重复。
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }

  // 第1步：创建服务端的socket。 
  int listenfd = socket(AF_INET,SOCK_STREAM,0);
  if (listenfd==-1) 
  { 
    perror("socket"); return -1; 
  }
  
  // 第2步：把服务端用于通信的IP和端口绑定到socket上。 
  struct sockaddr_in servaddr;                // 用于存放协议、端口和IP地址的结构体。
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family=AF_INET;                // ①协议族，固定填AF_INET。
  servaddr.sin_port=htons(atoi(argv[1]));     // ②指定服务端的通信端口。
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY); // ③如果操作系统有多个IP，全部的IP都可以用于通讯。
  //servaddr.sin_addr.s_addr=inet_addr("192.168.101.138"); // ③指定服务端用于通讯的IP(大端序)。
  // 绑定服务端的IP和端口。
  if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
  { 
    perror("bind"); close(listenfd); return -1; 
  }
 
  // 第3步：把socket设置为可连接（监听）的状态。
  if (listen(listenfd,5) == -1 ) 
  { 
    perror("listen"); close(listenfd); return -1; 
  }
 
  // 第4步：受理客户端的连接请求，如果没有客户端连上来，accept()函数将阻塞等待。
  int clientfd=accept(listenfd,0,0);
  if (clientfd==-1)
  {
    perror("accept"); close(listenfd); return -1; 
  }

  cout << "客户端已连接。\n";
 
  // 第5步：与客户端通信，接收客户端发过来的报文后，回复ok。
  char buffer[1024];
  while (true)
  {
    int iret;
    memset(buffer,0,sizeof(buffer));
    // 接收客户端的请求报文，如果客户端没有发送请求报文，recv()函数将阻塞等待。
    // 如果客户端已断开连接，recv()函数将返回0。
    if ( (iret=recv(clientfd,buffer,sizeof(buffer),0))<=0) 
    {
       cout << "iret=" << iret << endl;  break;   
    }
    cout << "接收：" << buffer << endl;
 
    strcpy(buffer,"ok");  // 生成回应报文内容。
    // 向客户端发送回应报文。
    if ( (iret=send(clientfd,buffer,strlen(buffer),0))<=0) 
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;
  }
 
  // 第6步：关闭socket，释放资源。
  close(listenfd);   // 关闭服务端用于监听的socket。
  close(clientfd);   // 关闭客户端连上来的socket。
}
```

## <font style="color:black;">封装socket </font>
+ 网络编程涉及到多个数据结构和函数，使用起来不方便
+ 吧客户端程序用到的数据结构和函数封装成`ctcpclient`类
+ 把服务端程序用到的数据结构和函数封装成`ctcpserver`类

### <font style="color:black;">demo7.cpp</font>
```cpp
/*
 * 程序名：demo7.cpp，此程序用于演示封装socket通讯的客户端
*/
#include <iostream>
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

  // 向服务端发送报文，成功返回true，失败返回false。
  bool send(const string &buffer)   // buffer不要用const char *
  {
    if (m_clientfd==-1) return false; // 如果socket的状态是未连接，直接返回失败。

    if ((::send(m_clientfd,buffer.data(),buffer.size(),0))<=0) return false;
    
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

 ~ctcpclient(){ close(); }
};
 
int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    cout << "Using:./demo7 服务端的IP 服务端的端口\nExample:./demo7 192.168.101.138 5005\n\n"; 
    return -1;
  }

  ctcpclient tcpclient;
  if (tcpclient.connect(argv[1],atoi(argv[2]))==false)  // 向服务端发起连接请求。
  {
    perror("connect()"); return -1;
  }

  // 第3步：与服务端通讯，客户发送一个请求报文后等待服务端的回复，收到回复后，再发下一个请求报文。
  string buffer;
  for (int ii=0;ii<10;ii++)  // 循环3次，将与服务端进行三次通讯。
  {
    buffer="这是第"+to_string(ii+1)+"个超级女生，编号"+to_string(ii+1)+"。";
    // 向服务端发送请求报文。
    if (tcpclient.send(buffer)==false)
    { 
      perror("send"); break; 
    }
    cout << "发送：" << buffer << endl;

    // 接收服务端的回应报文，如果服务端没有发送回应报文，recv()函数将阻塞等待。
    if (tcpclient.recv(buffer,1024)==false)
    {
      perror("recv()"); break;
    }
    cout << "接收：" << buffer << endl;

    sleep(1);
  }
}
```

### <font style="color:black;">demo8.cpp</font>
```cpp
/*
 * 程序名：demo8.cpp，此程序用于演示封装socket通讯的服务端
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
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
 
int main(int argc,char *argv[])
{
  if (argc!=2)
  {
    cout << "Using:./demo8 通讯端口\nExample:./demo8 5005\n\n";   // 端口大于1024，不与其它的重复。
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }

  ctcpserver tcpserver;
  if (tcpserver.initserver(atoi(argv[1]))==false) // 初始化服务端用于监听的socket。
  {
    perror("initserver()"); return -1;
  }

  // 受理客户端的连接（从已连接的客户端中取出一个客户端），  
  // 如果没有已连接的客户端，accept()函数将阻塞等待。
  if (tcpserver.accept()==false)
  {
    perror("accept()"); return -1;
  }
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
}
```

