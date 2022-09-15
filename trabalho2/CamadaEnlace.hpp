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
vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);
//void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro);
void CamadaEnlaceDadosTransmissora (vector<int> quadro);
//
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);
//void CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro);
void CamadaEnlaceDadosReceptora (vector<int> quadro);