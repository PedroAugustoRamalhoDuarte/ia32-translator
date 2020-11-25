#include "../include/tradutor.hpp"
#include "../include/intrucao.hpp"

bool operacaoIsJmp(string operacao) {
    return operacao == "JMPZ" or operacao == "JMPN" or operacao == "JMPZ"
}

string Tradutor::translate(Linha linha) {
    string output_line;
    // MOV, ADD, SUB
    if (linha.operacao == "MOV") {
        output_line = linha.operacao + " eax, " + linha.op1;
        // JMP
    } else if (linha.operacao == "JMP") {
        // JUMPS
    } else if (operacaoIsJmp(linha.operacao)) {
        output_line = "cmp eax 0";
        if (linha.operacao == "JMPZ") {
            // JZ
        } else if (linha.operacao == "JMPN") {
            // JL
        } else if (linha.operacao == "JMPP") {
            // JG
        }
    } else if (linha.operacao == "DIV") {
        output_line = "mov eax, acc";
        output_line = "mov edx, acc";
        output_line = "idiv " + linha.op1;
    }

    arquivo->writeLine(output_line);
}

// IF CONST DATA, IF SPACE BSS