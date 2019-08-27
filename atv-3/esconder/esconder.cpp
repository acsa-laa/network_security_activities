#include "esconder.h"
 
Esteganografia::Esteganografia()
{
 
}
 
Esteganografia::~Esteganografia()
{
 
}
 
void Esteganografia::inserirMensagem(string mensagem, string arquivo)
{
    arq = arquivo;
    this->arquivo = fopen(arq.c_str(), "rb");
    if(!this->arquivo)
    {
        cout << endl << " Erro ao acessar o arquivo";
        return;
    }
    string mensg = mensagem;

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
 
    unsigned long capacidade = (cab.tamanho - cab.enderecoInicial)/3;
    if(mensg.size() > capacidade)
    {
        cout << "Mensagem muito grande!" << endl;
        return;
    }
 
    if(cab.enderecoInicial != 0x36)
    {
        cout << "Tipo de arquivo inválido!" << endl;
        return;
    }

    this->esconderMensagem(mensg);
    this->salvarBitmap();
 
    delete pxl;
}
 
 
void Esteganografia::esconderMensagem(string mensagem)
{
    /*
    Este método pega 3 pixels da imagem por vez. Cada pixels com 3 cores, restando 9 bytes. Desses 9 bytes, usamos 8. Substituindo no bit menos significativo de cada cor.
     */
 
    for(unsigned int numCaracter = 0, indice = 0; numCaracter <= mensagem.size(); numCaracter++)
    {
        this->pxl[indice].red &= 254;
        this->pxl[indice].green &= 254;
        this->pxl[indice].blue &= 254;
 
        if(mensagem[numCaracter] & 1){ 
 			this->pxl[indice].red = 1;
 		}
        else{ 
        	this->pxl[indice].red = 0;
        }
        if(mensagem[numCaracter] & 2){ 
 			this->pxl[indice].green = 1;
 		}
        else{ 
        	this->pxl[indice].green = 0;
        }
        if(mensagem[numCaracter] & 4){ 
 			this->pxl[indice].blue = 1; 
 		}
        else{ 
        	this->pxl[indice].blue = 0;
        }
        indice++;
 
        this->pxl[indice].red &= 254;
        this->pxl[indice].green &= 254;
        this->pxl[indice].blue &= 254;

 		if(mensagem[numCaracter] & 8){ 
 			this->pxl[indice].red = 1;
 		}
        else{ 
        	this->pxl[indice].red = 0;
        }
        if(mensagem[numCaracter] & 16){ 
 			this->pxl[indice].green = 1;
 		}
        else{ 
        	this->pxl[indice].green = 0;
        }
        if(mensagem[numCaracter] & 32){ 
 			this->pxl[indice].blue = 1; 
 		}
        else{ 
        	this->pxl[indice].blue = 0;
        }
        indice++;
 		
        this->pxl[indice].red &= 254;
        this->pxl[indice].green &= 254;
 		
        if(mensagem[numCaracter] & 64){ 
 			this->pxl[indice].red = 1;
 		}
        else{ 
        	this->pxl[indice].red = 0;
        }
        if(mensagem[numCaracter] & 128){ 
 			this->pxl[indice].green = 1;
 		}
        else{ 
        	this->pxl[indice].green = 0;
        }
        indice++;
    }
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
