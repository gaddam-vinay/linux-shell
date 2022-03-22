#ifndef _process_
#define _process_

int background(char *args[], int flag);
int foreground(char *args[], int flag);
void backhandler(int num);
int pipefd[2][2];
char inout[1000000];
//int pipefd[10][2], pipefd_1[2];
int stdinput, stdoutput;
char homepath[200];
#endif