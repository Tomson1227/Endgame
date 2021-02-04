#include "main.h"

void write_to_stream(int stream, char * massage)
{
    write(stream, massage, mx_strlen(massage));
}

void file_close(int name)
{
    close(name);
}

int file_open(char *name)
{
    int pfd;
    if ((pfd = open(name, O_RDONLY)) == -1) {
    write_to_stream(ERROR,ERROR1_1);
    file_close(pfd);
    exit(1);
    }
    return pfd;
}

char *mx_file_to_str(const char *filename)
{
    int fpfd = file_open((char *)filename);
    char *text = (char *) malloc(BUF_SIZE);
    int count = 0;

    while(read(fpfd, text, BUF_SIZE))
        count += BUF_SIZE;
    
    free(text);
    file_close(fpfd);
    
    char *new_file;  
    new_file = (char *) malloc(count + 1);
    
    fpfd = file_open((char *)filename);
    read(fpfd, new_file, count);
    file_close(fpfd);

    return new_file;
}

char **readWordsFromFile(const char *filename) {
    char ch;
    int words = 0;
    FILE *fp = fopen(filename, "r");
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            words++;
        }
    }
    int i = 0, j = 0, count = 0;
    char **arr = (char**)malloc(words*sizeof(char*));
    
    fseek(fp, 0, SEEK_SET);
    
    while ((ch = fgetc(fp)) != EOF) {
        if(ch == '\n') {
            arr[i] = (char*)malloc(count + 1);
            ++i;
            count = 0;
            continue;
        }
        //arr[i] = (char*)malloc(count + 1);
        count++;
    }
    fseek(fp, 0, SEEK_SET);
    // fclose(fp);
    // fp = fopen(filename, "r");
    i = 0;
    j = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            arr[i][j] = '\0';
            i++;
            j = 0;
        }
        else {
            arr[i][j] = ch;
            j++;
        }
    }
    fclose(fp);
    return arr;
}
