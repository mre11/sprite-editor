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
    void GetResults(int &width, int &height);

private:
    Ui::NewSpriteDialog *ui;

};

#endif // NEWSPRITEDIALOG_H
