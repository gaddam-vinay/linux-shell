#include <stdio.h>
#include "prompt.h"
#include "jobs.h"
#include "sighan.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/fcntl.h>
int convert(char s[])
{
    int num = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        num = num * 10 + ((int)s[i] - 48);
    return num;
}
void prompt(char home[])
{
    // char usr[100] = getenv("USERNAME");
    char host[100];
    gethostname(host, 100);
    char path[200];
    getcwd(path, 200);
    char *pathh = path;
    if (strstr(path, home) != NULL)
    {
        pathh = &path[strlen(home)];
        printf("<%s@%s:~%s>", getenv("USERNAME"), host, pathh);
    }
    else
    {
        // printf("\033[0;32m");
        printf("<%s@%s:%s>", getenv("USERNAME"), host, pathh);
    }
}
int duplicateinput(char file[])
{
    int fd, k;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("error");
        return -1;
    }
    k = dup2(fd, 0);
    if (k < 0)
        perror("duplicationerror");
    close(fd);
    return 0;
}

int duplicateoutput(char file[])
{
    int fd, k;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        perror("error");
        return -1;
    }
    k = dup2(fd, 1);
    if (k < 0)
        perror("duplicationerror");
    close(fd);

    return 0;
}
void bringfore(char jobstr[])
{
    int pid1 = 0;
    int k;
    int jobno1;
    jobno1 = (int)jobstr[0];
    jobno1 = jobno1 - 48;
    if (jobno1 > H->noofjobs || jobno1 <= 0)
    {
        printf("error: invalid job number\n");
        return;
    }
    node *T;
    T = H->next;
    while (T != NULL)
    {
        if (T->jobno == jobno1)
        {
            pid1 = T->pid;
            break;
        }
        T = T->next;
    }
    if (pid1 > 0)
    {
        k = kill(pid1, SIGCONT);
        strcpy(runningprocess, T->name);
        deletenodepid(pid1);
        runpid = pid1;
        if (k < 0)
            perror("kill");
        waitpid(pid1, 0, WUNTRACED);
    }
}
void runback(char jobstr[])
{
    int pid1 = 0;
    int k;
    int jobno1;
    jobno1 = jobstr[0];
    jobno1 = jobno1 - 48;
    if (jobno1 > H->noofjobs || jobno1 <= 0)
    {
        printf("error: invalid job number\n");
        return;
    }
    node *T;
    T = H->next;
    while (T != NULL)
    {
        if (T->jobno == jobno1)
        {
            pid1 = T->pid;
            break;
        }
        T = T->next;
    }
    if (pid1 > 0)
    {
        k = kill(pid1, SIGCONT);
        if (k < 0)
        {
            perror("kill sys error");
            return;
        }
        strcpy(T->status, "running");
        //waitpid(pid1, 0, WNOHANG);
    }
}
void signalsender(char jobstr[], char signalstr[])
{
    int pid1 = 0;
    int k;
    int jobno1, signalno;
    jobno1 = convert(jobstr);
    //jobno1 = jobno1 - 48;
    signalno = convert(signalstr);
    //printf("%d", signalno);
    if (jobno1 > H->noofjobs || jobno1 <= 0)
    {
        printf("error: invalid job number\n");
        return;
    }
    node *T;
    T = H->next;
    while (T != NULL)
    {
        if (T->jobno == jobno1)
        {
            pid1 = T->pid;
            break;
        }
        T = T->next;
    }
    if (pid1 > 0)
    {
        k = kill(pid1, signalno);
        if (k < 0)
        {
            perror("kill sys error");
            return;
        }
        // strcpy(T->status, "running");
        //waitpid(pid1, 0, WNOHANG);
    }
}