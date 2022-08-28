#include <iostream>
#include <bitset>
#include "CamadaFisica.hpp"
#include <string>
using namespace std;

int main(void) {
    AplicacaoTransmissora();
    return 0;
};

// -----------------------Comeco da Camada Transmissora-----------------------

void AplicacaoTransmissora(void) {
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
};

void CamadaDeAplicacaoTransmissora(string mensagem) {
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
    int tipoDeCodificacao = 2;
    int *fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro, tamanho_quadro);
            MeioDeComunicacao(fluxoBrutoDeBits, tamanho_quadro * 8);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro, tamanho_quadro);
            MeioDeComunicacao(fluxoBrutoDeBits, tamanho_quadro * 8 * 2);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro, tamanho_quadro);
            MeioDeComunicacao(fluxoBrutoDeBits, tamanho_quadro * 8);
            break;
    }

};

int *CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[], int tamanho_quadro) {
    //multiplicamos por 8 pois o size retorna em bytes
    int fluxoBrutoDeBits[tamanho_quadro * 8];
    int contador = 0;
    for (int i = 0; i < tamanho_quadro; i++){
        string bin_char_str = bitset<8>(quadro[i]).to_string(); //transformar o algoritmo de ascii para binario
        for (int j = 0; j < 8; j++){
            //adicionando cada bit para o nosso array
            fluxoBrutoDeBits[contador] = bin_char_str[j] - 48;
            contador++;
        }
    }
    return fluxoBrutoDeBits;
    //algoritmo de CODIFICACAO
};

int *CamadaFisicaTransmissoraCodificacaoManchester(int quadro[], int tamanho_quadro) {
    int fluxoBrutoDeBits[tamanho_quadro * 8 * 2];
    int contador = 0;
    for (int i = 0; i < tamanho_quadro; i++){
        string bin_char_str = bitset<8>(quadro[i]).to_string(); //transformar o algoritmo de ascii para binario
        for (int j = 0; j < 8; j++){
            fluxoBrutoDeBits[contador] = (bin_char_str[j] ^ 0) - 48; // clock = 0
            contador++;
            fluxoBrutoDeBits[contador] = (bin_char_str[j] ^ 1) - 48; // clock = 1
            contador++;
        }
    }
    return fluxoBrutoDeBits;
    //algoritmo de CODIFICACAO
};

int *CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[], int tamanho_quadro) {
    int fluxoBrutoDeBits[tamanho_quadro * 8];
    int contador = 0;
    int polaridade = 0;
    for (int i = 0; i < tamanho_quadro; i++) {
        string bin_char_str = bitset<8>(quadro[i]).to_string(); //transformar o algoritmo de ascii para binario
        for (int j = 0; j < 8; j++) {
            if ((bin_char_str[j] - 48) == 0) {
                fluxoBrutoDeBits[contador] = 0;
            }
            else {
                switch (polaridade) {
                    case 0:
                        fluxoBrutoDeBits[contador] = 1;
                        polaridade = 1;
                        break;
                    case 1:
                        fluxoBrutoDeBits[contador] = -1;
                        polaridade = 0;
                        break;
                }
            }
            contador++;
        }
    }
    return fluxoBrutoDeBits;
    //algoritmo de CODIFICACAO
};

// -----------------------Fim da Camada Transmissora-----------------------

void MeioDeComunicacao(int fluxoBrutoDeBits[], int tamanhoFluxoBrutoDeBits) {
    int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

     fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

     while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA) {
         fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;
    }

     CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

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
//     //string mensagem = quadro[];

//     AplicacaoReceptora(mensagem_recebida);
// };

// void AplicacaoReceptora(string mensagem_recebida) {
//     cout << "A mensagem recebida foi:" << mensagem_recebida << endl;
// };

// // -----------------------Fim da Camada Receptora-----------------------
