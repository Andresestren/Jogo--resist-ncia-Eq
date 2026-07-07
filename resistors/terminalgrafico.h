#pragma once
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QBrush>
#include <vector>
#include <algorithm>
#include "fiografico.h"

class TerminalGrafico : public QGraphicsEllipseItem {
public:
    std::vector<FioGrafico*> fiosConectados;

    TerminalGrafico(QGraphicsItem *parent = nullptr) : QGraphicsEllipseItem(-6, -6, 12, 12, parent) {
        setBrush(Qt::blue);
        setAcceptHoverEvents(true);
        // Avisa ao terminal toda vez que ele for movido na cena
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    }

    void atualizarCor() {
        if (!fiosConectados.empty()) setBrush(Qt::green);
        else setBrush(Qt::blue); // Volta a ser azul se o último fio for deletado
    }

    // Função chamada quando o jogador apaga o fio
    void removerFio(FioGrafico* fio) {
        fiosConectados.erase(std::remove(fiosConectados.begin(), fiosConectados.end(), fio), fiosConectados.end());
        atualizarCor();
    }

    // Traduz a visualização dos fios para a matemática do MainWindow
    std::vector<TerminalGrafico*> getConexoes() const {
        std::vector<TerminalGrafico*> vizinhos;
        for(FioGrafico* fio : fiosConectados) {
            if(fio->term1 == this && fio->term2) vizinhos.push_back(fio->term2);
            else if(fio->term2 == this && fio->term1) vizinhos.push_back(fio->term1);
        }
        return vizinhos;
    }

protected:
    // A MÁGICA DO ELÁSTICO: Se o terminal mexer, manda os fios esticarem!
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemScenePositionHasChanged) {
            for (FioGrafico* fio : fiosConectados) {
                fio->atualizarPosicoes();
            }
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        fioTemporario = new FioGrafico(scenePos());
        fioTemporario->term1 = this; // O fio sabe onde nasceu
        scene()->addItem(fioTemporario);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        if (fioTemporario) fioTemporario->atualizarPontoFinal(event->scenePos());
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        if (fioTemporario) {
            QList<QGraphicsItem*> itensSobORato = scene()->items(event->scenePos());
            TerminalGrafico* terminalDestino = nullptr;

            for(QGraphicsItem* item : itensSobORato) {
                terminalDestino = dynamic_cast<TerminalGrafico*>(item);
                if(terminalDestino && terminalDestino != this) break;
            }

            if(terminalDestino) {
                fioTemporario->term2 = terminalDestino; // O fio sabe onde terminou
                fioTemporario->atualizarPontoFinal(terminalDestino->scenePos());

                this->fiosConectados.push_back(fioTemporario);
                terminalDestino->fiosConectados.push_back(fioTemporario);

                this->atualizarCor();
                terminalDestino->atualizarCor();
            } else {
                delete fioTemporario;
            }
            fioTemporario = nullptr;
        }
    }

private:
    FioGrafico* fioTemporario = nullptr;
};