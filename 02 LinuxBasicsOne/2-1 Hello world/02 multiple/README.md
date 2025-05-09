## 多源文件编译运行

```shell
➜  02 multiple git:(main) ✗ ls
demo.cpp  public.cpp  public.h  README.md
➜  02 multiple git:(main) ✗ g++ demo.cpp public.cpp -o demo
➜  02 multiple git:(main) ✗ ls
demo  demo.cpp  public.cpp  public.h  README.md
➜  02 multiple git:(main) ✗ ./demo 
Hello world!
调用了func()函数
➜  02 multiple git:(main) ✗ 
```