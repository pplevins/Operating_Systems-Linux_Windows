/*Pinchas Plevinski 322211558
OS HW2*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int num1, num2, i;
    pid_t pid[3];
    int status[3];
    int res;
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);

    for (i = 0; i < 3; i++)
    {
        pid[i] = fork();

        if (pid[i] < 0)
        {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        }
        else if (pid[i] == 0)
        {
            switch(i)
            {
                case 0:
                    printf("%d\n", num1 + num2);
                    return num1 + num2;
                case 1:
                    printf("%d\n", (num1 + num2) / 2);
                    return 0;
                case 2:
                    printf("%d\n", (int) pow(num1, num2));
                    return (int) pow(num1, num2);
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        waitpid(pid[i], &status[i], 0);
        if (WIFEXITED(status[i]))
        {
            res = WEXITSTATUS(status[i]);
            switch(i)
            {
                case 0:
                    printf("Process %d returned %d\n", i + 1, res);
                    break;
                case 1:
                    printf("Process %d returned %d\n", i + 1, (num1 + num2) / 2);
                    break;
                case 2:
                    printf("Process %d returned %d\n", i + 1, res);
                    break;
            }
        }
    }

    return 0;
}
