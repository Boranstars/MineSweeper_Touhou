//
// Created by Boran on 25-6-1.
//

#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class CustomDialog; }
QT_END_NAMESPACE

class CustomDialog : public QDialog {
Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr);
    ~CustomDialog() override;

private:
    Ui::CustomDialog *ui;
};


#endif //CUSTOMDIALOG_H
