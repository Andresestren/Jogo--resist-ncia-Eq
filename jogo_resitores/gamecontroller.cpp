#include "gamecontroller.h"

GameController::~GameController() {
    delete circuitoAtual;
}

vector<AbstractCircuit*> GameController::gerarNovoCircuito(int stages, int level, int qtdPecas) {
    delete circuitoAtual; // remove o circuito anterior antes de gerar outro

    while (true) {
        circuitoAtual = new RandomSeriesCircuit(stages, level);    //PEDE PARA RAMDOMSERIESCIRCUIT GERAR UM CIRCUITO NOVO EM SERIESCIRCUIT
        vector<AbstractCircuit*> pecas = circuitoAtual->getBaseResistors();

        if (pecas.size() == qtdPecas) {
            alvoAtual = circuitoAtual->getResistance();
            return pecas;
        }

        delete circuitoAtual; // veio fora do tamanho certo, descarta e tenta de novo
    }
}



