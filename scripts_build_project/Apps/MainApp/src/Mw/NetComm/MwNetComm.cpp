
#include "sysApi.h"
#include "MwNetComm.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SPORT 58888
#define CPORT 10010 
#define SIZE  1024
#define LISTENNUM 10

#define UDP_PORT 60000
#define SERVER_IP "192.168.0.244"

MwNetComm_c *MwNetComm_c::m_pThis = NULL;

void MwNetComm_c::Init(void)
{

}

void MwNetComm_c::Run(void)
{
  sta_tsk(m_recvTskId);
  sta_tsk(m_UdpRecvTskId);
}

void MwNetComm_c::Link(MwCV_c *pArgMwCV)
{
  m_pMwCV = pArgMwCV;
}

MwNetComm_c::MwNetComm_c()
{
  m_pThis = this;
  //创建待运行的task
  m_recvTskId = acre_tsk(recvTask);
  m_UdpRecvTskId = acre_tsk(UdpRecverTask);
  printf("recvTaskId = %d \n",m_recvTskId);
  printf("m_UdpRecvTskId = %d \n",m_UdpRecvTskId);
}

void MwNetComm_c::recvTask(void)
{
        INT32 socketID = 0;
        INT32 ret=0;
        INT32 connectedSocket = 0;
        socklen_t addrLength = 0;
        INT8 buf[SIZE] = {0};
        struct sockaddr_in addr;
	ID buff_id = m_pThis->m_pMwCV->getBuffId();

        //打开socket -- 协议tcp
        socketID = socket (PF_INET, SOCK_STREAM, 0);
        if ( socketID < 0 )
        {
                perror("socket error");
                //return 0;
        }
        printf("socket ok\r\n");

        //设置socket地址可以复用
        INT32 on = 1;
        setsockopt( socketID, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        //绑定自己的ip和port
        addrLength = sizeof(addr);
        memset( &addr, 0, addrLength );
        addr.sin_family = PF_INET;
        addr.sin_port = htons(SPORT);
        addr.sin_addr.s_addr = INADDR_ANY;
        //绑定的作用是让socketID找到对应的ip+port实现通信
        if ( 0 > bind( socketID, (struct sockaddr *)&addr, addrLength ) )
        {
                perror("bind error");
                close(socketID);
                //return;
        }
        printf("bind ok\r\n");

        //建立监听 
        //作用：建立一个监听队列，把三次握手未完成的客户端放在队列中。当三次握手全部完成的时候，>就从队列移除。目的：更方便更及时服务每一个客户端
        listen ( socketID, LISTENNUM );

        printf("listen ok\r\n");
        while(1)
        {
                //接受连接 
                //作用：建立连接，返回已连接的socket，并且让socketID又可以接受其它客户端的连接
                connectedSocket = accept( socketID, (struct sockaddr *)&addr, &addrLength);
                if ( connectedSocket < 0 )
                {
                        perror("accept error");
                        close(socketID);
                        //return -1;
                }
                printf( "accept ok, connectedSocket=%d\r\n", connectedSocket );

                while(1)
                {
                        memset(buf,'\0',SIZE);
                        ret=recv(connectedSocket,buf,SIZE-1,0);
                        //接受完毕
                        if(ret>0)
                        {
                                printf("recv msg: %s, lens = %d \n",buf,ret);
				tsnd_mbf(buff_id, buf, ret,0);
                                break;
                        }
                }
                //关闭socket
                close( connectedSocket );
        }
        close( socketID );
        //return 0;
}

void MwNetComm_c::UdpRecverTask(void)
{
  INT32 socketID = 0;
  INT8 buffer[1024];
  struct sockaddr_in clientaddr;
  socklen_t len = sizeof(clientaddr);
  memset(buffer, 0, sizeof(buffer));

  socketID = socket (PF_INET, SOCK_DGRAM, 0);
  if ( socketID < 0 )
  {
    perror("UDP socket error");
  }
  printf("UDP socket ok \n");
  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET; //IPv4
  serveraddr.sin_port = htons(UDP_PORT);//port
  serveraddr.sin_addr.s_addr = INADDR_ANY;//ip
  if (bind(socketID, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
  {
	perror("bind error");
	//exit(1);
	return;
  }
  while(1){
  if (recvfrom(socketID, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &len) < 0){perror("recvfrom error");}
  else
   {
    printf("client send into: %s \n", buffer);
    if(0 == strcmp(buffer,"SEARCH"))
    {
      INT8 *ptr = "192.168.0.244 58888";
      UINT32 size = strlen(ptr) * sizeof(INT8);
      if (sendto(socketID, ptr, size, 0, (struct sockaddr*)&clientaddr, len) < 0){perror("sendto error");}
    }
   }
  }

}
