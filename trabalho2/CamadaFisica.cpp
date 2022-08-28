#include <iostream>
#include <bitset>
#include "CamadaFisica.hpp"

int main(void) {
    AplicacaoTransmissora();
    return 0;
};

// -----------------------Comeco da Camada Transmissora-----------------------

void AplicacaoTransmissora(void) {
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    std::cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
};

void CamadaDeAplicacaoTransmissora(std::string mensagem) {
    int tamanho_quadro = mensagem.size();
    int quadro[tamanho_quadro];
    int bin_char;

    for (int i = 0; i < tamanho_quadro; i++) {
        bin_char = int(mensagem[i]);
        quadro[i] = bin_char;
    }

    CamadaFisicaTransmissora(quadro, tamanho_quadro);
};

void CamadaFisicaTransmissora (int quadro[], int tamanho_quadro) {
    int tipoDeCodificacao = 0;
    int *fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro, tamanho_quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro, tamanho_quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro, tamanho_quadro);
            break;
    }

    // MeioDeComunicacao(fluxoBrutoDeBits);
};

int *CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[], int tamanho_quadro) {
    //multiplicamos por 8 pois o size retorna em bytes
    int array[tamanho_quadro * 8];
    int contador = 0;
    for (int i = 0; i < tamanho_quadro; i++){
        for (int j = 0; j < 8; j++){
            //transformar o algoritmo de ascii para binario
            std::string bin_char_str = std::bitset<8>(quadro[i]).to_string();

            //adicionando cada bit para o nosso array
            array[contador] = bin_char_str[j];
            contador++;
        }
    }
    return array;
    //algoritmo de CODIFICACAO
};

int *CamadaFisicaTransmissoraCodificacaoManchester(int quadro[], int tamanho_quadro) {
    int array[tamanho_quadro * 8];
    int contador = 0;
    for (int i = 0; i < tamanho_quadro; i++){
        for (int *j = 0; *j < 8; j++){
            array[contador] = quadro[i][j] ^ 0; // clock = 0
            contador++;
            array[contador] = quadro[i][j] ^ 1; // clock = 1
            contador++;
        }
    }
    //algoritmo de CODIFICACAO
};

int *CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[], int tamanho_quadro) {
    int array[tamanho_quadro * 8];
    int contador = 0;
    int polarity = 0;
    for (int i = 0; i < tamanho_quadro; i++) {
        for (int *j = 0; *j < 8; j++) {
            if (quadro[i][j] == 0) {
                array[contador] = 0;
            }
            else {
                switch (polarity) {
                    case 0:
                        array[contador] = 1;
                        polarity = 1;
                    case 1:
                        array[contador] = -1;
                        polarity = 0;
                }
            }
            contador++;
        }
    }
    return array;
    //algoritmo de CODIFICACAO
};

// // -----------------------Fim da Camada Transmissora-----------------------

/*void MeioDeComunicacao (int fluxoBrutoDeBits[]) {
    uint32_t fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

     fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

     while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA) {
         fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;
    }

     CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}*/

// // -----------------------Comeco da Camada Receptora-----------------------

// void CamadaFisicaReceptora (uint8_t quadro[]) {
//     int tipoDeCodificacao = 0;
//     int fluxoBrutoDeBits[BIT_TRAIN_SIZE];

//     switch (tipoDeCodificacao) {
//         case 0:
//             fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
//             break;
//         case 1:
//             fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
//             break;
//         case 2:
//             fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
//             break;
//     }

//     CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
// };

// int[] CamadaFisicaReceptoraCodificacaoManchester (uint8_t quadro[]) {
//     //algoritmo de DECODIFICACAO
// };
// int[] CamadaFisicaReceptoraCodificacaoBipolar(uint8_t quadro[]) {
//     //algoritmo de DECODIFICACAO
// };
// int[] CamadaFisicaReceptoraCodificacaoBinaria (uint8_t quadro[]) {
//     //algoritmo de DECODIFICACAO
// };
// void CamadaDeAplicacaoReceptora(uint8_t quadro[]) {
//     //std::string mensagem = quadro[];

//     AplicacaoReceptora(mensagem_recebida);
// };

// void AplicacaoReceptora(std::string mensagem_recebida) {
//     std::cout << "A mensagem recebida foi:" << mensagem_recebida << std::endl;
// };

// // -----------------------Fim da Camada Receptora-----------------------
