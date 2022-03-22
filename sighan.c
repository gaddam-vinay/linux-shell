#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"
#include <sys/wait.h>
#include "jobs.h"
#include "process.h"
#include "sighan.h"
#include "prompt.h"
#include <signal.h>
#include <fcntl.h>

void ctrlc(int num)
{
    //printf("%d oops", runpid);
    if (runpid > 0)
    {
        kill(runpid, SIGKILL);
        // addnode(runningprocess, runpid, "stopped");
    }
    else
        //kill(runpid, SIG_IGN);
        //prompt(homepath);
        return;
}
void ctrlz(int num)
{
    //printf("%d oop", runpid);
    if (runpid > 0)
    {
        kill(runpid, SIGSTOP);
        addnode(runningprocess, runpid, "stopped");
    }
    else
        //kill(runpid, SIG_IGN);
        return;
}
void printjobs()
{
    node *T;
    if (H->noofjobs == 0)
    {
        printf("no jobs :)\n");
        return;
    }
    else
    {
        T = H->next;
        while (T != NULL)
        {
            printf("[%d] %s  %s  [%d]\n", T->jobno, T->status, T->name, T->pid);
            T = T->next;
        }
    }
}
void printrunningjobs()
{
    node *T;
    int flag = 0;
    if (H->noofjobs == 0)
    {
        printf("no running jobs :)\n");
        return;
    }
    else
    {
        T = H->next;
        while (T != NULL)
        {
            if (strcmp(T->status, "running") == 0)
            {
                printf("[%d] %s  %s  [%d]\n", T->jobno, T->status, T->name, T->pid);
                flag = 1;
            }
            T = T->next;
        }
    }
    if (flag == 0)
        printf("no running jobs :)\n");
    return;
}
void printstoppedjobs()
{
    node *T;
    int flag = 0;
    if (H->noofjobs == 0)
    {
        printf("no stopped jobs :)\n");
        return;
    }
    else
    {
        T = H->next;
        while (T != NULL)
        {
            if (strcmp(T->status, "stopped") == 0)
            {
                printf("[%d] %s  %s  [%d]\n", T->jobno, T->status, T->name, T->pid);
                flag = 1;
            }
            T = T->next;
        }
    }
    if (flag == 0)
        printf("no stopped jobs :)\n");
    return;
}