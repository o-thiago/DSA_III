===============================================================================
UNIVERSIDADE FEDERAL DE RONDÔNIA (UNIR)
FACULDADE DE ENGENHARIA, TECNOLOGIA E INOVAÇÃO
ESTRUTURA DE DADOS I - LISTA PRÁTICA 3: LISTAS
===============================================================================

1. Integrante (Trabalho Individual):
   Thiago Macedo Mendes

2. Turma:
   Estrutura de Dados I

3. Sistema Operacional utilizado:
   Linux (NixOS 26.05 Yarara, x86_64)

4. Compilador utilizado:
   Clang

5. Versão do compilador:
   Clang 23.1.0
   Padrão da linguagem: C23 (-std=c23)

6. IDE ou editor utilizado:
   CLion (JetBrains CLion 2026.2)

7. Instruções para compilação:
   O repositório contém três projetos independentes:
     - lista_sequencial/
     - lista_estatica_encadeada/
     - lista_dinamica_encadeada/

   Opção 1: Via CLion (IDE)
     1. Abra a pasta do subprojeto desejado no CLion (File -> Open...).
     2. O CLion configurará automaticamente o projeto via CMake.
     3. Execute o target "c_app" pelo botão Run (Shift+F10).

   Opção 2: Via CMake (Terminal)
     1. Navegue até a pasta do projeto desejado:
          cd lista_sequencial
          # ou: cd lista_estatica_encadeada
          # ou: cd lista_dinamica_encadeada
     2. Configure e compile com o CMake:
          cmake -S . -B build
          cmake --build build

8. Instruções para execução:
   - Para executar pelo terminal após a compilação:
       ./build/c_app
   - Os três projetos utilizam o mesmo programa cliente (main.c) e a mesma
     interface de operações (lista.h e menu.h).
   - É necessário um compilador com suporte ao C23.
