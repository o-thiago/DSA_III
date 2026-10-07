#include "lista.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void elemento_exibir(const struct elemento *elemento)
{
    if (!elemento) return;
    printf("[Chave: %d | Valor: %d]", elemento->chave, elemento->value);
}

void lista_iniciar(struct lista *lista)
{
    if (!lista) return;
    *lista = (struct lista){};
}

void lista_destruir(struct lista *lista)
{
    lista_iniciar(lista);
}

bool lista_is_vazia(const struct lista *lista)
{
    return !lista || lista->tamanho_atual == 0;
}

bool lista_inserir_inicio(struct lista *lista, const struct elemento *elemento)
{
    if (!lista || lista->tamanho_atual >= LISTA_CAPACIDADE || !elemento)
        return false;

    memmove(&lista->dados[1], &lista->dados[0],
            lista->tamanho_atual * sizeof(lista->dados[0]));

    lista->dados[0] = *elemento;
    lista->tamanho_atual++;

    return true;
}

bool lista_inserir_final(struct lista *lista, const struct elemento *elemento)
{
    if (!lista || lista->tamanho_atual >= LISTA_CAPACIDADE || !elemento)
        return false;

    lista->dados[lista->tamanho_atual++] = *elemento;
    return true;
}

bool lista_inserir_ordenado(struct lista *lista,
                            const struct elemento *elemento)
{
    if (!lista || lista->tamanho_atual >= LISTA_CAPACIDADE || !elemento)
        return false;

    size_t lo = 0;
    size_t hi = lista->tamanho_atual;

    while (lo < hi) {
        const size_t mid = lo + ((hi - lo) / 2);
        if (lista->dados[mid].chave > elemento->chave)
            hi = mid;
        else
            lo = mid + 1;
    }

    const size_t pivot = lo;
    const size_t to_move = lista->tamanho_atual - pivot;
    if (to_move)
        memmove(&lista->dados[pivot + 1], &lista->dados[pivot],
                to_move * sizeof(lista->dados[0]));

    lista->dados[pivot] = *elemento;
    lista->tamanho_atual++;

    return true;
}

bool lista_remover_indice(struct lista *lista, const size_t indice)
{
    if (!lista || indice >= lista->tamanho_atual) return false;

    const size_t to_move = lista->tamanho_atual - 1 - indice;
    if (to_move)
        memmove(&lista->dados[indice], &lista->dados[indice + 1],
                to_move * sizeof(lista->dados[0]));

    lista->tamanho_atual--;
    return true;
}

bool lista_remover_elemento(struct lista *lista, const int chave)
{
    if (!lista) return false;

    size_t idx = 0;
    if (!lista_indice_de(lista, chave, &idx)) return false;

    return lista_remover_indice(lista, idx);
}

bool lista_remover_inicio(struct lista *lista)
{
    return lista_remover_indice(lista, 0);
}

bool lista_remover_final(struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return false;
    return lista_remover_indice(lista, lista->tamanho_atual - 1);
}

void lista_exibir(const struct lista *lista)
{
    if (!lista) return;

    for (size_t i = 0; i < lista->tamanho_atual; ++i) {
        printf("%zu: ", i);
        elemento_exibir(&lista->dados[i]);
        putchar('\n');
    }
}

const struct elemento *lista_buscar(const struct lista *lista, const int chave)
{
    if (!lista) return nullptr;

    size_t idx = 0;
    if (!lista_indice_de(lista, chave, &idx)) return nullptr;

    return &lista->dados[idx];
}

bool lista_indice_de(const struct lista *lista, const int chave, size_t *indice)
{
    if (!lista || !indice) return false;

    for (size_t i = 0; i < lista->tamanho_atual; ++i) {
        if (lista->dados[i].chave == chave) {
            *indice = i;
            return true;
        }
    }

    return false;
}

size_t lista_tamanho(const struct lista *lista)
{
    if (!lista) return 0;
    return lista->tamanho_atual;
}

static size_t lista_tamanho_recursivo_aux(const struct lista *lista,
                                          const size_t indice,
                                          const size_t contador)
{
    if (indice >= lista->tamanho_atual) return contador;

    return lista_tamanho_recursivo_aux(lista, indice + 1, contador + 1);
}

size_t lista_tamanho_recursivo(const struct lista *lista)
{
    if (!lista) return 0;
    return lista_tamanho_recursivo_aux(lista, 0, 0);
}

static const struct elemento *
lista_buscar_recursivo_aux(const struct lista *lista, const int chave,
                           const size_t indice)
{
    if (indice >= lista->tamanho_atual) return nullptr;
    if (lista->dados[indice].chave == chave) return &lista->dados[indice];

    return lista_buscar_recursivo_aux(lista, chave, indice + 1);
}

const struct elemento *lista_buscar_recursivo(const struct lista *lista,
                                              const int chave)
{
    if (!lista || lista_is_vazia(lista)) return nullptr;
    return lista_buscar_recursivo_aux(lista, chave, 0);
}

static void lista_exibir_recursivo_aux(const struct lista *lista,
                                       const size_t indice)
{
    if (indice >= lista->tamanho_atual) return;

    printf("%zu: ", indice);
    elemento_exibir(&lista->dados[indice]);
    putchar('\n');

    lista_exibir_recursivo_aux(lista, indice + 1);
}

void lista_exibir_recursivo(const struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return;
    lista_exibir_recursivo_aux(lista, 0);
}

static void lista_exibir_inverso_recursivo_aux(const struct lista *lista,
                                               const size_t restante)
{
    if (restante == 0) return;

    const size_t indice = restante - 1;
    printf("%zu: ", indice);
    elemento_exibir(&lista->dados[indice]);
    putchar('\n');

    lista_exibir_inverso_recursivo_aux(lista, restante - 1);
}

void lista_exibir_inverso_recursivo(const struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return;
    lista_exibir_inverso_recursivo_aux(lista, lista->tamanho_atual);
}

size_t lista_contar_maiores(const struct lista *lista, const int chave)
{
    if (!lista || lista_is_vazia(lista)) return 0;

    size_t gt = 0;
    for (size_t i = 0; i < lista->tamanho_atual; ++i)
        if (lista->dados[i].chave > chave) ++gt;

    return gt;
}

static size_t
lista_contar_maiores_recursivo_aux(const struct elemento *elemento,
                                   const int chave, const size_t restante,
                                   const size_t contador)
{
    if (restante == 0) return contador;

    const size_t novo_contador = contador + (elemento->chave > chave ? 1 : 0);

    return lista_contar_maiores_recursivo_aux(elemento + 1, chave, restante - 1,
                                              novo_contador);
}

size_t lista_contar_maiores_recursivo(const struct lista *lista,
                                      const int chave)
{
    if (!lista || lista_is_vazia(lista)) return 0;
    return lista_contar_maiores_recursivo_aux(lista->dados, chave,
                                              lista->tamanho_atual, 0);
}
