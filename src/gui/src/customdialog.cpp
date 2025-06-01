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
