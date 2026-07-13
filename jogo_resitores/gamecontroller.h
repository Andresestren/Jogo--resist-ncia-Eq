#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#pragma once

#include <vector>
#include "abstractcircuit.h"
#include "seriescircuit.h"

using namespace std;

// Cuida da REGRA DO JOGO: gerar o circuito alvo e conferir se o jogador venceu.
// Não sabe nada de QGraphicsScene, QPushButton, etc. Isso é problema da MainWindow.
class GameController {
public:
    GameController() = default;
    ~GameController();

    // Gera um circuito aleatório com exatamente 4 resistores base e guarda o valor alvo.
    // Devolve as peças (resistores) prontas para a MainWindow desenhar na tela.
    vector<AbstractCircuit*> gerarNovoCircuito();

    double getAlvo() const { return alvoAtual; }

    bool verificarVitoria(double valorFinal) const {
        return valorFinal == alvoAtual;
    }

private:
    double alvoAtual = 0.0;
    RandomSeriesCircuit* circuitoAtual = nullptr; // dono do circuito gerado, para poder deletar
};

#endif // GAMECONTROLLER_H
