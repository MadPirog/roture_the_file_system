Фазлиев, Кожураткина, Блинова Гр.0907-32


## Функции файловой системы

### `open_fs`
**Описание:** Открывает или создает и открывает файл файловой системы.  
**Параметры:**  
- `filename` (const char*) - строка с именем файла  
**Возвращаемое значение:**  
- Указатель на FILE (FILE*) - файловый дескриптор  

### `view_fs`
**Описание:** Просматривает содержимое файла внутри файловой системы.  
**Параметры:**  
- `fs_file` (FILE*) - файловый дескриптор файловой системы  
- `target_filename` (const char*) - имя искомого файла  
**Возвращаемое значение:**  
- Указатель на char (char*) - содержимое файла или NULL если файл не найден  

### `delete_fs`
**Описание:** Удаляет файл внутри файловой системы.  
**Параметры:**  
- `fs_filename` (const char*) - имя файла файловой системы  
- `target_filename` (const char*) - имя файла для удаления  
**Возвращаемое значение:**  
- int - 1 если успешно, 0 если ошибка  

## Пример использования
c
FILE* fs = open_fs("my_fs.txt");
char* content = view_file_in_fs(fs, "test.txt");
if (content) {
    printf("File content:\n%s", content);
    free(content);
}

int result = delete_fs("my_fs.txt", "old_file.txt");
if (result) {
    printf("File deleted successfully\n");
}
fclose(fs);
