# HHXY-LBT
RoboMaster  LBT战队视觉

### 环境
  ubuntu18/20  最好为18版本 20版本相机驱动会出现问题   快速打开终端快捷键 ctrl + alt + T
  
  矩阵库（eigen3） 
# 安装矩阵库

    sudo apt-get install libeigen3-dev
    sudo cp -r /usr/include/eigen3/Eigen /usr/local/include/
    sudo cp -r /usr/include/eigen3 /usr/local/include/
  
  opencv4.5 ：
# 第一步 搭建环境（一个个命令粘贴复制）  安装g++, cmake, make, wget, unzip
    sudo apt update
    sudo apt install -y g++
    sudo apt install -y cmake
    sudo apt install -y make
    sudo apt install -y wget unzip
# 安装opencv依赖的库
    sudo apt-get install build-essential libgtk2.0-dev libgtk-3-dev libavcodec-dev libavformat-dev libjpeg-dev libswscale-dev libtiff5-dev
# 安装一些可选的库
# python3支持（首次安装了python的库，但make报错了，之后删了这两个库，若不使用python，建议不安装）
    sudo apt install python3-dev python3-numpy
# streamer支持
    sudo apt install libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
# 可选的依赖
    sudo apt install libpng-dev libopenexr-dev libtiff-dev libwebp-dev
# 下载opencv 4.5.0 （github上有代码程序 可以直接一同克隆下来） 选择一个克隆下来
# 安装4.5.0版本 如果github上没有就执行这个命令
    wget -O opencv.zip https://github.com/opencv/opencv/archive/4.5.0.zip
# 安装最新版本
    wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip   # 非必要不使用！！！！！！！
# 下载完成后，解压到主目录下，将解压后的文件重命名为opencv  在主目录下打开终端
    cd opencv
    mkdir build
    cd build
# 使用cmake配置opencv
    cmake -D CMAKE_BUILD_TYPE=Release -D OPENCV_GENERATE_PKGCONFIG=YES ..
# 用make进行编译（大约需要35分钟）
    make -j4 # j4是代表当前咱们的nuc有4个线程，如果你的电脑很强大，有32线程的话可以用 make -j32
# 用make进行安装
    sudo make install
# 默认安装路径为：
# /usr/local/bin - executable files
# /usr/local/lib - libraries (.so)
# /usr/local/cmake/opencv4 - cmake package
# /usr/local/include/opencv4 - headers
# /usr/local/share/opencv4 - other files (e.g. trained cascades in XML format)


#  配置pkg-config环境
    sudo find / -iname opencv4.pc
# 将路径加入到PKG_CONFIG_PATH（用vim打开）： 如果报错可以用下载vim 命令： sudo apt-get install vim
    sudo vim /etc/profile.d/pkgconfig.sh
# 在文件后面加入下面一行：
    export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
# vim保存退出的方式->输入:wq 然后回车
# 激活
    source /etc/profile
# 配置动态库
    sudo vim /etc/ld.so.conf.d/opencv4.conf
    /usr/local/lib # 用ctrl 加 v粘贴进去 再:wq 推出保存
    sudo ldconfig


  大华相机驱动
 
### 准备

    
安装相机驱动 
名字为MVviewer_Ver2.2.5_Linux_x86_Build20200910.run
解压后执行命令安装
    
    sudo chmod +x MVviewer_Ver2.2.5_Linux_x86_Build20200910.run
    sudo ./MVviewer_Ver2.2.5_Linux_x86_Build20200910.run

### 构建运行
接入相机后运行

    mkdir build
    cd build
    cmake ..
    make -j8
    ./HHXY_LBT2023
    
    #附加权限
    ./BamThriving-VISION
    
    sudo ./BamThriving-VISION 777 /dev/video2
    
    sudo ./HHXY_LBT2023 777 /dev/video1
    
    v4l2-ctl --list-devices//检测相机
    
### 一些说明
该项目为哨兵上场版本，其余版本其本框架一致，小部分有差异。
次项目算法实现比较简单，全为传统视觉实现，体量较小，能够实现数图案分类和卡尔曼运动预测，能够对目标保持固定帧跟踪（防止装甲板闪烁或丢失目标）。项目一边迭代一边测试，很多代码没有仔细斟酌。实际效果可查看上面提到的网盘或查阅比赛视频。
在此特别感谢战队所有视觉组成员！！

##### 欢迎交流
WX：xiaorui13039811650
