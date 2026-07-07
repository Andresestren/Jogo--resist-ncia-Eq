#include "mainwindow.h"
#include "resistorgrafico.h"
#include "terminalgrafico.h"
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <vector>
#include <QMessageBox>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <map>

// Inclusões do código do professor
#include "abstractcircuit.h"
#include "resistor.h"
#include "seriescircuit.h"
#include "parallelcircuit.h"

// =========================================================================
// FUNÇÃO RECURSIVA: Extrai os valores dos resistores da árvore do professor
// =========================================================================
void extrairResistores(AbstractCircuit* circuit, std::vector<float>& listaResistores) {
    if (!circuit) return;

    Resistor* r = dynamic_cast<Resistor*>(circuit);
    if (r) {
        listaResistores.push_back(r->getResistance());
        return;
    }

    SeriesCircuit* s = dynamic_cast<SeriesCircuit*>(circuit);
    if (s) {
        for (AbstractCircuit* sub : s->getComponents()) {
            extrairResistores(sub, listaResistores);
        }
        return;
    }

    ParallelCircuit* p = dynamic_cast<ParallelCircuit*>(circuit);
    if (p) {
        for (AbstractCircuit* sub : p->getComponents()) {
            extrairResistores(sub, listaResistores);
        }
        return;
    }
}

// =========================================================================
// CONSTRUTOR: Prepara os ecrãs (Menu e Jogo)
// =========================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    centralStack = new QStackedWidget(this);
    setCentralWidget(centralStack);

    // --- 1. Configurar o Ecrã Inicial (Menu) ---
    telaMenu = new QWidget();
    QVBoxLayout *layoutMenu = new QVBoxLayout(telaMenu);

    QLabel *titulo = new QLabel("Simulador de Circuitos POO");
    QFont fonteTitulo("Arial", 20, QFont::Bold);
    titulo->setFont(fonteTitulo);
    titulo->setAlignment(Qt::AlignCenter);

    QPushButton *btnIniciar = new QPushButton("Iniciar Jogo");
    btnIniciar->setFixedSize(200, 50);

    layoutMenu->addWidget(titulo);
    layoutMenu->addWidget(btnIniciar, 0, Qt::AlignCenter);

    connect(btnIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJogo);
    centralStack->addWidget(telaMenu);

    // --- 2. Configurar o Ecrã de Jogo (O Tabuleiro Único) ---
    telaJogo = new QWidget();
    QVBoxLayout *layoutJogo = new QVBoxLayout(telaJogo);
    layoutJogo->setContentsMargins(0,0,0,0); // Remove margens

    // Cria a lente da câmera (View) que vai olhar para o tabuleiro
    QGraphicsView *viewPrincipal = new QGraphicsView();
    viewPrincipal->setObjectName("viewPrincipal"); // Nomeamos para achá-lo depois
    viewPrincipal->setRenderHint(QPainter::Antialiasing); // Deixa os fios bonitos
    layoutJogo->addWidget(viewPrincipal);

    centralStack->addWidget(telaJogo);
}

// =========================================================================
// LÓGICA DO JOGO: O que acontece quando clica em "Iniciar"
// =========================================================================
void MainWindow::iniciarJogo() {
    // 1. Gera o circuito e salva a resistência alvo na variável da classe
    RandomSeriesCircuit* circuitoPuzzle = new RandomSeriesCircuit(3, 3);
    _resistenciaAlvo = circuitoPuzzle->getResistance();

    // 2. Extrai a lista de resistores
    std::vector<float> valores;
    extrairResistores(circuitoPuzzle, valores);

    // 3. Aceder à View que criámos no construtor
    QGraphicsView *viewPrincipal = telaJogo->findChild<QGraphicsView*>("viewPrincipal");

    // 4. Cria a CENA ÚNICA GIGANTE (Onde tudo se vai passar)
    QGraphicsScene *cenaPrincipal = new QGraphicsScene(this);
    cenaPrincipal->setSceneRect(0, 0, 1000, 700);

    // 5. Desenha uma linha tracejada para separar visualmente o "Estoque" da "Mesa"
    cenaPrincipal->addLine(250, 0, 250, 700, QPen(Qt::gray, 2, Qt::DashLine));

    // 6. Coloca os Textos na Cena
    QGraphicsTextItem *textoAlvo = cenaPrincipal->addText("ALVO:\n" + QString::number(_resistenciaAlvo) + " Ohms");
    textoAlvo->setFont(QFont("Arial", 14, QFont::Bold));
    textoAlvo->setDefaultTextColor(Qt::darkRed);
    textoAlvo->setPos(50, 20);

    QGraphicsTextItem *textoMesa = cenaPrincipal->addText("MESA DE TRABALHO");
    textoMesa->setFont(QFont("Arial", 16, QFont::Bold));
    textoMesa->setDefaultTextColor(Qt::lightGray);
    textoMesa->setPos(500, 20);

    // 7. Instanciar e posicionar os resistores no Estoque (Lado Esquerdo)
    int posY = 120; // Posição vertical inicial
    for (float v : valores) {
        ResistorGrafico* resVisual = new ResistorGrafico(v);
        resVisual->setPos(125, posY); // Todos enfileirados no eixo X=125
        cenaPrincipal->addItem(resVisual); // Adiciona ao Tabuleiro Único
        posY += 60; // Dá um espaço para o próximo bloco não sobrepor
    }

    // --- CRIAR OS TERMINAIS A e B NA MESA DE TRABALHO ---
    // Terminal A (Entrada)
    TerminalGrafico* terminalA = new TerminalGrafico();
    terminalA->setPos(350, 350);
    cenaPrincipal->addItem(terminalA);

    QGraphicsTextItem *textoA = cenaPrincipal->addText("A");
    textoA->setFont(QFont("Arial", 12, QFont::Bold));
    textoA->setPos(320, 340);

    // Terminal B (Saída)
    TerminalGrafico* terminalB = new TerminalGrafico();
    terminalB->setPos(850, 350);
    cenaPrincipal->addItem(terminalB);

    QGraphicsTextItem *textoB = cenaPrincipal->addText("B");
    textoB->setFont(QFont("Arial", 12, QFont::Bold));
    textoB->setPos(865, 340);
    // ----------------------------------------------------

    // --- CRIAR O BOTÃO DE VERIFICAR NA LATERAL ---
    QPushButton *btnVerificar = new QPushButton("TESTAR CIRCUITO");
    btnVerificar->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold; font-size: 14px; border-radius: 5px;");
    btnVerificar->setFixedSize(200, 50);

    // Liga o clique do botão à função verificarCircuito()
    connect(btnVerificar, &QPushButton::clicked, this, &MainWindow::verificarCircuito);

    // Adiciona o botão no rodapé da barra lateral esquerda
    cenaPrincipal->addWidget(btnVerificar)->setPos(25, 600);
    // ---------------------------------------------

    // 8. Coloca a Cena na Lente (View) e troca o ecrã
    viewPrincipal->setScene(cenaPrincipal);
    centralStack->setCurrentWidget(telaJogo);
}
struct ResistorNetlist {
    int con1;
    int con2;
    float valor;

    ResistorNetlist(int c1, int c2, float v) : con1(c1), con2(c2), valor(v) {}

    int getCon1() const { return con1; }
    int getCon2() const { return con2; }
    float getValor() const { return valor; }
    void setValor(float v) { valor = v; }
    void setNos(int c1, int c2) { con1 = c1; con2 = c2; }
};

// Função auxiliar usando a nova estrutura
int contarOcorrencias(const std::vector<ResistorNetlist>& lista, int no) {
    int count = 0;
    for (const auto& r : lista) {
        if (r.getCon1() == no || r.getCon2() == no) count++;
    }
    return count;
}

// =========================================================================
// O JUIZ DO JOGO: Valida se o circuito do jogador está correto
// =========================================================================
void MainWindow::verificarCircuito() {
    QGraphicsScene* cena = telaJogo->findChild<QGraphicsView*>("viewPrincipal")->scene();

    std::map<TerminalGrafico*, int> nodeIds;
    int idCounter = 1;

    TerminalGrafico* termA = nullptr;
    TerminalGrafico* termB = nullptr;

    // 1. Mapeia todos os terminais do ecrã com um ID numérico único
    for (QGraphicsItem* item : cena->items()) {
        if (TerminalGrafico* t = dynamic_cast<TerminalGrafico*>(item)) {
            nodeIds[t] = idCounter++;
            // Identifica automaticamente os terminais alvo (A e B) pois eles não têm peças "mães"
            if (!t->parentItem()) {
                if (!termA) termA = t;
                else if (!termB) termB = t;
            }
        }
    }

    // 2. Funde os IDs dos terminais que estão ligados por fios (Algoritmo Union-Find)
    std::vector<int> parent(idCounter);
    for(int i = 1; i < idCounter; i++) parent[i] = i;

    auto findNode = [&parent](int i) {
        int root = i;
        while(root != parent[root]) root = parent[root];
        return root;
    };

    auto unionNodes = [&parent, &findNode](int i, int j) {
        int rootI = findNode(i);
        int rootJ = findNode(j);
        if(rootI != rootJ) parent[rootI] = rootJ;
    };

    for (auto const& [t, id] : nodeIds) {
        for (TerminalGrafico* vizinho : t->getConexoes()) {
            unionNodes(id, nodeIds[vizinho]);
        }
    }


    // 3. Monta a Netlist traduzindo o ecrã para a sua classe ResistorNetlist
    std::vector<ResistorNetlist> lista;
    for (QGraphicsItem* item : cena->items()) {
        if (ResistorGrafico* rg = dynamic_cast<ResistorGrafico*>(item)) {
            std::vector<TerminalGrafico*> terms;
            for(QGraphicsItem* child : rg->childItems()) {
                if (TerminalGrafico* t = dynamic_cast<TerminalGrafico*>(child)) terms.push_back(t);
            }
            if (terms.size() == 2) {
                int no1 = findNode(nodeIds[terms[0]]);
                int no2 = findNode(nodeIds[terms[1]]);
                if (no1 != no2) { // Evita curto-circuito na mesma peça
                    lista.push_back(ResistorNetlist(no1, no2, rg->getValor())); // <-- NOME CORRIGIDO AQUI
                }
            }
        }
    }
    // 4. O SEU ALGORITMO ORIGINAL DE SIMPLIFICAÇÃO
    bool houveAlteracao = true;
    while (houveAlteracao) {
        houveAlteracao = false;

        // --- TESTE DE PARALELO ---
        for (size_t i = 0; i < lista.size() && !houveAlteracao; i++) {
            for (size_t j = i + 1; j < lista.size(); j++) {
                if ((lista[i].getCon1() == lista[j].getCon1() && lista[i].getCon2() == lista[j].getCon2()) ||
                    (lista[i].getCon1() == lista[j].getCon2() && lista[i].getCon2() == lista[j].getCon1())) {
                    float r1 = lista[i].getValor();
                    float r2 = lista[j].getValor();
                    lista[i].setValor((r1 * r2) / (r1 + r2));
                    lista.erase(lista.begin() + j);
                    houveAlteracao = true;
                    break;
                }
            }
        }
        if (houveAlteracao) continue;

        // --- TESTE DE SÉRIE ---
        for (size_t i = 0; i < lista.size() && !houveAlteracao; i++) {
            int nos[2] = {lista[i].getCon1(), lista[i].getCon2()};
            for (int n = 0; n < 2; n++) {
                int noComum = nos[n];
                if (contarOcorrencias(lista, noComum) == 2) {
                    for (size_t j = 0; j < lista.size(); j++) {
                        if (i == j) continue;
                        if (lista[j].getCon1() == noComum || lista[j].getCon2() == noComum) {
                            int outroNo = (lista[j].getCon1() == noComum) ? lista[j].getCon2() : lista[j].getCon1();
                            int noPermanente = (nos[0] == noComum) ? nos[1] : nos[0];
                            float novoValor = lista[i].getValor() + lista[j].getValor();
                            lista[i].setNos(noPermanente, outroNo);
                            lista[i].setValor(novoValor);
                            lista.erase(lista.begin() + j);
                            houveAlteracao = true;
                            break;
                        }
                    }
                }
                if (houveAlteracao) break;
            }
        }
    }

    // 5. Verifica o resultado final entre os terminais A e B
    float resistenciaCalculada = 0.0;
    int alvoNoA = findNode(nodeIds[termA]);
    int alvoNoB = findNode(nodeIds[termB]);

    for (const auto& r : lista) {
        if ((r.getCon1() == alvoNoA && r.getCon2() == alvoNoB) ||
            (r.getCon1() == alvoNoB && r.getCon2() == alvoNoA)) {
            resistenciaCalculada = r.getValor();
            break;
        }
    }

    // Mensagem na tela
    QString mensagem;
    if (lista.size() == 1 && std::abs(resistenciaCalculada - _resistenciaAlvo) < 0.1f) {
        mensagem = " PARABÉNS! O circuito está CORRETO!\n\nResistência Equivalente: " + QString::number(resistenciaCalculada) + " Ohms";
        QMessageBox::information(this, "Sucesso", mensagem);
    } else {
        mensagem = " CIRCUITO INCORRETO!\n\nA sua montagem resultou em: " + QString::number(resistenciaCalculada) + " Ohms\nO Alvo exigido é: " + QString::number(_resistenciaAlvo) + " Ohms\n\nRevise as suas ligações e tente novamente!";
        QMessageBox::warning(this, "Falha", mensagem);
    }
}