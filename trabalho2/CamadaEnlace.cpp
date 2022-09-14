//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaEnlace.hpp"
#include <string>
#include <vector>
using namespace std;

// -----------------------Camada Transmissora-----------------------

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]) {

}

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(int quadro[]) {

}

void CamadaEnlaceDadosTransmissoraEnquadramento (int quadro[]) {
    int tipoDeEnquadramento = 0;
    int quadroEnquadrado [];

    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErro (int quadro[]) {


};

void CamadaEnlaceDadosTransmissora (int quadro[]) {

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    //CamadaEnlaceDadosTransmissoraControleDeErro(quadro)

    //CamadaFisicaTransmissora(quadro)
}

// -----------------------Camada Receptora-----------------------

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(int quadro[]) {

}

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(int quadro[]) {

}

void CamadaEnlaceDadosReceptoraEnquadramento (int quadro[]) {
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

void CamadaEnlaceDadosReceptoraControleDeErro (int quadro[]) {


};

void CamadaEnlaceDadosReceptora (int quadro[]) {

    CamadaEnlaceDadosReceptoraEnquadramento(quadro);

    //CamadaEnlaceDadosReceptoraControleDeErro(quadro)

    //CamadaDeAplicacaoReceptora(quadro)
}