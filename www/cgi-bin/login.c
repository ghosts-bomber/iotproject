#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"sqlite3.h"

sqlite3 *db = NULL;
void db_init()
{
    int result;
	
	result = sqlite3_open("user.db",&db);
    if(result != SQLITE_OK){
		printf("open error\n");
		exit(-1);
	}
    char cmd[128] = "create table user(user text,passwd text);";
    char *err_msg = NULL;
    sqlite3_exec(db, cmd, NULL, NULL, &err_msg);
}

int check_user_passwd(char* user,char* passwd)
{
    int result, nRow, nColumn;
	char * errmsg = NULL;
	char sql[128] = "";
	char **dbResult;
    sprintf(sql,"select * from user "\
			"where \'%s\';",user);
	result = sqlite3_get_table(db, sql,
			&dbResult, &nRow, &nColumn, &errmsg);
    if(nRow==0)
    {
        printf("没有该用户\n");
        sqlite3_free_table(dbResult);
        return -1;
    }
    if(strcmp(dbResult[3],passwd)==0)
    {
        printf("successful\n");
    }
    else
    {
        printf("账号或密码错误\n");
    }
    
    sqlite3_free_table(dbResult);
    return 0;
}

int main()
{
    //传输HTML 文本第一行输出的内容必须是"content-type:text/html\n\n"
    printf("content-type:text/html\n\n");
    //1、首先的到数据的长度
    char *len = getenv("CONTENT_LENGTH");

    //2、根据长度 从标准输入设备 获取内容
    char data[128] = "";
    fgets(data, atoi(len) + 1, stdin);
    db_init();
    char select[12]="";
    char user[16]="";
    char passwd[16]="";
    sscanf(data,"%s %s %s",select,user,passwd);
    if(strncmp(select,"login",strlen("login"))==0)
    {
        check_user_passwd(user,passwd);
    }
    else if(strncmp(select,"register",strlen("register"))==0)
    {

    }
    sqlite3_close(db);
    return 0;
}

