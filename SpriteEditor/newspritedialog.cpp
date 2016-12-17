// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#include "newspritedialog.h"
#include "ui_newspritedialog.h"

NewSpriteDialog::NewSpriteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSpriteDialog)
{
    ui->setupUi(this);
}

NewSpriteDialog::~NewSpriteDialog()
{
    delete ui;
}

void NewSpriteDialog::getResults(int &width, int &height)
{
    QString selection = ui->comboBox->currentText();
    QStringList list;
    list = selection.split('x');
    width = list.at(0).toInt();
    height = list.at(1).toInt();
}
