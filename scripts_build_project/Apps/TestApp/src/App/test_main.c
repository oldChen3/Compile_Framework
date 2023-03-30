#include <stdio.h>


int main()
{
  int i = 0;
  printf("test app create \n");
  while(1)
  {
    sleep(10);
    printf("test app running \n");
    if(i++ >10)break;
  }
  printf("test app exit \n");

  return 0;
}

