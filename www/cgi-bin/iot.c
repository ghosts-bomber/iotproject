#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "iot.h"
int msg_id;
int main()
{
    //传输HTML 文本第一行输出的内容必须是"content-type:text/html\n\n"
    printf("content-type:text/html\n\n");
    //1、首先的到数据的长度
    char *len = getenv("CONTENT_LENGTH");

    //2、根据长度 从标准输入设备 获取内容
    char data[128] = "";
    fgets(data, atoi(len) + 1, stdin);
    //printf("%s\n",data);

    //初始化消息队列
    ipc_init();
     if(strncmp(data,"get_da",5)==0)
     {
    MSG msg;
    memset(&msg, 0, sizeof(MSG));

    if ((msgrcv(msg_id, &msg, sizeof(MSG) - sizeof(long), 10, IPC_NOWAIT)) < 0)
    {
        printf("NULL\n");
        return -1;
    }
   
    printf("%d,%d\n",msg.temp,msg.humi);

     }
    return 0;
}

void ipc_init()
{
    key_t key = ftok("/", 2020);
    msg_id = msgget(key, IPC_CREAT | 0666);
    if (msg_id == -1)
    {
        printf("create msg error \n");
        return;
    }
}
void cgi_get_data(MSG *msg)
{
}
