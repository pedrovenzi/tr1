//adicionando bibliotecas necessarias;
#include <iostream>
#include <bitset>
#include "CamadaFisica.hpp"
#include <string>
#include <vector>
using namespace std;

//variavel global utilizada para definir qual será codificacao usada;
int tipoDeCodificacao;

// -----------------------Comeco da Camada Transmissora-----------------------

void AplicacaoTransmissora(void) {

    //captando mensagem a ser transmitida por meio do getline;
    string mensagem_transmitida;
    cout << "Digite uma mensagem:" << endl;
    getline(cin, mensagem_transmitida);

    //captando qual sera a codificacao usada por meio do cin;
    cout << "Selecione o tipo de codificacao (0 - Binaria, 1 - Manchester, 2 - Bipolar): " << endl;
    cin >> tipoDeCodificacao;

    cout << "Mensagem a ser transmitida: " << mensagem_transmitida << endl;
    cout << "-> Chamando Camada De Aplicacao Transmissora..." << endl;
    CamadaDeAplicacaoTransmissora(mensagem_transmitida);
};

void CamadaDeAplicacaoTransmissora(string mensagem_transmitida) {
    //declarando vetor quadro que irá guardar nossa mensagem_transmitida e variavel auxiliar bin_char;
    vector<int> quadro;
    int bin_char;

    //iterando nossa mensagem transmitida para o vetor com cada caractere passado como um inteiro da tabela ascii;
    for (int i = 0; i < mensagem_transmitida.size(); i++) {
        bin_char = int(mensagem_transmitida[i]);
        quadro.push_back(bin_char);
    }

    //imprimindo nosso quadro feito no loop acima;
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
    //declarado variavel vetor para guardar o fluxo de bits pós codificacao;
    vector<int> fluxoBrutoDeBits;

    //com base na codificacao escolhida pelo input, chamar a funcao desejada;
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
    //varaivel tipo vetor para guardar os bits pós codificacao;
    vector<int> fluxoBrutoDeBits;

    //Algoritmo de codificacao;
    for (int i = 0; i < (quadro.size()); i++){
        //transformar o algoritmo de ascii para binario;
        string bin_char_str = bitset<8>(quadro[i]).to_string(); 
        for (int j = 0; j < 8; j++){
            //adicionando cada bit para o nosso array fluxoBrutoDeBits;
            fluxoBrutoDeBits.push_back(bin_char_str[j] - 48);
        }
    }

    //imprimindo na tela o fluxo de bits pós codificacao;
    cout << "   Fluxo Bruto de Bits Resultante da Codificacao Binaria: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBits) {
        cout << sinal;
    }
    cout << endl << endl;

    //retornando o fluxo de bits pós codificacao;
    return fluxoBrutoDeBits;
};

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro) {
    //varaivel tipo vetor para guardar os bits pós codificacao;
    vector<int> fluxoBrutoDeBits;

    //algoritmo de codificacao;
    for (int i = 0; i < (quadro.size()); i++){;
        //transformar o algoritmo de ascii para binario
        string bin_char_str = bitset<8>(quadro[i]).to_string(); 
        for (int j = 0; j < 8; j++){
            //adicionando os bits para o nosso array fluxoBrutoDeBits;
            fluxoBrutoDeBits.push_back((bin_char_str[j] ^ 0) - 48); // clock = 0
            fluxoBrutoDeBits.push_back((bin_char_str[j] ^ 1) - 48); // clock = 1
        }
    }
    //imprimindo na tela o fluxo de bits pós codificacao;
    cout << "   Fluxo Bruto de Bits Resultante da Codificacao Manchester: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBits) {
        cout << sinal;
    }
    cout << endl << endl;

    //retornando o fluxo de bits pós codificacao;
    return fluxoBrutoDeBits;
};

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro) {
    //varaivel tipo vetor para guardar os bits pós codificacao e variavel auxiliar para inversão polaridade;
    vector<int> fluxoBrutoDeBits;
    int polaridade = 0;

    //algoritmo de codificacao;
    for (int i = 0; i < (quadro.size()); i++) {
        //transformar o algoritmo de ascii para binario;
        string bin_char_str = bitset<8>(quadro[i]).to_string(); 
        //adicionando os bits para o nosso array fluxoBrutoDeBits;
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

    //imprimindo na tela o fluxo de bits pós codificacao;
    cout << "   Fluxo Bruto de Bits Resultante da Codificacao Bipolar: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBits) {
        cout << sinal;
    }
    cout << endl << endl;

    //retornando o fluxo de bits pós codificacao;
    return fluxoBrutoDeBits;
};

// -----------------------Fim da Camada Transmissora-----------------------

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) {
    //varaiveis do tipo vetor para simular a ida dos bits de um ponto para outro;
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    //imprimindo bits que estao no ponto A;
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    cout << "   Fluxo Bruto de Bits no ponto A: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBitsPontoA) {
        cout << sinal;
    }
    cout << endl << endl;

    //Passando cada bit presente no ponto A para o nosso vetor simulando ponto B;
    cout << "   Transferindo Bits de A para B... " << endl << endl;
    for (int i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
         fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
    }

    //imprimindo bits que estao no ponto A;
    cout << "   Fluxo Bruto de Bits no ponto B: " << endl;
    cout << "   ";
    for (int sinal : fluxoBrutoDeBitsPontoB) {
        cout << sinal;
    }
    cout << endl << endl;

    cout << "-> Chamando Camada Fisica Receptora..." << endl << endl;
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

// -----------------------Comeco da Camada Receptora-----------------------

//funcao que vai receber o fluxo bruto de bits e decodifica-lo;
void CamadaFisicaReceptora (vector<int> fluxoBrutoDeBits) {
    //variavel auxiliar para guardar o resultado da decodificacao;
     vector<int> quadro;

    //decodificando com base na codificacao escolhida;
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
    //variaveis auxiliares para processo de decodificacao;
    string bin_char_str;
    vector<int> quadro;

    //algoritmo de DECODIFICACAO;
    for (int i = 0; i < (fluxoBrutoDeBits.size() / 8); i++) {
        for (int j = 0; j < 8; j++) {
            bin_char_str += (fluxoBrutoDeBits[j + (i * 8)] + 48);
        }
        //transformando sequencia de bits em numeros inteiros;
        ulong bin_char_int = bitset<8>(bin_char_str).to_ulong();
        quadro.push_back(bin_char_int);
        bin_char_str = "";
    }

    //imprimindo quadro resultante da decodificacao;
    cout << "   Quadro Resultante da Decodificacao Binaria: " << endl;
    cout << "   ";
    for (int bit : quadro) {
        bitset<8> bin_char_code(bit);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    //retornando quadro pós decodificacao;
    return quadro;
};
vector<int> CamadaFisicaReceptoraDecodificacaoManchester(vector<int>  fluxoBrutoDeBits) {
    //variaveis auxiliares para processo de decodificacao;
    string bin_char_str;
    string bin_pair;
    vector<int> quadro;

    //algoritmo de DECODIFICACAO;
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
        //transformando sequencia de bits em numeros inteiros;
        ulong bin_char_int = bitset<8>(bin_char_str).to_ulong();
        quadro.push_back(bin_char_int);
        bin_char_str = "";
    }

    //imprimindo quadro resultante da decodificacao;
    cout << "   Quadro Resultante da Decodificacao Manchester: " << endl;
    cout << "   ";
    for (int bit : quadro) {
        bitset<8> bin_char_code(bit);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    //retornando quadro pós decodificacao
    return quadro;
};
vector<int> CamadaFisicaReceptoraDecodificacaoBipolar(vector<int>  fluxoBrutoDeBits) {
    //variaveis auxiliares para processo de decodificacao
    string bin_char_str;
    int bin_unsigned;
    vector<int> quadro;

     //algoritmo de decodificacao;
    for (int i = 0; i < (fluxoBrutoDeBits.size() / 8); i++) {
        for (int j = 0; j < 8; j++) {
            bin_unsigned = fluxoBrutoDeBits[j + (i * 8)];
            if (bin_unsigned == -1) {
                bin_unsigned = 1;
            }
            bin_char_str += (bin_unsigned + 48);
        }
        //transformando sequencia de bits em numeros inteiros;
        ulong bin_char_int = bitset<8>(bin_char_str).to_ulong();
        quadro.push_back(bin_char_int);
        bin_char_str = "";
    }

    //imprimindo quadro resultante da decodificacao;
    cout << "   Quadro Resultante da Decodificacao Bipolar: " << endl;
    cout << "   ";
    for (int bit : quadro) {
        bitset<8> bin_char_code(bit);
        cout << bin_char_code << " ";
    }
    cout << endl << endl;

    //retornando quadro pós decodificacao;
    return quadro;
};


void CamadaDeAplicacaoReceptora(vector<int> quadro) {
    string mensagem_recebida;
    string bin_char;

    //imprimindo mensagem decodificada utilizando ascii;
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
    //imprimindo mensagem recebida pós decodificacao;
    cout << "  A mensagem recebida foi: " << mensagem_recebida << endl;
    cout << "  Processo finalizado." << endl;
};


// -----------------------Fim da Camada Receptora-----------------------
