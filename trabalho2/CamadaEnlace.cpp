//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

//variavel global utilizada para definir qual será o tipo de enquadramento usado;
int tipoDeEnquadramento = 0;
//variavel global utilizada para definir qual será o tipo de controle de erro usado;
int tipoDeControleDeErro = 1;
//variavel global utilizada para definir bit de paridade;
int bitParidade = -1; //Para que saibamos que não utilizamos o controle de erro por bit de paridade, definimos como -1;
//variavel global utilizada para definir CRC;
string crc = "";

// -----------------------Camada Transmissora-----------------------

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {
    quadro.insert(quadro.begin(), quadro.size());

    return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {
    vector<int> quadroCorrigido;
    //vector<int>::iterator iteradorQuadro = quadro.begin();

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

    for (int i = 0; i < quadro.size(); i++) {
        somaQuadro += quadro[i];
        //transformar em bit? aqui ta somando o byte. nao importa pra soma, mas talvez importe pro insert
    }

    bitParidade = somaQuadro % 2;
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro) {
    ulong polinomioGerador = 4374732215; // CRC-32
    string polinomioStr = bitset<33>(polinomioGerador).to_string();
    string quadroCompleto = "";
    string resto = "";

    for (int i = 0; i < quadro.size(); i++) {
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

    for (int i = 0; i < 32; i++) {
        resto[i] = (resto[i]^1);
    }

    for (int j = 0; j < (resto.length() / 2); j++){
        swap(resto[j], resto[resto.length() - j - 1]);
    }

    crc = resto;

}

void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro) {

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

}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {
    vector<int> quadroDesenquadrado;
    int indexQuadro = 0;

    //Algoritmo de Desequadramento
    //Codigo DLE = 16, Codigo ESC = 27
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

        return quadroDesenquadrado;
    } else {
        cout << "Quadro não começa com flag designada." << endl;
    }
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramento (vector<int> quadro) {
    vector<int> quadroEnquadrado;

    switch (tipoDeEnquadramento) {
        case 0: //Contagem de Caracteres
            quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1: //Insercao de Byte
            quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
            break;
    }
}
vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidade (vector<int> quadro) {
    int somaQuadro = 0;

    for (int i = 0; i < quadro.size(); i++) {
        somaQuadro += quadro[i];
        //transformar em bit? aqui ta somando o byte. nao importa pra soma, mas talvez importe pro insert
    }

    if ((somaQuadro % 2) == quadro[quadro.size()]) {
        quadro.pop_back();
    } else {
        cout << "Erro: Bit de paridade incompatível" << endl;
    }

    return quadro;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (vector<int> quadro) {
    ulong polinomioGerador = 4374732215; // CRC-32
    string polinomioStr = bitset<33>(polinomioGerador).to_string();
    string quadroCompleto = "";
    string resto = "";
    string crc_check = "";

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

    for (int i = 0; i < 32; i++) {
        resto[i] = (resto[i]^1);
    }

    for (int j = 0; j < (resto.length() / 2); j++){
        swap(resto[j], resto[resto.length() - j - 1]);
    }

    crc = resto;

}

vector<int> CamadaEnlaceDadosReceptoraControleDeErro (vector<int> quadro) {
    int tipoDeControleDeErro = 0;
    vector<int> quadroChecado;

    switch (tipoDeControleDeErro) {
        case 0:
            quadroChecado = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidade(quadro);
            break;
        case 1:
            quadroChecado = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);

    }
}

void CamadaEnlaceDadosReceptora (vector<int> quadro) {
    vector<int> quadroDesenquadrado;

    quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro);

    //CamadaEnlaceDadosReceptoraControleDeErro(quadro)

    CamadaDeAplicacaoReceptora(quadroDesenquadrado);
}