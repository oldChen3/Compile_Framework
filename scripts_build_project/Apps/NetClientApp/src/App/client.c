#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

#define SERVPORT 58888
#define SERVER_ADDR "192.168.0.244"
#define SERVER_BOARDCAST_ADDR "192.168.0.1"
#define UDO_PORT 60000

typedef struct{
  char ip[32];
  int port;
}Server_Info_t;

int split(char *src_s, char split_c, char *d_s_0, char *d_s_1)
{
  int ret = -1;
  int len = strlen(src_s);
  char *p = d_s_0;
  int index = 0;
  for(int i=0; i<len; i++)
  {
    if(src_s[i] == split_c)
    {
	p = d_s_1;
	index = 0;
	continue;
    }
    p[index] = src_s[i];
    index++;
  }
  return 0;
}

int searchServer(Server_Info_t *t)
{
  const int opt = 1;
  char ip_str[64];
  char port_str[64];
  int port = -1;
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0){
    perror("socket error");
    exit(1);}
 
  /*2.调用recvfrom 、sendto等函数和服务器双向通信*/
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(UDO_PORT);
  serveraddr.sin_addr.s_addr = INADDR_BROADCAST;
#if 0 
  if (connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
  {
	perror("sendto error");;
	exit(1);
  }
#endif
  setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
 
  char buffer[32] = "SEARCH";
  //向服务器发送数据报文
  while(1){
  if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
  {
	perror("sendto error");
	exit(1);
  }
  else
  {
	//接收服务器端发送的数据报文
	memset(buffer, 0, sizeof(buffer));
	if (recv(sockfd, buffer, sizeof(buffer), 0) < 0)
	{
		perror("recv error");
		exit(0);
	}
	else
	{
		printf("%s \n", buffer);
		split(buffer, ' ', &(t->ip), port_str);
		t->port = atoi(port_str);
		break;
	}
  }
 }
 
	return 0; 
}


int main(int argc,char *argv[]) {
    int sockfd,sendbytes;
    static Server_Info_t server;
    struct sockaddr_in serv_addr;//需要连接的服务器地址信息
#if 0
    printf("test split \n");
    char ip[64];
    char port[64];
    split("192.168.0.244 56789",' ',ip,port);
    printf("ip=%s, port=%s \n",ip,port);
    printf("done \n");
#endif
    sleep(5);
    //udp broadcast to get server information
    searchServer(&server);
    printf("ip=%s, port=%d \n",server.ip,server.port);
    //1.创建socket
    //AF_INET 表示IPV4
    //SOCK_STREAM 表示TCP
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
    }

    //填充服务器地址信息
    serv_addr.sin_family 	= AF_INET; //网络层的IP协议: IPV4
    serv_addr.sin_port 		= htons(server.port); //传输层的端口号
    serv_addr.sin_addr.s_addr   = inet_addr(server.ip); //网络层的IP地址: 实际的服务器IP地址
    bzero(&(serv_addr.sin_zero),8); //保留的8字节置零

    //printf("Client is ready, and wait server \n");
    sleep(5);

    //2.发起对服务器的连接信息
    //三次握手,需要将sockaddr_in类型的数据结构强制转换为sockaddr
    if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))) < 0) {
        perror("connect failed!");
        exit(1);
    }

    //printf("connect successful! \n");

    //3.发送消息给服务器端
    if((sendbytes = send(sockfd,"hello",5,0)) < 0) {
        perror("send");
        exit(1);
    }

    //printf("send successful! %d \n",sendbytes);

    //4.关闭
    close(sockfd);

}

