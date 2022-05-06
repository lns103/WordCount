#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int readLines(const char *fileName, char *lines[]);
void countCharacters(char *lines[],int line);
void countWords(char *lines[],int line);

int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        printf("parameter isn't correct\n");
        exit(1);
    }
    printf("file address: %s\n\n",argv[2]);
    char **lines;
    int line = readLines(argv[2],lines);
    for(int i=0;i<line;i++)
    {
        printf("%s\n",lines[i]);
    }

    if(strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"-C") == 0)
    {
        countCharacters(lines,line);
    }
    if(strcmp(argv[1],"-w") == 0 || strcmp(argv[1],"-W") == 0)
    {
        countWords(lines,line);
    }
    printf("parameter isn't correct\n");
    return 0;
}

void countCharacters(char *lines[],int line)
{
    int character = 0;
    for(int i=0; i<line; i++)
    {
        for(int j=0; lines[i][j]!='\0'; j++) character++;
    }
    printf("\ncharacter: %d\n\n",character+line-1);
    exit(0);
}

void countWords(char *lines[],int line)
{
    int word = 0;
    char pre = ' ';
    for(int i=0; i<line; i++)
    {
        for(int j=0; ; j++)
        {
            if(lines[i][j]=='\0' || lines[i][j]==' ' || lines[i][j]==',')
                if(pre!='\0' && pre!=' ' && pre!=',')
                    word++;
            pre = lines[i][j];
            if(lines[i][j]=='\0') break;
        }
    }
    printf("\nword: %d\n\n",word);
    exit(0);
}

char *readLine(FILE *fp, char *buffer, int *len)
{
    int ch;
    int i = 0;
    size_t buff_len = 0;
 
    buffer = (char *)malloc(buff_len + 1);
    if (!buffer)
        return NULL; // Out of memory
 
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
    {
        buff_len++;
        void *tmp = realloc(buffer, buff_len + 1);
        if (tmp == NULL)
        {
            free(buffer);
            return NULL; // Out of memory
        }
        buffer = (char *)tmp;
 
        buffer[i] = (char)ch;
        i++;
    }
    buffer[i] = '\0';
 
    *len = buff_len;
 
    // Detect end
    if (ch == EOF && (i == 0 || ferror(fp)))
    {
        free(buffer);
        return NULL;
    }
    return buffer;
}
 
int readLines(const char *fileName, char *lines[])
{
    FILE *file = fopen(fileName, "r");
    char *s;
    int i = 0;
    int n = 0;
    if (file == NULL)
    {
        printf("fail to read");
        exit(1);
    }
    while ((s = readLine(file, s, &n)) != NULL)
    {
        lines[i++] = s;
        // if (i >= max_line)
        //     break;
    }
    return i;
}