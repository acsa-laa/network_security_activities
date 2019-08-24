#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(int argc, char const *argv[])
{
	string str;
	string arquivo = argv[1];
	string alfabeto = argv[2];
	string chave = argv[3];
	int tamanho = alfabeto.size();
	int aux = 0;
	int aux1 = 0;
	int aux2 = 0;
	int constante = 0;
	ifstream obj(arquivo);

	ofstream decifrado;
	decifrado.open("mensagem.sac");

	if (obj.is_open() == 0)
	{
	  ofstream obj;
	  obj.open(arquivo);
	}

	while(!obj.eof()){
		getline(obj, str);
		for (int l = 0; l < str.size(); l++)
		{
			if (constante >= chave.size())
			{
				constante = 0;
			}
			if(str[l] == ' '){
				decifrado << ' ';
			}
			else{
				for (int k = 0; k < tamanho; k++)
				{
					if (str[l] == argv[2][k])
					{	
						aux = k;
					}
					if (chave[constante] == argv[2][k]){
						aux1 = k;
					}
				}
				constante++; 
				aux2 = (aux - aux1);
				if(aux2<0){
					aux2 = aux2 +tamanho;
				}
				decifrado << argv[2][aux2];
			}
		}
		decifrado << "\n";
	}


	obj.close();
	decifrado.close();

	return 0;
}
