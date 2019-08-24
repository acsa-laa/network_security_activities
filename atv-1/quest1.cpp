#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(int argc, char const *argv[])
{
	string str;
	string arquivo = argv[1];
	string alfabeto = argv[2];
	int tamanho = alfabeto.size();
	int aux;
	int constante  = 0;
	ifstream obj(arquivo);
	
	ofstream decifrado;
	decifrado.open("mensagem.sac");

	for (int i = 0; i < tamanho; i++)
	{
		ifstream obj(arquivo);
		if (obj.is_open() == 0)
		{
		  ofstream obj;
		  obj.open(arquivo);
		}
		decifrado << i;
		decifrado << "\n";
		while(!obj.eof()){
			getline(obj, str);
			for (int l = 0; l < str.size(); l++)
			{
				constante = 0;
				for (int k = 0; k < tamanho; k++)
				{
				 	if (str[l] == argv[2][k])
				 	{
				 		constante = 1;
			 			aux = k-i;
			 			if ((aux) < 0)
			 			{
			 			 	aux = k-i+tamanho;
			 			} 
			 			decifrado << argv[2][aux];
			 			k = tamanho;
			 		}
				} 
				if (constante == 0)
				{
					decifrado << str[l];
				}
			}
			decifrado << "\n";
		}

		decifrado << "\n\n";
	}
	
	obj.close();
	decifrado.close();

	return 0;
}