#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr, QImage result = QImage());
    ~Dialog();

private slots:
    void on_saveImageBtn_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
