#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

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

int main(int argc, char* argv[]){
  DIR* a;
  char buffer[100];
  int hold;
  hold=open("/dev/stdin", O_RDONLY);
  if(argc>1){a=opendir(argv[1]);}else{printf("which directory would you like to scan? (use ctrl+d to submit)\n");
                                      read(hold,buffer,sizeof(buffer));
                                      printf("\n");
                                      a=opendir(buffer);
                                      if(errno){printf("%s\n",strerror(errno));}
                                    }
  if(!errno){
  struct dirent *current;
  current=readdir(a);
  printdir(a,current,0);
  close(hold);
  closedir(a);
  return 0;}
  return 1;
}
