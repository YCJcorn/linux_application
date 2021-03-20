/*
实现功能：从一个文件中读取最后10k数据并复制到另一个文件中。
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024
#define SRC_FILE_NAME "src_file"
#define DEST_FILE_NAME "dest_file"
#define OFFSE 10240

int main()
{
  int src_file,dest_file;
  unsigned char buff[BUFFER_SIZE];
  int real_read_len;

  src_file = open(SRC_FILE_NAME,O_RDONLY);
  dest_file = open(DEST_FILE_NAME,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  if (src_file < 0 || dest_file < 0)
    {
      printf("open file failed\r\n");
      exit(1);
    }

  lseek(src_file,-OFFSE,SEEK_END);
  while((real_read_len = read(src_file,buff, sizeof(buff)))>0)
    {
      write(dest_file,buff,real_read_len);
    }
  close(src_file);
  close(dest_file);
  
}
