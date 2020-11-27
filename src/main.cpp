#include <iostream>
#include "../include/tradutor.hpp"
#include "../include/preProcessador.hpp"
#include "../include/utils.hpp"

int main(int argc, char **argv) {
    auto preProcessador = new PreProcessador("../test.asm", true);
    preProcessador->run();
    auto *arquivoFisico = new ArquivoFisico("../test.pre");
    auto tradutor = new Tradutor(arquivoFisico);
    tradutor->run();
    return 0;
};