#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "sqlite3.h"
#include "analy_data.h"

sqlite3 *db = NULL;


void analy_data(char *buf, int len)
{
    
    Get_Data data;
    char discard[20]="";
    //解析数据
    if (len > 6 && strncmp((buf + 6), "recv", 4) == 0)
    {  
        sscanf(buf, "%[^:]:%[^:]:%[^,],%d,%d,%[^,],%s", data.id, data.head,discard, &data.temp, &data.humi, data.curr_t, data.curr_h);
        printf("jieguo:%s--%s--%d--%d--%s--%s\n", data.id, data.head, data.temp, data.humi, data.curr_t, data.curr_h);
    }
    //存入管道

    //线程存入数据库
    pthread_t tid;
    pthread_create(&tid,NULL,db_write,(void*)&data);
    pthread_detach(tid);
   
}

int get_db_data(void *para, int n_column, char **column_value, char **column_name)
{
    int i = 0;
    for (i = 0; i < n_column; i++)
    {
        printf("%s ", column_name[i]);
    }
    printf("\n");
    for (i = 0; i < n_column; i++)
    {
        printf("%s ", column_value[i]);
    }
    printf("\n");
    return 0;
}
void db_init()
{
    db_open();
    //组sql操作语句，创建一个表
    char cmd[128] = "create table iot(id text,head text,temp int,humi int,curr_t text,curr_h text);";
    char *err_msg = NULL;
    sqlite3_exec(db, cmd, NULL, NULL, &err_msg);
    if (err_msg)
    {
        printf("%s\n", err_msg);
    }
}
void db_open()
{

    int ret = sqlite3_open("data.db", &db);

    if (ret != SQLITE_OK)
    {
        perror("sqlite3_open");
        return 0;
    }
}
void *db_write(void *arg)
{
    Get_Data *data = (Get_Data*)arg;
    db_open();
    char *err_msg = NULL;
    char cmd[128] = "";
    sprintf(cmd, "insert into iot values(\'%s\',\'%s\',%d,%d,\'%s\',\'%s\');",
            data->id, data->head, data->temp, data->humi, data->curr_t, data->curr_h);
    sqlite3_exec(db, cmd, NULL, NULL, &err_msg);
    if (err_msg)
    {
        printf("%s\n", err_msg);
    }
    db_close();
}

#if 0
    memset(cmd, 0, sizeof(cmd));
    sprintf(cmd, "select * from stu;");
    char **resultp = NULL;
    int row = 0, col = 0;
    sqlite3_get_table(db, cmd, &resultp, &row, &col, &err_msg);
    printf("row=%d,col=%d\n", row, col);
    if (row > 0)
    {
        int i = 0, j = 0;
        for (i = 0; i < row + 1; i++)
        {
            for (j = 0; j < col; j++)
                printf("%s ",resultp[i*col+j]);
            printf("\n");
        }
    }
    if (resultp != NULL)
    {
        sqlite3_free_table(resultp);
        resultp = NULL;
    }
#endif
void db_close()
{
    sqlite3_close(db);
}