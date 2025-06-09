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

// 气象站观测数据的结构体
struct st_surfdata {
  char obtid[11];      // 站点代码
  char ddatetime[15];  // 数据时间：格式yyyymmddhh24miss，精确到分钟，秒固定填00
  int t;               // 气温：单位，0.1摄氏度
  int p;               // 气压：单位，0.1百帕
  int u;               // 相对湿度：0-100之间的值
  int wd;              // 风向：0-360之间的值
  int wf;              // 风速：单位，0.1米/秒
  int r;               // 降雨量：单位，0.1毫米
  int vis;             // 能见度：单位，0.1米
};
list<struct st_surfdata> datalist;  // 存放观测数据的容器
void crtsurfdata();  // 根据stlist容器中的站点参数，生成站点的观测数据，存放在datalist中·

list<st_stcode> stlist;                  // 存放全部的站点参数
bool loadstcode(const string& inifile);  // 把站点参数文件加载到stlist容器中

char strddatetime[15];  // yyyymmddhh24miss格式的当前时间

// 把容器datalist中的气象观测数据写入文件，outpath-数据文件存放的目录；datafmt-数据文件的格式，取值：csv、xml、json
bool crtsurffile(const string& outpath, const string& datafmt);

clogfile logfile;  // 本程序运行的日志

// 程序退出和信号2,15的处理函数
void EXIT(int sig);

cpactive pactive;  // 进程的心跳

int main(int argc, char* argv[]) {
  // 检查参数数量是否正确
  // 站点参数文件 生成的测试数据存放的目录 本程序运行的日志 输出数据文件的格式
  if (argc != 5) {
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

  // 把当前进程的心跳加入到共享内存
  pactive.addpinfo(10, "crtsurfdata");

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
  // 获取时间的代码
  memset(strddatetime, 0, sizeof(strddatetime));
  ltime(strddatetime, "yyyymmddhh24miss");  // 获取系统当前时间
  strncpy(strddatetime + 12, "00", 2);      // 把时间数据中的秒固定填00
  // 2. 根据站点参数，生成站点观测数据（随机数）；
  crtsurfdata();
  // 3.
  // 把站点观测数据保存到文件中。把容器datalist中的气象观测数据写入文件，outpath-数据文件存放的目录；datafmt-数据文件的格式，取值：csv、xml、json
  if (strstr(argv[4], "csv") != 0)
    crtsurffile(argv[2], "csv");
  if (strstr(argv[4], "xml") != 0)
    crtsurffile(argv[2], "xml");
  if (strstr(argv[4], "json") != 0)
    crtsurffile(argv[2], "json");

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

// 根据stlist容器中的站点参数，生成站点的观测数据，存放在datalist中·
void crtsurfdata() {
  srand(time(0));          //  设置随机数种子。
  st_surfdata stsurfdata;  // 存放观测数据的结构体
  // 遍历气象站点的参数的stlist容器，生成每个站点的观测数据，存放在datalist容器中。
  for (auto& aa : stlist) {
    memset(&stsurfdata, 0, sizeof(stsurfdata));  // 初始化stsurfdata结构体。

    // 填充观测数据的结构体的成员
    strcpy(stsurfdata.obtid, aa.obtid);          // 站点代码
    strcpy(stsurfdata.ddatetime, strddatetime);  // 数据时间
    stsurfdata.t =
        rand() % 350;  // 气温：单位0.1摄氏度。0-350之间。可犯可不犯的错误不要犯
    stsurfdata.p = rand() % 265 + 10000;      // 气压：单位0.1百帕。0-1000之间。
    stsurfdata.u = rand() % 101;              // 相对湿度：0-100之间。
    stsurfdata.wd = rand() % 360;             // 风向：0-360之间。
    stsurfdata.wf = rand() % 150;             // 风速：单位0.1m/s。
    stsurfdata.r = rand() % 16;               // 降雨量：0.1mm
    stsurfdata.vis = rand() % 5001 + 100000;  // 能见度：0.1米

    datalist.push_back(stsurfdata);  // 把观测数据的结构体放入datalist容器
  }
  // 将生成的数据写入日志中
  // for (auto& aa : datalist) {
  //   logfile.write("%s %s %.1f %.1f %d %.1f %.1f %.1f %.1f\n", aa.obtid,
  //                 aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
  //                 aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);
  // }
}

// 把容器datalist中的气象观测数据写入文件，outpath-数据文件存放的目录；datafmt-数据文件的格式，取值：csv、xml、json
bool crtsurffile(const string& outpath, const string& datafmt) {
  // 加进程编号是一种常见的方法，这样，不同进程的输出文件不会冲突。
  // 拼接生成数据的文件名，例如：/tmp/idc/surfdata/SURF_ZH_20210629092200_2254.csv
  string strfilename = outpath + "/" + "SURF_ZH_" + strddatetime + "_" +
                       to_string(getpid()) + "." + datafmt;

  cofile ofile;  // 写入数据文件的对象。

  if (ofile.open(strfilename) == false) {
    logfile.write("ofile.open(%s) failed.\n", strfilename.c_str());
    return false;
  }

  // 把datalist容器中的观测数据写入文件，支持csv、xml和json三种格式。
  if (datafmt == "csv")
    ofile.writeline(
        "站点代码,数据时间,气温,气压,相对湿度,风向,风速,降雨量,能见度\n");
  if (datafmt == "xml")
    ofile.writeline("<data>\n");
  if (datafmt == "json")
    ofile.writeline("{\"data\":[\n");

  // 遍历存放观测数据的datalist容器。
  for (auto& aa : datalist) {
    // 把每行数据写入文件。
    if (datafmt == "csv")
      ofile.writeline("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n", aa.obtid,
                      aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
                      aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);

    if (datafmt == "xml")
      ofile.writeline(
          "<obtid>%s</obtid><ddatetime>%s</ddatetime><t>%.1f</t><p>%.1f</"
          "p><u>%d</u>"
          "<wd>%d</wd><wf>%.1f</wf><r>%.1f</r><vis>%.1f</vis><endl/>\n",
          aa.obtid, aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
          aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);

    if (datafmt == "json") {
      ofile.writeline(
          "{\"obtid\":\"%s\",\"ddatetime\":\"%s\",\"t\":\"%.1f\",\"p\":\"%."
          "1f\","
          "\"u\":\"%d\",\"wd\":\"%d\",\"wf\":\"%.1f\",\"r\":\"%.1f\",\"vis\":"
          "\"%.1f\"}",
          aa.obtid, aa.ddatetime, aa.t / 10.0, aa.p / 10.0, aa.u, aa.wd,
          aa.wf / 10.0, aa.r / 10.0, aa.vis / 10.0);
      // 注意，json文件的最后一条记录不需要逗号，用以下代码特殊处理。
      static int ii = 0;               // 已写入数据行数的计数器。
      if (ii < datalist.size() - 1) {  // 如果不是最后一行。
        ofile.writeline(",\n");
        ii++;
      } else
        ofile.writeline("\n");
    }
  }

  if (datafmt == "xml")
    ofile.writeline("</data>\n");
  if (datafmt == "json")
    ofile.writeline("]}\n");

  ofile.closeandrename();  // 关闭临时文件，并改名为正式的文件。

  logfile.write("生成数据文件%s成功，数据时间%s，记录数%d。\n",
                strfilename.c_str(), strddatetime, datalist.size());

  return true;
}

/*
./crtsurfdata ../ini/stcode.ini
/home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/output logfile xml
*/

/*
编译文件：该文件的编译基于makefile文件

文件运行：
该文件通过procctl启动，运行周期建议为60秒，命令如下：
/home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/procctl 60
/home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/cpp/crtsurfdata
/home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/ini/stcode.ini
/tmp/idc/surfdata
/home/gtc/GitHub/DataOpenPlatform/project_0.5/log/idc/crtsurfdata.log
csv,xml,json

需要使用以下命令才能杀死进程
killall -9 procctl
*/