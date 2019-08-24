// Arquivo esteganografia.h
 
#ifndef ESTEGANOGRAFIA_H
#define ESTEGANOGRAFIA_H
 
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
using namespace std;
 
struct RGB
{
    char green;
    char red;
    char blue;
};
 
struct CabecalhoBitmap
{
    char id[2]; 
    int tamanho;
    short int reserv1; 
    short int reserv2;
    int enderecoInicial;
};
 
struct CabecalhoMapaBits
{
    int tamanho; 
    int largura;
    int altura;
    short int planosCor; 
    short int bpp; 
    int metodoCompressao; 
    int tamanhoImagem;
    int resolucaoHorizontal; 
    int resolucaoVertical;
    int coresNaPaleta;
    int coresImportantes; 
};
 
class Esteganografia
{
private:
    FILE *arquivo;
    CabecalhoBitmap cab;
    CabecalhoMapaBits cabDados;
    string arq;
    char bytesDeAjuste; 
 
    void esconderMensagem(string mensagem);
    void salvarBitmap(void);
public:
    RGB *pxl;
    int quantDepxl;
    Esteganografia();
    ~Esteganografia();
    void inserirMensagem(string mensagem, string arquivo);
};
#endif