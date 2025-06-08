# 开发框架的头文件路径
PUBINCL = -I/home/gtc/GitHub/DataOpenPlatform/project_0.5/public

# 开发框架CPP文件名，这里直接包含进来，没有采用连接库，是为了方便调试
PUBCPP = /home/gtc/GitHub/DataOpenPlatform/project_0.5/public/_public.cpp

all:demo01 demo02 

demo01:demo01.cpp
	g++ -g -o demo01 demo01.cpp $(PUBINCL) $(PUBCPP)

demo02:demo02.cpp
	g++ -g -o demo02 demo02.cpp $(PUBINCL) $(PUBCPP)


clean:
	rm -f demo01 demo02 

