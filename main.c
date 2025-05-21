#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem.h"

int main(){
  FILE* fs = open_f("my_fs.dat");
  create_file(fs, "test.txt", "Hello, world!");
  char* content = view_f(fs, "test.txt");
  if (content) {
    printf("File content:/n%s", content);
    free(content);
  }
fcolse(fs);
  return 0;
  
}



