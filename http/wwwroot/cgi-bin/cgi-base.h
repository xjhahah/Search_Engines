#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

static int GetQueryString(char buf[]){
  char* method=getenv("REQUEST_METHOD");
  if(method == NULL){
    fprintf(stderr,"[CGI] method is NULL\n");
    return -1;
  }

  fprintf(stderr,"[CGI] method[%s]\n",method);
  //如果是GET方法 
  if(strcasecmp(method,"GET")==0){
    char* query_string=getenv("QUERY_STRING");
    if(query_string==NULL){
      fprintf(stderr,"[CGI]query_string is NULL\n"); 
      return -1;
    }
    strcpy(buf,query_string);
  }
  if(strcasecmp(method,"POST") == 0){

    fprintf(stderr,"####################################\n");
    //如果是POST方法,从管道中获取body
    //char content_length_str[1024*4] = {0};
    //fprintf(stderr,"content_length_str :%s\n",getenv("CONTENT_LENGTH"));
    //strcpy(content_length_str,getenv("CONTENT_LENGTH"));
    //fprintf(stderr,"content_length_str :%s\n",content_length_str);
    char * content_length_str = getenv("CONTENT_LENGTH");
    if(content_length_str == NULL ){
      fprintf(stderr,"[CGI] content_length is NULL\n");
      return -1;
    }
    int content_length = atoi(content_length_str);
    int i=0;
    for(;i<content_length;++i){
      read(0,&buf[i],1);
    }
    buf[i]='\0';
  }
  return 0;
  }
