#include <pthread.h>

#include "sysApi.h"
#include "common.h"


#define MBF_MAX_OBJ 32

typedef struct{
  ID id;
  UINT32 sz;
  UINT8 *buff;
 
  pthread_cond_t snd_cond;
  pthread_cond_t rcv_cond;

  pthread_mutex_t mutex;

}mbf_info_t;

static mbf_info_t mbf_info[MBF_MAX_OBJ];

//->内部使用函数声明
static UINT32 find_empty_mbf_index(void);


//创建邮箱
ER acre_mbf(UINT32 sz)
{
  UINT32 index = -1;
  UINT32 ret = -1;
  mbf_info_t *info = NULL;
  
  index = find_empty_mbf_index();
  if(index < MBF_MAX_OBJ)
  {
    info = &mbf_info[index];
    info->id = index+1;
    info->buff = malloc(sz);
    info->sz = sz;
    ret = index+1;

    pthread_cond_init(&info->snd_cond, NULL);
    pthread_cond_init(&info->rcv_cond, NULL);

    pthread_mutex_init(&info->mutex, NULL);
  }
  else
  {
    ret = -1;
  }
  return ret;
}

//删除邮箱
ER del_mbf(ID mbfid)
{
  UINT32 ret = -1;
  mbf_info_t *info = NULL;

  info = &mbf_info[mbfid-1];
  if(info->id)
  {
    free(info->buff);
    info->id = 0;
    info->sz = 0;

    pthread_cond_destroy(&info->snd_cond);
    pthread_cond_destroy(&info->rcv_cond);
    pthread_mutex_destroy(&info->mutex);
    ret = 0;
  }

  return ret;
}

//邮箱-发送消息
ER tsnd_mbf(ID mbfid, VP msg, UINT32 msgsz, TMO tmout)
{
  mbf_info_t *info = NULL;

  info = &mbf_info[mbfid-1];
 
  pthread_mutex_lock(&info->mutex);

  memcpy(info->buff,msg,msgsz);

  info->sz = msgsz;

  pthread_cond_broadcast(&info->rcv_cond);

  pthread_mutex_unlock(&info->mutex);

  return 0;
}

//邮箱-接受消息
ER trcv_mbf(ID mbfid, VP msg, UINT32 msgsz, TMO tmout)
{
  mbf_info_t *info = NULL;

  info = &mbf_info[mbfid-1];
 
  pthread_mutex_lock(&info->mutex);

  pthread_cond_wait(&info->rcv_cond, &info->mutex);

  memcpy(msg,info->buff,info->sz);

  pthread_mutex_unlock(&info->mutex);

  return info->sz;
}

//内部使用
static UINT32 find_empty_mbf_index(void)
{
  UINT32 i;
  for(i=0; i<MBF_MAX_OBJ; i++)
  {
    if(0 == mbf_info[i].id)break;
  }
  return i;
}

