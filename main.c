#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void printdir(DIR* d, struct dirent* entry, int size){
  struct stat *stt;
  if(entry){
    printf("%s\t",entry->d_name);
    printf("%d\t",entry->d_type);
    if(entry->d_type==4){printf("(directory)\n");}else{
      stat(entry->d_name,stt);
      size+=stt->st_size;
      printf("(regular file)\t%lu Bytes\n",stt->st_size);
    }
    printdir(d,readdir(d),size);
  }else{printf("Total Directory Size = %d Bytes\n",size);}
}

int main(){
  DIR* a;
  a=opendir(".");
  struct dirent *current;
  current=readdir(a);
  printdir(a,current,0);
  closedir(a);
  return 0;
}
