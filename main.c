#include<stdio.h>
#include"uart_init.h"
#define DEV_NAME "/dev/ttyUSB0"
int main()
{
	//�򿪴����豸
	int fd = 0;
	fd= uart_open(&fd, DEV_NAME);
	if(fd < 0)
	{
		perror("open");
	}
	//��ʼ�������豸
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