#include "_public.h"
using namespace idc;

cpactive pactive;  // 进程的心跳

// 程序退出和信号2、15的处理函数。
void EXIT(int sig);

int main(int argc, char* argv[]) {
  // 1. 程序的帮助文档
  if (argc != 4) {
    printf("\n");
    // pathname 目录中子目录的文件也会被清理掉。
    printf("Using:/project/tools/bin/gzipfiles pathname matchstr timeout\n\n");

    printf(
        "Example:/project/tools/bin/gzipfiles /tmp/idc/surfdata "
        "\"*.xml,*.json\" 0.01\n");
    cout << R"(        /project/tools/bin/gzipfiles /log/idc "*.log.20*" 0.02)"
         << endl;
    printf(
        "        /project/tools/bin/procctl 300 /project/tools/bin/gzipfiles "
        "/log/idc \"*.log.20*\" 0.02\n");
    printf(
        "        /project/tools/bin/procctl 300 /project/tools/bin/gzipfiles "
        "/tmp/idc/surfdata \"*.xml,*.json\" 0.01\n\n");

    printf("这是一个工具程序，用于压缩历史的数据文件或日志文件。\n");
    printf(
        "本程序把pathname目录及子目录中timeout天之前的匹配matchstr文件全部压缩"
        "，timeout可以是小数。\n");
    printf("本程序调用/usr/bin/gzip命令压缩文件。\n\n\n");

    return -1;
  }
  // 2. 忽略全部的信号和关闭I/O，设置信号处理函数
  // closeioandsignal(true);  //
  // 在开发测试阶段，这行代码不启用，方便显示调试信息。
  signal(2, EXIT);
  signal(15, EXIT);
  pactive.addpinfo(120, "gzipfiles");  // 把当前进程的心跳加入共享内存。
  // 3. 获取被定义为历史数据文件的时间点
  string strtimeout =
      ltime1("yyyymmddhh24miss", 0 - (int)(atof(argv[3]) * 24 * 60 * 60));
  // cout << "strtimeout=" << strtimeout << endl;
  // 4. 打开目录
  cdir dir;
  if (dir.opendir(argv[1], argv[2], 10000, true) == false) {
    printf("dir.opendir(%s) failed.\n", argv[1]);
    return -1;
  }
  // 5. 遍历目录中的文件，如果是历史数据文件，压缩它。
  while (dir.readdir() == true) {
    // 把文件的时间与历史文件的时间点比较，如果更早，并且不是压缩文件，就需要压缩。
    if ((dir.m_mtime < strtimeout) &&
        (matchstr(dir.m_filename, "*.gz") == false)) {
      // 压缩文件，调用操作系统的gzip命令。
      // 该句代码需要注意空格
      string strcmd =
          "/usr/bin/gzip -f " + dir.m_ffilename + " 1>/dev/null 2>/dev/null";
      if (system(strcmd.c_str()) == 0) {
        cout << "压缩文件成功：" << dir.m_ffilename << "\n";
      } else {
        cout << "压缩文件失败：" << dir.m_ffilename << "\n";
      }
      // 如果压缩的文件比较大，有几个G，需要时间可能比较长，所以，增加更新心跳的代码
      pactive.uptatime();
    }
  }
  return 0;
}

void EXIT(int sig) {
  printf("程序退出，sig=%d\n", sig);
  exit(0);
}