# 指定编译的目标文件是libpublic.a和libpublic.so
all:libpublic.a \
    libpublic.so

# 编译libpublic.a需要依赖public.h和public.cpp
# 如果被依赖文件内容发生了变化，将重新编译libpublic.a
libpublic.a:public.h public.cpp
        g++ -c -o libpublic.a public.cpp

libpublic.so:public.h public.cpp
        g++ -fPIC -shared -o libpublic.so public.cpp

# clean用于清理编译目标文件，仅在make clean才会执行。
clean:
        rm -f libpublic.a libpublic.so
