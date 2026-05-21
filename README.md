#  Jogo de Resistência Equivalente (Nome Provisório)

##  Sobre o Projeto
Este é um jogo educativo desenvolvido em **C++** com interface gráfica em **Qt**, criado como projeto para a disciplina de Programação Orientada a Objetos. O objetivo principal é desafiar o jogador a montar circuitos elétricos utilizando associações em série e paralelo para atingir um valor de resistência alvo.

##  Como Funciona
Em cada nível, o jogo fornece um **Valor Alvo de Resistência Equivalente** e uma "caixa" contendo vários resistores com valores predefinidos. 
O jogador deve organizar e conectar esses resistores na área de montagem para criar um circuito que resulte no valor exato pedido.

##  Principais Funcionalidades
- **Geração Aleatória com Garantia de Solução:** O motor do jogo não utiliza fases estáticas. Ele gera aleatoriamente um circuito válido por baixo dos panos, calcula sua resistência e depois "desmonta" as peças para o jogador resolver. 
- **Níveis de Dificuldade:** O algoritmo ajusta a complexidade das associações (quantidade de malhas e nós) de acordo com o nível escolhido.
- **Resistores Iscas:** Para aumentar o desafio, resistores extras que não faziam parte do circuito original gerado são misturados no inventário do jogador.
- **Interface Visual e Interativa:** Arrastar e soltar componentes e criar conexões facilmente usando as bibliotecas gráficas do framework Qt.


flowchart LR
    Jogador([Jogador])
    
    Jogador --> UC1(Iniciar Nova Partida)
    Jogador --> UC2(Selecionar Dificuldade)
    Jogador --> UC3(Adicionar Resistor na Área de Montagem)
    Jogador --> UC4(Remover Resistor da Área de Montagem)
    Jogador --> UC5(Criar Associação Série/Paralelo)
    Jogador --> UC6(Verificar Solução do Circuito)
    
    %% Inclusões e Extensões
    UC1 ..->|> include| UC2
    UC6 ..->|> extend| UC7(Avançar para Próximo Nível)

    classDiagram
    class Componente {
        <<abstract>>
        +calcularResistencia() double
    }

    class Resistor {
        -double valor
        +Resistor(double v)
        +calcularResistencia() double
    }

    class Associacao {
        <<abstract>>
        #List~Componente~ componentes
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
        +verificarVitoria(circuitoMontado: Componente) boolean
    }

    class GeradorDeCircuito {
        +gerarDesafio(dificuldade: int) List~Resistor~
        -gerarCircuitoAleatorio() Componente
    }

    Componente <|-- Resistor
    Componente <|-- Associacao
    Associacao <|-- AssociacaoSerie
    Associacao <|-- AssociacaoParalelo
    Associacao o-- Componente : "Contém"
    GerenciadorDeFase --> GeradorDeCircuito : "Utiliza"
