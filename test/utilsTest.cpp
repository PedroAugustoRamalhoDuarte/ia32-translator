#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../include/utils.hpp"

TEST_CASE("Variavel valida", "[utils]") {
    REQUIRE_FALSE(isVariavelValida(""));
    REQUIRE(isVariavelValida("ABACATE"));
    REQUIRE(isVariavelValida("teste"));
}

TEST_CASE("ColetaTermos da Linha", "[utils]") {
    SECTION("Linha completa") {
        Linha linha = coletaTermosDaLinha("CPY: COPY N1, N4 ;comentario qualquer");
        REQUIRE(linha.rotulo == "CPY");
        REQUIRE(linha.operacao == "COPY");
        REQUIRE(linha.op1 == "N1");
        REQUIRE(linha.op2 == "N4");
    }SECTION("Linha sem rotúlo") {
        Linha linha = coletaTermosDaLinha("COPY N1, N4 ;comentario qualquer");
        REQUIRE(linha.rotulo.empty());
        REQUIRE(linha.operacao == "COPY");
        REQUIRE(linha.op1 == "N1");
        REQUIRE(linha.op2 == "N4");
    }SECTION("Linha sem op2") {
        Linha linha = coletaTermosDaLinha("SUB N1");
        REQUIRE(linha.rotulo.empty());
        REQUIRE(linha.operacao == "SUB");
        REQUIRE(linha.op1 == "N1");
        REQUIRE(linha.op2.empty());
    }SECTION("com tab") {
        Linha linha = coletaTermosDaLinha("   SUB N1");
        REQUIRE(linha.rotulo.empty());
        REQUIRE(linha.operacao == "SUB");
        REQUIRE(linha.op1 == "N1");
        REQUIRE(linha.op2.empty());
    }SECTION("Rótulo com operações matemáticas") {
        Linha linha = coletaTermosDaLinha("COPY LABEL, LABEL + 1");
        REQUIRE(linha.rotulo.empty());
        REQUIRE(linha.operacao == "COPY");
        REQUIRE(linha.op1 == "LABEL");
        REQUIRE(linha.op2 == "LABEL + 1");
    }SECTION("Rótulo com operações matemáticas com números com mais dígitos") {
        Linha linha = coletaTermosDaLinha("COPY LABEL + 123, LABEL");
        REQUIRE(linha.rotulo.empty());
        REQUIRE(linha.operacao == "COPY");
        REQUIRE(linha.op1 == "LABEL + 123");
        REQUIRE(linha.op2 == "LABEL");
    } SECTION("Rótulo com operações matemáticas com números com um dígito na primeira label") {
        Linha linha = coletaTermosDaLinha("COPY LABEL + 3, OLD_DATA");
        REQUIRE(linha.rotulo.empty());
        REQUIRE(linha.operacao == "COPY");
        REQUIRE(linha.op1 == "LABEL + 3");
        REQUIRE(linha.op2 == "OLD_DATA");
    }
}


TEST_CASE("linhaToString", "[utils]") {
    SECTION("COPY LABEL + 3, OLD_DATA") {
        Linha linha;
        linha.operacao = "COPY";
        linha.op1 = "LABEL + 3";
        linha.op2 = "OLD_DATA";
        REQUIRE(linhaToString(linha) == "COPY LABEL + 3, OLD_DATA");
    }
}
