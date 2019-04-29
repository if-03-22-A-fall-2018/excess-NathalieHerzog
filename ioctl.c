/*
 **************************************************		
 * Program:	    excess
 * Author:		Nathalie Herzog
 * Class:		2AHIF
 * Date:		29.04.
 * *************************************************
*/

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
    char curr = fgetc(fd);

    int line = 0;
    int page = 1;
    char input = ' ';
    int count = 0;

    while (curr != EOF)
    {
        printf("%c", curr);
        count++;

        if ((curr = fgetc(fd)) == '\n' || count >= width)
        {
            line++;
            count = 0;

            if (line == height - 1)
            {
                printf("\n[Page %d] Enter to continue, + b for previous: ", page);

                input = getchar();

                if (input == 'b')
                {

                    if (page < 2)
                    {
                        printf("\nOut of range!\n");
                        fclose(fd);
                        return 0;
                    }

                    page--;
                    line = 0;
                    fseek(fd, 0, SEEK_SET);
                }
                else
                {
                    page++;
                    line = 0;
                    count = 0;
                }
            }
        }
    }
    printf("\n");
    fclose(fd);
    return 0;
}