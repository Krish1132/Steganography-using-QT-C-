#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent, QImage result) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->encodedImage->setPixmap(QPixmap::fromImage(result));
}

Dialog::~Dialog()
{
    delete ui;
}

void failed_to_download(QString str) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(str);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet("*{background: #161616; color: white;} #QMessageBox::Ok{font-size: 12px;}");
    if(msgBox.exec() == msgBox.Ok) {
        msgBox.close();
    }
}

void Dialog::on_saveImageBtn_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("Choose: "), tr(""), tr("JPEG (*.jpg .jpeg);;PNG (.png)"));
    if(filepath == NULL) {
        failed_to_download("Please select a valid save path.");
    } else {
        const QPixmap* res = ui->encodedImage->pixmap();
        QImage encoded(res->toImage().scaled(ui->encodedImage->width(), ui->encodedImage->height(), Qt::KeepAspectRatio));
        encoded.save(filepath);
    }
}
