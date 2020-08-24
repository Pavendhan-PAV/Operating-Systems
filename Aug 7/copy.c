#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *src, *dest;
    char c;

    if (argc != 3)
    {
        printf("Number of arguments don't match.\nSyntax: ./copy <src_file> <dest_file>\nAborting.\n");
        return 0;
    }

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    if (src == NULL || dest == NULL)
    {
        printf("Unable to open source/destination file!\n");
        return 0;
    }

    while ((c = fgetc(src)) != EOF)
        fputc(c, dest);

    printf("Copied file successfully!\n");

    fclose(src);
    fclose(dest);

    return 0;
}
