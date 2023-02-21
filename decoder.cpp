#include "decoder.h"
#include "ui_decoder.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow * m;

Decoder::Decoder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Decoder)
{
    ui->setupUi(this);
}

Decoder::~Decoder()
{
    delete ui;
}

void error_msg(QString str) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(str);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet("*{background: #161616; color: white;} #QMessageBox::Ok{font-size: 12px;}");
    if(msgBox.exec() == msgBox.Ok) {
        msgBox.close();
    }
}

QImage encoded;

void Decoder::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Choose"),
                                                    "",
                                                    tr("Image()"));
    if(QString::compare(QString(), filename) != 0) {
        bool valid = encoded.load(filename);
        if(valid) {
            encoded.scaled(ui->label_3->width(),
                           ui->label_3->height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
            ui->label_3->setPixmap(QPixmap::fromImage(encoded));
        } else {
            error_msg("Encoded image failed to load!");
        }
    }
}

QImage _base, _target;

void Decoder::decode() {
    if(encoded.isNull()) {
        error_msg("Encoded image has not yet been loaded!");
    } else {
        _base = QImage(encoded.width(), encoded.height(), QImage::Format_RGB32);
        _target = QImage(encoded.width(), encoded.height(), QImage::Format_RGB32);
        for(int i = 0; i < encoded.height(); i++) {
            for(int j = 0; j < encoded.width(); j++) {
                QColor color(encoded.pixel(j, i));

                QColor t(((color.red() % 16) * 16),
                         ((color.green() % 16) * 16),
                         ((color.blue() % 16) * 16));

                _target.setPixelColor(j, i, t);

                QColor b(((color.red() / 16) * 16),
                         ((color.green() / 16) * 16),
                         ((color.blue() / 16) * 16));

                _base.setPixelColor(j, i, b);
            }
        }

        ui->label_2->setPixmap(QPixmap::fromImage(_base.scaled(ui->label_2->width(),
                                                               ui->label_2->height(),
                                                               Qt::KeepAspectRatio)));
        ui->label_4->setPixmap(QPixmap::fromImage(_target.scaled(ui->label_4->width(),
                                                                 ui->label_4->height(),
                                                                 Qt::KeepAspectRatio)));
    }
}

void Decoder::on_pushButton_2_clicked()
{
    decode();
}


void Decoder::on_pushButton_5_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this,
                                                    tr("Choose: "),
                                                    tr(""),
                                                    tr("Image (*.jpg .jpeg .png)"));
    if(filepath == NULL) {
        error_msg("Please select a valid save path.");
    } else {
        _base.save(filepath);
    }
}


void Decoder::on_pushButton_3_clicked()
{
    hide();
    m = new MainWindow();
    m->show();
}


void Decoder::on_pushButton_6_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this,
                                                    tr("Choose: "),
                                                    tr(""),
                                                    tr("Image (*.jpg .jpeg .png)"));
    if(filepath == NULL) {
        error_msg("Please select a valid save path.");
    } else {
        _target.save(filepath);
    }
}

