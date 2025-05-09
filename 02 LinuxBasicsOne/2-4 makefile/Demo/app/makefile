INCLUDEDIR=-I/home/wucz/tools -I/home/wucz/api
LIBDIR=-L/home/wucz/tools -L/home/wucz/api

all:demo01 demo02 demo03

demo01:demo01.cpp
        g++ -o demo01 demo01.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi
        cp demo01 /tmp/.

demo02:demo02.cpp
        g++ -o demo02 demo02.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi

demo03:demo03.cpp
        g++ -o demo03 demo03.cpp $(INCLUDEDIR) $(LIBDIR) -lpublic -lmyapi

clean:
        rm -f demo01 demo02 demo03