# 开发框架的头文件路径
PUBINCL = -I/home/gtc/GitHub/DataOpenPlatform/project_0.5/public

# 开发框架CPP文件名，这里直接包含进来，没有采用连接库，是为了方便调试
PUBCPP = /home/gtc/GitHub/DataOpenPlatform/project_0.5/public/_public.cpp

# 编译参数
CFLAGS = -g

# 定义目标文件
TARGET = crtsurfdata

# 定义源文件
SRC = crtsurfdata.cpp

# 定义目标文件的生成规则
all: $(TARGET)

$(TARGET): $(SRC)
	g++ $(CFLAGS) -o $(TARGET) $(SRC) $(PUBINCL) $(PUBCPP) -lm -lc
	cp -f $(TARGET) ../bin/.

# 清理生成的文件
clean:
	rm -f $(TARGET)