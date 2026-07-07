#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void iniciarJogo(); // Função que gera o circuito e troca o ecrã
    void verificarCircuito(); // <--- NOVA FUNÇÃO (O Juiz do Jogo)

private:
    QStackedWidget *centralStack;
    QWidget *telaMenu;
    QWidget *telaJogo;

    float _resistenciaAlvo; // <--- NOVO: Guarda o alvo gerado pelo professor
};
#endif