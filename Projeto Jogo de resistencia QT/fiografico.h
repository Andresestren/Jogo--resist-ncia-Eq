#pragma once
#include <QGraphicsPathItem>
#include <QPen>
#include <QPainterPath>
#include <QKeyEvent>
#include <QGraphicsScene>

// Promessa ao C++ de que a classe Terminal existe (evita erro de include cruzado)
class TerminalGrafico;

class FioGrafico : public QGraphicsPathItem {
public:
    TerminalGrafico* term1 = nullptr;
    TerminalGrafico* term2 = nullptr;

    FioGrafico(QPointF inicio);
    void atualizarPontoFinal(QPointF fim);
    void atualizarPosicoes(); // Faz o fio esticar se as peças moverem

protected:
    // Eventos do Qt para escutar cliques e teclado
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPointF pontoInicial;
    QPointF pontoFinal;
};