#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem.h"

int main(){
 /* FILE* fs = open_f("my_fs.dat");
  create_file(fs, "test.txt", "Hello, world!");
  char* content = view_f(fs, "test.txt");
  if (content) {
    printf("File content:/n%s", content);
    free(content);
  }
fclose(fs);*/
 void print_help() {
    printf("Доступные команды:\n");
    printf("создать <имя_файла> <содержимое>\n");
    printf("удалить <имя_файла>\n");
    printf("изменить <имя_файла> <новое_содержимое>\n");
    printf("посмотреть <имя_файла>\n");
    printf("выход\n");
}

int main() {
    char command[256];
    char filename[256];
    char content[1024];
    FILE* fs = open_f("myfs.dat");
    
    printf("Добро пожаловать в roture!\n");
    print_help();
    
    while(1) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';
        
        if (strcmp(command, "выход") == 0) break;
        
        if (sscanf(command, "создать %255s %1023[^\n]", filename, content) == 2) {
            if(create_f(fs, filename, content)) {
                printf("Файл '%s' создан\n", filename);
            }
        }
        else if (sscanf(command, "удалить %255s", filename) == 1) {
            if(delete_f("myfs.dat", filename)) {
                printf("Файл '%s' удален\n", filename);
            }
        }
        else if (sscanf(command, "изменить %255s %1023[^\n]", filename, content) == 2) {
            if(modify_f("myfs.dat", filename, content)) {
                printf("Файл '%s' изменен\n", filename);
            }
        }
        else if (sscanf(command, "посмотреть %255s", filename) == 1) {
            char* content = view_f(fs, filename);
            if(content) {
                printf("Содержимое:\n%s", content);
                free(content);
            } else {
                printf("Файл не найден\n");
            }
        }
        else {
            printf("Неверная команда\n");
            print_help();
        }
    }
    
    fclose(fs);
  return 0;
  
}



