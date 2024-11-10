#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void handle_sigint(int sig)  
{
    printf("\nSIGINT received, but ignoring it. Type 'exit' to quit.\n");
}

int is_delim(char *delim, char ch) 
{
    int i;
    for(i=0; delim[i]!='\0'; i++)
   	{
        if(ch == delim[i])
            return 1;
    }
    return 0;
}

char *strtok (char *str, char *delim)
{
    static char *ptr = NULL;
    char *p, *ret;
    if(str != NULL)
        ptr = str;
    if(ptr == NULL)
        return NULL;
    ret = ptr;
    p = ptr;
    while(!is_delim(delim, *p))
        p++;
    if(*p != '\0') {
        *p = '\0';
        ptr = p + 1;
    }
    else {
        ptr = NULL;
        printf("....\n");
    }
    return ret;
}

int main() 
{
    signal(SIGINT, handle_sigint);

    char string[] = "this is an example";
    char *ptr;

    ptr = strtok(string, " ");
    printf("1st token: %s\n", ptr);
    ptr = strtok(NULL, " ");
    printf("2nd token: %s\n", ptr);
    ptr = strtok(NULL, " ");
    printf("3rd token: %s\n", ptr);
    ptr = strtok(NULL, " ");
    printf("4th token: %s\n", ptr);
    ptr = strtok(NULL, " ");
    if(ptr == NULL)
       printf("end!\n");

    return 0;
}

