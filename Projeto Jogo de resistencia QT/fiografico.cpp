#include "fiografico.h"
#include "terminalgrafico.h"

FioGrafico::FioGrafico(QPointF inicio) {
    setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    pontoInicial = inicio;
    setZValue(-1); // Fica por baixo dos resistores

    // A MÁGICA: Permite que o fio seja clicado e selecionado (para poder apagar)
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}

void FioGrafico::atualizarPontoFinal(QPointF fim) {
    pontoFinal = fim;
    QPainterPath caminho;
    caminho.moveTo(pontoInicial);

    // Matemática dos 90 graus
    float meioX = (pontoInicial.x() + pontoFinal.x()) / 2.0;
    caminho.lineTo(meioX, pontoInicial.y());
    caminho.lineTo(meioX, pontoFinal.y());
    caminho.lineTo(pontoFinal);
    setPath(caminho);
}

// Faz o fio esticar como um elástico se o jogador arrastar a peça
void FioGrafico::atualizarPosicoes() {
    if (term1 && term2) {
        pontoInicial = term1->scenePos();
        atualizarPontoFinal(term2->scenePos());
    }
}

// Feedback Visual: Fica VERMELHO se você clicar em cima dele!
QVariant FioGrafico::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemSelectedHasChanged) {
        setPen(QPen(isSelected() ? Qt::red : Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    return QGraphicsPathItem::itemChange(change, value);
}

// O Apagador de Fios
void FioGrafico::keyPressEvent(QKeyEvent *event) {
    // Se o jogador pressionar Delete ou Backspace
    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        // 1. Avisa aos terminais que eles não estão mais ligados
        if (term1) term1->removerFio(this);
        if (term2) term2->removerFio(this);

        // 2. Apaga-se da tela e da memória!
        scene()->removeItem(this);
        delete this;
    } else {
        QGraphicsPathItem::keyPressEvent(event);
    }
}