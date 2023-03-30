#ifndef _SYSAPI_H_
#define _SYSAPI_H_

#if defined(__cplusplus)
extern "C"{
#endif

#include <common.h>


//创建task
ER acre_tsk(FP func);

//运行task
ER sta_tsk(ID tskid);

//停止task
ER stp_tsk(ID tskid);

//删除task
ER del_tsk(ID tskid);

//退出task
ER ext_tsk(ID tskid);

//创建邮箱
ER acre_mbf(UINT32 sz);

//邮箱-发送消息
ER tsnd_mbf(ID mbfid, VP msg, UINT32 msgsz, TMO tmout);

//邮箱-接受消息
ER trcv_mbf(ID mbfid, VP msg, UINT32 msgsz, TMO tmout);

#if defined(__cplusplus)
}
#endif

#endif

