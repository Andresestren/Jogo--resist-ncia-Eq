#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#pragma once

#include <vector>
#include "abstractcircuit.h"
#include "seriescircuit.h"

using namespace std;

// Cuida da REGRA DO JOGO: gerar o circuito alvo e conferir se o jogador venceu.
// Não sabe nada de QGraphicsScene, QPushButton, etc. Isso TA Na MainWindow.
class GameController {
public:
    GameController() = default;
    ~GameController();

    // Gera um circuito aleatório com nivel variado com os valores stages leevl qtdpeç
    // Devolve as peças (resistores) prontas para a MainWindow desenhar na tela.
   vector<AbstractCircuit*> gerarNovoCircuito(int stages, int level, int qtdPecas);

    double getAlvo() const { return alvoAtual; }

    bool verificarVitoria(double valorFinal) const {  //RECEBE O VALOR DA MAINWINDOW E COMPARA, RESPONDE TRUE OU FALSE
        return valorFinal == alvoAtual;
    }

private:
    double alvoAtual = 0.0;  //GARANTE QUE COMEÇA EM 0 (VALOR DO CIRCUITO)
    RandomSeriesCircuit* circuitoAtual = nullptr; // dono do circuito gerado, para poder deletar
};

#endif // GAMECONTROLLER_H
