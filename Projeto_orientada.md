## Diagrama de Classes
```mermaid
classDiagram
    class Componente {
        <<abstract>>
        +calcularResistencia() double
    }

    class Resistor {
        -double valor
        +Resistor(v: double)
        +calcularResistencia() double
    }

    class Associacao {
        <<abstract>>
        #QList componentes
        +adicionarComponente(c: Componente)
        +removerComponente(c: Componente)
        +calcularResistencia() double
    }

    class AssociacaoSerie {
        +calcularResistencia() double
    }

    class AssociacaoParalelo {
        +calcularResistencia() double
    }

    class GerenciadorDeFase {
        -double resistenciaAlvo
        -int dificuldade
        +iniciarFase(dificuldade: int)
        +verificarVitoria(circuito: Componente) boolean
    }

    class GeradorDeCircuito {
        +gerarDesafio(dificuldade: int)
        -gerarCircuitoAleatorio() Componente
    }

    Componente <|-- Resistor
    Componente <|-- Associacao
    Associacao <|-- AssociacaoSerie
    Associacao <|-- AssociacaoParalelo
    Associacao o-- Componente : Contem
    GerenciadorDeFase --> GeradorDeCircuito : Utiliza
