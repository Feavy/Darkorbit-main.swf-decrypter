#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum FILE {MAIN, LOADINGSCREEN};

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    void fileSelected(const QString &file);
    void mainDownloaded(QNetworkReply *reply);
    void loadingscreenDownloaded(QNetworkReply *reply);
    void loadingscreenDecrypter(QByteArray &byteArray);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QFileDialog fileDialog;
    QString path;
    FILE selectedFile;
};

#endif // MAINWINDOW_H
