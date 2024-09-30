import interpret from "./brainfuck.js"

function get(id) { return document.getElementById(id); }

get("startProgram").addEventListener("click", startProgram);

function startProgram() {
    get("output").value = "";
    resetError();

    let re = interpret(get("program").value, get("input").value, Number.parseInt(get("EOFCode").value), get("output"));

    console.debug("program finished c:");

    showResult(re);
}

function showResult(code) {
    let error = get("error");
    error.style.display = "block";
    error.style.backgroundColor = "#FF5555";
    switch(code) {
        case 0:
            error.innerHTML = "Program ran succesfully.";
            error.style.backgroundColor = "lightgreen";
            break;
        case 1:
            error.innerHTML = "Data pointer moved out of bounds.";
            break;
        case 2:
            error.innerHTML = "Malformed loop.";
            break;
        case 3:
            error.innerHTML = "Program tried reading from empty input stream.";
            break;
        default:
            console.error("Recieved error code: " + code);
            error.innerHTML = "Unknown error.";
    }
}

function resetError() {
    get("error").display = "none";
}
