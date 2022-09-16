//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"
#include <string>
#include <vector>
using namespace std;

//variavel global utilizada para definir qual será o tipo de enquadramento usado;
int tipoDeEnquadramento = 0;

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

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidade (vector<int> quadro) {
    int somaQuadro = 0;

    for (int i = 0; i < quadro.size(); i++) {
        somaQuadro += quadro[i];
        //transformar em bit? aqui ta somando o byte. nao importa pra soma, mas talvez importe pro insert
    }

    quadro.insert(quadro.end(), (somaQuadro % 2));
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (vector<int> quadro) {
    int polinomioGerador = 9; // 1001 - comeca e termina com bit 1
    //string polinomioStr = bitset<4>(polinomioGerador).to_string();

    //divisao com XOR

}

void CamadaEnlaceDadosTransmissoraControleDeErro (vector<int> quadro) {
    int tipoDeControleDeErro = 0;
    vector<int> quadroControlado;

    switch (tipoDeControleDeErro) {
        case 0:
            quadroControlado = CamadaEnlaceDadosTransmissoraControleDeErroBitDeParidade(quadro);
            break;
        case 1:
            quadroControlado = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);

    }
}

void CamadaEnlaceDadosTransmissora (vector<int> quadro) {
    vector<int> quadroEnquadrado;

    quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    //CamadaEnlaceDadosTransmissoraControleDeErro(quadro)

    CamadaFisicaTransmissora(quadroEnquadrado);
}

// -----------------------Camada Receptora-----------------------

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro) {
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

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro) {


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
    int polinomioGerador = 9; // 1001 - comeca e termina com bit 1
    //string polinomioStr = bitset<4>(polinomioGerador).to_string();

    //divisao com XOR

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

    CamadaDeAplicacaoReceptora(quadroDesenquadrado)
}