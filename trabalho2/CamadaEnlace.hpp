//
// Created by pedrovenzi on 13/09/22.
//

#ifndef TRABALHO2_CAMADAENLACE_HPP
#define TRABALHO2_CAMADAENLACE_HPP
#include <vector>
#include <string>
using namespace std;

#endif //TRABALHO2_CAMADAENLACE_HPP

extern int bitParidade;
extern string crc;
//variavel global utilizada para definir qual será o tipo de enquadramento usado;
extern int tipoDeEnquadramento;
//variavel global utilizada para definir qual será o tipo de controle de erro usado;
extern int tipoDeControleDeErro;

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidade (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro);
void CamadaEnlaceDadosTransmissora (vector<int> quadro);
//
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidade (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro);
void CamadaEnlaceDadosReceptora (vector<int> quadro);