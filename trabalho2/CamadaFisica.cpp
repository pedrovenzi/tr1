#include <iostream>
#include <bitset>
#include "CamadaFisica.hpp"
#include <string>
#include <vector>
using namespace std;

int tipoDeCodificacao;

// -----------------------Comeco da Camada Transmissora-----------------------

void AplicacaoTransmissora(void) {
    string mensagem_transmitida;
    cout << "Digite uma mensagem:" << endl;
    getline(cin, mensagem_transmitida);
    cout << "Selecione o tipo de codificacao (0 - Binaria, 1 - Manchester, 2 - Bipolar): " << endl;
    cin >> tipoDeCodificacao;

    cout << "Mensagem a ser transmitida: " << mensagem_transmitida << endl;
    cout << "-> Chamando Camada De Aplicacao Transmissora..." << endl;
    CamadaDeAplicacaoTransmissora(mensagem_transmitida);
};

void CamadaDeAplicacaoTransmissora(string mensagem_transmitida) {
    //int tamanho_quadro = mensagem_transmitida.size();
    vector<int> quadro;
    int bin_char;

    for (int i = 0; i < mensagem_transmitida.size(); i++) {
        bin_char = int(mensagem_transmitida[i]);
        quadro.push_back(bin_char);
    }

    cout << "   Quadro montado em formato binário" << endl;
    cout << "   ";
    for (int char_code : quadro) {
        bitset<8> bin_char_code(char_code);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    cout << "-> Chamando Camada Fisica Transmissora..." << endl << endl;
    CamadaFisicaTransmissora(quadro);
};

void CamadaFisicaTransmissora (vector<int> quadro) {
    vector<int> fluxoBrutoDeBits;

    switch (tipoDeCodificacao) {
        case 0:
            cout << "-> Chamando Codificacao Binaria..." << endl;
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            cout << "-> Chamando Codificacao Manchester..." << endl;
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            cout << "-> Chamando Codificacao Bipolar..." << endl;
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }

    cout << "-> Chamando Meio De Comunicacao..." << endl;
    MeioDeComunicacao(fluxoBrutoDeBits);
};

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro) {
    //multiplicamos por 8 pois o size retorna em bytes
    vector<int> fluxoBrutoDeBits;

    for (int i = 0; i < (quadro.size()); i++){
        string bin_char_str = bitset<8>(quadro[i]).to_string(); //transformar o algoritmo de ascii para binario
        for (int j = 0; j < 8; j++){
            //adicionando cada bit para o nosso array
            fluxoBrutoDeBits.push_back(bin_char_str[j] - 48);
        }
    }

    cout << "   Fluxo Bruto de Bits Resultante da Codificacao Binaria: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBits) {
        cout << sinal;
    }
    cout << endl << endl;

    return fluxoBrutoDeBits;
    //algoritmo de CODIFICACAO
};

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
    vector<int> fluxoBrutoDeBits;

    for (int i = 0; i < (quadro.size()); i++){
        string bin_char_str = bitset<8>(quadro[i]).to_string(); //transformar o algoritmo de ascii para binario
        for (int j = 0; j < 8; j++){
            fluxoBrutoDeBits.push_back((bin_char_str[j] ^ 0) - 48); // clock = 0
            fluxoBrutoDeBits.push_back((bin_char_str[j] ^ 1) - 48); // clock = 1
        }
    }

    cout << "   Fluxo Bruto de Bits Resultante da Codificacao Manchester: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBits) {
        cout << sinal;
    }
    cout << endl << endl;

    return fluxoBrutoDeBits;
    //algoritmo de CODIFICACAO
};

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
    vector<int> fluxoBrutoDeBits;
    int polaridade = 0;

    for (int i = 0; i < (quadro.size()); i++) {
        string bin_char_str = bitset<8>(quadro[i]).to_string(); //transformar o algoritmo de ascii para binario
        for (int j = 0; j < 8; j++) {
            if ((bin_char_str[j] - 48) == 0) {
                fluxoBrutoDeBits.push_back(0);
            }
            else {
                switch (polaridade) {
                    case 0:
                        fluxoBrutoDeBits.push_back(1);
                        polaridade = 1;
                        break;
                    case 1:
                        fluxoBrutoDeBits.push_back(-1);
                        polaridade = 0;
                        break;
                }
            }
        }
    }

    cout << "   Fluxo Bruto de Bits Resultante da Codificacao Bipolar: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBits) {
        cout << sinal;
    }
    cout << endl << endl;

    return fluxoBrutoDeBits;
    //algoritmo de CODIFICACAO
};

// -----------------------Fim da Camada Transmissora-----------------------

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) {
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    cout << "   Fluxo Bruto de Bits no ponto A: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBitsPontoA) {
        cout << sinal;
    }
    cout << endl << endl;

    cout << "   Transferindo Bits de A para B... " << endl << endl;
    for (int i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
         fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
    }

    cout << "   Fluxo Bruto de Bits no ponto B: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBitsPontoA) {
        cout << sinal;
    }
    cout << endl << endl;

    cout << "-> Chamando Camada Fisica Receptora..." << endl << endl;
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

// -----------------------Comeco da Camada Receptora-----------------------

void CamadaFisicaReceptora (vector<int> fluxoBrutoDeBits) {
     vector<int> quadro;

     switch (tipoDeCodificacao) {
         case 0:
             cout << "-> Chamando Decodificacao Binaria..." << endl;
             quadro = CamadaFisicaReceptoraDecodificacaoBinaria(fluxoBrutoDeBits);
             break;
         case 1:
             cout << "-> Chamando Decodificacao Manchester..." << endl;
             quadro = CamadaFisicaReceptoraDecodificacaoManchester(fluxoBrutoDeBits);
             break;
         case 2:
             cout << "-> Chamando Decodificacao Bipolar..." << endl;
             quadro = CamadaFisicaReceptoraDecodificacaoBipolar(fluxoBrutoDeBits);
             break;
     }

     cout << "-> Chamando Camada De Aplicacao Receptora..." << endl;
     CamadaDeAplicacaoReceptora(quadro);
};

vector<int> CamadaFisicaReceptoraDecodificacaoBinaria(vector<int>  fluxoBrutoDeBits) {
    //algoritmo de DECODIFICACAO
    string bin_char_str;
    vector<int> quadro;

    for (int i = 0; i < (fluxoBrutoDeBits.size() / 8); i++) {
        for (int j = 0; j < 8; j++) {
            bin_char_str += (fluxoBrutoDeBits[j + (i * 8)] + 48);
        }
        ulong bin_char_int = bitset<8>(bin_char_str).to_ulong();
        quadro.push_back(bin_char_int);
        bin_char_str = "";
    }

    cout << "   Quadro Resultante da Decodificacao Binaria: " << endl;
    cout << "   ";
    for (int bit : quadro) {
        bitset<8> bin_char_code(bit);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    return quadro;
};
vector<int> CamadaFisicaReceptoraDecodificacaoManchester(vector<int>  fluxoBrutoDeBits) {
    //algoritmo de DECODIFICACAO
    string bin_char_str;
    string bin_pair;
    vector<int> quadro;

    for (int i = 0; i < (fluxoBrutoDeBits.size() / 16); i++) {
        for (int j = 0; j < 8; j++) {
            bin_pair += fluxoBrutoDeBits[(j * 2) + (i * 16)] + 48;
            bin_pair += fluxoBrutoDeBits[(j * 2) + 1 + (i * 16)] + 48;

            if (bin_pair == "01") {
                bin_char_str += "0";
            } else if (bin_pair == "10") {
                bin_char_str += "1";
            }

            bin_pair = "";
        }
        ulong bin_char_int = bitset<8>(bin_char_str).to_ulong();
        quadro.push_back(bin_char_int);
        bin_char_str = "";
    }

    cout << "   Quadro Resultante da Decodificacao Manchester: " << endl;
    cout << "   ";
    for (int bit : quadro) {
        bitset<8> bin_char_code(bit);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    return quadro;
};
vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(vector<int>  fluxoBrutoDeBits) {
     //algoritmo de DECODIFICACAO
    string bin_char_str;
    int bin_unsigned;
    vector<int> quadro;

    for (int i = 0; i < (fluxoBrutoDeBits.size() / 8); i++) {
        for (int j = 0; j < 8; j++) {
            bin_unsigned = fluxoBrutoDeBits[j + (i * 8)];
            if (bin_unsigned == -1) {
                bin_unsigned = 1;
            }
            bin_char_str += (bin_unsigned + 48);
        }
        ulong bin_char_int = bitset<8>(bin_char_str).to_ulong();
        quadro.push_back(bin_char_int);
        bin_char_str = "";
    }

    cout << "   Quadro Resultante da Decodificacao Bipolar: " << endl;
    cout << "   ";
    for (int bit : quadro) {
        bitset<8> bin_char_code(bit);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    return quadro;
};


void CamadaDeAplicacaoReceptora(vector<int> quadro) {
    string mensagem_recebida;
    string bin_char;

    cout << "   Mensagem montada de acordo com codificacao ASCII: " << endl;
    for (int i = 0; i < quadro.size(); i++) {
        bin_char = char(quadro[i]);
        mensagem_recebida += bin_char;
    }
    cout << "   " << mensagem_recebida << endl << endl;

    cout << "-> Chamando Camada De Aplicacao Receptora..." << endl;
    AplicacaoReceptora(mensagem_recebida);
 };

void AplicacaoReceptora(string mensagem_recebida) {
     cout << "  A mensagem recebida foi: " << mensagem_recebida << endl;
     cout << "  Processo finalizado." << endl;
};


// -----------------------Fim da Camada Receptora-----------------------
