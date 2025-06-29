//
// Created by Boran on 25-6-1.
//

#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomDialog; }
QT_END_NAMESPACE

class CustomDialog : public QDialog {
Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr);
    ~CustomDialog() override;
    int getCustomRows() const;
    int getCustomCols() const;
    int getCustomMines() const;
private slots:
    void on_doneButton_clicked();
private:
    Ui::CustomDialog *ui;
    int customRows;
    int customCols;
    int customMines;
};


#endif //CUSTOMDIALOG_H
