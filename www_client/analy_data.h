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


extern void analy_data(char *buf, int len);
int get_db_data(void *para, int n_column, char **column_value, char **column_name);
void db_init();
void db_open();
void *db_write(void *arg);
void db_close();

#endif