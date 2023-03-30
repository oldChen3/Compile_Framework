#include <stdio.h>
#include <unistd.h>

#include "common.h"
//#include "MwCamera.h"
#include "sysApi.h"
#include "MwNetComm.h"
#include "MwCv.h"

int main()
{
  CHAR str[256];

  MwNetComm_c *pMwNetComm = new MwNetComm_c;
  MwCV_c *pMwCv = new MwCV_c;

  pMwCv->Init();
  pMwNetComm->Init();

  pMwNetComm->Link(pMwCv);

  pMwCv->Run();
  pMwNetComm->Run();

  //acre_tsk();
  //getCameraInfo(0);
  //getCameraInfo(1);
#ifdef MY_DEBUG
  printf("CMake pratice demo \n");
#endif
  while(1)
  {
#if 0
    printf("->");
    scanf("%s",str);
    printf("%s \n",str);
#else
    printf("Main App Running \n");
    sleep(30);
#endif
  }
  printf("finish \n");
  return 0;
}

