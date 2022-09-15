//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
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
    vector<int> quadroCorrigido;
    //vector<int>::iterator iteradorQuadro = quadro.begin();

    //Algoritmo de Enquadramento
    //Codigo DLE = 16, Codigo ESC = 27
    for (int i = 0; i < (quadro.size()); i++) {
        if (quadro[i] == 27 | quadro[i] == 16) {
            quadroCorrigido.push_back(27); //codigo ASCII ESC
        }
        quadroCorrigido.push_back(quadro[i]);
    }

    // Insercao de Bytes (Flags)
    quadroCorrigido.insert(quadroCorrigido.begin(), 16);
    quadroCorrigido.insert(quadroCorrigido.end(), 16);

    return quadroCorrigido;

}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro) {
    vector<int> quadroEnquadrado;

    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    return quadroEnquadrado;
}

//void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro) {
//
//
//};

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
    vector<int> quadroEnquadrado;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    //CamadaEnlaceDadosTransmissoraControleDeErro(quadro)

    CamadaFisicaTransmissora(quadroEnquadrado);
}

// -----------------------Camada Receptora-----------------------

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {

}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {

}

vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro) {
    vector<int> quadroEnquadrado;

    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}

//void CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro) {
//
//
//};

void CamadaEnlaceDadosReceptora (vector<int> quadro) {
    vector<int> quadroDesenquadrado;

    quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro);

    //CamadaEnlaceDadosReceptoraControleDeErro(quadro)

    CamadaDeAplicacaoReceptora(quadroDesenquadrado)
}