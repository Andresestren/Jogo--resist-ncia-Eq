#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow janela;
    janela.resize(1000, 700); // Tamanho confortável para um jogo
    janela.setWindowTitle("Simulador de Circuitos POO - Resistor Puzzle");
    janela.show();

    return app.exec();
}