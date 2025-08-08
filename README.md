# 📝 Gerenciador de Tarefas com Lista Encadeada Ordenada em C

Este projeto é uma implementação completa de um sistema de gerenciamento de tarefas via linha de comando, desenvolvido em C puro. O objetivo principal foi aprofundar os conhecimentos em estruturas de dados, gerenciamento de memória manual e manipulação de arquivos em baixo nível.

O coração do sistema é uma **lista encadeada ordenada** que mantém as tarefas organizadas por prioridade e, como critério de desempate, por ordem alfabética.

---

## ✨ Features Principais

- **CRUD Completo de Tarefas:** Crie, leia, atualize e delete tarefas.
- **Ordenação Automática:** Novas tarefas são inseridas na posição correta da lista para manter a ordenação por prioridade e nome.
- **Gerenciamento de Múltiplas Listas:** O sistema permite ao usuário trabalhar com duas listas separadas e gerar uma terceira lista com a **interseção** entre elas.
- **Persistência em Arquivo:** Salve e carregue suas listas de tarefas em arquivos binários, garantindo que os dados não sejam perdidos.
- **Interface de Linha de Comando:** Um menu interativo guia o usuário através de todas as funcionalidades do programa.

---

## 🚀 Desafios Técnicos e o que Aprendi

Este projeto foi uma jornada de aprendizado profundo nos fundamentos da Ciência da Computação.

*   **Gerenciamento de Memória Manual:** O maior desafio foi lidar diretamente com `malloc` e `free`. Aprendi na prática a importância de alocar memória para cada nova tarefa e, crucialmente, liberá-la para evitar vazamentos de memória (*memory leaks*), especialmente em operações complexas de deleção e alteração.

*   **Ponteiros e Ponteiros para Ponteiros:** Para modificar a cabeça da lista (`*inicio`) de dentro de uma função, precisei dominar o conceito de ponteiros para ponteiros (`**inicio`). Depurar a lógica de manipulação dos ponteiros `prox` e `anterior` para manter a integridade da lista foi um exercício intenso e de grande aprendizado.

*   **Implementação de Algoritmos:** O algoritmo de **inserção ordenada** foi particularmente desafiador, pois precisava lidar com múltiplos casos de borda: inserção no início, no meio, no fim, e o critério de desempate alfabético.

*   **Manipulação de Arquivos Binários:** Aprendi a serializar `structs` diretamente em arquivos usando `fwrite` e `fread`, entendendo como a persistência de dados funciona em um nível mais baixo do que um banco de dados tradicional.

---


## 🔧 Como Abrir e Executar o Projeto

Este projeto foi desenvolvido utilizando a IDE Code::Blocks.

1.  **Pré-requisitos:** Ter o [Code::Blocks](http://www.codeblocks.org/downloads) instalado (recomenda-se a versão que já inclui o compilador MinGW).
2.  **Clone o repositório:**
    ```bash
    git clone https://github.com/bieltris/Lista_encadeada_ordenada_projeto.git
    ```
3.  **Abra o Projeto:**
    *   Abra o Code::Blocks.
    *   Vá em `File > Open...`.
    *   Navegue até a pasta do projeto clonado e abra o arquivo de projeto do Code::Blocks (geralmente com a extensão `.cbp`).
4.  **Compile e Execute:**
    *   Dentro do Code::Blocks, você pode compilar o projeto indo em `Build > Build` (ou pressionando `Ctrl + F9`).
    *   Para executar o programa, vá em `Build > Run` (ou pressione `Ctrl + F10`).