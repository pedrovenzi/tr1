//
// Created by pedrovenzi on 26/08/22.
//

#ifndef TRABALHO2_CAMADAFISICA_HPP
#define TRABALHO2_CAMADAFISICA_HPP
using namespace std;

#endif //TRABALHO2_CAMADAFISICA_HPP

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(int quadro[], int tamanho_quadro);
int *CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[], int tamanho_quadro);
int *CamadaFisicaTransmissoraCodificacaoManchester(int quadro[], int tamanho_quadro);
int *CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[], int tamanho_quadro);

void MeioDeComunicacao(int fluxoBrutoDeBits[], int i);

// void CamadaFisicaReceptora (uint8_t quadro[]);
// int[] CamadaFisicaReceptoraCodificacaoManchester (uint8_t quadro[]);
// int[] CamadaFisicaReceptoraCodificacaoBipolar(uint8_t quadro[]);
// int[] CamadaFisicaReceptoraCodificacaoBinaria (uint8_t quadro[]);
// void CamadaDeAplicacaoReceptora(uint8_t quadro[]);
// void AplicacaoReceptora(string mensagem_recebida);
