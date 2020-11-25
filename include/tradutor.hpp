#include <string>
#include <map>
#include "arquivoHandler.hpp"
#include "utils.hpp"

using namespace std;

class Tradutor {
public:
    ArquivoHandler *arquivo;

    map<string, int> tabelaDeSimbolos = {};
    // Tabela de instrucoes com o nome de instrução/opcode
    map<string, int> tabelaDeIntrucoes = {
            {"ADD",    1},
            {"SUB",    2},
            {"MULT",   3},
            {"DIV",    4},
            {"JMP",    5},
            {"JMPN",   6},
            {"JMPP",   7},
            {"JMPZ",   8},
            {"COPY",   9},
            {"LOAD",   10},
            {"STORE",  11},
            {"INPUT",  12},
            {"OUTPUT", 13},
            {"STOP",   14}
    };
    // Tabela de diretivas com o nome da diretiva e o tamanho da diretiva
    map<string, int> tabelaDeDiretivas = {
            {"SECTION", 0},
            {"SPACE",   1},
            {"CONST",   1},
            {"EQU",     0},
            {"IF",      0}
    };

    explicit Tradutor(ArquivoHandler *arquivoHandler);

    string translate(Linha linha);
};