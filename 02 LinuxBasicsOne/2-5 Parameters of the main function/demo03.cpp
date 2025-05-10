// 显示环境变量
#include <iostream>
using namespace std;

int main(int argc,char *argv[],char *envp[])
{
  cout << "一共有" << argc << "个参数。\n";

  // 显示全部的参数。
  for (int ii=0;ii<argc;ii++)
  {
    cout << "第" << ii << "个参数：" << argv[ii] << endl;
  }
  // 显示全部的环境变量。
  for (int ii=0;envp[ii]!=0;ii++)  // 环境变量数组最后一个元素是0。
  {
    cout << envp[ii] << endl;
  }

  // 设置环境变量AA。
  setenv("AA","aaaa",0);

  // 显示环境变量AA的值。
  cout << "AA=" << getenv("AA") << endl;

  return 0;
}

/*  
编译运行：
➜  2-5 Parameters of the main function git:(main) ✗ ./demo03                         
一共有1个参数。
第0个参数：./demo03
vscode_base_dir=/home/gtc/.trae-server
SHELL=/usr/bin/zsh
PLATFORM=linux
SERVER_APP_VERSION=
LC_ADDRESS=zh_CN.UTF-8
LC_NAME=zh_CN.UTF-8
OS_RELEASE_ID=ubuntu
SERVER_TOKENFILE=/home/gtc/.trae-server/.stable-5c60eab728f4cce183f319de2d3ee32fc9040268.token
TRAE_RESOLVE_TYPE=ssh
DISTRO_QUALITY=stable
SERVER_INITIAL_EXTENSIONS=
LC_MONETARY=zh_CN.UTF-8
SERVER_SCRIPT=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/index_trae.js
DISTRO_VSCODIUM_RELEASE=
PWD=/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-5 Parameters of the main function
LOGNAME=gtc
XDG_SESSION_TYPE=tty
MOTD_SHOWN=pam
HOME=/home/gtc
LANG=en_US.UTF-8
LC_PAPER=zh_CN.UTF-8
SERVER_LOGS_DIR=/home/gtc/.trae-server/logs
DISTRO_COMMIT=5c60eab728f4cce183f319de2d3ee32fc9040268
SCRIPT_ID=e18681075b48e767927a2578
SERVER_ARCH=x64
TMP_DIR=/run/user/1000
SERVER_HOST=127.0.0.1
SSH_CONNECTION=127.0.0.1 39318 127.0.0.1 22
SERVER_APP_NAME=Trae
XDG_SESSION_CLASS=user
LC_IDENTIFICATION=zh_CN.UTF-8
DOWNLOAD_RETRY_COUNT=0
SERVER_SCRIPT_PRODUCT=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/product.json
DISTRO_VERSION=1.98.2
USER=gtc
SERVER_PIDFILE=/home/gtc/.trae-server/.stable-5c60eab728f4cce183f319de2d3ee32fc9040268.pid
EXTRACT_RETRY_COUNT=0
SERVER_DIR=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268
SERVER_PACKAGE_NAME=Trae-linux-x64-875187723010_2.tar.gz
ARCH=x86_64
SHLVL=2
SERVER_APP_QUALITY=dev
LC_TELEPHONE=zh_CN.UTF-8
LC_MEASUREMENT=zh_CN.UTF-8
SERVER_LISTEN_FLAG=--port=0
XDG_SESSION_ID=6
PAPERSIZE=a4
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=127.0.0.1 39318 22
LC_TIME=zh_CN.UTF-8
MANAGER_LOGS_DIR=/home/gtc/.trae-server/manager-logs/1746879826866_979440
TRAE_DETECT_REGION=CN
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share:/usr/share:/var/lib/snapd/desktop
PATH=/home/gtc/Qt/6.9.0/gcc_64/bin:/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/bin/remote-cli:/home/gtc/Qt/6.9.0/gcc_64/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
SERVER_EXTENSIONS_DIR=/home/gtc/.trae-server/extensions
SERVER_DATA_DIR=/home/gtc/.trae-server
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
SERVER_LOGFILE=/home/gtc/.trae-server/.stable-5c60eab728f4cce183f319de2d3ee32fc9040268.log
SERVER_DOWNLOAD_PREFIX=https://lf-cdn.trae.com.cn/obj/trae-com-cn/pkg/server/releases/stable/5c60eab728f4cce183f319de2d3ee32fc9040268/linux/
LC_NUMERIC=zh_CN.UTF-8
OLDPWD=/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne
_=/home/gtc/GitHub/DataOpenPlatform/02 LinuxBasicsOne/2-5 Parameters of the main function/./demo03
ZSH=/home/gtc/.oh-my-zsh
PAGER=less
LESS=-R
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
QT_ROOT=/home/gtc/Qt/6.9.0/gcc_64
LD_LIBRARY_PATH=/home/gtc/Qt/6.9.0/gcc_64/lib:/home/gtc/Qt/6.9.0/gcc_64/lib:
QT_PLUGIN_PATH=/home/gtc/Qt/6.9.0/gcc_64/plugins
QML2_IMPORT_PATH=/home/gtc/Qt/6.9.0/gcc_64/qml
BROWSER=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/bin/helpers/browser.sh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.98.2
COLORTERM=truecolor
GIT_ASKPASS=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/node
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/home/gtc/.trae-server/bin/stable-5c60eab728f4cce183f319de2d3ee32fc9040268/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-054f264857.sock
VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-7bd68885-3115-470d-828a-9497170a8bc5.sock
VSCODE_INJECTION=1
ZDOTDIR=/home/gtc
USER_ZDOTDIR=/home/gtc
TERM=xterm-256color
AA=aaaa
*/