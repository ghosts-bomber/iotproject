#include<stdio.h>
#include"uart_init.h"
#define DEV_NAME "/dev/ttyUSB0"
int main()
{
	//打开串口设备
	int fd = 0;
	fd= uart_open(&fd, DEV_NAME);
	if(fd < 0)
	{
		perror("open");
	}
	//初始化串口设备
	uart_init(fd);

	while(1)
		{
		char buf[128]="";
		read(fd,buf,sizeof(fd));
		printf("%s",buf);
	}
	
	uart_close(fd);
	return 0;
}