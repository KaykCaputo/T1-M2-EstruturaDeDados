#include <iostream>
#include <string>
#include "calculadora_logic.h"

using namespace std;

int main() {
    Calculadora calc;
    calc.inicializada = false;
    string linha;

    cout << "=== EDITOR DE EXPRESSOES ARITMETICAS ===\n";
    cout << "Digite os comandos (INICIO para comecar, FIM para sair):\n\n";
    cout << "Comandos: \nSOMA(X)\nSUBTRAI(X)\nDIVIDE(X)\nMULTIPLICA(X)\nPARCELAS\nIGUAL\nZERA \n\n";

    while (getline(cin, linha)) {
        if (limparEConverter(linha) == "FIM") break;
        processarComando(calc, linha);
    }

    if (calc.inicializada) {
        destruir(calc.historico);
    }

    cout << "\nPrograma finalizado.\n";
    return 0;
}
