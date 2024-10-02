#include <stdio.h>

int main() {
    FILE* file = fopen("testfile.txt", "r");
    char c;
    int i = 0;
    while (feof(file) == 0)
    {
        i = 1;
        c = fgetc(file);
        printf("%c", c);
    }
    printf("%d", i);
    fclose(file);
    return 0;
}