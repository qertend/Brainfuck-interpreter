/**
 * 
 * @param {String} program 
 * @param {String} input 
 * @param {number} EOFcode 
 * @param {HTMLElement} inputNode
 * @param {HTMLElement} outputNode
 * @returns {number} **exit code** \
 * 0 - program ran successfully \
 * 1 - data pointer out of bounds \
 * 2 - malformed loop \
 * 3 - read from empty input
 */
export default function interpret(program, input, EOFcode, outputNode) {
    //instructions
    const increment = "+";
    const decrement = "-";
    const shiftRight = ">";
    const shiftLeft= "<";
    const read = ",";
    const write = ".";
    const cycleStart = "[";
    const cycleEnd = "]";
    const tapeMax = 32768;

    //remove later please c:
    let haltProgram = false;

    let tape = Array(tapeMax).fill(0);
    let programIndex = 0;
    let tapeIndex = 0;
    let inputIndex = 0;

    function printCell(cell) {
        outputNode.value += String.fromCharCode(cell);
    }

    function readToCell(cellIndex) {
        if (inputIndex < input.length && input.charCodeAt(inputIndex) != NaN) {
            tape[cellIndex] = input.charCodeAt(inputIndex);
        }
        else if (inputIndex == input.length) tape[cellIndex] = EOFcode;
        else return 1;
        inputIndex++;
        return 0;
    }
   

    while (programIndex < program.length) {
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
                printCell(tape[tapeIndex]);
                break;

            //reads 1 byte from stdin and stores it in the current byte
            //converts the EOF signal to -1
            case read:
                if(readToCell(tapeIndex)) return 3;
                break;

            //if the current byte is 0, jumps to the correct cycleEnd character ("]")
            //else, it enters the cycle body
            case cycleStart:
                if (tape[tapeIndex] == 0) {
                    let cycles = 1;
                    programIndex++;
                    while (cycles) {
                        if (programIndex >= program.length) return 2;
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
                    let cycles = 1;
                    programIndex--;
                    while (cycles) {
                        if (programIndex < 0) return 2;
                        if (program[programIndex] == cycleEnd) cycles++;
                        else if (program[programIndex] == cycleStart) cycles--;
                        programIndex--;
                    }
                }
                break;
            default:
                break;
                
        }
        //go to the next instruction
        programIndex++;

        if (haltProgram) return 0;
    }
    return 0;
}
