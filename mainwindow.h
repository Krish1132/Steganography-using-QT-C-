#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_baseImageUploadButton_clicked();

    void on_targetImageUploadButton_clicked();

    void on_resetTarget_clicked();

    void on_resetBase_clicked();

    void encode();

    void on_encodeButton_clicked();

    void on_actionImage_decoder_triggered();

    void on_actionClear_base_image_triggered();

    void on_actionClear_target_image_triggered();

private:
    Ui::MainWindow *ui;
    Dialog* encoded;
};

#endif // MAINWINDOW_H
