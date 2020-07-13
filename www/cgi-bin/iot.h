#ifndef _IOT_H
#define _IOT_H
typedef struct
{
    long mtype;
    int temp;
    int humi;
    char curr_t[12];
    char curr_h[12];
    char id[12];
    char head[18];
}MSG;
typedef struct
{
    long mtype;
    char cmd[64];
}GETCMD;


extern void ipc_init();


#endif