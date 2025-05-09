# 指定编译的目标文件是libmyapi.a和libmyapi.so
all:libmyapi.a libmyapi.so

# 编译libmyapi.a需要依赖myapi.h和myapi.cpp
# 如果被依赖文件内容发生了变化，将重新编译libmyapi.a
libmyapi.a:myapi.h myapi.cpp
	g++ -c -o libmyapi.a myapi.cpp

libmyapi.so:myapi.h myapi.cpp
	g++ -fPIC -shared -o libmyapi.so myapi.cpp

# clean用于清理编译目标文件，仅在make clean才会执行。
clean:
	rm -f libmyapi.a libmyapi.so
