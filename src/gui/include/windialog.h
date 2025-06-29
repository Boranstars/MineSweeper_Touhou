//
// Created by Boran on 25-6-30.
//

#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class WinDialog; }
QT_END_NAMESPACE

class WinDialog : public QDialog {
Q_OBJECT

public:
    explicit WinDialog(QWidget *parent = nullptr);
    WinDialog(int elapsedTime, QWidget *parent = nullptr);
    ~WinDialog() override;
signals:
    void restartRequested();       // “重新开始”信号
    void leaderboardRequested();   // “进入排行榜”信号
private:
    Ui::WinDialog *ui;
};


#endif //WINDIALOG_H
