#include "lista.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static constexpr size_t NODO_VAZIO = SIZE_MAX;

void elemento_exibir(const struct elemento *elemento)
{
    printf("[Chave: %d | Valor: %d]", elemento->chave, elemento->value);
}

void lista_iniciar(struct lista *lista)
{
    if (!lista) return;

    lista->inicio = NODO_VAZIO;
    if (LISTA_CAPACIDADE == 0) {
        lista->disponivel = NODO_VAZIO;
        return;
    }

    lista->disponivel = 0;
    for (size_t i = 0; i < LISTA_CAPACIDADE - 1; ++i)
        lista->nodos[i].proximo = i + 1;

    lista->nodos[LISTA_CAPACIDADE - 1].proximo = NODO_VAZIO;
}

void lista_destruir(struct lista *lista)
{
    lista_iniciar(lista);
}

bool lista_is_vazia(const struct lista *lista)
{
    return !lista || lista->inicio == NODO_VAZIO;
}

bool lista_inserir_inicio(struct lista *lista, const struct elemento *elemento)
{
    if (!lista || !elemento || lista->disponivel == NODO_VAZIO) return false;

    const size_t novo = lista->disponivel;
    lista->disponivel = lista->nodos[novo].proximo;

    lista->nodos[novo].elemento = *elemento;
    lista->nodos[novo].proximo = lista->inicio;

    lista->inicio = novo;
    return true;
}

bool lista_inserir_final(struct lista *lista, const struct elemento *elemento)
{
    if (!lista || !elemento || lista->disponivel == NODO_VAZIO) return false;

    const size_t novo = lista->disponivel;
    lista->disponivel = lista->nodos[novo].proximo;

    lista->nodos[novo].elemento = *elemento;
    lista->nodos[novo].proximo = NODO_VAZIO;

    size_t *link = &lista->inicio;
    while (*link != NODO_VAZIO) link = &lista->nodos[*link].proximo;
    *link = novo;

    return true;
}

bool lista_inserir_ordenado(struct lista *lista,
                            const struct elemento *elemento)
{
    if (!lista || !elemento || lista->disponivel == NODO_VAZIO) return false;

    size_t *link = &lista->inicio;
    while (*link != NODO_VAZIO &&
           lista->nodos[*link].elemento.chave < elemento->chave)
        link = &lista->nodos[*link].proximo;

    const size_t novo = lista->disponivel;
    lista->disponivel = lista->nodos[novo].proximo;

    lista->nodos[novo].elemento = *elemento;
    lista->nodos[novo].proximo = *link;
    *link = novo;

    return true;
}

bool lista_remover_indice(struct lista *lista, const size_t indice)
{
    if (!lista) return false;

    size_t idx = 0;
    size_t *link = &lista->inicio;

    while (*link != NODO_VAZIO && idx < indice) {
        link = &lista->nodos[*link].proximo;
        idx++;
    }

    if (*link == NODO_VAZIO) return false;

    const size_t removido = *link;
    *link = lista->nodos[removido].proximo;

    lista->nodos[removido].proximo = lista->disponivel;
    lista->disponivel = removido;

    return true;
}

bool lista_remover_elemento(struct lista *lista, const int chave)
{
    if (!lista) return false;

    size_t *link = &lista->inicio;
    while (*link != NODO_VAZIO && lista->nodos[*link].elemento.chave != chave)
        link = &lista->nodos[*link].proximo;

    if (*link == NODO_VAZIO) return false;

    const size_t removido = *link;
    *link = lista->nodos[removido].proximo;

    lista->nodos[removido].proximo = lista->disponivel;
    lista->disponivel = removido;

    return true;
}

bool lista_remover_inicio(struct lista *lista)
{
    return lista_remover_indice(lista, 0);
}

bool lista_remover_final(struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return false;

    size_t *link = &lista->inicio;
    while (lista->nodos[*link].proximo != NODO_VAZIO)
        link = &lista->nodos[*link].proximo;

    const size_t removido = *link;
    *link = NODO_VAZIO;

    lista->nodos[removido].proximo = lista->disponivel;
    lista->disponivel = removido;

    return true;
}

void lista_exibir(const struct lista *lista)
{
    if (!lista) return;

    for (size_t atual = lista->inicio, idx = 0; atual != NODO_VAZIO;
         atual = lista->nodos[atual].proximo, ++idx) {
        printf("%zu: ", idx);
        elemento_exibir(&lista->nodos[atual].elemento);
        putchar('\n');
    }
}

const struct elemento *lista_buscar(const struct lista *lista, const int chave)
{
    if (!lista) return nullptr;

    for (size_t atual = lista->inicio; atual != NODO_VAZIO;
         atual = lista->nodos[atual].proximo)
        if (lista->nodos[atual].elemento.chave == chave)
            return &lista->nodos[atual].elemento;

    return nullptr;
}

bool lista_indice_de(const struct lista *lista, const int chave, size_t *indice)
{
    if (!lista || !indice) return false;

    for (size_t atual = lista->inicio, pos = 0; atual != NODO_VAZIO;
         atual = lista->nodos[atual].proximo, ++pos) {
        if (lista->nodos[atual].elemento.chave == chave) {
            *indice = pos;
            return true;
        }
    }

    return false;
}

size_t lista_tamanho(const struct lista *lista)
{
    if (!lista) return 0;

    size_t tamanho = 0;
    for (size_t atual = lista->inicio; atual != NODO_VAZIO;
         atual = lista->nodos[atual].proximo)
        tamanho++;

    return tamanho;
}

static size_t lista_tamanho_recursivo_aux(const struct lista *lista,
                                          const size_t atual,
                                          const size_t tamanho)
{
    if (atual == NODO_VAZIO) return tamanho;

    return lista_tamanho_recursivo_aux(lista, lista->nodos[atual].proximo,
                                       tamanho + 1);
}

size_t lista_tamanho_recursivo(const struct lista *lista)
{
    if (!lista) return 0;
    return lista_tamanho_recursivo_aux(lista, lista->inicio, 0);
}

static const struct elemento *
lista_buscar_recursivo_aux(const struct lista *lista, const int chave,
                           const size_t atual)
{
    if (atual == NODO_VAZIO) return nullptr;
    if (lista->nodos[atual].elemento.chave == chave)
        return &lista->nodos[atual].elemento;

    return lista_buscar_recursivo_aux(lista, chave,
                                      lista->nodos[atual].proximo);
}

const struct elemento *lista_buscar_recursivo(const struct lista *lista,
                                              const int chave)
{
    if (!lista) return nullptr;

    return lista_buscar_recursivo_aux(lista, chave, lista->inicio);
}

static void lista_exibir_recursivo_linear_aux(const struct lista *lista,
                                              const size_t cur)
{
    if (cur == NODO_VAZIO) return;

    elemento_exibir(&lista->nodos[cur].elemento);
    putchar('\n');

    lista_exibir_recursivo_linear_aux(lista, lista->nodos[cur].proximo);
}

void lista_exibir_recursivo(const struct lista *lista)
{
    if (!lista) return;

    lista_exibir_recursivo_linear_aux(lista, lista->inicio);
}

static void lista_exibir_recursivo_reverso_aux(const struct lista *lista,
                                               const size_t cur)
{
    if (cur == NODO_VAZIO) return;
    lista_exibir_recursivo_reverso_aux(lista, lista->nodos[cur].proximo);

    elemento_exibir(&lista->nodos[cur].elemento);
    putchar('\n');
}

void lista_exibir_inverso_recursivo(const struct lista *lista)
{
    if (!lista || lista_is_vazia(lista)) return;

    lista_exibir_recursivo_reverso_aux(lista, lista->inicio);
}

size_t lista_contar_maiores(const struct lista *lista, const int chave)
{
    if (!lista) return 0;

    size_t qt_maior = 0;
    for (size_t atual = lista->inicio; atual != NODO_VAZIO;
         atual = lista->nodos[atual].proximo)
        if (lista->nodos[atual].elemento.chave > chave) qt_maior++;

    return qt_maior;
}

static size_t lista_contar_maiores_recursivo_aux(const struct lista *lista,
                                                 const size_t atual,
                                                 const int chave,
                                                 const size_t qt_maior)
{
    if (atual == NODO_VAZIO) return qt_maior;

    const size_t novo_acc =
        qt_maior + ((size_t)(lista->nodos[atual].elemento.chave > chave));

    return lista_contar_maiores_recursivo_aux(
        lista, lista->nodos[atual].proximo, chave, novo_acc);
}

size_t lista_contar_maiores_recursivo(const struct lista *lista,
                                      const int chave)
{
    if (!lista) return 0;
    return lista_contar_maiores_recursivo_aux(lista, lista->inicio, chave, 0);
}
