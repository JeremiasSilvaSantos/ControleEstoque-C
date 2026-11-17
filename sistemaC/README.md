# StockFlow-C — Sistema de Controle de Estoque

Aplicação em linguagem C para gestão eficiente de estoque, cadastro, movimentação e análise financeira de itens, com persistência de dados em arquivo texto.

## Autoria
* **Desenvolvedor:** Jeremias Silva Santos

---

## Funcionalidades do Sistema

O sistema conta com um menu interativo completo com 13 operações:

1. **Cadastrar Produto:** Registro de código numérico único (com validação de duplicidade), nome, preço e quantidade.
2. **Listar Produtos:** Exibição tabular de todos os itens cadastrados.
3. **Consultar Produto:** Busca rápida por código do produto.
4. **Alterar Produto:** Atualização de nome, preço e quantidade em estoque.
5. **Excluir Produto:** Remoção segura de registros do vetor.
6. **Verificar Situação do Estoque:** Classificação automática por status (`ESTOQUE ESGOTADO`, `ESTOQUE BAIXO` ≤ 5 unidades, ou `ESTOQUE NORMAL`).
7. **Calcular Valor Total:** Soma financeira de todo o inventário armazenado.
8. **Maior Valor em Estoque:** Identifica o item com maior capital imobilizado (`preço × quantidade`).
9. **Menor Valor em Estoque:** Identifica o item com menor valor total em estoque.
10. **Ordenar Produtos:** Ordenação crescente por código utilizando o algoritmo *Bubble Sort*.
11. **Salvar Dados:** Exportação automática e manual dos registros para o arquivo `estoques.txt`.
12. **Carregar Dados:** Leitura automática dos dados salvos ao iniciar o sistema.
13. **Sair:** Salva as alterações automaticamente antes de encerrar o programa.

---

## Estrutura do Repositório

```text
StockFlow-C/
├── docs/
│   └── Documentacao_Projeto.pdf   # Documentação técnica e código-fonte formatado
├── src/
│   └── estoque.c                  # Código-fonte principal do sistema em C
├── .gitignore                     # Regras para ignorar binários compilados
└── README.md                      # Documentação do repositório
```

---

## Como Compilar e Executar

### Pré-requisitos
Certifique-se de ter um compilador C instalado (como **GCC**, **Clang** ou **MinGW**).

### Passo a passo

1. Clone ou extraia este repositório e acesse a pasta raiz:
   ```bash
   cd StockFlow-C
   ```

2. Compile o código-fonte:
   ```bash
   gcc src/estoque.c -o estoque
   ```

3. Execute o programa:
   * **Linux / macOS:**
     ```bash
     ./estoque
     ```
   * **Windows (CMD / PowerShell):**
     ```cmd
     estoque.exe
     ```

---

## 🛠️ Tecnologias Utilizadas
* **Linguagem C** (Bibliotecas padrão `stdio.h` e `string.h`)
* **Manipulação de Arquivos** (`FILE*`, `fopen`, `fprintf`, `fscanf`)
* **Estruturas de Dados** (`struct`, vetores e algoritmos de busca/ordenação)
