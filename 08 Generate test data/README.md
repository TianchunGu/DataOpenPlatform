## 业务需求
### 程序员必须熟悉业务
+ 做项目的目的是为了解决业务的需求。
+ 把项目做好的前提是必须熟悉业务的流程和数据。
+ 银行系统：存款和取款的流程，利息的计算方法。
+ 医院系统：挂号、门诊、住院、药房、收费等流程和数据的含义。
+ 游戏开发：先会玩游戏。
+ 在中国，程序员的工作以应用系统的开发为主。
+ 所以，几乎没有只会写程序，不熟悉业务的程序员。
+ 找工作面试的时候，除了聊技术，也可能聊业务，业务是工作经验的一部分。
+ 数据开放平台的业务相关性不强，数据很多，但不必深入了解。
+ 两种数据用例：全国气象站点参数、全国气象站点观测数据。
+ 课程的最后一章会介绍更多的数据以及获取数据的方法，应对面试。

### 测试数据用例
+ 全国气象站点参数（已准备好，存于文件中）

> 文件路径：
>
> `/DataOpenPlatform/project/idc/ini/stcode.ini`
>

```plain
省   站号  站名 纬度   经度  海拔高度
安徽,58015,砀山,34.27,116.2,44.2
安徽,58102,亳州,33.47,115.44,39.1
安徽,58118,蒙城,33.16,116.31,10.3
安徽,58122,宿州,33.38,116.59,25.9
安徽,58203,阜阳,32.52,115.44,32.7
安徽,58215,寿县,32.26,116.47,25.7
安徽,58221,蚌埠,32.51,117.18,26.8
```

+ 全国气象站点观测数据（需要写程序生成，生成后的数据存于文件中，包括csv、xml、json三种格式）

### 超级女生信息
| no | name | height | sc | yz |
| --- | --- | --- | --- | --- |
| 0001 | 西施 | 165 | 火辣 | 沉鱼 |
| 0002 | 貂蝉 | 168 | 匀称 | 落雁 |
| 0003 | 冰冰 | 167 | 丰满 | 漂亮 |


字段说明：no (编号)、name (姓名)、height (身高)、sc (身材)、yz (颜值)

#### CSV
```plain
no,name,height,sc,yz
0001,西施,165,火辣,沉鱼
0002,貂蝉,168,匀称,落雁
0003,冰冰,167,丰满,漂亮
```



<font style="color:rgb(27, 28, 29);">第一行表示字段名的内容可有可无；</font>

<font style="color:rgb(27, 28, 29);">每一行代表一条记录，字段之间用逗号分隔；</font>

<font style="color:rgb(27, 28, 29);">字段的取值中不能包含逗号，否则有歧义。</font>

#### <font style="color:rgb(27, 28, 29);">xml</font>
```xml
<girls>
  <no>0001</no><name>西施</name><height>165</height><sc>火辣</sc><yz>沉鱼</yz><endl/>
  <no>0002</no><name>貂蝉</name><height>168</height><sc>匀称</sc><yz>落雁</yz><endl/>
  <no>0003</no><name>冰冰</name><height>167</height><sc>丰满</sc><yz>漂亮</yz><endl/>
</girls>
```

数据集的开始和结束的标签: `<grils> </girls>` 

每行数据结束的标签: `<endl/>` 

字段标签: no (编号)、name (姓名)、height (身高)、sc (身材)、yz (颜值)  

+ 可扩展标记语言，标准通用标记语言的子集，简称XML。
+ 自我描述，简单易懂，容错性和可扩展性非常好。
+ 是数据处理、数据通讯和数据交换等应用场景的常用数据格式。

#### json
```json
{
"girls":
  [
    {"no":"0001","name":"西施","height":"165","sc":"火辣","yz":"沉鱼"},
    {"no":"0002","name":"貂蝉","height":"168","sc":"匀称","yz":"落雁"},
    {"no":"0003","name":"冰冰","height":"167","sc":"丰满","yz":"漂亮"}
  ]
}
```

 girls对象包含了三个超女记录的数组。  

+ JavaScript Object Notation, JavaScript对象表示法。 
+ 是一种轻量级的文本数据交换格式。 
+ 使用JavaScript语法来描述数据对象，自我描述，容易理解。  

### 扩展阅读
+ XML和JSON有点复杂，大部分的场景采用最简单的格式即可。 
+ XML和JSON是一种思想，可随意发挥，实用就好，不必拘泥于形式。  
+ 前端常用JSON，后端常用XML。
+ 不一定要采用标准的XML或JSON格式。

### 气象站点观测数据
+ 气象站一分钟进行一次观测，每观测一次产生一条数据。
+ 一共有839个站点，每分钟将生成839条数据。

#### CSV
![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1749049066501-8315f0a0-37be-4de8-981f-703ab78aea23.png)

#### XML
![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1749049093605-97b164f2-6e5a-4002-ab69-89138ec1fd74.png)

#### JSON
![](https://cdn.nlark.com/yuque/0/2025/png/33636091/1749049117219-70e06843-e865-4ef5-b5aa-d16dffa084c6.png)

## 搭建程序的框架
### 学习方法
+ 先把一节视频看完，不能完全理解为什么这么做也没关系。
+ 把代码默写出来，编译，调试，实现功能。（初学阶段不要有自己的想法）
+ 一步一个脚印，搞定了一节课再继续下一节课。（环环相扣）
+ 目录结构、文件名与我保持相同，避免没必要的麻烦

### 编写程序框架`crtsurfdata.cpp`
对于服务程序而言，日志和处理信号是基本功能。

目前主要实现其日志和处理信号的功能。

```cpp
/*
 * 程序名：crtsurfdata.cpp
 * 功能：本程序用于生成气象站点的分钟数据
 * 使用方法：程序每分钟运行一次，由调度模块启动
 */

#include "_public.h"
using namespace idc;

clogfile logfile;  // 本程序运行的日志

// 程序退出和信号2,15的处理函数
void EXIT(int sig);

int main(int argc, char* argv[]) {
  // 检查参数数量是否正确
  if (argc != 4) {
    // 如果参数数量不正确，输出帮助信息
    cout << "Using:./crtsurfdata inifile outpath logfile datafmt\n";
    cout << "Examples:/project/tools/bin/procctl 60 "
            "/project/idc/bin/crtsurfdata /project/idc/ini/stcode.ini "
            "/tmp/idc/surfdata /log/idc/crtsurfdata.log csv,xml,json\n\n";

    cout << "本程序用于生成气象站点观测的分钟数据，程序每分钟运行一次，由调度模"
            "块启动。\n";
    cout << "inifile  气象站点参数文件名。\n";
    cout << "outpath  气象站点数据文件存放的目录。\n";
    cout << "logfile  本程序运行的日志文件名。\n";
    cout << "datafmt  "
            "输出数据文件的格式，支持csv、xml和json，中间用逗号分隔。\n\n";

    return -1;
  }

  // 设置信号处理函数，确保程序可以正常退出
  closeioandsignal(true);  // 关闭0,1,2和忽略全部的信号
  signal(SIGINT, EXIT);
  signal(SIGTERM, EXIT);

  // 打开日志文件
  if (logfile.open(argv[3]) == false) {
    cout << "logfile.open(" << argv[3] << ") failed!\n";
    return -1;
  }

  // 记录程序开始运行的日志
  logfile.write("crtsurfdata 开始运行\n");

  // 在这里编写处理业务的代码
  // TODO: 实现生成气象站点数据的逻辑
  sleep(100);

  // 记录程序运行结束的日志
  logfile.write("crtsurfdata 运行结束\n");

  return 0;
}

// 程序退出和信号2,15的处理函数
void EXIT(int sig) {
  // 记录程序退出的日志
  logfile.write("程序退出，sig=%d\n\n", sig);

  exit(0);
}
```

```makefile
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
```

## 加载站点参数
1. 从站点参数文件中加载站点参数，存放于容器中；
2. 根据站点参数，生成站点观测数据（随机数）；
3. 把站点观测数据保存到文件中。

## 模拟观测数据


## 把数据写入文件




