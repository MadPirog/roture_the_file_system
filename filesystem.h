#indef FILESYSTEM_H
#define FILESYSTEM_H

FILE *open_f(const char* filename);
char* view_f(FILE* fs_file, const char* target_filename);
int delete_f(const char *fs_filename, const char *target_filename);
int create_f(FILE* fs_file, const char* filename, const char* content);
int modify_f(const char* fs_filename, const char* target_filename, const char* new_content);

#endif

   
