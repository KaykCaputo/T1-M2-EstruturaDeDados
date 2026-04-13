#ifndef CALCULADORA_LOGIC_H
#define CALCULADORA_LOGIC_H

#include "pilha.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Calculadora {
    Pilha<double> historico;
    bool inicializada;
};

string limparEConverter(string str) {
    string resultado = "";
    for (char c : str) {
        if (c != ' ') resultado += toupper(c);
    }
    return resultado;
}

bool extrairValor(string entrada, double &valor) {
    try {
        size_t start = entrada.find('(');
        size_t end = entrada.find(')');
        if (start != string::npos && end != string::npos) {
            string numStr = entrada.substr(start + 1, end - start - 1);
            valor = stod(numStr);
            return true;
        }
    } catch (...) {}
    return false;
}

void processarComando(Calculadora &calc, string linha) {
    string entradaLimpa = limparEConverter(linha);

    if (entradaLimpa == "INICIO") {
        calc.inicializada = true;
        criar(calc.historico);
        return;
    }

    if (!calc.inicializada) {
        if (entradaLimpa != "FIM") cout << "** COMANDO INVALIDO **" << endl;
        return;
    }

    if (entradaLimpa == "ZERA") {
        destruir(calc.historico);
        empilhar(calc.historico, 0.0);
    }
    else if (entradaLimpa == "IGUAL") {
        if (!estaVazia(calc.historico))
            cout << fixed << setprecision(2) << recuperarTopo(calc.historico) << endl;
    }
    else if (entradaLimpa == "PARCELAS") {
        if (estaVazia(calc.historico)) {
            cout << "Sem parcelas." << endl;
        } else {
            int total = calc.historico.quantidade;
            for (int i = total; i >= 1; i--) {
                double v = recuperarPosicao(calc.historico, i);
                if (v != 0) cout << fixed << setprecision(2) << v << (i > 1 ? ", " : "");
            }
            cout << endl;
        }
    }
    else {
        double valor;
        double atual = estaVazia(calc.historico) ? 0 : recuperarTopo(calc.historico);

        if (!extrairValor(entradaLimpa, valor)) {
            cout << "** COMANDO INVALIDO **" << endl;
            return;
        }

        if (entradaLimpa.find("SOMA") == 0) empilhar(calc.historico, atual + valor);
        else if (entradaLimpa.find("SUBTRAI") == 0) empilhar(calc.historico, atual - valor);
        else if (entradaLimpa.find("MULTIPLICA") == 0) empilhar(calc.historico, atual * valor);
        else if (entradaLimpa.find("DIVIDE") == 0) {
            if (valor != 0) empilhar(calc.historico, atual / valor);
            else cout << "** ERRO: DIVISAO POR ZERO **" << endl;
        }
        else cout << "** COMANDO INVALIDO **" << endl;
    }
}

#endif
