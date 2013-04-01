#include "Sequential.h"

#ifndef __STDIO_SET_
#include <stdio.h>
#define __STDIO_SET_
#endif

#ifndef __CSTRING_SET_
#include <cstring>
#define __CSTRING_SET_
#endif
#include <cstdlib>
#define MAX_REG_SIZE 98

Sequential::Sequential() { //ctor
    f_handler=NULL;
}

Sequential::~Sequential() { //dtor
    s_close();
}

bool Sequential::is_sequential() { return true; }

int Sequential::s_create(char *url)
{
  f_handler = fopen (url,"w");
  if(f_handler== NULL){
    return 1;
  }
  return 0;
}


int Sequential::s_write(char *url, char *text){
  f_handler= fopen(url, "a");

  if(f_handler != NULL){
   char buff[MAX_REG_SIZE];
   unsigned int size= strlen(text)+1;
   (size <= 9) ? sprintf(buff, "0%d", size) : sprintf(buff, "%d", size);
   fwrite(buff, 1, 3, f_handler); //guardo el tamaño + \0
   fwrite(text, 1, (size_t)size, f_handler); // el texto
  } else {
   return 1;
  }
return 0;
}

int Sequential::s_open(char * url, const char mode[]){
   f_handler= fopen(url, mode);
   if(f_handler == NULL){return 1;}
return 0;
}

int Sequential::s_read(char *url, char *reg)
{
  if(f_handler==NULL){ return 1; } // el archivo debe estar abierto
  char buff[MAX_REG_SIZE];

  if(!feof(f_handler)){
     fread(&buff, 1, 3, f_handler);
     int size = atoi(buff);
     fread(reg, 1, (size_t)size, f_handler);
  } else {
     return 1;
  }
return 0;
}

void Sequential::s_list(char *url){
  char reg[MAX_REG_SIZE];
  while(s_read(url, reg) != 1){
    printf("%s\n", reg);
    reg[0]='\0';
  }
}

int Sequential::s_search(char *url, char *str){
  char reg[MAX_REG_SIZE];
  bool finded=false;
  int pos=0;
  while(s_read(url, reg) != 1 && finded==false){
//    printf("reg: %s\n",reg);
//    printf("str: %s\n",str);
    (strcmp(reg, str)==0) ? finded=true : pos++;
  }
if(finded == false){ pos=-1; }
return pos;
}

int Sequential::s_destroy(char *url){
  if( remove(url) != 0 ){
    return 1;
  }
return 0;
}

void Sequential::s_close(){
  if(f_handler != NULL){ fclose(f_handler); f_handler=NULL; }
}
