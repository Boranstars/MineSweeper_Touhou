//
// Created by Boran on 25-6-1.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include <QScreen>
#include <QMouseEvent>
#include <QTimer>
#include "customdialog.h"
#include "windialog.h"
#include "lostdialog.h"
#include "scenewidget.h"
#include "gameboard.h"
#include "constants.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:

    Ui::MainWindow *ui;
    QTimer *_timer;
    int elapsedTime = 0;
    CustomDialog *_customDialog;
    MineSweeperTouHou::GameBoard *_gameBoard;

    int fitnessW;
    int fitnessH;



private:
    void createActions();
    void createConnections();
private:
    void setCustomLevel();
    void resizeWindow();
private slots:
    void on_restartButton_clicked();
    void on_GameWon();
    void on_GameLost();
    void on_FlagsChanged(int flags);
    void on_StatusChanged(MineSweeperTouHou::GameStatus newStatus);
    void on_FirstClicked();
    void on_GamePaused();
public:
    void init();
};


#endif //MAINWINDOW_H
