# Estruturas de Dados e Algoritmos (DSA III) - UNIR

Implementações e projetos práticos desenvolvidos para a atividade III da
disciplina de Estruturas de Dados e Algoritmos da Universidade Federal de
Rondônia (UNIR).

## Conteúdo

- [`lista_sequencial/`](./lista_sequencial): Implementação de Lista
  Sequencial Estática em C.
- [`lista_estatica_encadeada/`](./lista_estatica_encadeada): Implementação de
  Lista Estática Encadeada com gerenciamento de posições livres em C.
- [`lista_dinamica_encadeada/`](./lista_dinamica_encadeada): Implementação de
  Lista Dinâmica Encadeada em C.

## Ambiente de Desenvolvimento

Cada subprojeto possui seu próprio ambiente de desenvolvimento independente e
reprodutível com [Nix Flakes](https://nixos.wiki/wiki/Flakes), Clang e
[CMake](https://cmake.org/):

```sh
# Entrar no diretório do projeto desejado
cd lista_sequencial # ou cd lista_estatica_encadeada

# Carregar o ambiente de desenvolvimento com Nix
nix develop

# Compilar e executar
cmake -S . -B build && cmake --build build && ./build/c_app
```

## Licença

Este projeto está licenciado sob os termos da licença
[GNU General Public License v3.0](LICENSE).
