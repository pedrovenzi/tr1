//
// Created by pedrovenzi on 26/08/22.
//

#ifndef TRABALHO2_CAMADAFISICA_HPP
#define TRABALHO2_CAMADAFISICA_HPP
#include <vector>
using namespace std;

#endif //TRABALHO2_CAMADAFISICA_HPP

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora (vector<int> fluxoBrutoDeBits);
vector<int> CamadaFisicaReceptoraDecodificacaoManchester (vector<int> fluxoBrutoDeBits);
vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(vector<int> fluxoBrutoDeBits);
vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (vector<int> fluxoBrutoDeBits);
void CamadaDeAplicacaoReceptora(vector<int> fluxoBrutoDeBits);
void AplicacaoReceptora(string mensagem_recebida);
