INCLUDEDIR=-I'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/tools/' -I'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/api'
LIBDIR=-L'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/tools/' -L'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/api'

all:demo01

demo01:demo01.cpp
	g++ -o demo01 demo01.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi -Wl,-rpath,'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/tools/' -Wl,-rpath,'/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-4 makefile/Demo/api'

clean:
	rm -f demo01