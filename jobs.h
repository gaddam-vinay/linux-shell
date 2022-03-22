#ifndef _job__
#define _job__

typedef struct job node;
typedef struct gads head;

struct job
{
    char name[50];
    int jobno;
    char status[20];
    int pid;
    node *next;
};
struct gads
{
    int noofjobs;
    node *next;
};
head *H;
head *createhead();
void addnode(char name1[], int pid1, char status1[]);
int deletenodejob(int jobno1); //for fg command
int deletenodepid(int pid1);   //for termination

#endif