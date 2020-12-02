#include <iostream>
#include "../include/tradutor.hpp"
#include "../include/preProcessador.hpp"
#include "../include/utils.hpp"

int main(int argc, char **argv) {
    if (argc > 1) {
        std::cout << "Traduzindo programa: " << argv[1] << endl;
        auto preProcessador = new PreProcessador(argv[1], true);
        preProcessador->run();
        auto *arquivoFisico = new ArquivoFisico(trocarTipo(argv[1], ".pre"));
        auto tradutor = new Tradutor(arquivoFisico, trocarTipo(argv[1], ".s"));
        tradutor->run();
        std::cout << "Tradução concluida: " << trocarTipo(argv[1], ".s") << endl;
    } else {
        std::cout << "É necessário passar de parametro o nome do arquivo." << endl;
    }

    return 0;
};