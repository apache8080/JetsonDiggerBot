#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

int uart_status = 0;

int main(int argc,char **argv)
{
	unsigned char tx_buffer[20];
	
	if(argc<2)
	{
		printf("Not enough Arguments. Enter uart on/off/status\n");
		return -1;
	}
	
	if(strcmp(argv[1],"send") == 0)
	{
                strcpy(tx_buffer, argv[2]);
		/*if(strcmp(argv[2],"on") == 0)
		{
			strcpy(tx_buffer,"on");
		}
		else if(strcmp(argv[2],"off") == 0)
		{
			strcpy(tx_buffer,"off");
		}
		else
		{
			printf("Invalid Data to send\n");
			return -1;
		}*/
	}
	else if(strcmp(argv[1],"off") == 0)
	{
		uart_status = 0;
		return 0;
	}
	else if(strcmp(argv[1],"status") == 0)
	{
		if(uart_status == 1)
			printf("Status of UART is: ON \n");
		else
			printf("Status of UART is: OFF \n");
			
		return 0;
	}
	else
	{
		printf("Invalid option \n");
		return -1;
	}
	int fd = -1;

	fd = open("/dev/ttyUSB0",O_RDWR |O_NOCTTY | O_NDELAY);

	if(fd == -1)
	{
		printf("Error opening UART \n");
		return fd;
	} 

	struct termios options;

	tcgetattr(fd, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(fd,TCIFLUSH);
	tcsetattr(fd,TCSANOW,&options);

//	unsigned char *p_tx_buffer;


	int count = write(fd,&tx_buffer,15);
         write(fd,"\r",3);

	if(count < 0)
	{
		printf("UART TX Error \n");
	}

	//Reading
	/*
	char buf[256];
	int n = read(fd, (void*)buf,255);
	if(n <0)
	{
		perror("Read failed - ");
		return -1;
	}
	else if(n == 0)
	{
		printf("No Data on port \n");
	}
	else
	{
		buf[n] = '\0';
		printf("%i bytes read: %s", n, buf);
	}
	*/
	close(fd);

	return 0;

}
