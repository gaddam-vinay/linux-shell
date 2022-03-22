#ifndef _PROMPT_
#define _PROMPT_

void prompt(char home[]);
int duplicateinput(char file[]);
int duplicateoutput(char file[]);
void bringfore(char jobstr[]);
void runback(char jobstr[]);
void signalsender(char jobstr[], char signalstr[]);
int convert(char s[]);

#endif