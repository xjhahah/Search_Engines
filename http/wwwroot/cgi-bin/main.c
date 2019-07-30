#include<stdio.h>
#include"cgi-base.h"



int main()
{
  fprintf(stderr," main ::content_length_str :%s\n",getenv("CONTENT_LENGTH"));
  char buf[1024 * 4]={0};
  int ret = GetQueryString(buf);
  if(ret < 0){
    fprintf(stderr,"[CGI]GetQueryString Failed\n");
    return 1;
  }
  int a,b;
  sscanf(buf,"a=%d&b=%d",&a,&b);
  int sum = a+b;
  printf("<h1>sum=%d</h1>",sum);
  return 0;
}
