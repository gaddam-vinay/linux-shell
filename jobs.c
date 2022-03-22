#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"
#include "jobs.h"
#include <sys/wait.h>
#include <stdlib.h>
#include "process.h"
#include "sighan.h"
#include "prompt.h"
#include <signal.h>
#include <fcntl.h>

head *createhead()
{
    head *H;
    H = (head *)malloc(sizeof(head));
    H->noofjobs = 0;
    H->next = NULL;
    return H;
}

void addnode(char name1[], int pid1, char status1[])
{
    head *K;
    node *T;
    K = H;
    node *N = (node *)malloc(sizeof(node));
    strcpy(N->name, name1);
    strcpy(N->status, status1);
    N->pid = pid1;
    N->next = NULL;
    K->noofjobs++;
    N->jobno = K->noofjobs;
    if (K->next == NULL)
    {
        K->next = N;
    }
    else
    {
        if (strcmp(N->name, H->next->name) < 0)
        {
            N->next = H->next;
            H->next = N;
        }
        else
        {
            T = H->next;
            while (T->next != NULL)
            {
                if (strcmp(N->name, T->next->name) < 0)
                {
                    N->next = T->next;
                    T->next = N;
                    break;
                }
                T = T->next;
            }
            if (T->next == NULL)
            {
                N->next = NULL;
                T->next = N;
            }
        }
    }
}
int deletenodejob(int jobno1)
{
    node *T;
    T = H->next;
    H->noofjobs--;

    if (T->jobno == jobno1)
    {
        H->next = T->next;
        free(T);
    }
    else
    {
        while (T->next != NULL)
        {
            if (T->next->jobno == jobno1)
            {
                T->next = T->next->next;
                break;
            }
            T = T->next;
        }
    }
    if (T->next == NULL)
    {
        return -1;
    }
    T = H->next;
    while (T != NULL)
    {
        if (T->jobno > jobno1)
        {
            T->jobno--;
        }
        T = T->next;
    }

    return 0;
}

int deletenodepid(int pid1)
{
    node *T;
    int jobno1;
    T = H->next;
    while (T != NULL)
    {
        if (T->pid == pid1)
        {
            jobno1 = T->jobno;
            break;
        }
        T = T->next;
    }
    if (T == NULL)
    {
        return -1;
    }

    H->noofjobs--;
    T = H->next;
    if (T->pid == pid1)
    {
        H->next = T->next;
        free(T);
    }
    else
    {
        while (T->next != NULL)
        {
            if (T->next->pid == pid1)
            {
                T->next = T->next->next;
                break;
            }
            T = T->next;
        }
    }
    T = H->next;
    while (T != NULL)
    {
        if (T->jobno > jobno1)
        {
            T->jobno--;
        }
        T = T->next;
    }
    return 0;
}