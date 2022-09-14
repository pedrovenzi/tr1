//
// Created by pedrovenzi on 13/09/22.
//

#ifndef TRABALHO2_CAMADAENLACE_HPP
#define TRABALHO2_CAMADAENLACE_HPP
#include <vector>
#include <string>
using namespace std;

#endif //TRABALHO2_CAMADAENLACE_HPP

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro);
void CamadaEnlaceDadosTransmissora (vector<int> quadro);

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro);
void CamadaEnlaceDadosReceptora (vector<int> quadro);