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
    cena->setSceneRect(0, 0, 800, 600); // Define o tamanho da prancheta virtual

    // 3. Conecta a tela visual (a "lente") com a nossa cena invisível
    ui->graphicsView->setScene(cena);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->label->setText("Bem-vindo! Aperte 'Nova Partida' para começar.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::combinarSelecionados(bool emSerie)
{
    QList<QGraphicsItem*> selecionados = cena->selectedItems();

    if (selecionados.size() != 2) {
        ui->label->setText("Erro: Selecione exatamente 2 blocos!");
        return;
    }

    CircuitGraphicsItem* item1 = dynamic_cast<CircuitGraphicsItem*>(selecionados[0]);
    CircuitGraphicsItem* item2 = dynamic_cast<CircuitGraphicsItem*>(selecionados[1]);

    // Cria o circuito matemático certo, série ou paralelo, conforme o botão apertado
    AbstractCircuit* novoCircuito;
    if (emSerie) {
        SeriesCircuit* s = new SeriesCircuit();
        s->addComponent(item1->circuit);
        s->addComponent(item2->circuit);
        novoCircuito = s;
    } else {
        ParallelCircuit* p = new ParallelCircuit();
        p->addComponent(item1->circuit);
        p->addComponent(item2->circuit);
        novoCircuito = p;
    }

    // RECICLAGEM VISUAL: o item 1 absorve o novo circuito e fica no mesmo lugar
    item1->circuit = novoCircuito;
    item1->update(); // repinta o texto com o novo valor

    // Remove o item 2 da tela e da memória
    cena->removeItem(item2);
    delete item2;

    cena->clearSelection();
    ui->label->setText(emSerie ? "Associado em Série com sucesso!"
                                : "Associado em Paralelo com sucesso!");

    // --- VERIFICAÇÃO DE VITÓRIA ---
    if (cena->items().size() == 1) {  // VERIFICA SE HÁ APENAS 1 PEÇA EM JOGO PARA TERMINAR A PARTIDA
        double valorFinal = item1->circuit->getResistance();  // PERGUNTA PARA GAMECONTROLER SE ESSE É O VALOR CORRETO

        if (jogo.verificarVitoria(valorFinal)) {  //GAMECONTROLER COMPARA E RESPONDE COM TRUE OU FALSE
            ui->label->setText("Parabéns! Circuito fechado no valor exato!");
        } else {
            ui->label->setText(QString("Falhou! Circuito fechado em %1 ohms.").arg(valorFinal));
        }
    }
}




//=======BOTÃO SÉRIE
void MainWindow::on_pushButton_clicked()
{
    combinarSelecionados(true); // true = série
}



//=======BOTÃO PARALELO
void MainWindow::on_pushButton_2_clicked()
{
    combinarSelecionados(false); // false = paralelo
}



//====BOTÃO FÁCIL
void MainWindow::on_pushButton_3_clicked()
{
    iniciarPartida(3, 3, 4); // 4 peças
}




//=====BOTÃO MÉDIO
void MainWindow::on_pushButton_4_clicked()
{
    iniciarPartida(4, 4, 6); // 6 peças
}



//=====BOTÃO DIFÍCIL
void MainWindow::on_pushButton_5_clicked()
{
    iniciarPartida(5, 5, 8); // 8 peças
}






//============== INICIA A PARTIDA

void MainWindow::iniciarPartida(int stages, int level, int qtdPecas)
{
    cena->clear(); // Limpa a prancheta

    vector<AbstractCircuit*> pecas = jogo.gerarNovoCircuito(stages, level, qtdPecas);

    ui->label_2->setText(QString("Objetivo: Alcançar %1 ohms").arg(jogo.getAlvo()));


    //embaralha antes de jogar na tela

    for (size_t i = pecas.size() - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        std::swap(pecas[i], pecas[j]);
    }



    //coloca as peças na tela
    for (size_t i = 0; i < pecas.size(); i++) {
        CircuitGraphicsItem* itemVisual = new CircuitGraphicsItem(pecas[i]);

        int posX = 130 + ((i % 4) * 140);
        int posY = 150 + ((i / 4) * 120);
        itemVisual->setPos(posX, posY);

        cena->addItem(itemVisual);
    }

}








