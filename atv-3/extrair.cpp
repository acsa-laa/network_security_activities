#include <iostream>
#include "recuperar.h"
#include <fstream>

using namespace std;
int main(){
        Esteganografia teste = Esteganografia();
        string arquivo = "bitmap.bmp";
		cout << teste.extrairMensagem(arquivo) << endl;
		return 0;
}