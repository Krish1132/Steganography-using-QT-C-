#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "decoder.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setStyleSheet("background: url(:/images/menubar_bg.jpg); color: white;");
}

QImage result;

MainWindow::~MainWindow()
{
    delete ui;
}

void failed_to_load(QString str) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(str);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet("*{background: #161616; color: white;} #QMessageBox::Ok{font-size: 12px;}");
    if(msgBox.exec() == msgBox.Ok) {
        msgBox.close();
    }
}

void MainWindow::on_baseImageUploadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose:"), "", tr("Image ()"));
    if(QString::compare(QString(), filename) != 0) {
        QImage baseImage;
        bool valid = baseImage.load(filename);
        if(valid) {
            baseImage = baseImage.scaledToWidth(ui->baseImage->width(), Qt::SmoothTransformation);
            ui->baseImage->setPixmap(QPixmap::fromImage(baseImage));
        } else {
            failed_to_load("Base image failed to load!");
        }
    }
}


void MainWindow::on_targetImageUploadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose:"), "", tr("Images ()"));
    if(QString::compare(QString(), filename) != 0) {
        QImage targetImage;
        bool valid = targetImage.load(filename);
        if(valid) {
            targetImage = targetImage.scaledToWidth(ui->targetImage->width(), Qt::SmoothTransformation);
            ui->targetImage->setPixmap(QPixmap::fromImage(targetImage));
        } else {
            failed_to_load("Target image failed to load!");
        }
    }
}

void MainWindow::on_resetBase_clicked()
{
    ui->baseImage->setText(" ");
}

void MainWindow::on_resetTarget_clicked()
{
    ui->targetImage->setText(" ");
}

QColor modify(QColor baseP, QColor targetP) {
    int r = (floor(baseP.red() / 16) * 16) + floor(targetP.red() / 16);
    int g = (floor(baseP.green() / 16) * 16) + floor(targetP.green() / 16);
    int b = (floor(baseP.blue() / 16) * 16) + floor(targetP.blue() / 16);
    QColor resP(r, g, b, 255);
    return resP;
}

void MainWindow::encode() {
    const QPixmap* base = ui->baseImage->pixmap();
    const QPixmap* target = ui->targetImage->pixmap();

    if(!base) {
        failed_to_load("Base image has not been loaded yet!");
    } else if(!target) {
        failed_to_load("Target image has not been loaded yet!");
    } else {
        QImage b = QImage(base->toImage().convertToFormat(QImage::Format_RGB32));
        QImage t = QImage(target->toImage().scaled(b.width(), b.height()).convertToFormat(QImage::Format_RGB32));

        unsigned int dimX = t.height();
        unsigned int dimY = t.width();
        result = QImage(base->width(), base->height(), QImage::Format_RGB32);

        for(int i = 0; i < dimX; i++) {
            for(int j = 0; j < dimY; j++) {
                QColor targetP(t.pixel(j, i));
                QColor baseP(b.pixel(j, i));
                QColor resP = modify(baseP, targetP);
                result.setPixelColor(j, i, resP);
            }
        }

    }
}

void MainWindow::on_encodeButton_clicked()
{
    encode();
    if(ui->baseImage == NULL) {
        failed_to_load("Base image not yet loaded!");

    } else if(ui->targetImage == NULL) {
        failed_to_load("Target image not yet loaded!");
    } else {
        encoded = new Dialog(this, result);
        encoded->show();
    }
}


void MainWindow::on_actionImage_decoder_triggered()
{
    hide();
    Decoder decoder;
    decoder.setModal(true);
    decoder.exec();
}


void MainWindow::on_actionClear_base_image_triggered()
{
    ui->baseImage->setText(" ");
}


void MainWindow::on_actionClear_target_image_triggered()
{
    ui->targetImage->setText(" ");
}

