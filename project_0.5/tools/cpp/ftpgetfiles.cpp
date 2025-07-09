#include "_ftp.h"
#include "_public.h"

using namespace idc;

// 程序退出和信号2、15的处理函数
void EXIT(int sig);

// 文件信息的结构体（实际是 C++ 类）
struct st_fileinfo {
  // 文件名
  string filename;
  // 文件时间
  string mtime;

  // 默认构造函数
  st_fileinfo() = default;

  // 带参数的构造函数，初始化 filename 和 mtime
  st_fileinfo(const string& in_filename, const string& in_mtime)
      : filename(in_filename), mtime(in_mtime) {}

  // 清空 filename 和 mtime 的内容
  void clear() {
    filename.clear();
    mtime.clear();
  }
};

vector<struct st_fileinfo>
    vfilelist;  // 下载前列出服务端文件名的容器，从nlist文件中加载

bool loadlistfile();  // 把ftpclient.nlist()方法获取到的list文件加载到容器vfilelist中

// 程序运行参数的结构体
struct st_arg {
  char host[31];         // 远程服务端的IP和端口。
  int mode;              // 传输模式，1-被动模式，2-主动模式，缺省采用被动模式。
  char username[31];     // 远程服务端ftp的用户名。
  char password[31];     // 远程服务端ftp的密码。
  char remotepath[256];  // 远程服务端存放文件的目录。
  char localpath[256];   // 本地文件存放的目录。
  char matchname[256];   // 待下载文件匹配的规则。
  int ptype;  // 下载后服务端文件的处理方式：1-什么也不做 2-删除 3-备份
  char remotepathbak[256];  // 下载后服务端文件的备份目录。
} starg;

bool _xmltoarg(char* strxmlbuffer);  // 把xml解析到参数starg结构中

clogfile logfile;  // 创建日志对象
cftpclient ftp;    // 创建ftp客户端对象

void _help();  // 显示帮助文档

int main(int argc, char* argv[]) {
  // 第一步：从服务器某个目录中下载文件，可以指定文件名匹配的规则
  // main()函数的参数：日志文件名 ftp服务器的ip ftp服务器的端口 ftp的传输模式
  // ftp用户名 ftp密码 ftp服务器的目录 ftp下载到的目录 ftp文件名匹配的规则
  //.ftpgetfiles /log/idc/ftpgetfiles.log
  //"<host>192.168.150.28:21</host><mode>1</mode><username>wucz</username>"\
  "<password>oracle</password><remotepath>/data/server/surfdata</remotepath>"\
  "<localpath>/data/client/surfdata</localpath><matchname>*.xml,*.csv</matchname>"

  if (argc != 3) {
    _help();
    return -1;
  }

  // 设置信号在shell状态下可用“kill+进程号”正常终止进程。
  // 但请不要用“kill -9 + 进程号”，否则进程会被强制终止。
  // closeioandsignal(true);
  // //关闭0、1、2和忽略全部信号，在调试阶段，这行代码可以不启用
  signal(SIGINT, EXIT);
  signal(SIGTERM, EXIT);

  // 1. 打开日志文件
  if (logfile.open(argv[1]) == false) {
    printf("打开日志文件(%s)失败！\n", argv[1]);
    return -1;
  }
  // 2. 解析xml，得到程序运行的参数
  if (_xmltoarg(argv[2]) == false) {
    return -1;
  }
  // 3. 登录ftp服务器

  if (ftp.login(starg.host, starg.username, starg.password, starg.mode) ==
      false) {
    logfile.write("ftp.login(%s,%s,%s)登录失败。\n %s \n", starg.host,
                  starg.username, starg.password, ftp.response());
    return -1;
  }

  logfile.write("ftp.login()登录成功。\n");

  // 4. 进入ftp服务器存放文件的目录

  if (ftp.chdir(starg.remotepath) == false) {
    logfile.write("ftp.chdir(%s)失败。\n %s \n", starg.remotepath,
                  ftp.response());
    return -1;
  }

  // 5. 调用ftpclient.nlist()方法列出服务器目录中的文件名，保存在本地文件中。

  if (ftp.nlist(".", sformat("/home/gtc/GitHub/DataOpenPlatform/project_0.5/"
                             "idcdata/temp/nlist/ftpgetfiles_%d.nlist",
                             getpid())) == false) {
    logfile.write("ftp.nlist(%s)失败。\n %s \n", starg.remotepath,
                  ftp.response());
    return -1;
  }

  logfile.write("nlist(%s) ok.\n",
                sformat("/home/gtc/GitHub/DataOpenPlatform/project_0.5/"
                        "idcdata/temp/nlist/ftpgetfiles_%d.nlist",
                        getpid())
                    .c_str());

  // 6. 把ftpclient.nlist()方法获取到的list文件加载到容器vfilelist中

  if (loadlistfile() == false) {
    logfile.write("loadlistfile()失败。\n %s \n", ftp.response());
    return -1;
  }

  // 7. 遍历vfilelist容器，调用ftpclient.get()方法下载文件
  string strremotefilename, strlocalfilename;
  for (auto& aa : vfilelist) {
    sformat(strremotefilename, "%s/%s", starg.remotepath,
            aa.filename.c_str());  // 拼接服务端全路径的文件名。
    sformat(strlocalfilename, "%s/%s", starg.localpath,
            aa.filename.c_str());  // 拼接本地全路径的文件名。

    logfile.write("get %s ...", strremotefilename.c_str());
    // 调用ftpclient.get()方法下载文件。
    if (ftp.get(strremotefilename, strlocalfilename) == false) {
      logfile << "failed.\n" << ftp.response() << "\n";
      return -1;
    }

    logfile << "ok.\n";
    // ptype==1,增量下载文件；
    // if (starg.ptype == 1) {
    // }
    // ptype==2,删除服务端的文件；
    if (starg.ptype == 2) {
      if (ftp.ftpdelete(strremotefilename) == false) {
        logfile.write("ftp.ftpdelete(%s)失败。\n %s \n",
                      strremotefilename.c_str(), ftp.response());
        return -1;
      }
    }

    // ptype==3,备份
    if (starg.ptype == 3) {
      string strremotefilenamebak =
          sformat("%s/%s", starg.remotepathbak,
                  aa.filename.c_str());  // 生成全路径的备份文件名
      if (ftp.ftprename(strremotefilename, strremotefilenamebak) == false) {
        logfile.write("ftp.ftprename(%s,%s)失败。\n %s \n",
                      strremotefilename.c_str(), strremotefilenamebak.c_str(),
                      ftp.response());
        return -1;
      }
    }
  }

  return 0;
}

// 显示帮助文档
void _help() {
  printf("\n");
  printf("Usage: ftpgetfiles logfilename xmlbuffer\n\n");
  printf(
      "/home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/ftpgetfiles "
      "/home/gtc/GitHub/DataOpenPlatform/project_0.5/log/idc/"
      "ftpgetfiles_surfdata.log"
      "\"<host>127.0.0.1</host><mode>1</mode>\" "
      "\"<username>ggb</username><password>ggb123456</password>\" "
      "\"<remotepath>/home/ggb/ftp_data/tmp</remotepath><localpath>/home/gtc/"
      "GitHub/DataOpenPlatform/project_0.5/idcdata/surfdata"
      "</localpath>\" "
      "\"<matchname>SURF_ZH*.XML,SURF_ZH*.CSV</matchname>"
      "<ptype>3</ptype><remotepathbak>/home/ggb/ftp_data/tmp/idc/surfdatabak</"
      "remotepathbak>\n\n");

  printf("本程序是通用的功能模块，用于把远程ftp服务端的文件下载到本地目录。\n");
  printf("logfilename是本程序运行的日志文件。\n");
  printf("xmlbuffer为文件下载的参数，如下：\n");
  printf("<host>192.168.150.28:21</host> 远程服务端的IP和端口。\n");
  printf(
      "<mode>1</mode> "
      "传输模式，1-被动模式，2-主动模式，缺省采用被动模式。\n");
  printf("<username>wucz</username> 远程服务端ftp的用户名。\n");
  printf("<password>oracle</password> 远程服务端ftp的密码。\n");
  printf(
      "<remotepath>/tmp/idc/surfdata</remotepath> "
      "远程服务端存放文件的目录。\n");
  printf("<localpath>/idcdata/surfdata</localpath> 本地文件存放的目录。\n");
  printf(
      "<matchname>SURF_ZH*.XML,SURF_ZH*.CSV</matchname> "
      "待下载文件匹配的规则。\n"
      "不匹配的文件不会被下载，本字段尽可能设置精确，不建议用*"
      "匹配全部的文件。\n\n\n");
  printf("<ptype>1</ptype> 文件下载成功后，远程服务端文件的处理方式：\n");
  printf("  1-什么也不做；2-删除；3-备份，如果为3，还要指定备份的目录。\n");
  printf(
      "<remotepathbak>/home/ggb/ftp_data/tmp/idc/surfdatabak</remotepathbak> "
      "文件下载成功后，服务端文件的备份目录，\n");
  printf("  此参数只有当ptype=3时才有效。\n\n\n");
}

// 把xml解析到参数starg结构中
bool _xmltoarg(char* strxmlbuffer) {
  memset(&starg, 0, sizeof(struct st_arg));

  getxmlbuffer(strxmlbuffer, "host", starg.host, 30);  // 远程服务器的IP和端口。
  if (strlen(starg.host) == 0) {
    logfile.write("host值为空！\n");
    return false;
  }

  getxmlbuffer(
      strxmlbuffer, "mode",
      starg.mode);  // 传输模式，1-被动模式，2-主动模式，缺省采用被动模式。
  if (starg.mode != 2) {
    starg.mode = 1;
  }

  getxmlbuffer(strxmlbuffer, "username", starg.username,
               30);  // 远程服务端ftp的用户名。
  if (strlen(starg.username) == 0) {
    logfile.write("username值为空！\n");
    return false;
  }

  getxmlbuffer(strxmlbuffer, "password", starg.password,
               30);  // 远程服务端ftp的密码。
  if (strlen(starg.password) == 0) {
    logfile.write("password值为空！\n");
    return false;
  }

  getxmlbuffer(strxmlbuffer, "remotepath", starg.remotepath,
               255);  // 远程服务端存放文件的目录。
  if (strlen(starg.remotepath) == 0) {
    logfile.write("remotepath值为空！\n");
    return false;
  }

  getxmlbuffer(strxmlbuffer, "localpath", starg.localpath,
               255);  // 本地文件存放的目录。
  if (strlen(starg.localpath) == 0) {
    logfile.write("localpath值为空！\n");
    return false;
  }

  getxmlbuffer(strxmlbuffer, "matchname", starg.matchname,
               100);  // 待下载文件匹配的规则。
  if (strlen(starg.matchname) == 0) {
    logfile.write("matchname值为空！\n");
    return false;
  }

  // 下载后服务端文件的处理方式：1-什么也不做；2-删除；3-备份，如果为3，还要指定备份的目录。
  getxmlbuffer(strxmlbuffer, "ptype", starg.ptype);
  if ((starg.ptype != 1) && (starg.ptype != 2) && (starg.ptype != 3)) {
    logfile.write("ptype值错误！\n");
    return false;
  }

  // 下载后服务端文件的备份目录
  if (starg.ptype == 3) {
    getxmlbuffer(strxmlbuffer, "remotepathbak", starg.remotepathbak, 255);
    if (strlen(starg.remotepathbak) == 0) {
      logfile.write("remotepathbak值为空！\n");
      return false;
    }
  }

  return true;
}

// 把ftpclient.nlist()方法获取到的list文件加载到容器vfilelist中
bool loadlistfile() {
  vfilelist.clear();
  cifile ifile;

  if (ifile.open(sformat("/home/gtc/GitHub/DataOpenPlatform/project_0.5/"
                         "idcdata/temp/nlist/ftpgetfiles_%d.nlist",
                         getpid())) == false) {
    logfile.write("ifile.open(%s)失败。\n",
                  sformat("/home/gtc/GitHub/DataOpenPlatform/project_0.5/"
                          "idcdata/temp/nlist/ftpgetfiles_%d.nlist",
                          getpid())
                      .c_str());
    return false;
  }

  string strfilename;
  while (true) {
    if (ifile.readline(strfilename) == false)
      break;

    if (matchstr(strfilename, starg.matchname) == false)
      continue;

    vfilelist.push_back(st_fileinfo(strfilename, ""));
  }
  ifile.closeandremove();

  // for (auto& aa : vfilelist) {
  //   logfile.write("filename=%s=\n", aa.filename.c_str());
  // }

  return true;
}

void EXIT(int sig) {
  printf("程序退出，sig=%d\n", sig);
  exit(0);
}

// /home/gtc/GitHub/DataOpenPlatform/project_0.5/log/idc/ftpgetfiles_surfdata.log
// "<host>127.0.0.1</host><mode>1</mode><username>ggb</username><password>ggb123456</password><remotepath>/home/ggb/ftp_data/tmp</remotepath><localpath>/home/gtc/GitHub/DataOpenPlatform/project_0.5/idcdata/surfdata</localpath><matchname>SURF_ZH*.XML,*.CSV</matchname><ptype>3</ptype><remotepathbak>/home/ggb/ftp_data/tmp/idc/surfdatabak</remotepathbak>"
