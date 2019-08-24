#include "recuperar.h"
 
Esteganografia::Esteganografia()
{
 
}
 
Esteganografia::~Esteganografia()
{
 
}
 
string Esteganografia::extrairMensagem(string arquivo)
{
    arq = arquivo;
    this->arquivo = fopen(arq.c_str(), "rb");
    if(!this->arquivo)
    {
        cout << endl << " Erro ao acessar o arquivo";
        return "";
    }

    fread(&cab.id, sizeof(cab.id), 1, this->arquivo);
    fread(&cab.tamanho, sizeof(cab.tamanho), 1, this->arquivo);
    fread(&cab.reserv1, sizeof(cab.reserv1), 1, this->arquivo);
    fread(&cab.reserv2, sizeof(cab.reserv2), 1, this->arquivo);
    fread(&cab.enderecoInicial, sizeof(cab.enderecoInicial), 1, this->arquivo);

    fread(&cabDados.tamanho, sizeof(cabDados.tamanho), 1, this->arquivo);
    fread(&cabDados.largura, sizeof(cabDados.largura), 1, this->arquivo);
    fread(&cabDados.altura, sizeof(cabDados.altura), 1, this->arquivo);
    fread(&cabDados.planosCor, sizeof(cabDados.planosCor), 1, this->arquivo);
    fread(&cabDados.bpp, sizeof(cabDados.bpp), 1, this->arquivo);
    fread(&cabDados.metodoCompressao, sizeof(cabDados.metodoCompressao), 1, this->arquivo);
    fread(&cabDados.tamanhoImagem, sizeof(cabDados.tamanhoImagem), 1, this->arquivo);
    fread(&cabDados.resolucaoHorizontal, sizeof(cabDados.resolucaoHorizontal), 1, this->arquivo);
    fread(&cabDados.resolucaoVertical, sizeof(cabDados.resolucaoVertical), 1, this->arquivo);
    fread(&cabDados.coresNaPaleta, sizeof(cabDados.coresNaPaleta), 1, this->arquivo);
    fread(&cabDados.coresImportantes, sizeof(cabDados.coresImportantes), 1, this->arquivo);
 
    this->bytesDeAjuste = cabDados.largura % 4;

    fseek(this->arquivo, 0, SEEK_END);

    quantDepxl = cabDados.largura * cabDados.altura;
    pxl = new RGB[quantDepxl];

    fseek(this->arquivo, cab.enderecoInicial, SEEK_SET);

    for (int larg = 0, pix = 0; pix < quantDepxl;  larg++)
    {
        if (larg == cabDados.largura)
        {
            fseek(this->arquivo, bytesDeAjuste, SEEK_CUR); 
            larg = 0;
            continue;
        }
 
        fread(&pxl[pix++], sizeof(RGB), 1, this->arquivo);
    }
 
    fclose(this->arquivo);
 
    // Agora temos o bitmap estruturado dentro da nossa classe
    string mensagem;
 
    mensagem = this->extrairMensagem();
 
    return mensagem;
}

string Esteganografia::extrairMensagem(void)
{
    string mensagem;
    char caracter;
    int indice = 0;
 
    /*fazemos o sentido inverso a forma como foi gravado
     */
 
    do
    {
        caracter = (pxl[indice].red & 1) +
                   ((pxl[indice].green & 1) * 2) +
                   ((pxl[indice].blue & 1) * 4) +
                   ((pxl[indice+1].red  & 1) * 8 ) +
                   ((pxl[indice+1].green & 1) * 16) +
                   ((pxl[indice+1].blue & 1) * 32) +
                   ((pxl[indice+2].red & 1) * 64) +
                   ((pxl[indice+2].green & 1) * 128);
 
        mensagem += caracter;
        indice += 3;
    }
    while (caracter != '3');
 
    mensagem = mensagem.substr(0, mensagem.length() - 1);
    return mensagem;
}

void Esteganografia::salvarBitmap()
{
    arquivo = fopen(arq.c_str(), "wb");
    if (!arquivo)
    {
        cout << " Erro ao acessar o arquivo." << endl;
        return;
    }
 
    fwrite(&cab.id, sizeof(cab.id), 1, arquivo);
    fwrite(&cab.tamanho, sizeof(cab.tamanho), 1, arquivo);
    fwrite(&cab.reserv1, sizeof(cab.reserv1), 1, arquivo);
    fwrite(&cab.reserv2, sizeof(cab.reserv2), 1, arquivo);
    fwrite(&cab.enderecoInicial, sizeof(cab.enderecoInicial), 1, arquivo);
 
    fwrite(&cabDados.tamanho, sizeof(cabDados.tamanho), 1, arquivo);
    fwrite(&cabDados.largura, sizeof(cabDados.largura), 1, arquivo);
    fwrite(&cabDados.altura, sizeof(cabDados.altura), 1, arquivo);
    fwrite(&cabDados.planosCor, sizeof(cabDados.planosCor), 1, arquivo);
    fwrite(&cabDados.bpp, sizeof(cabDados.bpp), 1, arquivo);
    fwrite(&cabDados.metodoCompressao, sizeof(cabDados.metodoCompressao), 1, arquivo);
    fwrite(&cabDados.tamanhoImagem, sizeof(cabDados.tamanhoImagem), 1, arquivo);
    fwrite(&cabDados.resolucaoHorizontal, sizeof(cabDados.resolucaoHorizontal), 1, arquivo);
    fwrite(&cabDados.resolucaoVertical, sizeof(cabDados.resolucaoVertical), 1, arquivo);
    fwrite(&cabDados.coresNaPaleta, sizeof(cabDados.coresNaPaleta), 1, arquivo);
    fwrite(&cabDados.coresImportantes, sizeof(cabDados.coresImportantes), 1, arquivo);
 
    char fimDeLinha[bytesDeAjuste];
 
    for (int i = 0; i < bytesDeAjuste; i++)
        fimDeLinha[i] = 0;
 
    for (int pix = 0, larg = 0; pix < quantDepxl;)
    {
        if (larg == cabDados.largura)
        {
            fwrite(&fimDeLinha, bytesDeAjuste, 1, arquivo);
            larg = 0;
            continue;
        }
        fwrite(&pxl[pix++], sizeof(RGB), 1, arquivo);
        larg++;
    }
 
    fclose(arquivo); 
}