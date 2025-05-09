## 制作静态库

```shell
➜  Demo git:(main) ✗ cd tools 
➜  tools git:(main) ✗ ls
public.cpp  public.h
➜  tools git:(main) ✗ g++ -c -o libpublic.a public.cpp
➜  tools git:(main) ✗ ls
libpublic.a  public.cpp  public.h
```
静态库文件为二进制文件（打开无法理解其内容），后缀为.a。

命令行中包含空格的路径会导致连接器视为多个参数。

## 制作动态库
```shell
➜  tools git:(main) g++ -fPIC -shared -o libpublic.so public.cpp 
➜  tools git:(main) ✗ ls
libpublic.a  libpublic.so  public.cpp  public.h  public.o
```