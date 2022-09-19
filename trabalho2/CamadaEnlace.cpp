//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

//variavel global utilizada para definir bit de paridade;
int bitParidade = -1; //Para que saibamos que não utilizamos o controle de erro por bit de paridade, definimos como -1;
//variavel global utilizada para definir CRC;
string crc = "";

// -----------------------Camada Transmissora-----------------------

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {
    //adicionando a quantidade de caracteres no inicio do nosso vetor
    quadro.insert(quadro.begin(), quadro.size());

    return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {
    vector<int> quadroCorrigido;


    //Algoritmo de Enquadramento
    //Codigo DLE = 16, Codigo ESC = 27
    for (int i = 0; i < (quadro.size()); i++) {
        if (quadro[i] == 27 | quadro[i] == 16) {
            quadroCorrigido.push_back(27); //codigo ASCII ESC
        }
        quadroCorrigido.push_back(quadro[i]);
    }

    // Insercao de Bytes (Flags)
    quadroCorrigido.insert(quadroCorrigido.begin(), 16);
    quadroCorrigido.insert(quadroCorrigido.end(), 16);

    return quadroCorrigido;

}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (vector<int> quadro) {
    vector<int> quadroEnquadrado;
    //com base no enquadramento escolhida pelo input, chamar a funcao desejada;
    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    return quadroEnquadrado;
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidade (vector<int> quadro) {
    int somaQuadro = 0;

    //algoritmo para identificar paridade

    for (int i = 0; i < quadro.size(); i++) {
        somaQuadro += quadro[i];
    }
    //se quantidade de '1' for par retorna zero, se impar retorna 1
    bitParidade = somaQuadro % 2;
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro) {
    ulong polinomioGerador = 4374732215; // polinomio gerador CRC-32
    string polinomioStr = bitset<33>(polinomioGerador).to_string();
    string quadroCompleto = "";
    string resto = "";

    //inversão de todos os bytes do nosso quadro
    for (int i = 0; i < quadro.size(); i++) {
        string binchar = bitset<8>(quadro[i]).to_string();
        for (int j = 0; j < (binchar.length() / 2); j++){
            swap(binchar[j], binchar[binchar.length() - j - 1]);
        }
        quadroCompleto += binchar;
    }

    //adicao de 32 bits '0' no final do nosso dado
    quadroCompleto += "00000000000000000000000000000000";
    cout << quadroCompleto << endl;

    //'xor' (ou invertido) dos 4 primeiros bytes com o 0xFFFFFFFF
    for (int i = 0; i < 32; i++) {
        quadroCompleto[i] = (quadroCompleto[i]^1);
    }

    //divisao do dado utilizando o polinomio gerador do crc-32.
    //Caso nosso dado comece com zero no momento da divisão, ele é ignorado. Caso contrario segue o algoritmo abaixo
    //Essa divisã é feita com xor
    for (int i = 0; i < (quadroCompleto.size() - 33); i++) {
        if (quadroCompleto[i] != '0') {
            resto = quadroCompleto.substr(i, 33);
            for (int j = 0; j < 33; j++) {
                resto[j] = (resto[j] ^ (polinomioStr[j] - 48));
            }
            quadroCompleto.replace(i, 33, resto);
        }
    }

    resto = quadroCompleto.substr(quadroCompleto.size() - 32, 32);
    cout << resto << endl;

    //flip dos bits
    for (int i = 0; i < 32; i++) {
        resto[i] = (resto[i]^1);
    }

    //reverter todos os bits
    for (int j = 0; j < (resto.length() / 2); j++){
        swap(resto[j], resto[resto.length() - j - 1]);
    }

    crc = resto;

}

void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro) {
    //com base no tipo de controle de erro escolhida pelo input, chamar a funcao desejada;
    switch (tipoDeControleDeErro) {
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidade(quadro);
            break;
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
    }
}

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
    vector<int> quadroEnquadrado;
    vector<int> quadroControlado;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);

    CamadaFisicaTransmissora(quadroEnquadrado);
}

// -----------------------Camada Receptora-----------------------

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {
    //Verificar existencia de erro utilizando a contagem de caracteres como enquadramento
    try{
        if (quadro.size() != (quadro[0] + 1)){
            throw 404;
        }
    }
    catch(int e){
        cout << "Tamanho quadro errado" << e << endl;
    }
    //algoritmo de desenquadramento
    vector<int> quadroDescontado = {quadro.begin() + 1, quadro.end()};
    return quadroDescontado;
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {
    vector<int> quadroDesenquadrado;
    int indexQuadro = 0;

    //Verificar existencia de erro utilizando o inserção de bytes como enquadramento e 'desenquadrar'
    //Algoritmo de Desequadramento
    //Codigo DLE = 16, Codigo ESC = 27
    try{
        if (quadro[0] == 16) {
            indexQuadro++;

            while (true) {
                if (quadro[indexQuadro] == 16) {
                    break;
                } else if (quadro[indexQuadro] == 27) {
                    indexQuadro += 2;
                } else {
                    quadroDesenquadrado.push_back(quadro[indexQuadro]);
                    indexQuadro++;
                }
            }
        }
        else {
            throw 404;
        }
    }
    catch(int e){
        cout << "Tamanho quadro errado" << e << endl;
    }
    return quadroDesenquadrado;
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro) {
    vector<int> quadroDesenquadrado;
    //com base no tipo de enquadramento escolhida pelo input, chamar a funcao desejada para desenquadramento;
    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }

    return quadroDesenquadrado;
}
vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidade (vector<int> quadro) {
    //variaveis auxliares para essa funcao
    int somaQuadro = 0;
    int bitCorrecao;

    // algoritmo para verificar a existências de erro no bit de paridade
    for (int i = 0; i < quadro.size(); i++) {
        somaQuadro += quadro[i];
    }

    bitCorrecao = somaQuadro % 2;

    if (bitCorrecao != bitParidade) {
        cout << "Erro: Bit de paridade incompatível" << endl;
    }
    else {
        return quadro;
    }
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro) {
    ulong polinomioGerador = 4374732215; // CRC-32
    string polinomioStr = bitset<33>(polinomioGerador).to_string();
    string quadroCompleto = "";
    string resto = "";
    string crc_check = "";
    vector<int> subvector = {quadro.begin(), quadro.end() - 4};

    //inversão de todos os bytes do nosso quadro
    for (int i = 0; i < (quadro.size() - 4); i++) {
        string binchar = bitset<8>(quadro[i]).to_string();
        for (int j = 0; j < (binchar.length() / 2); j++){
            swap(binchar[j], binchar[binchar.length() - j - 1]);
        }
        quadroCompleto += binchar;
    }

    quadroCompleto += "00000000000000000000000000000000";
    cout << quadroCompleto << endl;

    for (int i = 0; i < 32; i++) {
        quadroCompleto[i] = (quadroCompleto[i]^1);
    }

    //divisao do dado utilizando o polinomio gerador do crc-32.
    //Caso nosso dado comece com zero no momento da divisão, ele é ignorado. Caso contrario segue o algoritmo abaixo
    //Essa divisã é feita com xor
    for (int i = 0; i < (quadroCompleto.size() - 33); i++) {
        if (quadroCompleto[i] != '0') {
            resto = quadroCompleto.substr(i, 33);
            for (int j = 0; j < 33; j++) {
                resto[j] = (resto[j] ^ (polinomioStr[j] - 48));
            }
            quadroCompleto.replace(i, 33, resto);
        }
    }

    resto = quadroCompleto.substr(quadroCompleto.size() - 32, 32);
    cout << resto << endl;

    //flip dos bits
    for (int i = 0; i < 32; i++) {
        resto[i] = (resto[i]^1);
    }

    //revertendo os bits
    for (int j = 0; j < (resto.length() / 2); j++){
        swap(resto[j], resto[resto.length() - j - 1]);
    }

    crc = bitset<8>(quadro[quadro.size() - 4]).to_string() + bitset<8>(quadro[quadro.size() - 3]).to_string()
            + bitset<8>(quadro[quadro.size() - 2]).to_string() + bitset<8>(quadro[quadro.size() - 1]).to_string();

    crc_check = resto;

    //verificacao se o crc está correto
    if (crc == crc_check){
        return subvector;
    }
    else {
        cout << "Erro na checagem do CRC" << endl;
    }

}

vector<int> CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro) {
    vector<int> quadroChecado;
    //com base no tipo de controle de erro escolhido pelo input, chamar a funcao desejada;
    switch (tipoDeControleDeErro) {
        case 0:
            quadroChecado = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidade(quadro);
            break;
        case 1:
            quadroChecado = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            break;
    }

    return quadroChecado;
}

void CamadaEnlaceDadosReceptora (vector<int> quadro) {
    vector<int> quadroDesenquadrado;
    vector<int> quadroChecado;

    quadroChecado = CamadaEnlaceDadosReceptoraControleDeErro(quadro);

    quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadroChecado);

    CamadaDeAplicacaoReceptora(quadroDesenquadrado);
}