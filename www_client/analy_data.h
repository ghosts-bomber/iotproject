#ifndef _ANALY_DATA_H
#define _ANALY_DATA_H

typedef struct
{
    int temp;
    int humi;
    char curr_t[12];
    char curr_h[12];
    char id[12];
    char head[18];
} Get_Data;

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

extern void analy_data(char *buf, int len);
extern int get_db_data(void *para, int n_column, char **column_value, char **column_name);
extern void db_init();
extern void db_open();
extern void *db_write(void *arg);
extern void db_close();
extern void ipc_init();
extern void read_ipc(char *buf);

#endif