#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <iostream>

using namespace std;

template <typename T>
struct No {
    T dado;
    No<T>* prox;
};

template <typename T>
struct Pilha {
    No<T>* topoPilha;
    int quantidade;
};

template <typename T>
void criar(Pilha<T> &p) {
    p.topoPilha = nullptr;
    p.quantidade = 0;
}

template <typename T>
bool estaVazia(const Pilha<T> &p) {
    return p.topoPilha == nullptr;
}

template <typename T>
void empilhar(Pilha<T> &p, T elemento) {
    No<T>* novo = new No<T>;
    novo->dado = elemento;
    novo->prox = p.topoPilha;
    p.topoPilha = novo;
    p.quantidade++;
}

template <typename T>
T desempilhar(Pilha<T> &p) {
    if (estaVazia(p)) throw "Pilha vazia.";

    No<T>* temp = p.topoPilha;
    T valor = temp->dado;
    p.topoPilha = p.topoPilha->prox;
    delete temp;
    p.quantidade--;
    return valor;
}

template <typename T>
void destruir(Pilha<T> &p) {
    while (!estaVazia(p)) {
        desempilhar(p);
    }
}

template <typename T>
T recuperarTopo(const Pilha<T> &p) {
    if (estaVazia(p)) throw "Pilha vazia.";
    return p.topoPilha->dado;
}

template <typename T>
T recuperarPosicao(const Pilha<T> &p, int pos) {
    if (pos < 1 || pos > p.quantidade) throw "Posicao inexistente.";

    No<T>* atual = p.topoPilha;
    for (int i = 1; i < pos; i++) {
        atual = atual->prox;
    }
    return atual->dado;
}

template <typename T>
bool existeElemento(const Pilha<T> &p, T elem) {
    No<T>* atual = p.topoPilha;
    while (atual != nullptr) {
        if (atual->dado == elem) return true;
        atual = atual->prox;
    }
    return false;
}

#endif
