//
// Created by Boran on 25-6-1.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include <QScreen>
#include "customdialog.h"
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
private:
    CustomDialog *_customDialog;
    MineSweeperTouHou::GameBoard *_gameBoard;
    int fitnessW;
    int fitnessH;
private:

private:
    void createActions();
private:
    void setCustomLevel();
    void resizeWindow();
private slots:
   void on_restartButton_clicked();
public:
    void init();
};


#endif //MAINWINDOW_H
