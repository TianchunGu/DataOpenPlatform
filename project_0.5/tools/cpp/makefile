# 开发框架的头文件路径
PUBINCL = -I/home/gtc/GitHub/DataOpenPlatform/project_0.5/public

# 开发框架CPP文件名，这里直接包含进来，没有采用连接库，是为了方便调试
PUBCPP = /home/gtc/GitHub/DataOpenPlatform/project_0.5/public/_public.cpp

# 编译参数
CFLAGS = -g
# CFLAGS = -O2

all:procctl checkproc deletefiles gzipfiles ftpgetfiles

procctl:procctl.cpp
				g++ -g -o procctl procctl.cpp 
				cp -f procctl ../bin/.

checkproc:checkproc.cpp
				g++ $(CFLAGS) -o checkproc checkproc.cpp $(PUBINCL) $(PUBCPP)
				cp -f checkproc ../bin/.

deletefiles:deletefiles.cpp
				g++ $(CFLAGS) -o deletefiles deletefiles.cpp $(PUBINCL) $(PUBCPP)
				cp -f deletefiles ../bin/.

gzipfiles:gzipfiles.cpp
				g++ $(CFLAGS) -o gzipfiles gzipfiles.cpp $(PUBINCL) $(PUBCPP)
				cp -f gzipfiles ../bin/.

ftpgetfiles:ftpgetfiles.cpp
				g++ $(CFLAGS) -o ftpgetfiles ftpgetfiles.cpp $(PUBINCL) $(PUBCPP) /home/gtc/GitHub/DataOpenPlatform/project_0.5/public/libftp.a /home/gtc/GitHub/DataOpenPlatform/project_0.5/public/_ftp.cpp
				cp -f ftpgetfiles ../bin/.

clean:
	rm -f procctl checkproc deletefiles gzipfiles ftpgetfiles