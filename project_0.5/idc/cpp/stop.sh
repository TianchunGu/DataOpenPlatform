# 此脚本用于停止数据共享平台全部的服务程序

# 停止调度程序
killall -9 procctl

#停止其他的服务程序
#尝试让其他服务程序正常终止
killall crtsurfdata deletefile

#让其他服务程序有足够的时间退出
sleep 5

#不管服务程序有没有限制，都强制杀死
killall -9 crtsurfdata deletefile
