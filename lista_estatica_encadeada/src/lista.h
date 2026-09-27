#ifndef LISTA_H
#define LISTA_H

#include <stddef.h>

constexpr size_t LISTA_CAPACIDADE = 8;

struct elemento {
    int chave;
    int value;
};

struct nodo {
    struct elemento elemento;
    size_t proximo;
};

struct lista {
    struct nodo nodos[LISTA_CAPACIDADE];
    size_t inicio;
    size_t disponivel;
};

void elemento_exibir(const struct elemento *elemento);

void lista_iniciar(struct lista *lista);

void lista_destruir(struct lista *lista);

bool lista_is_vazia(const struct lista *lista);

bool lista_inserir_inicio(struct lista *lista, const struct elemento *elemento);

bool lista_inserir_final(struct lista *lista, const struct elemento *elemento);

bool lista_inserir_ordenado(struct lista *lista,
                            const struct elemento *elemento);

bool lista_remover_indice(struct lista *lista, size_t indice);

bool lista_remover_elemento(struct lista *lista, int chave);

bool lista_remover_inicio(struct lista *lista);

bool lista_remover_final(struct lista *lista);

void lista_exibir(const struct lista *lista);

bool lista_indice_de(const struct lista *lista, int chave, size_t *indice);

const struct elemento *lista_buscar(const struct lista *lista, int chave);

size_t lista_tamanho(const struct lista *lista);

size_t lista_tamanho_recursivo(const struct lista *lista);

const struct elemento *lista_buscar_recursivo(const struct lista *lista,
                                              int chave);

void lista_exibir_recursivo(const struct lista *lista);

void lista_exibir_inverso_recursivo(const struct lista *lista);

size_t lista_contar_maiores(const struct lista *lista, int chave);

size_t lista_contar_maiores_recursivo(const struct lista *lista, int chave);

#endif
