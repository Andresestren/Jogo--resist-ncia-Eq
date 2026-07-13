#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include "seriescircuit.h"
#include "parallelcircuit.h"



// Nossas bibliotecas e classes
#include "circuitgraphicsitem.h"
#include "resistor.h"
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // 2. Cria a nossa "Área de Trabalho" (Cena)
    cena = new QGraphicsScene(this);
    cena->setSceneRect(0, 0, 800, 600); // Define o tamanho da prancheta virtualZ

    // 3. Conecta a tela visual (a "lente") com a nossa cena invisível
    ui->graphicsView->setScene(cena);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //DESLIGA ROLAGEM
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //DESLIGA ROLAGEM



    // 3. Coloca uma mensagem inicial para o jogador em vez de gerar o nível
    ui->label->setText("Bem-vindo! Aperte 'Nova Partida' para começar.");

    // (Apagamos a chamada do botão daqui!)
}











MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    //1. Pega todos os itens que o jogador deixou "azuis" (selecionados) na prancheta
        QList<QGraphicsItem*> selecionados = cena->selectedItems();

    if(selecionados.size() != 2) {
        ui->label->setText("Erro: Selecione exatamente 2 blocos!"); // Troque 'label' se renomeou
        return;
    }

    // 2. Converte os itens genéricos para as nossas caixas de circuito
    CircuitGraphicsItem* item1 = dynamic_cast<CircuitGraphicsItem*>(selecionados[0]);
    CircuitGraphicsItem* item2 = dynamic_cast<CircuitGraphicsItem*>(selecionados[1]);

    // 3. A MÁGICA DA O.O.: Cria o circuito matemático
    SeriesCircuit* novoSerie = new SeriesCircuit();
    novoSerie->addComponent(item1->circuit);
    novoSerie->addComponent(item2->circuit);

    // 4. RECICLAGEM VISUAL: O item 1 absorve o novo circuito e fica no mesmo lugar!
    item1->circuit = novoSerie;
    item1->update(); // OBRIGATÓRIO: Avisa o Qt para repintar o texto com o novo valor!

    // 5. Limpa os rastros: remove o item 2 da tela e da memória
    cena->removeItem(item2);
    delete item2;

    // Limpa a seleção azul para a próxima jogada
    cena->clearSelection();
    ui->label->setText("Associado em Série com sucesso!");

    // --- VERIFICAÇÃO DE VITÓRIA ---
    if (cena->items().size() == 1) { // Se sobrou só um bloco na tela inteira
        double valorFinal = item1->circuit->getResistance();

        if (valorFinal == alvoAtual) { // Pode mudar para o valor que desejar
            ui->label->setText("Parabéns! Circuito fechado no valor exato!");
        } else {
            ui->label->setText(QString("Falhou! Circuito fechado em %1 ohms.").arg(valorFinal));
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QList<QGraphicsItem*> selecionados = cena->selectedItems();

    if(selecionados.size() != 2) {
        ui->label->setText("Erro: Selecione exatamente 2 blocos!");
        return;
    }

    CircuitGraphicsItem* item1 = dynamic_cast<CircuitGraphicsItem*>(selecionados[0]);
    CircuitGraphicsItem* item2 = dynamic_cast<CircuitGraphicsItem*>(selecionados[1]);

    // A única diferença: criamos um ParallelCircuit!
    ParallelCircuit* novoParalelo = new ParallelCircuit();
    novoParalelo->addComponent(item1->circuit);
    novoParalelo->addComponent(item2->circuit);

    item1->circuit = novoParalelo;
    item1->update(); // Repinta com o novo valor

    cena->removeItem(item2);
    delete item2;

    cena->clearSelection();
    ui->label->setText("Associado em Paralelo com sucesso!");

    if (cena->items().size() == 1) {
        double valorFinal = item1->circuit->getResistance();
        if (valorFinal == alvoAtual) { // Pode mudar para o valor que desejar
            ui->label->setText("Parabéns! Circuito fechado no valor exato!");
        } else {
            ui->label->setText(QString("Falhou! Circuito fechado em %1 ohms.").arg(valorFinal));
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    cena->clear(); // Limpa a prancheta

    RandomSeriesCircuit* circuitoGerador = nullptr;
    vector<AbstractCircuit*> pecas;

    // ---FILTRO ---
    // Ele vai ficar preso neste laço  até o gerador  cuspir um circuito que tenha entre 4 e 6 peças

    while (true) {
        // Gera um circuito com potencial grande
        circuitoGerador = new RandomSeriesCircuit(3, 3);

        // Pede as peças
        pecas = circuitoGerador->getBaseResistors();

        // Verifica se a quantidade está conforme
        if (pecas.size() == 4) {
            break; // Tamanho cert Quebra o laço e continua o jogo.
        } else {
            // Se veio muito fácil ou muito difícil, deletamos da memória e o laço repete
            delete circuitoGerador;
        }
    }
    // -------------------------------------


    alvoAtual = circuitoGerador->getResistance();
    ui->label_2->setText(QString("Objetivo: Alcançar %1 ohms").arg(alvoAtual));


    for(size_t i = 0; i < pecas.size(); i++) {
        CircuitGraphicsItem* itemVisual = new CircuitGraphicsItem(pecas[i]);

        int posX = 130 + ((i % 4) * 140);
        int posY = 150 + ((i / 4) * 120);
        itemVisual->setPos(posX, posY);

        cena->addItem(itemVisual);
    }
}


void MainWindow::on_label_linkActivated(const QString &link)
{

}

