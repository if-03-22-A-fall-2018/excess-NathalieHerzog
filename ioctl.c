#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct winsize ws;

    if (ioctl(0, TIOCGWINSZ, &ws) != 0)
    {
        fprintf(stderr, "TIOCGWINSZ:%s\n", strerror(errno));
        exit(-1);
    }

    const int height = ws.ws_col;
    const int width = ws.ws_row;

    FILE *fd = fopen("data.txt", "r");
    char curr;

    int line = 0;
    int page = 1;
    char input = ' ';

    while ((curr = fgetc(fd)) != EOF)
    {
        printf("%c", curr);

        if ((curr = fgetc(fd)) == '\n')
        {
            line++;

            if (line == height - 1)
            {
                printf("[Page %d] Enter to continue, + b for previous: ", page);
            }

            input = getchar();

            if (input == 'b')
            {

                if (page < 2)
                {
                    printf("\nOut of range!\n");
                    return 0;
                }

                page--;
                line = 0;
                fseek(fd, (height * width * page), SEEK_SET);
            }
            else
            {
                page++;
                line = 0;
            }
        }
    }

    return 0;
}