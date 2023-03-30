#include "sysApi.h"
#include "MwCv.h"

#define BUFFER_SIZE	128

MwCV_c *MwCV_c::m_pThis = NULL;

void MwCV_c::Init(void)
{

}

void MwCV_c::Run(void)
{
  sta_tsk(m_recvTskId);
}

MwCV_c::MwCV_c()
{
  ER mbf_id;
  m_pThis = this;
  //创建一个待运行的task
  m_recvTskId = acre_tsk(recvTask);
  printf("recvTaskId = %d \n",m_recvTskId);

  //创建一个通信用缓冲区
  mbf_id = acre_mbf(BUFFER_SIZE);
  m_buffId = mbf_id;
}

void MwCV_c::recvTask(void)
{
  printf("CV Manager runing recv msg \n");
  UINT8 msg[256];
  while(1)
  {
    trcv_mbf(m_pThis->m_buffId,msg, 0, 0);
    printf("CV recv message: %c \n",msg[0]);
  }
}

ID MwCV_c::getBuffId(void)
{
  return m_buffId;
}


