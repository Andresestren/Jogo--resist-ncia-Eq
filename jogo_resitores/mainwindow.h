#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "gamecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_label_linkActivated(const QString &link);

private:
    // Junta os 2 itens selecionados em série ou paralelo, dependendo de emSerie.
    // Substitui o código que estava duplicado entre os dois botões.
    void combinarSelecionados(bool emSerie);

    Ui::MainWindow *ui;
    QGraphicsScene *cena;

    GameController jogo; // toda a regra do jogo (alvo, geração de circuito, vitória) mora aqui
};

#endif // MAINWINDOW_H
