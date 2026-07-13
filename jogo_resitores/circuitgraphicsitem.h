#ifndef CIRCUITGRAPHICSITEM_H
#define CIRCUITGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "abstractcircuit.h"

// Herdamos do QGraphicsItem para poder viver livremente na cena
class CircuitGraphicsItem : public QGraphicsItem {
public:
    AbstractCircuit* circuit;

    // Dimensões do nosso bloco
    int width = 120;
    int height = 80;

    CircuitGraphicsItem(AbstractCircuit* c) : circuit(c) {
        // A MÁGICA DO ARRASTO: Estas duas linhas dizem ao Qt que o jogador
        // pode clicar, arrastar livremente e selecionar este item!
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
    }

    // 1. OBRIGATÓRIO: Define a área que o mouse consegue clicar
    QRectF boundingRect() const override {
        return QRectF(0, 0, width, height);
    }

    // 2. OBRIGATÓRIO: É aqui que você "pinta" o visual do componente
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        QRectF rect = boundingRect();

        // Verifica se o jogador clicou no item para mudar a cor de fundo
        if (isSelected()) {
            painter->setBrush(QColor("#3498db")); // Azul se selecionado
        } else {
            painter->setBrush(QColor("#f0f0f0")); // Cinza padrão
        }


        // Prepara para desenhar o texto
        if (isSelected()) {
            painter->setPen(Qt::white); // Texto branco no fundo azul
        } else {
            painter->setPen(Qt::black); // Texto preto no fundo cinza
        }

        // Busca o valor da resistência do seu código de Orientação a Objetos
        double res = circuit->getResistance();
        QString texto = QString("\n%1 ohms").arg(res);




        // Define uma caneta mais grossa para o símbolo
        painter->setPen(QPen(Qt::black, 3));

        // Desenha os terminais (linhas horizontais)
        painter->drawLine(20, 25, 40, 25); // Linha esquerda
        painter->drawLine(80, 25, 100, 25); // Linha direita

        // Desenha o corpo do resistor IEC (um retângulo no meio)
        painter->drawRect(40, 15, 40, 20);

        // Se quiser usar o símbolo em Zigue-Zague (padrão americano),
        // você usaria uma sequência de painter->drawLine(...) subindo e descendo!




        // Imprime o texto bem no centro do retângulo
        painter->drawText(rect, Qt::AlignCenter, texto);
    }
};

#endif // CIRCUITGRAPHICSITEM_H