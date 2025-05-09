INCLUDEDIR=-I'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/tools/' -I'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/api'
LIBDIR=-L'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/tools/' -L'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/api'

all:demo01

demo01:demo01.cpp
	g++ -o demo01 demo01.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi -Wl,-rpath,'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/tools/' -Wl,-rpath,'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/api'
# -Wl,-rpath 链接选项：在可执行文件中嵌入运行时库搜索路径，这样程序运行时就能自动找到所需的共享库

clean:
	rm -f demo01