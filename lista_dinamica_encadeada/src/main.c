#include "lista.h"
#include "menu.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static constexpr unsigned int OUTPUT_WAIT_SECONDS = 3;

static bool screen_clear(void)
{
    return fputs("\033[H\033[J", stdout) >= 0 && fflush(stdout) == 0;
}

static bool output_prompt(const char *prompt)
{
    return fputs(prompt, stdout) >= 0 && fflush(stdout) == 0;
}

static bool err_puts(const char *msg)
{
    return fputs(msg, stderr) >= 0 && fputc('\n', stderr) >= 0;
}

static bool read_int(char *input, const int input_size, int *out)
{
    if (!input || !out || input_size <= 1) return false;
    if (!fgets(input, input_size, stdin)) return false;

    if (!strchr(input, '\n') && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return false;
    }

    errno = 0;
    char *end = nullptr;
    const long val = strtol(input, &end, 10);

    if (end == input || errno == ERANGE || val < INT_MIN || val > INT_MAX)
        return false;

    int (*const check_space)(int) = isspace;
    while (*end != '\0') {
        if (!check_space((unsigned char)*end)) return false;
        end++;
    }

    *out = (int)val;
    return true;
}

static bool prompt_insertion(
    const struct application_data *app_data,
    bool (*insertion_function)(struct lista *, const struct elemento *))
{
    if (!output_prompt("Digite o valor a ser inserido: ")) return false;

    struct elemento elemento = {};
    if (!read_int(app_data->input, app_data->input_size, &elemento.value))
        return false;

    if (!output_prompt("Digite a chave associada a esse valor: ")) return false;
    if (!read_int(app_data->input, app_data->input_size, &elemento.chave))
        return false;

    return insertion_function(app_data->lista, &elemento);
}

static bool prompt_chave(const struct application_data *app_data,
                         const char *prompt, int *out)
{
    if (!output_prompt(prompt)) return false;
    return read_int(app_data->input, app_data->input_size, out);
}

static bool handle_insertion(
    const struct application_data *app_data,
    bool (*insertion_function)(struct lista *, const struct elemento *))
{
    if (!prompt_insertion(app_data, insertion_function))
        return err_puts("Falha ao inserir elemento.");
    return true;
}

static bool handle_removal(const bool success)
{
    if (!success) return err_puts("Falha ao remover elemento.");
    return true;
}

static bool handle_search(const struct application_data *app_data,
                          const bool recursive)
{
    int chave = 0;
    if (!prompt_chave(app_data, "Digite a chave a ser buscada: ", &chave))
        return false;

    const struct elemento *elemento =
        recursive ? lista_buscar_recursivo(app_data->lista, chave)
                  : lista_buscar(app_data->lista, chave);

    if (elemento) {
        printf("Elemento encontrado: chave=%d, valor=%d\n", elemento->chave,
               elemento->value);
        return true;
    }

    return err_puts("Elemento não encontrado.");
}

static bool handle_count(const struct application_data *app_data,
                         const bool recursive)
{
    int chave = 0;
    if (!prompt_chave(app_data, "Digite a chave X: ", &chave)) return false;

    const size_t count =
        recursive ? lista_contar_maiores_recursivo(app_data->lista, chave)
                  : lista_contar_maiores(app_data->lista, chave);
    printf("Quantidade de chaves maiores que %d: %zu\n", chave, count);
    return true;
}

static bool handle_option(const struct application_data *app_data,
                          const enum menu_option option)
{
    switch (option) {
    case MENU_OPTION_SAIR:
        return true;
    case MENU_OPTION_VERIFY_VAZIA:
        printf("A lista %sestá vazia\n",
               lista_is_vazia(app_data->lista) ? "" : "não ");
        return true;
    case MENU_OPTION_INSERT_INICIO:
        return handle_insertion(app_data, &lista_inserir_inicio);
    case MENU_OPTION_INSERT_FINAL:
        return handle_insertion(app_data, &lista_inserir_final);
    case MENU_OPTION_INSERT_ORDENADO:
        return handle_insertion(app_data, &lista_inserir_ordenado);
    case MENU_OPTION_REMOVER_INICIO:
        return handle_removal(lista_remover_inicio(app_data->lista));
    case MENU_OPTION_REMOVER_FINAL:
        return handle_removal(lista_remover_final(app_data->lista));
    case MENU_OPTION_REMOVER_CHAVE: {
        int chave = 0;
        const bool ok =
            prompt_chave(app_data, "Digite a chave a ser removida: ", &chave) &&
            lista_remover_elemento(app_data->lista, chave);
        return handle_removal(ok);
    }
    case MENU_OPTION_BUSCAR:
        return handle_search(app_data, false);
    case MENU_OPTION_BUSCAR_RECURSIVO:
        return handle_search(app_data, true);
    case MENU_OPTION_EXIBIR:
        lista_exibir(app_data->lista);
        return true;
    case MENU_OPTION_EXIBIR_RECURSIVO:
        lista_exibir_recursivo(app_data->lista);
        return true;
    case MENU_OPTION_EXIBIR_INVERSO:
        lista_exibir_inverso_recursivo(app_data->lista);
        return true;
    case MENU_OPTION_TAMANHO:
        printf("Tamanho da lista: %zu\n", lista_tamanho(app_data->lista));
        return true;
    case MENU_OPTION_TAMANHO_RECURSIVO:
        printf("Tamanho da lista (recursivo): %zu\n",
               lista_tamanho_recursivo(app_data->lista));
        return true;
    case MENU_OPTION_CONTAR_MAIORES_X:
        return handle_count(app_data, false);
    case MENU_OPTION_CONTAR_MAIORES_X_RECURSIVO:
        return handle_count(app_data, true);
    case MENU_OPTION_DESTRUIR:
        lista_destruir(app_data->lista);
        puts("Lista destruída.");
        return true;
    case MENU_OPTION_COUNT_OPTIONS:
    default:
        return false;
    }
}

int main()
{
    char buffer[BUFSIZ];

    struct lista lista = {};
    lista_iniciar(&lista);

    const struct application_data app_data = {
        .lista = &lista,
        .input = buffer,
        .input_size = (int)sizeof(buffer),
    };

    do {
        (void)screen_clear();

        menu_show();
        if (!output_prompt("Digite sua opção: ")) return EXIT_FAILURE;

        int raw_option = 0;
        if (!read_int(app_data.input, app_data.input_size, &raw_option) ||
            raw_option < 0 || raw_option >= MENU_OPTION_COUNT_OPTIONS) {
            if (!fprintf(stderr,
                         "Por favor selecione uma opção válida [%d-%d].\n", 0,
                         MENU_OPTION_COUNT_OPTIONS - 1))
                return EXIT_FAILURE;

            sleep(OUTPUT_WAIT_SECONDS);
            continue;
        }

        const auto option = (enum menu_option)raw_option;
        if (option == MENU_OPTION_SAIR) break;

        if (!handle_option(&app_data, option) &&
            !err_puts("Falha interna da aplicação."))
            return EXIT_FAILURE;

        sleep(OUTPUT_WAIT_SECONDS);
    } while (true);

    return EXIT_SUCCESS;
}
