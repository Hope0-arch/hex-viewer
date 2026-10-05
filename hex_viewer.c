#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

void print_offset(size_t offset);
void hex(FILE *file);
void ascii(FILE *file);
void normal(FILE *file);
void help(const char *program);


int main(int argc, char *argv[])
{
    FILE *file;
    const char *filename;

    enum
    {
        NORMAL,
        HEX,
        ASCII
    } mode = NORMAL;


    if (argc < 2)
    {
        printf("No file has been to given to read!\nPlease use '-h' or '--help' to get more info.\n");
        return 1;
    }


    // Flags

    if (strcmp(argv[1], "-h") == 0 ||
        strcmp(argv[1], "--help") == 0)
    {
        help(argv[0]);
        return 0;
    }

    else if (strcmp(argv[1], "-x") == 0 ||
             strcmp(argv[1], "--hex") == 0)
    {
        if (argc < 3)
        {
            fprintf(stderr, "No file provided.\n");
            return 1;
        }

        mode = HEX;
        filename = argv[2];
    }

    else if (strcmp(argv[1], "-a") == 0 ||
             strcmp(argv[1], "--ascii") == 0)
    {
        if (argc < 3)
        {
            fprintf(stderr, "No file provided.\n");
            return 1;
        }

        mode = ASCII;
        filename = argv[2];
    }

    else
    {
        filename = argv[1];
    }


    // open file

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror(filename);
        return 1;
    }

    switch (mode)
    {
        case HEX:
            hex(file);
            break;

        case ASCII:
            ascii(file);
            break;

        case NORMAL:
            normal(file);
            break;
    }


    fclose(file);

    return 0;
}

void print_offset(size_t offset)
{
    printf("%08zX  ", offset);
}



void hex(FILE *file)
{
    uint8_t buff[16];

    size_t bytes_read;
    size_t offset = 0;


    while ((bytes_read = fread(buff, 1, sizeof buff, file)) > 0)
    {
        print_offset(offset);


        for (size_t j = 0; j < bytes_read; j++)
        {
            printf("%02X ", buff[j]);
        }


        printf("\n");

        offset += bytes_read;
    }


    if (ferror(file))
    {
        fprintf(stderr, "Error while reading file.\n");
    }
}



void ascii(FILE *file)
{
    uint8_t buff[16];

    size_t bytes_read;
    size_t offset = 0;


    while ((bytes_read = fread(buff, 1, sizeof buff, file)) > 0)
    {
        print_offset(offset);


        for (size_t j = 0; j < bytes_read; j++)
        {
            
            if (isprint(buff[j]))
            {
                printf("%c", buff[j]);
            }

            else
            {
                printf(".");
            }
        }


        printf("\n");

        offset += bytes_read;
    }


    if (ferror(file))
    {
        fprintf(stderr, "Error while reading file.\n");
    }
}



void normal(FILE *file)
{
    uint8_t buff[16];

    size_t bytes_read;
    size_t offset = 0;


    while ((bytes_read = fread(buff, 1, sizeof buff, file)) > 0)
    {
        print_offset(offset);


        /* HEX */

        for (size_t j = 0; j < bytes_read; j++)
        {
            printf("%02X ", buff[j]);
        }


        /* Keep ASCII column aligned on final line */

        for (size_t j = bytes_read; j < sizeof buff; j++)
        {
            printf("   ");
        }


        printf(" |");


        /* ASCII */

        for (size_t j = 0; j < bytes_read; j++)
        {

            if (isprint(buff[j]))
            {
                printf("%c", buff[j]);
            }

            else
            {
                printf(".");
            }
        }


        printf("|\n");

        offset += bytes_read;
    }


    if (ferror(file))
    {
        fprintf(stderr, "Error while reading file.\n");
    }
}




void help(const char *program)
{
    printf("Usage:\n");
    printf("  %s <file>\n", program);
    printf("  %s [OPTION] <file>\n\n", program);

    printf("Options:\n");
    printf("  -x, --hex       Display hexadecimal bytes only\n");
    printf("  -a, --ascii     Display ASCII representation only\n");
    printf("  -h, --help      Display this help message\n");
}

