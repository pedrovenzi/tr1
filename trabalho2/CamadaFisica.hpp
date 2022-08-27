//
// Created by pedrovenzi on 26/08/22.
//

#ifndef TRABALHO2_CAMADAFISICA_HPP
#define TRABALHO2_CAMADAFISICA_HPP

#endif //TRABALHO2_CAMADAFISICA_HPP

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(std::string mensagem);
void CamadaFisicaTransmissora(uint8_t quadro[]);
int *CamadaFisicaTransmissoraCodificacaoBinaria(uint8_t quadro[]);
int *CamadaFisicaTransmissoraCodificacaoManchester(uint8_t quadro[]);
int *CamadaFisicaTransmissoraCodificacaoBipolar(uint8_t quadro[]);

// void MeioDeComunicacao (int fluxoBrutoDeBits[]);

// void CamadaFisicaReceptora (uint8_t quadro[]);
// int[] CamadaFisicaReceptoraCodificacaoManchester (uint8_t quadro[]);
// int[] CamadaFisicaReceptoraCodificacaoBipolar(uint8_t quadro[]);
// int[] CamadaFisicaReceptoraCodificacaoBinaria (uint8_t quadro[]);
// void CamadaDeAplicacaoReceptora(uint8_t quadro[]);
// void AplicacaoReceptora(std::string mensagem_recebida);
