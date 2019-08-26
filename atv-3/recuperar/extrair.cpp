#include <iostream>
#include "recuperar.h"
#include <fstream>

using namespace std;
int main(int argc, char const *argv[]){
        Esteganografia teste = Esteganografia();
        string arquivo = argv[1];
	cout << teste.extrairMensagem(arquivo) << endl;
	return 0;
}
