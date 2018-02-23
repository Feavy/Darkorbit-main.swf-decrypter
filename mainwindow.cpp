#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zlib.h"
#include <QFileDialog>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

#include <QtMath>

#include <QMessageBox>
#include "juge.h"

QByteArray hicyfyn(QString param1)
{
   QByteArray _loc2_;
   int _loc3_ = param1.length() & 1;
   if(_loc3_ == 1)
   {
      param1 = "0" + param1;
   }
   unsigned int _loc4_ = 0;
   while(_loc4_ < param1.length())
   {
      _loc2_[_loc4_ / 2] = param1.mid(_loc4_, 2).toInt(nullptr, 16);
      _loc4_ = _loc4_ + 2;
   }
   return _loc2_;
}

unsigned int unsignedRightShift(int a, int b){
    unsigned int A = (unsigned int)a;
    return A >> b;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileDialog(this, "Save file to...")
{
    ui->setupUi(this);
    setFixedSize(size());
    connect(&fileDialog, &QFileDialog::fileSelected, this, &MainWindow::fileSelected);
    qDebug() << (195 ^ unsignedRightShift(93, 2));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    if(ui->lineEdit->text().length() == 0){
        QMessageBox(QMessageBox::Warning, "Error", "You must put the key before decrypting main.swf.", QMessageBox::Ok).exec();
        return;
    }
    selectedFile = FILE::MAIN;
    fileDialog.showNormal();
}

void MainWindow::on_pushButton_2_clicked() {
    selectedFile = FILE::LOADINGSCREEN;
    fileDialog.showNormal();
}

void MainWindow::fileSelected(const QString &file){
    qDebug() << "File selected ! " << "Path = " << file;
    path = file;
    QNetworkRequest request;
    if(selectedFile == FILE::MAIN){
        connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::mainDownloaded);
        request.setUrl(QUrl("http://darkorbit-22.bpsecure.com/spacemap/main.swf"));
    }else if(selectedFile == FILE::LOADINGSCREEN){
        connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::loadingscreenDownloaded);
        request.setUrl(QUrl("http://darkorbit-22.bpsecure.com/spacemap/loadingscreen.swf"));
    }
    manager.get(request);
}

void MainWindow::mainDownloaded(QNetworkReply *reply){
    disconnect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::mainDownloaded);
    qDebug() << "Preloader downloaded !";
    QByteArray byteArray;
    int length;
    char data[500];
    while((length = reply->read(data, 500)) >= 0) {
        byteArray.append(data, length);
    }
    int size = byteArray.length();

    byteArray.prepend( (unsigned int)((size >> 0) & 0xFF));
    byteArray.prepend( (unsigned int)((size >> 8) & 0xFF));
    byteArray.prepend( (unsigned int)((size >> 16) & 0xFF));
    byteArray.prepend( (unsigned int)((size >> 24) & 0xFF));
    byteArray = qUncompress(byteArray);

    Juge(hicyfyn(ui->lineEdit->text())).lapih(byteArray);

    char ver = byteArray[3];

    byteArray.remove(0, 4);

    char c1, c2, c3, c4;

    c4 = byteArray[3];
    c3 = byteArray[2];
    c2 = byteArray[1];
    c1 = byteArray[0];
    byteArray[3] = c1;
    byteArray[2] = c3;
    byteArray[1] = c2;
    byteArray[0] = c4;

    byteArray = qUncompress(byteArray);

    byteArray.prepend(c4);
    byteArray.prepend(c3);
    byteArray.prepend(c2);
    byteArray.prepend(c1);
    byteArray.prepend(ver);
    byteArray.prepend((unsigned int)0x53);
    byteArray.prepend((unsigned int)0x57);
    byteArray.prepend((unsigned int)0x46);

    QFile file(path);
    file.open(QFile::WriteOnly);
    file.write(byteArray);
    file.flush();
    file.close();
    qDebug() << "File saved !";
}

void MainWindow::loadingscreenDownloaded(QNetworkReply *reply){
    disconnect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::loadingscreenDownloaded);
    qDebug() << "Loadingscreen downloaded !";
    QByteArray byteArray;
    int length;
    char data[500];
    while((length = reply->read(data, 500)) >= 0) {
        byteArray.append(data, length);
    }
    int size = byteArray.length();

    qDebug() << "new version";

    byteArray.prepend( (unsigned int)((size >> 0) & 0xFF));
    byteArray.prepend( (unsigned int)((size >> 8) & 0xFF));
    byteArray.prepend( (unsigned int)((size >> 16) & 0xFF));
    byteArray.prepend( (unsigned int)((size >> 24) & 0xFF));
    byteArray = qUncompress(byteArray);
    qDebug() << "Size after uncompression : " << byteArray.length();

    loadingscreenDecrypter(byteArray);

    QFile file(path);
    file.open(QFile::WriteOnly);
    file.write(byteArray);
    file.flush();
    file.close();

    qDebug() << "File saved !";

    byteArray.remove(0, 4);

    char c1, c2, c3, c4;

    c4 = byteArray[3];
    c3 = byteArray[2];
    c2 = byteArray[1];
    c1 = byteArray[0];
    byteArray[3] = c1;
    byteArray[2] = c3;
    byteArray[1] = c2;
    byteArray[0] = c4;

    byteArray = qUncompress(byteArray);

    QString currentKey = "";
    int currentKeyLength = 0;
    int keyCollected = 0;

    for(int i = 0; i < byteArray.size(); i++){
        char c = byteArray[i];
        int val = (int)c;
        if(val >= 48 && val <= 57 && currentKeyLength < 50){
            currentKey += c;
            currentKeyLength++;
        }else{
            if(currentKeyLength > 10 && currentKeyLength != 50){
                keyCollected++;
                if(keyCollected == 1) { // Changer ici pour changer entre la première clé et la seconde
                    ui->lineEdit->setText(currentKey);
                    break;
                }
            }
            currentKeyLength = 0;
            currentKey = "";
        }
    }

    /*byteArray.prepend(c4);
    byteArray.prepend(c3);
    byteArray.prepend(c2);
    byteArray.prepend(c1);
    byteArray.prepend(0x15);
    byteArray.prepend((unsigned int)0x53);
    byteArray.prepend((unsigned int)0x57);
    byteArray.prepend((unsigned int)0x46);

    QFile file2(path.split(".")[0]+"_uncompressed.swf");
    file2.open(QFile::WriteOnly);
    file2.write(byteArray);
    file2.flush();
    file2.close();*/
}

void MainWindow::loadingscreenDecrypter(QByteArray &byteArray){
    unsigned int _loc3_ = 0;
    unsigned int _loc4_ = 0;
    unsigned int _loc2_ = byteArray.length();
    unsigned int _loc5_ = 57;
    int _loc6_ = 0;
    while(_loc6_ < _loc2_)
    {
       _loc5_ = (unsigned int)((unsigned int)(_loc5_ + 3) & 255);
       _loc4_ = _loc5_ & 4;
       _loc3_ = byteArray[_loc6_];
       byteArray[_loc6_] = (unsigned char)(_loc3_ ^ _loc5_);
       _loc6_++;
    }
}
