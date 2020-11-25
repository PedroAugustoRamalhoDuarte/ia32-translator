#ifndef PRE_PROCESSADOR
#define PRE_PROCESSADOR

#include "../include/preProcessador.hpp"

using namespace std;


PreProcessador::PreProcessador(const string &nomeArquivo, bool isToWrite) {
    arquivo = new ArquivoFisico(nomeArquivo.c_str());
    if (isToWrite) {
        arquivoPreProcessado = new ArquivoFisico(trocarTipo(nomeArquivo, ".pre").c_str(), true);
    } else {
        arquivoPreProcessado = new ArquivoEmMemoria;
    }
}

// ----------------------------------------------------------------

void PreProcessador::run() {
    string linha, ultimoRotulo;
    bool printLine = true;
    int contadorLinha = 0;
    while (!arquivo->hasEnd()) {

        arquivo->getLine(&linha);
        contadorLinha++;
        if (linha.empty()) continue;
        Linha l = coletaTermosDaLinha(linha, false);

        // Somente rótulo na linha
        if (somenteRotulo(l)) {
            ultimoRotulo = l.rotulo;
            continue;
        } else {
            if (!ultimoRotulo.empty()) {
                if (l.rotulo.empty()) {
                    l.rotulo = ultimoRotulo;
                }
            }
            ultimoRotulo = "";
        }

        if (l.operacao == "EQU") {
            tabelaDeDefinicoes[l.rotulo] = l.op1;
        } else if (l.operacao == "IF") {
            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op1)) {
                printLine = !(tabelaDeDefinicoes[l.op1] == "0");
            }
        } else {
            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op1)) {
                l.op1 = tabelaDeDefinicoes[l.op1];
            }
            if (tabelaDeDefinicoes.end() != tabelaDeDefinicoes.find(l.op2)) {
                l.op2 = tabelaDeDefinicoes[l.op2];
            }
            if (printLine) {
                arquivoPreProcessado->writeLine(linhaToString(l));
            } else {
                printLine = true;
            }
        }

    }
    arquivo->arquivo.close();
    arquivoPreProcessado->finishWrite();
}

#endif
