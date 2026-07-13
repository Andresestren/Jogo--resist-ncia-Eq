

##  Modelagem Orientada a Objetos



### 1. Diagrama de Classes

O diagrama abaixo descreve a estrutura estática do sistema.

```mermaid
classDiagram
    %% ==========================================
    %% MODELO (A Lógica Matemática - Composite)
    %% ==========================================
    class AbstractCircuit {
        <<interface>>
        +getResistance() double
        +dumpCircuit(showResistance bool, level int) void
        +getBaseResistors() vector~AbstractCircuit*~
    }

    class Resistor {
        -_resistance : double
        +getResistance() double
        +dumpCircuit(showResistance bool, level int) void
        +getBaseResistors() vector~AbstractCircuit*~
    }

    class RandomResistor {
        -VALUES : double[]
        -VCOUNT : int
        +RandomResistor()
    }

    class SeriesCircuit {
        -_components : vector~AbstractCircuit*~
        +addComponent(c AbstractCircuit*)
        +getResistance() double
        +getBaseResistors() vector~AbstractCircuit*~
    }

    class RandomSeriesCircuit {
        +RandomSeriesCircuit(stages int, level int)
    }

    class ParallelCircuit {
        -_components : vector~AbstractCircuit*~
        +addComponent(c AbstractCircuit*)
        +getResistance() double
        +getBaseResistors() vector~AbstractCircuit*~
    }

    class RandomParallelCircuit {
        +RandomParallelCircuit(stages int, level int)
    }

    %% ==========================================
    %% CONTROLLER (Regras do Jogo)
    %% ==========================================
    class GameController {
        -alvoAtual : double
        -circuitoAtual : RandomSeriesCircuit*
        +gerarNovoCircuito() vector~AbstractCircuit*~
        +getAlvo() double
        +verificarVitoria(valorFinal double) bool
    }

    %% ==========================================
    %% VIEW (Interface Gráfica do Qt)
    %% ==========================================
    class CircuitGraphicsItem {
        +circuit : AbstractCircuit*
        +width : int
        +height : int
        +boundingRect() QRectF
        +paint(painter QPainter*, option QStyleOptionGraphicsItem*, widget QWidget*) void
    }

    class MainWindow {
        -ui : Ui::MainWindow*
        -cena : QGraphicsScene*
        -jogo : GameController
        -combinarSelecionados(emSerie bool) void
    }

    %% ==========================================
    %% RELACIONAMENTOS (Setas do Diagrama)
    %% ==========================================
    
    %% Herança (Setas brancas)
    AbstractCircuit <|-- Resistor
    Resistor <|-- RandomResistor
    AbstractCircuit <|-- SeriesCircuit
    SeriesCircuit <|-- RandomSeriesCircuit
    AbstractCircuit <|-- ParallelCircuit
    ParallelCircuit <|-- RandomParallelCircuit

    %% Agregação do Composite (Os losangos vazados)
    SeriesCircuit o-- AbstractCircuit : _components
    ParallelCircuit o-- AbstractCircuit : _components

    %% Interações MVC (Setas normais e associações)
    GameController *-- RandomSeriesCircuit : gerencia memória
    MainWindow *-- GameController : possui (jogo)
    MainWindow *-- CircuitGraphicsItem : desenha na cena
    CircuitGraphicsItem o-- AbstractCircuit : representa na tela






