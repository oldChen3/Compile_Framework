#include <string.h>
#include <pthread.h>

#include "sysApi.h"

#define	TASK_MAX_OBJ	12

typedef struct
{
  ID id;
  ID thread_id;
  FP func;
  INT8 sta; //-1:empty, 0:stop, 1:wait, 2:running
}thread_info_t;

static thread_info_t thread_info[TASK_MAX_OBJ];


//->inside functions declare
static UINT32 find_empty_task_obj(void);
//<-

//->outside call
//创建task
ER acre_tsk(FP f)
{
  UINT32 index = -1;
  ER ret = -1;
  thread_info_t *info;

  index = find_empty_task_obj();
  if(index < TASK_MAX_OBJ)
  {
    info = &thread_info[index];
    info->id = index+1;
    info->func = f;
    info->sta = 1; //waiting
    ret = index+1;
  }
  else
  {ret = -1;}

  return ret;
}

//运行task
ER sta_tsk(ID tskid)
{
  thread_info_t *info;
  pthread_t id;
  ER ret = -1;

  info = &thread_info[tskid-1];
  if(info->sta == 1) //waiting to running
  {
    if(0 == pthread_create(&id, NULL, info->func, NULL))
    {
      info->thread_id = id;
      pthread_detach(id);
      ret = 0;
    }
  }
  else{ret = -1;}

  return ret;
}

//停止task
ER stp_tsk(ID tskid)
{
  return 0;
}

//删除task
ER del_tsk(ID tskid)
{
  return 0;
}

//退出task
ER ext_tsk(ID tskid)
{
  return 0;
}
//<-

//-> internel use functions
static UINT32 find_empty_task_obj(void)
{
  UINT32 i;
  for(i=0; i<TASK_MAX_OBJ; i++)
  {
    if(thread_info[i].id == 0)break;
  }
  return i;
}
//<-
