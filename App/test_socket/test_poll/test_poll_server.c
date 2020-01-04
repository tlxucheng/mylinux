#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

/* int poll(struct pollfd fd[], nfds_t nfds, int timeout);
 * 作用：poll的作用是把当前的文件指针挂到等待队列。
 * 参数说明：
 *  (1) 
    struct pollfd{
　　int fd;          //文件描述符
　　short events;    //请求的事件
　　short revents;   //返回的事件
　　};
 * (2)
 * POLLIN       普通或优先级带数据可读
 * POLLRDNORM	普通数据可读
 * POLLRDBAND	优先级带数据可读
 * POLLPRI	    高优先级数据可读
 * POLLOUT	    普通数据可写
 * POLLWRNORM	普通数据可写
 * POLLWRBAND	优先级带数据可写
 * POLLERR	    发生错误
 * POLLHUP	    发生挂起POLLNVAL	描述字不是一个打开的文件
 *(3)
 * timeout值	说明
 * INFTIM	    永远等待
 *  0	        立即返回，不阻塞进程
 * ＞0	        等待指定数目的毫秒数
 */

/*****************Server****************/ 
 
#define MAX_BUFFER_SIZE 1024
#define IN_FILES 2
 
int main(int argc ,char **argv)
{
	struct pollfd fds[IN_FILES];
	char buf[MAX_BUFFER_SIZE] = "", domain[32] = "";
	int i;
	int ret;
	int server_sockfd[IN_FILES];
	int server_len[IN_FILES];
	struct sockaddr_un server_address[IN_FILES];
	
	for(i=0; i<IN_FILES; i++)
	{
		//create server socket
		sprintf(domain, "udp_tmp%d", i);
		unlink(domain);
		server_sockfd[i] = socket(AF_UNIX, SOCK_DGRAM, 0);
		if(server_sockfd[i]<0)
		{
			printf("socket error\n");
			return -1;
		}
		//name the socket
		server_address[i].sun_family = AF_UNIX;
		strcpy(server_address[i].sun_path, domain);
		server_len[i] = sizeof(server_address[i]);
		bind(server_sockfd[i], (struct sockaddr *)&server_address[i], server_len[i]);
	}
	//set the fd and events in poll listen pool
	for (i = 0; i < IN_FILES; i++)
        {
		fds[i].fd = server_sockfd[i];
		fds[i].events = POLLIN;
        }
	while(1)
        {
		if (poll(fds, IN_FILES, -1) <= 0)
		{
			printf("Poll error\n");
			return 1;
		}
		printf("********************\n");
		for (i = 0; i< IN_FILES; i++)
		{
			printf("%d.revents = %d\n", i+1, fds[i].revents);
			if ((fds[i].revents & POLLIN) != 0)
			{
				//accept a connection
				ret = recvfrom(server_sockfd[i], buf, 1024, 0, (struct sockaddr *)&server_address[i], (socklen_t *)&server_len[i]);
				//write and read by socket fd
				buf[ret]= '\0';
				printf("char from client is %s\n", buf);
			}
		}
	}
	//close
	for (i = 0; i < IN_FILES; i++)
	{
		close(server_sockfd[i]);
		sprintf(domain, "udp_tmp%d", i);
		unlink(domain);
	}
	return 0;
}
  