#include "../include/tradutor.hpp"
#include "../include/intrucao.hpp"

Tradutor::Tradutor(ArquivoHandler *arquivoHandler, string outputName) {
    this->arquivo = arquivoHandler;
    this->output = new ArquivoFisico(outputName, true);
    this->listaBss.emplace_back("BUFFER_IN resb 12");
    this->listaBss.emplace_back("BUFFER_IN_SIZE EQU 12");
    this->listaData.emplace_back("msg_init db \"Foram lidos \"");
    this->listaData.emplace_back("msg_end db \" caracteres\", 0ah");
}

bool operacaoIsJmp(const string &operacao) {
    return operacao == "JMPZ" or operacao == "JMPN" or operacao == "JMPP";
}

bool operacaoIsIOString(const string &operacao) {
    return operacao == "S_INPUT" or operacao == "S_OUTPUT";
}

bool operacaoIsIO(const string &operacao) {
    return operacao == "INPUT" or operacao == "OUTPUT" or
           operacao == "C_INPUT" or operacao == "C_OUTPUT" or
           operacao == "S_INPUT" or operacao == "S_OUTPUT";
}

string Tradutor::translate(const Linha &linha) {
    string output_line;
    string acc = "edx";
    if (linha.operacao == "ADD" or linha.operacao == "SUB") {
        output_line = linha.operacao + " " + acc + ", [" + linha.op1 + "]";
    } else if (linha.operacao == "SECTION") {
        if (linha.op1 == "TEXT") {
            output_line = "global _start\n";
            output_line += "section .text\n";
            output_line += "_start:";
        }
    } else if (linha.operacao == "COPY") {
        output_line = "mov [" + linha.op2 + "]" + ", [" + linha.op1 + "]";
    } else if (linha.operacao == "SPACE") {
        if (linha.op1.empty()) {
            listaBss.push_back(linha.rotulo + " resb 1");
        } else {
            listaBss.push_back(linha.rotulo + " resb " + linha.op1);
        }
    } else if (linha.operacao == "CONST") {
        listaData.push_back(linha.rotulo + " dd " + linha.op1);
    } else if (linha.operacao == "LOAD") {
        output_line = "mov " + acc + ",  [" + linha.op1 + "]"; // Parênteses para trabalhar com os valores
    } else if (linha.operacao == "STORE") {
        output_line = "mov [" + linha.op1 + "], " + acc; // Parênteses para trabalhar com os valores
    } else if (linha.operacao == "JMP") {
        output_line = "jmp " + linha.op1;
    } else if (operacaoIsJmp(linha.operacao)) {
        output_line = "cmp " + acc + ", 0\n";
        if (linha.operacao == "JMPZ") {
            output_line += "je " + linha.op1;
        } else if (linha.operacao == "JMPN") {
            output_line += "jl " + linha.op1;
        } else if (linha.operacao == "JMPP") {
            output_line += "jg " + linha.op1;
        }
    } else if (linha.operacao == "DIV") {
        output_line = "mov eax, " + acc + "\n";
        output_line += "cdq\n"; // Extende o sinal do eax no edx
        output_line += "idiv dword [" + linha.op1 + "]\n";
        output_line += "mov " + acc + ", eax";
    } else if (linha.operacao == "MULT") {
        output_line = "mov eax, " + acc + "\n";
        output_line += "imul dword [" + linha.op1 + "]\n";
        output_line += "mov " + acc + ", eax";
        // TODO ver overflow
    } else if (operacaoIsIOString(linha.operacao)) {
        output_line = "push " + linha.op1 + "\n"; // Endereço
        output_line += "push " + linha.op2 + "\n"; // Tamanho da string
        output_line += "call " + convertIO[linha.operacao];
        if (linha.operacao == "S_INPUT") {
            output_line += "\n";
            output_line += "call PrintMensagem";
        }
    } else if (linha.operacao == "OUTPUT") {
        output_line = "push dword [" + linha.op1 + "]\n";
        output_line += "call " + convertIO[linha.operacao];
    } else if (linha.operacao == "C_OUTPUT") {
        output_line = "push " + linha.op1 + "\n";
        output_line += "call " + convertIO[linha.operacao];
    } else if (linha.operacao == "C_INPUT" or linha.operacao == "INPUT") {
        output_line = "push " + linha.op1 + "\n";
        output_line += "call " + convertIO[linha.operacao] + "\n";
        if (linha.operacao == "C_INPUT") { output_line += "mov eax, 1\n"; }
        output_line += "call PrintMensagem";
    } else if (linha.operacao == "STOP") {
        output_line = "mov eax, 1\n";
        output_line += "int 80h";
    }

    // Tratamento de rótulos
    if (!linha.rotulo.empty() and linha.operacao != "SPACE" and linha.operacao != "CONST") {
        output_line = linha.rotulo + ":\n" + output_line;
    }

    return output_line;
}

void Tradutor::run() {
    string linha, ultimoRotulo;
    string linhaTranslate;
    int contadorLinha = 0;
    while (!arquivo->hasEnd()) {
        arquivo->getLine(&linha);
        contadorLinha++;
        if (linha.empty()) continue;
        Linha l = coletaTermosDaLinha(linha, false);
        linhaTranslate = translate(l);
        // Escreve no arquivo a linha traduzida
        if (!linhaTranslate.empty()) {
            output->writeLine(linhaTranslate);
        }
    }

    if (!listaData.empty()) {
        output->writeLine("section .data");
        for (auto data: listaData) {
            output->writeLine(data);
        }
    }

    if (!listaBss.empty()) {
        output->writeLine("section .bss");
        for (auto data: listaBss) {
            output->writeLine(data);
        }
    }

    printLibrary();

    arquivo->finishWrite();
}

void Tradutor::printLibrary() {
    auto lib = new ArquivoFisico("./src/lib.asm", false);
    string linha;
    output->writeLine("section .text ; Bibliotecas de IO");
    while (!lib->hasEnd()) {
        lib->getLine(&linha);
        output->writeLine(linha);
    }
}
