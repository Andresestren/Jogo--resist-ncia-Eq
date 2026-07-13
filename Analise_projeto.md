## Análise do Projeto

### 1. Configuração e Build (Sistema)
* **`CMakeLists.txt`**: Script de configuração para o sistema de build CMake. Realiza a localização e vinculação (`target_link_libraries`) dos módulos *Core* e *Widgets* do Qt6. Também configura os scripts de deploy para empacotamento do executável nativo.
* **`main.cpp`**: Ponto de entrada (*Entry Point*) da aplicação. Instancia a `QApplication` para gerenciar os recursos globais e o fluxo de controle do Qt, aloca a `MainWindow` e inicia o event loop principal do programa (`QCoreApplication::exec()`).

<br><br>
---
<br><br>
### 2. View (Interface Gráfica e Interação)
* **`mainwindow.ui`**: Arquivo XML gerado nativamente pelo Qt Designer. Define a hierarquia de objetos (*Object Tree*), a geometria espacial e os metadados dos componentes visuais, como o canvas `QGraphicsView` e as instâncias de `QPushButton` e `QLabel`.
<br><br>
* **`mainwindow.h` / `mainwindow.cpp`**: Classe controladora da interface. Inicializa e gerencia a área de trabalho 2D (`QGraphicsScene`). Utiliza o sistema de *Signals* e *Slots* do Qt para capturar interações do utilizador. Emprega RTTI (*Run-Time Type Information*) através de `dynamic_cast` para converter ponteiros genéricos `QGraphicsItem*` em `CircuitGraphicsItem*` de forma segura durante a associação de blocos.
<br><br>
* **`circuitgraphicsitem.h`**: Classe de renderização customizada que herda de `QGraphicsItem`. Representa fisicamente um nó matemático na tela. Sobrescreve o método `boundingRect()` para definição da hitbox (área de colisão e clique) e o método `paint()` utilizando `QPainter` para renderização dinâmica de estado (alteração de cores via `QBrush` e impressão da resistência). Mantém um ponteiro (`AbstractCircuit*`) que o vincula diretamente ao modelo de dados.

---

### 3. Controller (Regras de Negócio e Gestão de Estado)
* **`gamecontroller.h` / `gamecontroller.cpp`**: Classe responsável por orquestrar a lógica do jogo (*Game Loop* de background), garantindo alta coesão e total isolamento das bibliotecas gráficas do Qt.
   <br><br>
   * **Filtragem Heurística**: Implementa um laço `while(true)` que instancia circuitos proceduralmente até encontrar um estado válido (uma malha com exatamente 4 resistores base extraídos via `std::vector`).
  <br><br>
  * **Gerenciamento de Memória**: Realiza controle estrito de alocação dinâmica no Heap. Utiliza a instrução `delete` nas tentativas falhas de geração e no destrutor da classe (`~GameController()`) para destruir a árvore de componentes e evitar vazamentos de memória (*Memory Leaks*).

---

### 4. Model (Núcleo Matemático - Padrão Composite)
* **`abstractcircuit.h`**: A interface base (*Componente Abstrato*) do padrão Composite. Define um contrato polimórfico obrigatório declarando funções virtuais puras (`= 0`) para o cálculo da malha (`getResistance()`), impressão de estrutura (`dumpCircuit()`) e extração de nós folha (`getBaseResistors()`).
<br><br>
* **`resistor.h` / `resistor.cpp`**: Representam os nós folha (*Leaf*) da estrutura de árvore. A classe base `Resistor` encapsula um atributo de resistência estático (`_resistance`). A classe derivada `RandomResistor` estende o comportamento atribuindo um valor randômico predefinido no momento de sua instanciação através de um array estático.
<br><br>
* **`seriescircuit.h` / `seriescircuit.cpp`**: Implementa o nó composto (*Composite*) para topologias em série. Utiliza agregação guardando ponteiros `AbstractCircuit*` dentro de um `std::vector`. O cálculo polimórfico itera sobre as sub-malhas realizando a soma linear das resistências. O gerador `RandomSeriesCircuit` atua como uma *Factory* recursiva para montar galhos aleatórios.
<br><br>
* **`parallelcircuit.h` / `parallelcircuit.cpp`**: Implementa o nó composto (*Composite*) para topologias em paralelo. Realiza a agregação semelhante à estrutura em série, porém o cálculo aplica o inverso da soma dos inversos das sub-malhas:
    $$\frac{1}{R_{eq}} = \sum \frac{1}{R_i}$$
    O `RandomParallelCircuit` atua como sua respectiva *Factory* recursiva.
