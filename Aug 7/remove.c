#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Number of arguments don't match. Aborting.\n");
        return 0;
    }

    if (!remove(argv[1]))
        printf("File deleted successfully!\n");
    else
        printf("Error in deleting file\n");

    return 0;
}
