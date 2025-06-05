/*
 * 程序名：crtsurfdata.cpp
 * 功能：本程序用于生成气象站点的分钟数据
 * 使用方法：程序每分钟运行一次，由调度模块启动
 */

#include "_public.h"
using namespace idc;

// 省   站号  站名 纬度   经度  海拔高度
//  安徽,58015,砀山,34.27,116.2,44.2
struct st_stcode {  // 站点参数结构体
  // string 操作方便、自动扩容 操作数据库时 string没有优势，所以用char[]
  char provname[31];  // 省
  char obtid[11];     // 站号
  char obtname[31];   // 站名
  double lat;         // 纬度
  double lon;         // 经度
  double height;      // 海拔高度
};

list<st_stcode> stlist;                  // 存放全部的站点参数
bool loadstcode(const string& inifile);  // 把站点参数文件加载到stlist容器中

clogfile logfile;  // 本程序运行的日志

// 程序退出和信号2,15的处理函数
void EXIT(int sig);

int main(int argc, char* argv[]) {
  // 检查参数数量是否正确
  if (argc != 4) {
    // 如果参数数量不正确，输出帮助信息
    cout << "Using:./crtsurfdata inifile outpath logfile datafmt\n";
    cout << "Examples:/project/tools/bin/procctl 60 "
            "/project/idc/bin/crtsurfdata /project/idc/ini/stcode.ini "
            "/tmp/idc/surfdata /log/idc/crtsurfdata.log csv,xml,json\n\n";

    cout << "本程序用于生成气象站点观测的分钟数据，程序每分钟运行一次，由调度模"
            "块启动。\n";
    cout << "inifile  气象站点参数文件名。\n";
    cout << "outpath  气象站点数据文件存放的目录。\n";
    cout << "logfile  本程序运行的日志文件名。\n";
    cout << "datafmt  "
            "输出数据文件的格式，支持csv、xml和json，中间用逗号分隔。\n\n";

    return -1;
  }

  // 设置信号处理函数，确保程序可以正常退出
  closeioandsignal(true);  // 关闭0,1,2和忽略全部的信号
  signal(SIGINT, EXIT);
  signal(SIGTERM, EXIT);

  // 打开日志文件
  if (logfile.open(argv[3]) == false) {
    cout << "logfile.open(" << argv[3] << ") failed!\n";
    return -1;
  }

  // 记录程序开始运行的日志
  logfile.write("crtsurfdata 开始运行\n");

  // TODO: 实现生成气象站点数据的逻辑
  // 1. 从站点参数文件中加载站点参数，存放于容器中；
  if (loadstcode(argv[1]) == false) {
    EXIT(-1);
  }
  // 2. 根据站点参数，生成站点观测数据（随机数）；
  // 3. 把站点观测数据保存到文件中。

  // 记录程序运行结束的日志
  logfile.write("crtsurfdata 运行结束\n");

  return 0;
}

// 程序退出和信号2,15的处理函数
void EXIT(int sig) {
  // 记录程序退出的日志
  logfile.write("程序退出，sig=%d\n\n", sig);

  exit(0);
}

// 把站点参数文件加载到stlist容器中
bool loadstcode(const string& inifile) {
  cifile ifile;  // 读取文件的对象
  if (ifile.open(inifile) == false) {
    logfile.write("ifile.open(%s) failed.\n", inifile.c_str());
    return false;
  }
  string strbuffer;           // 存放从文件中读取的每一行。
  ifile.readline(strbuffer);  // 读取站点参数文件的第一行,他是标题，扔掉
  ccmdstr cmdstr;             // 用于拆分从文件中读取的行。
  st_stcode stcode;           // 站点参数的结构体

  while (ifile.readline(strbuffer)) {
    // logfile.write("strbuffer=%s\n",
    // strbuffer.c_str());//输出读取的行到日志文件。
    // 拆分从文件中读取的行，例如：安徽,58015,砀山,34.27,116.2,44.2
    cmdstr.splittocmd(strbuffer, ",");             // 拆分字符串
    memset(&stcode, 0, sizeof(struct st_stcode));  // 初始化结构体

    cmdstr.getvalue(0, stcode.provname, 30);  // 省
    cmdstr.getvalue(1, stcode.obtid, 10);     // 站点代码
    cmdstr.getvalue(2, stcode.obtname, 30);   // 站点名称
    cmdstr.getvalue(3, stcode.lat);           // 纬度
    cmdstr.getvalue(4, stcode.lon);           // 经度
    cmdstr.getvalue(5, stcode.height);        // 海拔高度

    stlist.push_back(stcode);  // 将站点数据添加到列表中
  }
  // 这里不需要手工关闭文件，cifile析构函数会自动关闭文件。

  // 把容器中全部数据写入日志中。
  // logfile.write("站点数:%d\n", stlist.size());
  // for (auto& aa : stlist) {
  //   logfile.write("%s %s %s %.2f %.2f %.2f\n\n", aa.provname, aa.obtname,
  //                 aa.obtid, aa.lat, aa.lon, aa.height);
  // }
  return true;
}

/*
./crtsurfdata ../ini/stcode.ini outpath logfile
*/