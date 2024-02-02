#include "threads.h"
#include <pthread.h>
#include "../serial/serial.h"


void Threads::T_serial(){
    while (1) {
        Serial.port_init(ss);
        printf("初始化串口------\n");
        tcflush(ss,TCIFLUSH);
        printf("清空串口的输入缓冲区------\n");
        waitKey(1);
        cout<<"";
        printf("程序暂停1毫秒。确保串口处于稳定状态, 清空之前的数据------\n");
        printf("正在启动串口------\n");
        Serial.port_RECV(ss);                              //串口接收
        printf("打印一条启动串口的消息，使用 Serial.port_RECV(ss) 函数来接收串口数据。用来从串口读取数据的------\n");
        while (serial_flag) {
            printf("serial_flag 为真\n");
        }

        cout<<"serial send  debug informations____________"<<endl;
        cout<<"send_pitch  "<<serial_pitch<<endl;
        cout<<"send_yaw  "<<serial_yaw<<endl;
        Serial.port_SEND(ss,serial_pitch,serial_yaw,fire_mode);

        double t=((double)getTickCount()-t__) / getTickFrequency();           //时间
        t__ =static_cast<double>(getTickCount());
        double FPS=1.0/t;
        cout<<" - - - - - - - - - - - - FPS_serial : "<<FPS<<endl;

    }

}
