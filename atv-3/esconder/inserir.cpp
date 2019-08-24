#include <iostream>
#include "esconder.h"
#include <fstream>

using namespace std;
int main(int argc, char const *argv[]){
        Esteganografia teste = Esteganografia();
        string mensagem = argv[2];
        string arquivo = argv[1];
        teste.inserirMensagem(mensagem, arquivo);
        return 0;
}
