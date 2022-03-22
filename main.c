#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"
#include "process.h"
#include "jobs.h"
#include "prompt.h"
#include "sighan.h"
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

void pwd()
{
    char presentwd[200];
    getcwd(presentwd, 200);
    printf("%s\n", presentwd);
}

int main()
{
    char input[1000];
    char *comarg, *comarg1, *comarg2, *comarg3, *final;
    getcwd(homepath, 200);
    runpid = 0;
    char mulinput[20][200];
    char pipesepcmd[10][50];
    int mulcom = 0, pipes = 0, i = 0, j = 0, k = 0;
    char args[6][100];
    H = createhead();
    int vinay = 0;

    char *argv[6];
    //pipe(pipefd);
    stdinput = dup(0);
    stdoutput = dup(1);
    int flag = 0;
    signal(SIGINT, &ctrlc);
    signal(SIGTSTP, &ctrlz);
    signal(SIGCHLD, &backhandler);
    // printf("%d", stdinput);
    while (1)
    {
        dup2(stdinput, 0);
        dup2(stdoutput, 1);
        //printf("helo");
        // printf("hello");
        prompt(homepath);
        mulcom = 0;
        i = 0;
        k = (long)fgets(input, 1000, stdin);
        //printf("%d", k);
        //printf("%s", input);
        if (k == 0)
        {
            printf("\n");
            exit(0);
        }
        comarg1 = strtok(input, "\n");
        // printf("%s", comarg1);
        comarg = strtok(comarg1, ";");
        //printf("%s", comarg);
        while (comarg != NULL)
        {
            strcpy(mulinput[mulcom], comarg);
            mulcom++;
            comarg = strtok(NULL, ";");
        };
        //printf("%d", mulcom);
        while (i < mulcom)
        {
            vinay = 0;
            if (i != 0)
            {
                dup2(stdinput, 0);
                dup2(stdoutput, 1);
            }
            pipes = 0;
            j = 0;
            //printf("%s", mulinput[i]);
            if (mulinput[i][strlen(mulinput[i]) - 1] == '|')
            {
                printf("error: no command\n");
                i++;
                continue;
            }
            comarg = strtok(mulinput[i], "|");
            while (comarg != NULL)
            {
                strcpy(pipesepcmd[pipes], comarg);
                pipes++;
                comarg = strtok(NULL, "|");
            }
            i++;
            //printf("%d", pipes);
            // for (int i = 0; i < 9; ++i)
            // {
            //     pipe(pipefd[i]);
            // }
            pipe(pipefd[0]);
            pipe(pipefd[1]);
            while (j < pipes)
            {

                // dup2(pipefd_1[0], 0);
                // close(pipefd_1[0]);
                if (pipes == 1)
                {
                    if (pipesepcmd[j][strlen(pipesepcmd[j]) - 1] == '>' || pipesepcmd[j][strlen(pipesepcmd[j]) - 1] == '<')
                    {
                        printf("error unexpected newline\n");
                        break;
                    }
                    comarg2 = strtok(pipesepcmd[j], "<");
                    comarg3 = strtok(NULL, "<");
                    if (comarg3 == NULL)
                    {
                        comarg = strtok(comarg2, ">");
                        comarg1 = strtok(NULL, ">");
                        if (comarg1 == NULL)
                        {
                            final = comarg;
                        }
                        else
                        {
                            final = comarg;
                            comarg = strtok(comarg1, " ");
                            if (comarg == NULL)
                            {
                                printf("error unexpected newline\n");
                                break;
                            }
                            else
                            {
                                k = duplicateoutput(comarg);
                                if (k < 0)
                                    break;
                            }
                        }
                    }
                    else
                    {
                        final = comarg2;
                        comarg = strtok(comarg3, ">");
                        comarg1 = strtok(NULL, ">");
                        comarg = strtok(comarg, " ");
                        if (comarg == NULL)
                        {
                            printf("error unexpected newline\n");
                            break;
                        }
                        else
                        {
                            k = duplicateinput(comarg);
                            if (k < 0)
                                break;
                        }
                        if (comarg1 != NULL)
                        {
                            comarg = strtok(comarg1, " ");
                            if (comarg == NULL)
                            {
                                printf("error unexpected newline\n");
                                break;
                            }
                            else
                            {
                                k = duplicateoutput(comarg);
                                if (k < 0)
                                    break;
                            }
                        }
                    }
                }
                else
                {
                    if (j == 0)
                    {
                        comarg2 = strtok(pipesepcmd[j], "<");
                        comarg3 = strtok(NULL, "<");
                        final = comarg2;
                        if (comarg3 != NULL)
                        {
                            comarg = strtok(comarg3, " ");
                            if (comarg == NULL)
                            {
                                printf("error unexpected newline\n");
                                break;
                            }
                            else
                            {
                                //printf("%s", comarg);
                                k = duplicateinput(comarg);
                                //printf("%d gaddam", k);
                                if (k < 0)
                                    break;
                            }
                        }
                        vinay = 1;
                        //printf("zkbc\n");
                        //dup2(pipefd[1][1], 1);
                        //dup2(pipefd[j][0], 0);

                        // dup2(pipefd_1[1], 1);
                        // dup2(pipefd_1[0], 0);
                    }
                    else if (j == pipes - 1)
                    {

                        comarg2 = strtok(pipesepcmd[j], ">");
                        comarg3 = strtok(NULL, ">");
                        final = comarg2;
                        if (comarg3 != NULL)
                        {
                            comarg = strtok(comarg3, " ");
                            if (comarg == NULL)
                            {
                                printf("error unexpected newline\n");
                                break;
                            }
                            else
                            {
                                k = duplicateoutput(comarg);
                                if (k < 0)
                                    break;
                            }
                        }
                        else
                        {

                            dup2(stdoutput, 1);
                        }
                        //char time[100];
                        //printf("%s", final);
                        //read(pipefd[j - 1][0], time, 90);
                        //printf("%s", time);
                        //dup2(pipefd[j - 1][0], 0);
                        vinay = 3;
                        //close(pipefd[j - 1][0]);
                    }
                    else
                    {
                        final = pipesepcmd[j];

                        // dup2(pipefd[j - 1][0], 0);
                        //close(pipefd[j - 1][0]);
                        vinay = 2;
                        // dup2(pipefd[j][1], 1);
                    }
                }

                flag = 0;

                comarg = strtok(final, " ");
                j++;
                // printf("hello");
                //printf("%s", comarg);
                if (comarg == NULL)
                {
                    if (pipes > 1)
                    {
                        printf("error: command not found\n");
                        break;
                    }
                    continue;
                }
                else if (strcmp(comarg, "cd") == 0)
                {
                    comarg = strtok(NULL, " ");
                    if (comarg == NULL)
                    {
                        changedirtohome(homepath);
                    }
                    else if (strtok(NULL, " ") == NULL)
                    {
                        if (strcmp(comarg, "-") == 0)
                        {
                            chdirtoprevious();
                        }
                        else if (strcmp(comarg, "~") == 0)
                        {
                            changedirtohome(homepath);
                        }
                        else
                        {
                            changedirtopath(comarg);
                        }
                    }
                    else
                    {
                        printf("error: too many arguments\n");
                    }
                }
                else if (strcmp(comarg, "echo") == 0)
                {
                    comarg = strtok(NULL, " ");
                    while (comarg != NULL)
                    {
                        printf("%s ", comarg);
                        comarg = strtok(NULL, " ");
                    }
                    printf("\n");
                }
                else if (strcmp(comarg, "pwd") == 0)
                {
                    pwd();
                }
                else if (strcmp(comarg, "fg") == 0)
                {
                    comarg = strtok(NULL, " ");
                    if (comarg == NULL)
                    {
                        printf("error: invalid arguments\n");
                        continue;
                    }
                    comarg1 = strtok(NULL, " ");
                    if (comarg1 == NULL)
                        bringfore(comarg);
                    else
                    {
                        printf("error: too many arguments\n");
                    }
                }
                else if (strcmp(comarg, "sig") == 0)
                {
                    comarg = strtok(NULL, " ");
                    if (comarg == NULL)
                    {
                        printf("No jobno signo\n");
                        continue;
                    }
                    comarg1 = strtok(NULL, " ");
                    if (comarg1 == NULL)
                    {
                        printf("No signo\n");
                        continue;
                    }
                    comarg2 = strtok(NULL, " ");
                    if (comarg2 != NULL)
                    {
                        printf("error: too many arguments\n");
                    }
                    else
                    {
                        signalsender(comarg, comarg1);
                    }
                }
                else if (strcmp(comarg, "bg") == 0)
                {
                    comarg = strtok(NULL, " ");
                    if (comarg == NULL)
                    {
                        printf("error: invalid arguments\n");
                        continue;
                    }
                    comarg1 = strtok(NULL, " ");
                    if (comarg1 == NULL)
                        runback(comarg);
                    else
                    {
                        printf("error: too many arguments\n");
                    }
                }
                else if (strcmp(comarg, "jobs") == 0)
                {
                    comarg = strtok(NULL, " ");
                    comarg1 = strtok(NULL, " ");
                    if (comarg1 != NULL)
                    {
                        printf("error: too many arguments\n");
                        continue;
                    }
                    if (comarg == NULL)
                    {
                        printjobs();
                    }
                    else if (strcmp(comarg, "-r") == 0)
                    {
                        printrunningjobs();
                    }
                    else if (strcmp(comarg, "-s") == 0)
                    {
                        printstoppedjobs();
                    }
                    else
                    {
                        printf("error: invalid arguments\n");
                    }
                }
                else
                {

                    argv[0] = args[0];
                    strcpy(args[0], comarg);
                    flag++;

                    for (int j = 1; j < 5; ++j)
                    {
                        comarg = strtok(NULL, " ");
                        argv[j] = NULL;
                        if (comarg != NULL)
                        {
                            argv[j] = args[j];
                            strcpy(args[j], comarg);
                            flag++;
                        }
                    }
                    argv[5] = NULL;
                    // printf("%d", flag);
                    // printf("%s %s", argv[0], argv[1]);
                    if (strcmp(argv[flag - 1], "&") == 0)
                    {
                        argv[flag - 1] = NULL;
                        k = background(argv, flag);
                        if (k < 0)
                            break;
                    }
                    else
                    {
                        //printf("zbkakhkah");
                        //printf("%s", argv[0]);
                        k = foreground(argv, vinay);
                        //printf("%d", k);
                        if (k < 0)
                            break;
                    }

                    // close(pipefd_1[1]);
                }
            }
            close(pipefd[0][1]);
            close(pipefd[0][0]);
            close(pipefd[1][0]);
            close(pipefd[1][1]);
        }
    }
}