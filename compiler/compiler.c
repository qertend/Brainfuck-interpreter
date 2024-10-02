#include <stdio.h>

#define textColorRed "\033[31m"
#define textColorDefault "\033[0m"

int main(int argc, char const *argv[])
{
    FILE* rawInput;
    //check if a filename was provided
    if (argc < 2) {
        //if not, print error message and exit
        printf(textColorRed "ERROR:" textColorDefault " No file specified");
        return 1;
    }
    rawInput = fopen(argv[1], "r");
    //check if filename is correct
    if (rawInput == NULL) {
        //if not, print error message and exit
        printf(textColorRed "ERROR:" textColorDefault  "No such file exists");
        return 1;
    }


    //process file here

    fclose(rawInput);

    //prepare bf instructions

    FILE* out = fopen("out.exe", "w");

    //output bf file here

    fclose(out);

    printf("%s", argv[1]);
    return 0;
}


/**
 * return values and meaning.
 * 0: success
 * 1: no such file
 */