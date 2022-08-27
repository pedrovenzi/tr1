#include <iostream>
#include "CamadaFisica.hpp";

int main(void) {
    AplicacaoTransmissora();
    return 0;
}

// -----------------------Comeco da Camada Transmissora-----------------------

void AplicacaoTransmissora(void) {
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    std::cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(std::string mensagem) {
    int quadro[];
    uint8_t bin_char;

    for (int i = 0; i < mensagem.size(); i++) {
        bin_char = int(mensagem[i]);
    }

    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora (int quadro[]) {
    int tipoDeCodificacao = 0;
    int fluxoBrutoDeBits[BIT_TRAIN_SIZE];

    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);
}

int[] CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]) {
    //algoritmo de CODIFICACAO
}

int[] CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]) {
    //algoritmo de CODIFICACAO
}

int[] CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]) {
    //algoritmo de CODIFICACAO
}

// -----------------------Fim da Camada Transmissora-----------------------

void MeioDeComunicacao (int fluxoBrutoDeBits[]) {
    uint32_t fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA) {
        fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

// -----------------------Comeco da Camada Receptora-----------------------

void CamadaFisicaReceptora (int quadro[]) {
    int tipoDeCodificacao = 0;
    int fluxoBrutoDeBits[BIT_TRAIN_SIZE];

    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
            break;
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}

int[] CamadaFisicaReceptoraCodificacaoManchester (int quadro[]) {
    //algoritmo de DECODIFICACAO
}
int[] CamadaFisicaReceptoraCodificacaoBipolar(int quadro[]) {
    //algoritmo de DECODIFICACAO
}
int[] CamadaFisicaReceptoraCodificacaoBinaria (int quadro[]) {
    //algoritmo de DECODIFICACAO
}
void CamadaDeAplicacaoReceptora(int quadro[]) {
    //std::string mensagem = quadro[];

    AplicacaoReceptora(mensagem_recebida);
}

void AplicacaoReceptora(std::string mensagem_recebida) {
    std::cout << "A mensagem recebida foi:" << mensagem_recebida << std::endl;
}

// -----------------------Fim da Camada Receptora-----------------------
