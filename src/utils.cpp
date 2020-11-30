#ifndef UTILS
#define UTILS

#include <iostream>
#include "../include/utils.hpp"

using namespace std;

bool isInteger(const std::string &s) {
    return std::regex_match(s, std::regex("-?[0-9]{0,10}"));
}

bool isVariavelValida(const string &variavel) {
    return variavel.size() <= 50 && regex_match(variavel, regex("^[a-zA-Z_$][a-zA-Z_$0-9]*"));
}

string toUpperCase(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool somenteRotulo(const Linha &linha) {
    return !linha.rotulo.empty() and linha.operacao.empty() and linha.op1.empty();
}

string trocarTipo(string nome, const string &terminacao) {
    if (std::string::npos == nome.find('.')) {
        return nome + '.' + terminacao;
    } else {
        return nome.replace(nome.find_last_of('.'), nome.length(), terminacao);
    }
}

Linha coletaTermosDaLinha(string linha, bool isToThrowErros) {
    string elementos[4];
    int cont = 0;
    bool jaPulou = false;
    // Desconsiderar tabulações #002
    linha = trim(linha);
    // Se não tiver rótulo, começa preenchendo instrução
    if (string::npos == linha.find(':'))
        cont++;

    for (int i = 0; i < linha.length(); i++) {
        auto ch = linha[i];

        if (ch == ';') {
            // Ignora os comentários (#004)
            break;
        }

        // Rótulos com operações matemáticas
        if (ch == '+') {
            cont--;
            elementos[cont] += " ";
            elementos[cont] += ch;
            elementos[cont] += linha[i + 1]; // Coleta o próximo char que obrigatoriamente é um espaço
            elementos[cont] += linha[i + 2]; // coleta o número
            jaPulou = false;
            i += 2;
            continue;
        }

        // Parse do COPY com vírgula #005
        if (ch == ' ' or ch == ',' or (ch == ':' and cont == 0)) {
            if (!jaPulou)
                cont++;
            jaPulou = true;
        } else {
            jaPulou = false;
            elementos[cont] += ch;
        }
    }

    // Transformar todos os elementos em caixa alta #001
    Linha l = {toUpperCase(elementos[0]),
               toUpperCase(elementos[1]),
               toUpperCase(elementos[2]),
               toUpperCase(elementos[3])};
    return l;
}

string linhaToString(const Linha &linha) {
    string str;
    if (!linha.rotulo.empty()) {
        str += linha.rotulo + ": ";
    }
    if (!linha.op1.empty()) {
        str += linha.operacao + ' ';
    } else {
        str += linha.operacao;
    }
    if (!linha.op1.empty() and !linha.op2.empty()) {
        str += linha.op1 + ", " + linha.op2;
    } else if (!linha.op1.empty()) {
        str += linha.op1;
    }
    return str;
}

void gerarArquivoObjeto(string codigo, string filename) {
    auto *arquivoFisico = new ArquivoFisico(trocarTipo(filename, ".obj").c_str(), true);
    arquivoFisico->writeLine(codigo);
    arquivoFisico->finishWrite();
}

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

#endif