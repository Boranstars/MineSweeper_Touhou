//
// Created by 杨博元 on 25-6-30.
//

#ifndef LOSTDIALOG_H
#define LOSTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class LostDialog; }
QT_END_NAMESPACE

class LostDialog : public QDialog {
Q_OBJECT

public:
    explicit LostDialog(QWidget *parent = nullptr);
    ~LostDialog() override;
signals:
    void restartRequested();       // “重新开始”信号
    void exitGameRequested();
private:
    Ui::LostDialog *ui;
};


#endif //LOSTDIALOG_H
