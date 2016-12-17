// A7: Sprite Editor
// CS 3505, University of Utah, Fall 2016
// Braden Klunker, Michael Swisher, Morgan Empey, Naoki Tominaga, Ryan Williams

#ifndef NEWSPRITEDIALOG_H
#define NEWSPRITEDIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class NewSpriteDialog;
}

class NewSpriteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSpriteDialog(QWidget *parent = 0);
    ~NewSpriteDialog();

    // Gets the users width and height selection.
    void getResults(int &width, int &height);

private:
    Ui::NewSpriteDialog *ui;

};

#endif // NEWSPRITEDIALOG_H
