

##  Modelagem Orientada a Objetos



### 1. Diagrama de Classes

O diagrama abaixo descreve a estrutura estática do sistema.

```mermaid
classDiagram
    class ComponenteEletrico {
        <<abstract>>
        +calcularResistencia() double*
        +validarConexao() boolean*
    }
    class Resistor {
        -resistencia: double
        +Resistor(valor: double)
        +calcularResistencia() double
        +validarConexao() boolean
    }
    class Associacao {
        <<abstract>>
        #componentes: List~ComponenteEletrico~
        +adicionarComponente(c: ComponenteEletrico) void
        +removerComponente(c: ComponenteEletrico) void
        +validarConexao() boolean
    }
    class AssociacaoSerie {
        +calcularResistencia() double
    }
    class AssociacaoParalela {
        +calcularResistencia() double
    }
    class Inventario {
        -resistoresDisponiveis: List~Resistor~
        +obterResistor(id: int) Resistor
        +devolverResistor(r: Resistor) void
        +verificarLimite() boolean
    }
    class Fase {
        -resistenciaAlvo: double
        -tentativas: int
        -concluida: boolean
        -dificuldade: int
        -margemErro: double
        +Fase(dificuldade: int)
        +validarCircuito(circuitoMontado: ComponenteEletrico) boolean
        +calcularPontuacao() int
    }
    class GeradorCircuitos {
        +gerarFase(dificuldade: int) Fase
        -gerarCircuitoValido(dificuldade: int) ComponenteEletrico
        -gerarIscas(quantidade: int) List~Resistor~
    }

    %% Relacionamentos de Herança (Generalização)
    ComponenteEletrico <|-- Resistor
    ComponenteEletrico <|-- Associacao
    Associacao <|-- AssociacaoSerie
    Associacao <|-- AssociacaoParalela

    %% Aplicação do Composite Pattern
    Associacao o-- ComponenteEletrico : agrupa
    
    %% Composições e Dependências de Controle
    Fase *-- Inventario : possui
    GeradorCircuitos ..> Fase : instancia
    Fase ..> ComponenteEletrico : valida

  ```








