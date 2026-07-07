
// === Arquivo: resistorgrafico.h ===
#ifndef RESISTORGRAFICO_H
#define RESISTORGRAFICO_H

#include <QGraphicsItem>
#include <QPainter>

class ResistorGrafico : public QGraphicsItem {
public:
    // O construtor recebe o valor para exibir na tela
    ResistorGrafico(double resistencia);
    double getValor() const { return _valorResistencia; }
    // Contratos obrigatórios do QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    double _valorResistencia;
};

#endif