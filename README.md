# Boop Game

Implementação do jogo de tabuleiro **Boop** para dois jogadores no terminal, desenvolvida em linguagem C para Windows.

---

## Sobre o Jogo

**Boop** é um jogo de tabuleiro estratégico para dois jogadores disputado em um tabuleiro 6×6. Cada jogador controla peças de dois tamanhos: **gatinhos** (`g`) e **gatos** (`G`). O objetivo é alinhar três **gatos grandes** em sequência — horizontal, vertical ou diagonal — para vencer.

Ao posicionar uma peça, ela "empurra" (**boop**) todas as peças adjacentes para longe. Alinhar três peças do mesmo tipo (mesmo que gatinhos) faz com que elas "se graduem" e se transformem em gatos, adicionando-os de volta ao estoque do jogador.

---

## Objetivo

Alinhar **três Gatos (`G`)** consecutivos do seu time em qualquer direção (horizontal, vertical ou diagonal) no tabuleiro.

---

## Como Jogar

### Iniciando o Jogo

Ao executar o programa, você verá uma tela de boas-vindas com arte ASCII e será perguntado se deseja carregar uma partida salva anteriormente:

```
Deseja carregar o jogo de onde parou? (s/n):
```

- **`s`** — Carrega o estado do arquivo `tabuleiro.bin`
- **`n`** — Começa uma nova partida (sobrescreve o arquivo salvo)

### Fazendo uma Jogada

O formato de entrada é:

```
<coluna> <linha> <tipo>
```

| Campo    | Valores       | Descrição                               |
|----------|---------------|-----------------------------------------|
| `coluna` | `a` até `f`   | Letra da coluna (eixo horizontal)        |
| `linha`  | `1` até `6`   | Número da linha (eixo vertical)          |
| `tipo`   | `g` ou `G`    | `g` = gatinho pequeno / `G` = gato grande |

**Exemplo:**
```
a 1 G
```
> Coloca um Gato grande na coluna `a`, linha `1`.

---

## Regras

1. **Turnos alternados** — Jogador 1 (vermelho) e Jogador 2 (verde) se alternam.
2. **Estoque inicial** — Cada jogador começa com **8 gatinhos** e **0 gatos**.
3. **Boop** — Ao posicionar uma peça, todas as peças nas 8 casas adjacentes são empurradas 1 casa para longe:
   - Um **gatinho** (`g`) só empurra outros **gatinhos** (`g`).
   - Um **gato** (`G`) empurra **qualquer** peça.
   - Se não houver espaço para onde empurrar (borda do tabuleiro), a peça empurrada é **removida** e devolvida ao estoque do dono.
4. **Graduação** — Se 3 peças do mesmo jogador (sejam gatinhos, gatos ou mistos) ficarem alinhadas:
   - Elas são removidas do tabuleiro.
   - O jogador recebe **3 gatos grandes** de volta ao seu estoque.
5. **Vitória** — O jogo termina quando:
   - Um jogador alinha **3 Gatos grandes** (`G`) consecutivos (horizontal, vertical ou diagonal), **ou**
   - Um jogador fica sem peças no estoque (gatinhos **e** gatos = 0), concedendo a vitória ao adversário.

---

## Tabuleiro

O tabuleiro é exibido no terminal com coordenadas de letras (`a`–`f`) nas colunas e números (`1`–`6`) nas linhas. As peças são coloridas:

| Cor         | Significado               |
|-------------|---------------------------|
| Vermelho    | Peças do **Jogador 1**    |
| Verde       | Peças do **Jogador 2**    |
| `g`         | Gatinho (peça pequena)    |
| `G`         | Gato grande (peça grande) |

**Exemplo de tabuleiro:**
```
+---+---+---+---+---+---+
| g |   |   |   |   |   |  1
+---+---+---+---+---+---+
|   |   | G |   |   |   |  2
...
  a   b   c   d   e   f
```

---

## Sistema de Save

O jogo salva automaticamente o estado após cada jogada no arquivo **`tabuleiro.bin`** (binário), localizado no mesmo diretório do executável. O arquivo armazena:

- O estado completo do tabuleiro (matriz 6×6)
- O placar de ambos os jogadores (estoque de gatinhos e gatos)

---

## Estrutura do Código

O projeto é composto por um único arquivo fonte:

```
Boop-game/
├── src/
│   └── main.c       # Código-fonte principal
├── tabuleiro.bin    # Arquivo de save (gerado em tempo de execução)
└── README.md
```

### Funções Principais

| Função                          | Descrição                                                                        |
|---------------------------------|----------------------------------------------------------------------------------|
| `main()`                        | Loop principal do jogo                                                           |
| `menuInicio()`                  | Exibe a tela inicial com arte ASCII                                              |
| `exibeTabuleiro()`              | Renderiza o tabuleiro 6×6 colorido no terminal                                  |
| `exibePlacar()`                 | Mostra o placar atual de ambos os jogadores                                      |
| `fazJogada()`                   | Lê e processa a entrada do jogador atual                                         |
| `validaJogada()`                | Valida a jogada (limites, peça disponível, casa vazia) e aplica no tabuleiro    |
| `fazBoop()`                     | Aplica o efeito de empurrão nas 8 direções ao redor da peça jogada              |
| `graduaGatinho()`               | Verifica alinhamentos de 3 peças e converte gatinhos em gatos                   |
| `verificaVitoria()`             | Checa condições de vitória em todas as direções                                 |
| `naCasa()`                      | Retorna o tipo e dono da peça em uma determinada casa                           |
| `salvarTabelas()`               | Persiste o estado do jogo em arquivo binário                                     |
| `carregarTabelas()`             | Restaura o estado do jogo a partir do arquivo binário                           |
| `validarTabelas()`              | Pergunta ao jogador se deseja carregar o jogo salvo                             |
| `inicializaMatrizTabuleiro()`   | Aloca e inicializa a matriz do tabuleiro (6×6 de zeros)                         |
| `inicializaMatrizPlacar()`      | Aloca e inicializa o placar (2 jogadores × 2 tipos de peça)                     |
| `printColoredText()`            | Imprime texto colorido usando a API do console do Windows                        |
| `setColor()` / `resetColor()`   | Controla as cores do terminal via `SetConsoleTextAttribute`                      |

### Representação Interna do Tabuleiro

Cada célula da matriz `tabuleiro[linha][coluna]` armazena um inteiro:

| Valor | Significado                         |
|-------|-------------------------------------|
| `0`   | Casa vazia                          |
| `1`   | Gatinho do Jogador 1 (vermelho)     |
| `2`   | Gato grande do Jogador 1 (vermelho) |
| `3`   | Gatinho do Jogador 2 (verde)        |
| `4`   | Gato grande do Jogador 2 (verde)    |

---

## Compilação e Execução

### Requisitos

- **Sistema Operacional:** Windows (usa `windows.h` para cores no console)
- **Compilador:** GCC (MinGW) ou MSVC

### Compilando com GCC (MinGW)

```bash
gcc src/main.c -o boop.exe
```

### Executando

```bash
./boop.exe
```

---

## Dependências

| Biblioteca  | Uso                                            |
|-------------|------------------------------------------------|
| `stdio.h`   | Entrada/saída padrão (`printf`, `scanf`, etc.) |
| `stdlib.h`  | Alocação de memória (`malloc`, `free`) e `system()` |
| `windows.h` | Controle de cores do console do Windows        |

> **Atenção:** Por utilizar a API `windows.h`, o jogo **não é compatível** com Linux ou macOS sem modificações.

---

## Licença

Este projeto está licenciado sob a **Licença MIT**.
