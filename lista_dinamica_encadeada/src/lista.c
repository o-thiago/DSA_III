#include "lista.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void elemento_exibir(const struct elemento *elemento)
{
    if (!elemento) return;
    printf("[Chave: %d | Valor: %d]", elemento->chave, elemento->value);
}

void lista_iniciar(struct lista *lista)
{
    if (!lista) return;

    lista->inicio = nullptr;
}

void lista_destruir(struct lista *lista)
{
    if (!lista) return;

    while (lista->inicio) {
        struct nodo *removido = lista->inicio;
        lista->inicio = removido->proximo;
        free(removido);
    }
}

bool lista_is_vazia(const struct lista *lista)
{
    return !lista || !lista->inicio;
}

bool lista_inserir_inicio(struct lista *lista, const struct elemento *elemento)
{
    if (!lista || !elemento) return false;

    struct nodo *novo = malloc(sizeof(*novo));
    if (!novo) return false;

    struct nodo *inicio = lista->inicio;

    novo->elemento = *elemento;
    novo->proximo = inicio;

    lista->inicio = novo;
    return true;
}

bool lista_inserir_final(struct lista *lista, const struct elemento *elemento)
{
    if (!lista || !elemento) return false;

    struct nodo *novo = malloc(sizeof(*novo));
    if (!novo) return false;

    novo->proximo = nullptr;
    novo->elemento = *elemento;

    struct nodo **link = &lista->inicio;
    while (*link) link = &(*link)->proximo;
    *link = novo;

    return true;
}

bool lista_inserir_ordenado(struct lista *lista,
                            const struct elemento *elemento)
{
    if (!lista || !elemento) return false;

    struct nodo *novo = malloc(sizeof(*novo));
    if (!novo) return false;

    novo->proximo = nullptr;
    novo->elemento = *elemento;

    struct nodo **link = &lista->inicio;
    while (*link && (*link)->elemento.chave < elemento->chave)
        link = &(*link)->proximo;

    novo->proximo = *link;
    *link = novo;

    return true;
}

bool lista_remover_indice(struct lista *lista, const size_t indice)
{
    if (!lista) return false;

    size_t idx = 0;
    struct nodo **link = &lista->inicio;

    while (*link && idx < indice) {
        link = &(*link)->proximo;
        idx++;
    }

    if (!*link) return false;

    struct nodo *removido = *link;
    *link = removido->proximo;

    free(removido);
    return true;
}

bool lista_remover_elemento(struct lista *lista, const int chave)
{
    if (!lista) return false;

    struct nodo **link = &lista->inicio;
    while (*link && (*link)->elemento.chave != chave) link = &(*link)->proximo;

    if (!*link) return false;

    struct nodo *removido = *link;
    *link = removido->proximo;

    free(removido);
    return true;
}

bool lista_remover_inicio(struct lista *lista)
{
    return lista_remover_indice(lista, 0);
}

bool lista_remover_final(struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return false;

    struct nodo **link = &lista->inicio;
    while (*link && (*link)->proximo) link = &(*link)->proximo;

    struct nodo *removido = *link;
    *link = nullptr;

    free(removido);
    return true;
}

void lista_exibir(const struct lista *lista)
{
    if (!lista) return;

    size_t idx = 0;
    for (const struct nodo *atual = lista->inicio; atual;
         atual = atual->proximo) {
        printf("%zu: ", idx++);
        elemento_exibir(&atual->elemento);
        putchar('\n');
    }
}

const struct elemento *lista_buscar(const struct lista *lista, const int chave)
{
    if (!lista) return nullptr;

    for (const struct nodo *atual = lista->inicio; atual;
         atual = atual->proximo)
        if (atual->elemento.chave == chave) return &atual->elemento;

    return nullptr;
}

bool lista_indice_de(const struct lista *lista, const int chave, size_t *indice)
{
    if (!lista || !indice) return false;

    size_t pos = 0;
    for (const struct nodo *atual = lista->inicio; atual;
         atual = atual->proximo) {
        if (atual->elemento.chave == chave) {
            *indice = pos;
            return true;
        }

        pos++;
    }

    return false;
}

size_t lista_tamanho(const struct lista *lista)
{
    if (!lista) return 0;

    size_t tamanho = 0;
    for (const struct nodo *atual = lista->inicio; atual;
         atual = atual->proximo)
        tamanho++;

    return tamanho;
}

static size_t lista_tamanho_recursivo_aux(const struct nodo *atual,
                                          const size_t tamanho)
{
    if (!atual) return tamanho;

    return lista_tamanho_recursivo_aux(atual->proximo, tamanho + 1);
}

size_t lista_tamanho_recursivo(const struct lista *lista)
{
    if (!lista) return 0;
    return lista_tamanho_recursivo_aux(lista->inicio, 0);
}

static const struct elemento *
lista_buscar_recursivo_aux(const int chave, const struct nodo *atual)
{
    if (!atual) return nullptr;
    if (atual->elemento.chave == chave) return &atual->elemento;

    return lista_buscar_recursivo_aux(chave, atual->proximo);
}

const struct elemento *lista_buscar_recursivo(const struct lista *lista,
                                              const int chave)
{
    if (!lista) return nullptr;

    return lista_buscar_recursivo_aux(chave, lista->inicio);
}

static void lista_exibir_recursivo_linear_aux(const struct nodo *atual,
                                              const size_t idx)
{
    if (!atual) return;

    printf("%zu: ", idx);
    elemento_exibir(&atual->elemento);
    putchar('\n');

    lista_exibir_recursivo_linear_aux(atual->proximo, idx + 1);
}

void lista_exibir_recursivo(const struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return;

    lista_exibir_recursivo_linear_aux(lista->inicio, 0);
}

static void lista_exibir_recursivo_reverso_aux(const struct nodo *atual,
                                               const size_t idx)
{
    if (!atual) return;
    lista_exibir_recursivo_reverso_aux(atual->proximo, idx + 1);

    printf("%zu: ", idx);
    elemento_exibir(&atual->elemento);
    putchar('\n');
}

void lista_exibir_inverso_recursivo(const struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return;

    lista_exibir_recursivo_reverso_aux(lista->inicio, 0);
}

size_t lista_contar_maiores(const struct lista *lista, const int chave)
{
    if (!lista) return 0;

    size_t qt_maior = 0;
    for (const struct nodo *atual = lista->inicio; atual;
         atual = atual->proximo) {
        if (atual->elemento.chave > chave) qt_maior++;
    }

    return qt_maior;
}

static size_t lista_contar_maiores_recursivo_aux(const struct nodo *atual,
                                                 const int chave,
                                                 const size_t qt_maior)
{
    if (!atual) return qt_maior;

    const size_t novo_acc =
        qt_maior + ((size_t)(atual->elemento.chave > chave));

    return lista_contar_maiores_recursivo_aux(atual->proximo, chave, novo_acc);
}

size_t lista_contar_maiores_recursivo(const struct lista *lista,
                                      const int chave)
{
    if (!lista) return 0;
    return lista_contar_maiores_recursivo_aux(lista->inicio, chave, 0);
}
