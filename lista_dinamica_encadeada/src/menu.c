#include "menu.h"

#include <stdio.h>

const char *menu_option_get_name(const enum menu_option option)
{
    switch (option) {
    case MENU_OPTION_SAIR:
        return "Sair";
    case MENU_OPTION_VERIFY_VAZIA:
        return "Verificar se a lista está vazia";
    case MENU_OPTION_INSERT_INICIO:
        return "Inserir no início";
    case MENU_OPTION_INSERT_FINAL:
        return "Inserir no final";
    case MENU_OPTION_INSERT_ORDENADO:
        return "Inserir ordenadamente";
    case MENU_OPTION_REMOVER_INICIO:
        return "Remover do início";
    case MENU_OPTION_REMOVER_FINAL:
        return "Remover do final";
    case MENU_OPTION_REMOVER_CHAVE:
        return "Remover por chave";
    case MENU_OPTION_BUSCAR:
        return "Buscar elemento";
    case MENU_OPTION_EXIBIR:
        return "Exibir lista";
    case MENU_OPTION_EXIBIR_RECURSIVO:
        return "Exibir lista recursivamente";
    case MENU_OPTION_EXIBIR_INVERSO:
        return "Exibir lista em ordem inversa";
    case MENU_OPTION_TAMANHO:
        return "Informar tamanho";
    case MENU_OPTION_TAMANHO_RECURSIVO:
        return "Informar tamanho recursivamente";
    case MENU_OPTION_BUSCAR_RECURSIVO:
        return "Buscar recursivamente";
    case MENU_OPTION_CONTAR_MAIORES_X:
        return "Contar chaves maiores que X";
    case MENU_OPTION_CONTAR_MAIORES_X_RECURSIVO:
        return "Contar chaves maiores que X recursivamente";
    case MENU_OPTION_DESTRUIR:
        return "Destruir lista";
    case MENU_OPTION_COUNT_OPTIONS:
    default:
        return "Opção desconhecida";
    }
}

void menu_show(void)
{
    for (int i = 0; i < MENU_OPTION_COUNT_OPTIONS; ++i)
        printf("%d - %s\n", i, menu_option_get_name((enum menu_option)i));
    putchar('\n');
}
