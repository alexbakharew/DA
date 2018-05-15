#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "avl_tree.h"
#include <stdbool.h>
//#include "string.h"
void ToLowerCase(char* Buffer)
{
    for(int i = 0; i < 256; ++i)
    {
        if(Buffer[i] == '\0' || Buffer[i] == '\n') break;
        if(Buffer[i] >= 'A' && Buffer[i] <= 'Z')
        {
            Buffer[i] += 32;
        }
    }
}
int main()
{
    char s[257];
    while(1)
    {
        scanf("%s", s);
        size_t size = strlen(s);
        printf("Length of input string = %lu\n", size);
        ToLowerCase(s);
        char* buff = new char[size + 1];
        strncpy(buff, s,size);
        buff[size] = '\n';
        int i = 0;
        while(1)
        {
            printf("%c", buff[i]);
            if(buff[i] == '\0' || buff[i] == '\n') break;
            ++i;
        }
        delete[] buff;
        //putchar(buff[i]);
        // printf("Copied string = %s\n", buff);
        // printf("Length of new string = %lu\n", strlen(buff));
        // if(!strncmp(s,buff,size)) printf("New string is equal to old string\n");
        // delete[] buff;
        //TString str;
        //printf("String created\n");
        //str.Print();
        //if(!strcmp(s,str.GetStr())) printf("New string is equal to old string\n");
        
    }
}