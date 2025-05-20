#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT_SIZE 1024

FILE *open_f(const char* filename) {
    FILE *file = fopen(filename, "a+"); 
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

char* view_f(FILE* fs_file, const char* target_filename) {
    fseek(fs_file, 0, SEEK_SET);
    
    char line[256];
    int found = 0;
    char *content = malloc(MAX_CONTENT_SIZE);
    content[0] = '\0';
    
    while (fgets(line, sizeof(line), fs_file)) {
        line[strcspn(line, "\n")] = '\0'; 
        
        if (!found) {
            if (strcmp(line, target_filename) == 0) {
                found = 1;
            }
        } else {
            if (line[0] == '/') {
                break;
            }
            strcat(content, line);
            strcat(content, "\n");
        }
    }
    
    if (!found) {
        free(content);
        return NULL;
    }
    
    return content;
}


int delete_f(const char *fs_filename, const char *target_filename) {
    FILE *fs_file = fopen(fs_filename, "r");
    if (fs_file == NULL) {
        return 0;
    }
    
    char** lines = NULL;
    int count = 0;
    int delete_mode = 0;
    char line[256];
    
  
    while (fgets(line, sizeof(line), fs_file)) {
        line[strcspn(line, "\n")] = '\0';
        
        if (!delete_mode) {
            if (strcmp(line, target_filename) == 0) {
                delete_mode = 1;
                continue;
            }
        } else {
            if (line[0] == '/') {
                delete_mode = 0;
            } else {
                continue;
            }
        }
        
        lines = realloc(lines, (count + 1) * sizeof(char*));
        lines[count] = strdup(line);
        count++;
    }
    
    fclose(fs_file);
    

    fs_file = fopen(fs_filename, "w");
    if (fs_file == NULL) {
        for (int i = 0; i < count; i++) free(lines[i]);
        free(lines);
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(fs_file, "%s\n", lines[i]);
        free(lines[i]);
    }
    
    free(lines);
    fclose(fs_file);
    return 1;
}
int create_file(FILE* fs_file, const char* filename, const char* content) {
    fseek(fs_file, 0, SEEK_END); 
    
   
    if (fprintf(fs_file, "%s\n", filename) < 0) {
        return 0;
    }
    
   
    if (fprintf(fs_file, "%s\n", content) < 0) {
        return 0;
    }
    
   
    if (fprintf(fs_file, "/\n") < 0) {
        return 0;
    }
    
    fflush(fs_file);
    return 1;
}


int modify_fs(const char* fs_filename, const char* target_filename, const char* new_content) {
    FILE* fs_file = fopen(fs_filename, "r");
    if (fs_file == NULL) {
        return 0;
    }
    
    char** lines = NULL;
    int count = 0;
    int modify_mode = 0;
    int file_found = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fs_file)) {
        line[strcspn(line, "\n")] = '\0';
        
        if (!modify_mode) {
            if (strcmp(line, target_filename) == 0) {
                modify_mode = 1;
                file_found = 1;
                lines = realloc(lines, (count + 1) * sizeof(char*));
                lines[count] = strdup(line);
                count++;
                continue;
            }
        } else {
            if (line[0] == '/') {
                modify_mode = 0;
               
                lines = realloc(lines, (count + 1) * sizeof(char*));
                lines[count] = strdup(new_content);
                count++;
              
                lines = realloc(lines, (count + 1) * sizeof(char*));
                lines[count] = strdup(line);
                count++;
                continue;
            }
         
            continue;
        }
        
        lines = realloc(lines, (count + 1) * sizeof(char*));
        lines[count] = strdup(line);
        count++;
    }
    
    fclose(fs_file);
    
    if (!file_found) {
        for (int i = 0; i < count; i++) free(lines[i]);
        free(lines);
        return 0;
    }
    
    
    fs_file = fopen(fs_filename, "w");
    if (fs_file == NULL) {
        for (int i = 0; i < count; i++) free(lines[i]);
        free(lines);
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(fs_file, "%s\n", lines[i]);
        free(lines[i]);
    }
    
    free(lines);
    fclose(fs_file);
    return 1;
}


   
