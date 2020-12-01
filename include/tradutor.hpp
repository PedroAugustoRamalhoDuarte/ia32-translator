#include <string>
#include <map>
#include <vector>
#include "arquivoHandler.hpp"
#include "utils.hpp"

using namespace std;

class Tradutor {
public:
    ArquivoHandler *arquivo;
    ArquivoHandler *output;

    vector<string> listaData;
    vector<string> listaBss;

    explicit Tradutor(ArquivoHandler *arquivoHandler);

    void run();

private:
    map<string, string> convertIO = {
            {"INPUT",    "LerInteiro"},
            {"OUTPUT",   "EscreverInteiro"},
            {"C_INPUT",  "LeerChar"},
            {"C_OUTPUT",  "EscreverChar"},
            {"S_INPUT",  "LeerString"},
            {"S_OUTPUT", "EscreverString"}
    };

    void printLibrary();
    string translate(const Linha &linha);
};