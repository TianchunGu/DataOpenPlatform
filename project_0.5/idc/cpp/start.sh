#此脚本用于启动数据共享平台全部的服务程序。

#启动守护模块
/home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/procctl 10 /home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/bin/checkproc /tmp/log/checkproc.log
#启动气象站点观测的分钟数据，程序每分钟运行一次
/home/gtc/GitHub/DataOpenPlatform/project_0.5/tools/cpp/procctl 60 /home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/cpp/crtsurfdata /home/gtc/GitHub/DataOpenPlatform/project_0.5/idc/ini/stcode.ini /tmp/idc/surfdata /home/gtc/GitHub/DataOpenPlatform/project_0.5/log/idc/crtsurfdata.log csv,xml,json
