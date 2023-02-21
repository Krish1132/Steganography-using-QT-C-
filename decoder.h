#ifndef DECODER_H
#define DECODER_H

#include <QDialog>

namespace Ui {
class Decoder;
}

class Decoder : public QDialog
{
    Q_OBJECT

public:
    explicit Decoder(QWidget *parent = nullptr);
    ~Decoder();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void decode();

    void on_pushButton_6_clicked();

private:
    Ui::Decoder *ui;
};

#endif // DECODER_H
