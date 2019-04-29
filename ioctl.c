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
    char input = 0;

    while ((curr = getc(fd)) != EOF)
    {
        printf("%c", curr);

        if((curr = getc(fd)) == '\n')
        {
            line++;

            if(line == height - 1)
            {
                printf("[Page %d] Enter to continue, + b for previous: ", page);
            }

            input = getchar();

            if(input == 'b')
            {
                page--;
                fseek(fd, (height * width * page), SEEK_SET);
            }
        }
    }
}