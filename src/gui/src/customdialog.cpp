//
// Created by Boran on 25-6-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CustomDialog.h" resolved

#include "customdialog.h"
#include "ui_CustomDialog.h"


CustomDialog::CustomDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::CustomDialog) {
    ui->setupUi(this);

}

CustomDialog::~CustomDialog() {
    delete ui;
}

int CustomDialog::getCustomRows() const
{
    return ui->rowsSpinBox->value();
}

int CustomDialog::getCustomCols() const
{
    return ui->colsSpinBox->value();
}

int CustomDialog::getCustomMines() const
{
    return ui->mineSpinBox->value();
}

void CustomDialog::on_doneButton_clicked()
{
    if (this->getCustomRows() <= 0 || this->getCustomCols() <= 0 || this->getCustomMines() <= 0 ||
        this->getCustomRows() * this->getCustomCols() <= this->getCustomMines())
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("警告");
        msgBox.setText("非法的行列、雷输入！");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDetailedText("114514");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    this->accept();
}


