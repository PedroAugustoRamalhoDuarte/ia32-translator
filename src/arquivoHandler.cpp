#ifndef ARQUIVO
#define ARQUIVO

#include "../include/arquivoHandler.hpp"

void ArquivoEmMemoria::getLine(std::string *linha) {
    if (!this->hasEnd()) {
        *linha = arquivo[this->linhaAtual];
        this->linhaAtual++;
    }
}

void ArquivoEmMemoria::writeLine(std::string linha) {
    arquivo.push_back(linha);
}

bool ArquivoEmMemoria::hasEnd() {
    return arquivo.size() == linhaAtual;
}

void ArquivoEmMemoria::resetFile() {
    linhaAtual = 0;
}

ArquivoFisico::ArquivoFisico(const char *nomeArquivo, bool modoDeEscrita) {
    if (modoDeEscrita) {
        arquivo.open(nomeArquivo, std::ios::out | std::ios::trunc);
    } else {
        arquivo.open(nomeArquivo);
    }
    if (!arquivo)
        throw std::invalid_argument("ArquivoFisico não encontrado");
}

void ArquivoFisico::getLine(std::string *linha) {
    std::getline(this->arquivo, *linha);
}

void ArquivoFisico::writeLine(std::string linha) {
    arquivo << linha << std::endl;
}

bool ArquivoFisico::hasEnd() {
    return arquivo.eof();
}

void ArquivoFisico::resetFile() {
    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);
}

void ArquivoFisico::finishWrite() {
    arquivo.close();
}

#endif