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

    string translate(const Linha& linha);

    void run();
};