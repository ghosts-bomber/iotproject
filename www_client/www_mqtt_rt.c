#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "sqlite3.h"
#include "analy_data.h"

char ip[16] = "127.0.0.1";
char port[8] = "8000";
char send_title[32] = "CMD";
char recv_title[32] = "DATA";

void *start_sub(void *arg)
{
    if (execlp("mosquitto_sub", "mosquitto_sub", "-h", ip, "-p", port,
               "-v", "-t", recv_title, NULL) < 0)
    {
        exit(0);
    }
}
int main()
{
    //初始化数据库
    db_init();
    // 创建两个子进程
    pid_t pid;
    int i = 0;
    for (i = 0; i < 2; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            break;
        }
    }

    //进程1  mqtt发
    if (i == 0)
    {
        while (1)
        {
            //从队列中读取控制指令
            char buf[64] = "get_data";
            sleep(10);
            /*----------------------------------*/

            //mqtt发送 控制指令
            unsigned char cmd[128] = "";
            sprintf(cmd, "mosquitto_pub -h %s -p %s -t %s -m \"%s\"", ip, port, send_title, buf);
            //printf("%s\n",cmd);
            system(cmd);
        }
    }

    //进程2 mqtt收
    else if (i == 1)
    {
        //无名管道
        int fd[2];
        int ret = pipe(fd);
        if (ret == -1)
        {
            perror("pipe");
            exit(0);
        }

        //启动mqtt订阅功能
        pid_t pid_son;

        int j = 0;
        for (j = 0; j < 2; j++)
        {
            pid_son = fork();
            if (pid_son == -1)
            {
                perror("fork");
                exit(1);
            }
            else if (pid_son == 0)
            {
                break;
            }
        }
        if (j == 0) //子进程
        {
            close(1);
            dup(fd[1]);
            //启动mqtt订阅
            if (execlp("mosquitto_sub", "mosquitto_sub", "-h", ip, "-p", port,
                       "-v", "-t", recv_title, NULL) < 0)
            {
                exit(0);
            }
        }
        else if (j == 1)
        {
            while (1)
            {
                char buf[128] = "";
                read(fd[0], buf, sizeof(buf));
                //处理接收到的数据
                /*----------------------------------*/
                int ret = 0;
                while (!(buf[ret++] == ' '))
                {
                }
               
                analy_data(buf + ret, strlen(buf)-ret);
            }
        }
        else if (j == 2)
        {
            while (1)
            {
                pid_son = waitpid(-1, NULL, WNOHANG);
                if (pid_son == -1)
                {
                    printf("process all exit\n");
                    break;
                }
            }
        }
        close(fd[0]);
        close(fd[1]);
    }
    //主进程 回收子进程
    else if (i == 2)
    {
        while (1)
        {
            pid = waitpid(-1, NULL, WNOHANG);
            if (pid == -1)
            {
                printf("process all exit\n");
                break;
            }
        }
    }
    return 0;
}
