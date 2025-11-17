# Máximo Sub‑retângulo em Matriz (Brute Force e Branch & Bound)

Este projeto compara duas abordagens para encontrar o sub‑retângulo de soma máxima em uma matriz de inteiros (com a regra extra de ignorar sub‑retângulos quadrados em algumas variantes):

- Brute Force (`BruteForce.cc`)
- Branch & Bound (`BreanchEndBound.cc`)

Os programas geram uma matriz aleatória (valores entre −10 e 10), imprimem a matriz e reportam o melhor sub‑retângulo encontrado (soma, coordenadas, dimensões e conteúdo).

> Observação: O diretório tem espaço no nome. Nos comandos abaixo, mantenha as aspas.

---

## Requisitos

- Linux com `g++` (C++17) instalado
- Opcional: VS Code, já com as tasks configuradas (build/run com `/usr/bin/time`)

Verifique a versão do compilador:

```bash
g++ --version
```

---

## Como compilar e executar (terminal)

Dentro da pasta do projeto:

```bash
# Compilar Brute Force
g++ -std=c++17 -O2 -Wall -Wextra -pedantic "./BruteForce.cc" -o ./BruteForce

# Compilar Branch & Bound
g++ -std=c++17 -O2 -Wall -Wextra -pedantic "./BreanchEndBound.cc" -o ./BreanchEndBound

# Executar
./BruteForce
./BreanchEndBound
```

Medir tempo/memória da execução:

```bash
/usr/bin/time -p ./BruteForce
/usr/bin/time -v ./BreanchEndBound
```

## Explicação das soluções

### 1) Brute Force (`BruteForce.cc`)

- Ideia: enumerar todos os sub‑retângulos possíveis (pares de linhas e colunas), ignorando quadrados, calcular a soma das células e guardar o melhor.
- Complexidade: existem O(R²·C²) sub‑retângulos. Como a soma é recalculada varrendo a área, o custo total é O(R³·C³) no pior caso. Para matrizes pequenas funciona, cresce rápido para maiores.
- Vantagens: simples e exato; base de comparação.
- Desvantagens: escala mal; sem otimizações (ex.: prefix sums) o tempo aumenta bastante.

### 2) Branch & Bound (`BreanchEndBound.cc`)

- Ideia: explorar sub‑retângulos de forma recursiva tentando podar ramos que não podem melhorar a melhor solução. O “bound” usado é a soma dos valores positivos na região (um limite superior grosseiro para a soma possível naquela área).
- Funcionamento resumido:
  - Gera sub‑retângulos candidatos a partir de uma região e avalia seu “bound”.
  - Se `bound <= melhor_sum`, poda a busca daquele ramo.
  - Atualiza o melhor quando encontra soma maior.
- Observações importantes:
  - O bound “soma dos positivos” é simples, mas pode ser fraco (poda pouco em matrizes com muitos positivos), então o desempenho pode se aproximar do brute force.

---

## Ajustes úteis

- Tamanho da matriz: mude `R` e `C` no `main()` de cada arquivo.
- Faixa de valores: altere `std::uniform_int_distribution<int> dist(-10, 10);`.
- Reprodutibilidade: use uma seed fixa em vez de `std::random_device{}` para repetir os mesmos dados em execuções diferentes.

Exemplo de seed fixa:

```cpp
std::mt19937 rng(123456u); // seed fixa
```

## Estrutura do projeto

- `BruteForce.cc`: implementação ingênua (exata) enumerando todos os sub‑retângulos não quadrados.
- `BreanchEndBound.cc`: versão com Branch & Bound usando um bound simples (soma dos positivos) para podas.
- Pastas/bins adicionais podem conter executáveis gerados em outras execuções.


