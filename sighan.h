#ifndef sig__han
#define sig_han

void ctrlc(int num);
void ctrlz(int num);
void printjobs();
void printstoppedjobs();
void printrunningjobs();
char runningprocess[50];
int runpid;

#endif