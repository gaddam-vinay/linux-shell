#include "cd.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
char prevdir1[200] = "0";
char prevdir2[200] = "0";
void changedirtopath(char path[])
{
    getcwd(prevdir1, 200);
    int k;
    k = chdir(path);
    if (k < 0)
    {
        perror("");
        strcpy(prevdir1, prevdir2);
        return;
    }
    strcpy(prevdir2, prevdir1);
    return;
}
void changedirtohome(char home[])
{
    getcwd(prevdir1, 200);
    int k;
    k = chdir(home);
    if (k < 0)
    {
        perror("");
        strcpy(prevdir1, prevdir2);
        return;
    }
    strcpy(prevdir2, prevdir1);
    return;
}
void chdirtoprevious()
{
    if (strcmp(prevdir1, "0") == 0)
        printf("no previoud directory");
    else
    {
        getcwd(prevdir1, 200);
        chdir(prevdir2);
        strcpy(prevdir2, prevdir1);
        return;
    }
}