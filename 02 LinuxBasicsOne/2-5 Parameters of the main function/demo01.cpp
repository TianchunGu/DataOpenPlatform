#include<iostream>
using namespace std;
/*
    1. argc 表示命令行参数的个数
    2. argv 是一个指针数组，每个元素是一个字符指针，指向一个字符串
    3. argv[0] 是程序的名称
    4. argv[1] 是第一个命令行参数
    5. argv[2] 是第二个命令行参数
*/
int main(int argc, char *argv[], char *environ[]) {
  cout<<"一共有"<<argc<<"个参数"<<endl;
  // 显示全部的参数
  for(int i=0;i<argc;i++) {
    cout<<"第"<<i<<"个参数是"<<argv[i]<<endl;
  }
  // 显示全部环境变量
  for(int i=0;environ[i]!=NULL;i++) {// environ是一个全局变量，是一个指针数组，每个元素是一个字符指针，指向一个字符串.最后一个元素是NULL
    // 显示第i个环境变量
    // environ[i] 是一个字符指针，指向一个字符串
    // environ[i] 是一个字符串
    cout<<"第"<<i<<"个环境变量是"<<environ[i]<<endl;
  }
}

/*
程序运行及输出
➜  2-5 Parameters of the main function git:(main) ✗ ls                      
demo01.cpp
➜  2-5 Parameters of the main function git:(main) ✗ g++ demo01.cpp -o demo01
➜  2-5 Parameters of the main function git:(main) ✗ ls
demo01  demo01.cpp
➜  2-5 Parameters of the main function git:(main) ✗ ./demo01 ../../123 123 456 789
一共有5个参数
第0个参数是./demo01
第1个参数是../../123
第2个参数是123
第3个参数是456
第4个参数是789
第0个环境变量是vscode_base_dir=/home/gtc/.trae-server
第1个环境变量是SHELL=/usr/bin/zsh
第2个环境变量是PLATFORM=linux
第3个环境变量是SERVER_APP_VERSION=
第4个环境变量是LC_ADDRESS=zh_CN.UTF-8
第5个环境变量是LC_NAME=zh_CN.UTF-8
第6个环境变量是OS_RELEASE_ID=ubuntu
第7个环境变量是SERVER_TOKENFILE=/home/gtc/.trae-server/.stable-5c60eab728f4cce183f319de2d3ee32fc9040268.token
第8个环境变量是TRAE_RESOLVE_TYPE=ssh
第9个环境变量是DISTRO_QUALITY=stable
第10个环境变量是SERVER_INITIAL_EXTENSIONS=
第11个环境变量是LC_MONETARY=zh_CN.UTF-8
第12个环境变量是SERVER_SCRIPT=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/index_trae.js
第13个环境变量是DISTRO_VSCODIUM_RELEASE=
第14个环境变量是PWD=/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-5 Parameters of the main function
第15个环境变量是LOGNAME=gtc
第16个环境变量是XDG_SESSION_TYPE=tty
第17个环境变量是MOTD_SHOWN=pam
第18个环境变量是HOME=/home/gtc
第19个环境变量是LANG=en_US.UTF-8
第20个环境变量是LC_PAPER=zh_CN.UTF-8
第21个环境变量是SERVER_LOGS_DIR=/home/gtc/.trae-server/logs
第22个环境变量是DISTRO_COMMIT=5c60eab728f4cce183f319de2d3ee32fc9040268
第23个环境变量是SCRIPT_ID=e18681075b48e767927a2578
第24个环境变量是SERVER_ARCH=x64
第25个环境变量是TMP_DIR=/run/user/1000
第26个环境变量是SERVER_HOST=127.0.0.1
第27个环境变量是SSH_CONNECTION=127.0.0.1 39318 127.0.0.1 22
第28个环境变量是SERVER_APP_NAME=Trae
第29个环境变量是XDG_SESSION_CLASS=user
第30个环境变量是LC_IDENTIFICATION=zh_CN.UTF-8
第31个环境变量是DOWNLOAD_RETRY_COUNT=0
第32个环境变量是SERVER_SCRIPT_PRODUCT=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/product.json
第33个环境变量是DISTRO_VERSION=1.98.2
第34个环境变量是USER=gtc
第35个环境变量是SERVER_PIDFILE=/home/gtc/.trae-server/.stable-5c60eab728f4cce183f319de2d3ee32fc9040268.pid
第36个环境变量是EXTRACT_RETRY_COUNT=0
第37个环境变量是SERVER_DIR=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268
第38个环境变量是SERVER_PACKAGE_NAME=Trae-linux-x64-875187723010_2.tar.gz
第39个环境变量是ARCH=x86_64
第40个环境变量是SHLVL=2
第41个环境变量是SERVER_APP_QUALITY=dev
第42个环境变量是LC_TELEPHONE=zh_CN.UTF-8
第43个环境变量是LC_MEASUREMENT=zh_CN.UTF-8
第44个环境变量是SERVER_LISTEN_FLAG=--port=0
第45个环境变量是XDG_SESSION_ID=6
第46个环境变量是PAPERSIZE=a4
第47个环境变量是XDG_RUNTIME_DIR=/run/user/1000
第48个环境变量是SSH_CLIENT=127.0.0.1 39318 22
第49个环境变量是LC_TIME=zh_CN.UTF-8
第50个环境变量是MANAGER_LOGS_DIR=/home/gtc/.trae-server/manager-logs/1746879826866_979440
第51个环境变量是TRAE_DETECT_REGION=CN
第52个环境变量是XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
第53个环境变量是PATH=/home/gtc/Qt/6.9.0/gcc_64/bin:/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/bin/remote-cli:/home/gtc/Qt/6.9.0/gcc_64/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
第54个环境变量是SERVER_EXTENSIONS_DIR=/home/gtc/.trae-server/extensions
第55个环境变量是SERVER_DATA_DIR=/home/gtc/.trae-server
第56个环境变量是DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
第57个环境变量是SERVER_LOGFILE=/home/gtc/.trae-server/.stable-5c60eab728f4cce183f319de2d3ee32fc9040268.log
第58个环境变量是SERVER_DOWNLOAD_PREFIX=https://lf-cdn.trae.com.cn/obj/trae-com-cn/pkg/server/releases/stable/5c60eab728f4cce183f319de2d3ee32fc9040268/linux/
第59个环境变量是LC_NUMERIC=zh_CN.UTF-8
第60个环境变量是OLDPWD=/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne
第61个环境变量是_=/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-5 Parameters of the main function/./demo01
第62个环境变量是ZSH=/home/gtc/.oh-my-zsh
第63个环境变量是PAGER=less
第64个环境变量是LESS=-R
第65个环境变量是LSCOLORS=Gxfxcxdxbxegedabagacad
第66个环境变量是LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
第67个环境变量是QT_ROOT=/home/gtc/Qt/6.9.0/gcc_64
第68个环境变量是LD_LIBRARY_PATH=/home/gtc/Qt/6.9.0/gcc_64/lib:/home/gtc/Qt/6.9.0/gcc_64/lib:
第69个环境变量是QT_PLUGIN_PATH=/home/gtc/Qt/6.9.0/gcc_64/plugins
第70个环境变量是QML2_IMPORT_PATH=/home/gtc/Qt/6.9.0/gcc_64/qml
第71个环境变量是BROWSER=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/bin/helpers/browser.sh
第72个环境变量是TERM_PROGRAM=vscode
第73个环境变量是TERM_PROGRAM_VERSION=1.98.2
第74个环境变量是COLORTERM=truecolor
第75个环境变量是GIT_ASKPASS=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/extensions/git/dist/askpass.sh
第76个环境变量是VSCODE_GIT_ASKPASS_NODE=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/node
第77个环境变量是VSCODE_GIT_ASKPASS_EXTRA_ARGS=
第78个环境变量是VSCODE_GIT_ASKPASS_MAIN=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/extensions/git/dist/askpass-main.js
第79个环境变量是VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-054f264857.sock
第80个环境变量是VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-7bd68885-3115-470d-828a-9497170a8bc5.sock
第81个环境变量是VSCODE_INJECTION=1
第82个环境变量是ZDOTDIR=/home/gtc
第83个环境变量是USER_ZDOTDIR=/home/gtc
第84个环境变量是TERM=xterm-256color
*/