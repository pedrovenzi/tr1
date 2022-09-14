//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaEnlace.hpp"
#include <string>
#include <vector>
using namespace std;

//variavel global utilizada para definir qual será o tipo de enquadramento usado;
int tipoDeEnquadramento = 0;

// -----------------------Camada Transmissora-----------------------

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {
    quadro.insert(quadro.begin(), quadro.size());

    return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {
    int contagemESC;
    //vector<int>::iterator iteradorQuadro = quadro.begin();

    //Algoritmo de Enquadramento
    //Codigo DLE = 16, Codigo ESC = 27
    for (int i = 0; i < (quadro.size()); i++) {
        if (quadro[i + contagemESC] == 27 | quadro[i + contagemESC] == 16) {
            quadro.insert((quadro.begin() + (i + contagemESC)), 27); //codigo ASCII DLE // referencia: https://cplusplus.com/reference/vector/vector/insert/
        }
    }

    // Insercao de Bytes (Flags)
    quadro.insert(quadro.begin(), 16);
    quadro.insert(quadro.end(), 16);

    return quadro;

}

void CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro) {
    vector<int> quadroEnquadrado;

    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro) {


};

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    //CamadaEnlaceDadosTransmissoraControleDeErro(quadro)

    //CamadaFisicaTransmissora(quadro)
}

// -----------------------Camada Receptora-----------------------

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {

}

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {

}

void CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro) {
    int tipoDeEnquadramento = 0;
    int quadroEnquadrado [];

    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro) {


};

void CamadaEnlaceDadosReceptora (vector<int> quadro) {

    CamadaEnlaceDadosReceptoraEnquadramento(quadro);

    //CamadaEnlaceDadosReceptoraControleDeErro(quadro)

    //CamadaDeAplicacaoReceptora(quadro)
}