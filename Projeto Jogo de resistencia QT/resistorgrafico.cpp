// === Arquivo: resistorgrafico.cpp ===
#include "resistorgrafico.h"
#include "terminalgrafico.h" // <-- ADICIONE ESTE INCLUDE PARA RECONHECER O TERMINAL

ResistorGrafico::ResistorGrafico(double resistencia) {
    _valorResistencia = resistencia;

    // A mágica da Orientação a Objetos no Qt: Ativa a física de arrastar com o mouse!
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    // === ADICIONE OS TERMINAIS AQUI ===
    // Cria o terminal da esquerda e o prende ao bloco
    TerminalGrafico* t1 = new TerminalGrafico(this);
    t1->setPos(-50, 0);

    // Cria o terminal da direita e o prende ao bloco
    TerminalGrafico* t2 = new TerminalGrafico(this);
    t2->setPos(50, 0);
    // ==================================
}

QRectF ResistorGrafico::boundingRect() const {
    // Define uma "caixa de colisão" de 100x40 pixels, centralizada no eixo (0,0)
    return QRectF(-50, -20, 100, 40);
}

void ResistorGrafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 1. Desenha o fundo do retângulo (cinza claro) com borda preta
    painter->setBrush(QBrush(QColor(220, 220, 220)));
    painter->setPen(QPen(Qt::black, 2));
    painter->drawRect(-50, -20, 100, 40);

    // 2. Escreve o valor da resistência no centro do bloco
    painter->setPen(Qt::black);
    QFont fonte("Arial", 10, QFont::Bold);
    painter->setFont(fonte);

    QString texto = QString::number(_valorResistencia) + " Ohms";
    painter->drawText(boundingRect(), Qt::AlignCenter, texto);
}