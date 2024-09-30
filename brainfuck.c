//brainfuck interpreter

#include <stdio.h>
//defined special characters for better readability
#define increment '+'
#define decrement '-'
#define shiftRight '>'
#define shiftLeft '<'
#define write '.'
#define read ','
#define cycleStart '['
#define cycleEnd ']'
#define tapeMax 32768
//the program to execute
char program[] = "[ThisprogramprintsSierpinskitriangleon80-columndisplay.]>++++[<++++++++>-]>++++++++[>++++<-]>>++>>>+>>>+<<<<<<<<<<[-[->+<]>[-<+>>>.<<]>>>[[->++++++++[>++++<-]>.<<[->+<]+>[->++++++++++<<+>]>.[-]>]]+<<<[-[->+<]+>[-<+>>>-[->+<]++>[-<->]<<<]<<<<]++++++++++.+++.[-]<]+++++*****Made*By:*NYYRIKKI*2002*****";
//the "memory" tape
char tape[tapeMax] = {0};

int programIndex = 0, tapeIndex = 0;


int main() {
    while (1) {
        //printf("%c %d;", program[programIndex], programIndex);
        switch (program[programIndex]) {
            //adds 1 to the current bit
            case increment:
                tape[tapeIndex]++;
                break;

            //subtracts 1 from the current bit
            case decrement:
                tape[tapeIndex]--;
                break;

            //shifts the byte manipulator to the right (i + 1)
            //exits with code 1 if it runs out of tape
            case shiftRight:
                if (tapeIndex == tapeMax - 1) return 1;
                else tapeIndex++;
                break;

            //shifts the byte manipulator to the left (i - 1)
            //exits with code 1 if it runs out of tape
            case shiftLeft:
                if (tapeIndex == 0) return 1;
                else tapeIndex--;
                break;

            //writes the current byte to stdout
            case write:
                printf("%c", tape[tapeIndex]);
                break;

            //reads 1 byte from stdin and stores it in the current byte
            //converts the EOF signal to -1
            case read:
                scanf("%c", &tape[tapeIndex])
                if (tape[tapeIndex] == EOF) tape[tapeIndex] = -1;
                break;

            //if the current byte is 0, jumps to the correct cycleEnd character ("]")
            //else, it enters the cycle body
            case cycleStart:
                if (tape[tapeIndex] == 0) {
                    int cycles = 1;
                    programIndex++;
                    while (cycles) {
                        if (programIndex >= tapeMax) return 1;
                        if (program[programIndex] == cycleStart) cycles++;
                        else if (program[programIndex] == cycleEnd) cycles--;
                        programIndex++;
                    }
                    programIndex--;
                }
                break;

            //if the current byte is 0, exits the cycle body
            //else, it jumps to the correct cycleStart character ("[")
            case cycleEnd:
                if (tape[tapeIndex] != 0) {
                    int cycles = 1;
                    programIndex--;
                    while (cycles) {
                        if (programIndex < 0) return 1;
                        if (program[programIndex] == cycleEnd) cycles++;
                        else if (program[programIndex] == cycleStart) cycles--;
                        programIndex--;
                    }
                }
                break;
        }
        //execute the next instruction
        programIndex++;
        //check if the program finished, if so, exit
        if (program[programIndex] == NULL) {
            //printf("safely exited on insturction id %d, instruction %c", programIndex, program[programIndex]);
            return 0;
        }
    }
}
