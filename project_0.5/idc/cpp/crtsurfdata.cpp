/*
 * 程序名：crtsurfdata.cpp
 * 功能：本程序用于生成气象站点的分钟数据
 * 使用方法：程序每分钟运行一次，由调度模块启动
 */

#include "_public.h"
using namespace idc;

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

  // 在这里编写处理业务的代码
  // TODO: 实现生成气象站点数据的逻辑
  sleep(100);

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