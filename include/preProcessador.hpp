#ifndef PRE_PROCESSADOR_H
#define PRE_PROCESSADOR_H

#include <string>
#include <map>
#include "arquivoHandler.hpp"
#include "utils.hpp"

using namespace std;

class PreProcessador {
public:
    map<string, string> tabelaDeDefinicoes = {};
    ArquivoFisico *arquivo;
    ArquivoHandler *arquivoPreProcessado;

    explicit PreProcessador(const string &nomeArquivo, bool isToWrite);

    void run();
};

#endif