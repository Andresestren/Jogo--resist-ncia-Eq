#include "gamecontroller.h"

GameController::~GameController() {
    delete circuitoAtual;
}

vector<AbstractCircuit*> GameController::gerarNovoCircuito() {
    delete circuitoAtual; // remove o circuito anterior antes de gerar outro

    while (true) {
        circuitoAtual = new RandomSeriesCircuit(3, 3);
        vector<AbstractCircuit*> pecas = circuitoAtual->getBaseResistors();

        if (pecas.size() == 4) {
            alvoAtual = circuitoAtual->getResistance();
            return pecas;
        }

        delete circuitoAtual; // veio fora do tamanho certo, descarta e tenta de novo
    }
}
