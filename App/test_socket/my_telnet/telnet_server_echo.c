#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#define BUFSIZE 1024

void error(char *msg){
	perror(msg);
	exit(1);
}

int g_num = 0;

static void *sum_func(void *para)
{
	while(1)
    {
	    g_num++;
		sleep(1);
	}

}

int save_fd;

int ioStdSet(int src_fd, int dest_fd, int *save_fd) 
{
    *save_fd = dup(dest_fd);
    dup2(src_fd, dest_fd);
    //close(src_fd);
    return *save_fd;
}

void recoverIoStdSet(int src_fd, int dest_fd) 
{
    dup2(src_fd, dest_fd);
    close(src_fd);
}

void show_estab(int connfd)
{
    ioStdSet(connfd, 1, &save_fd); 

	printf("127.0.0.1:10000> ");
    fflush(stdout);
	
	recoverIoStdSet(save_fd, 1);
}

void show_sum(int connfd)
{
	ioStdSet(connfd, 1, &save_fd); 

	printf("127.0.0.1:10000> g_num: %d\n", g_num);
    printf("127.0.0.1:10000> ");
    fflush(stdout);
    
	recoverIoStdSet(save_fd, 1);
}

void run_func(void(*func_name)(int), int para)
{
	func_name(para);
}

int main(int argc,char **argv){
	int listenfd;
	int connfd;
	int portno;
	int clientlen;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	struct hostent *hostp;
	char buf[BUFSIZE];
	char *hostaddrp;
	int optval;
	int n;
	
	pthread_t sum_thread;
	
	pthread_create(&sum_thread, NULL, &sum_func, NULL);
	
#if 0
	if(argc != 2){
		fprintf(stderr, "usage: %s <port>\n",argv[0]);
		exit(1);
	}
#endif
	
	//portno = atoi(argv[1]);
	portno = 10000;
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
		error("ERROR opening socket");

	optval = 1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval,sizeof(int));
	
	bzero((char *)&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)portno);
	//binding
	if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
		error("ERROR on binding");
	//listen
	if(listen(listenfd,5)<0)
		error("ERROR on listen");

	clientlen = sizeof(clientaddr);
	while(1){
	
		connfd = accept(listenfd,(struct sockaddr*)&clientaddr,&clientlen);
		if(connfd <0 )
			error("ERROR on accept");
		
		hostp = gethostbyaddr((const char*)&clientaddr.sin_addr.s_addr,sizeof(clientaddr.sin_addr.s_addr),AF_INET);
		if(hostp == NULL)
			error("ERROR on gethostbyaddr");
		
		hostaddrp = inet_ntoa(clientaddr.sin_addr);
		if(hostaddrp == NULL)
			error("ERROR on inet_ntoa");
		
		printf("server established connection with %s (%s)\n",hostp->h_name,hostaddrp);

        show_estab(connfd);
            
		while(1)
        {
			bzero(buf,BUFSIZE);
			n = read(connfd,buf,BUFSIZE);
			if(n<0)
				error("ERROR reading from socket");
			printf("server received %d bytes: %s",n,buf);
			
			char input_func_name[10] = {0};
			strncpy(input_func_name, buf, strlen(buf));
			input_func_name[strlen(input_func_name)] = '\0';
		    run_func(show_sum, connfd);
			
		    bzero(buf,BUFSIZE);
			
		    //n = write(connfd,buf,strlen(buf));
			//if(n<0)
			//	error("ERROR writing to socket");
        }
		//close(connfd);
	}
	
	close(connfd);
}
