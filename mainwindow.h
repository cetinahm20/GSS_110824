#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTextStream>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaRecorder>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVariant>
#include <QtCore>
#include <QtGui>
#include <QtQuick>
#include <vlc/vlc.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#pragma pack(push,1)
typedef struct tTelemetri{


    short int pakNo =0;
    unsigned char state =0;
    unsigned char hataKodu = 0;
    int64_t zaman=0;
    float bas1 =0;
    float bas2 =0;
    float yuk1 =0;
    float yuk2 =0;
    float fark =0;
    float hiz =0;
    float sic =0;
    float ger =0;
    float lat =0;
    float lon =0;
    float alt =0;
    float pitch =0;
    float roll =0;
    float yaw =0;
    short int rhrh=0;
    float iot=0;
    int takNo =0;


}Telemetri;
#pragma pack(pop)

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Telemetri telemetri;


signals:
        void newMessage(QString);
        void setCenter(QVariant,QVariant);
        void setLocMarker(QVariant,QVariant);
        void eulerFunction(QVariant, QVariant, QVariant);

private slots:



    void on_baslat_clicked(bool checked);
    void on_ayril_clicked();
   // void on_gonder_clicked();
    void on_rgb_clicked();
    void baslat_transfer();
    void timerFunc();
    void playVideo(QUrl filepath);
    void writeData();
    void rgbData();
    void iotData();


    //void newConnection();

    //void appendToSocketList(QTcpSocket* socket);

    void readData();

    //void readSocket();

    //void sendAttachment(QTcpSocket* socket);
    //void sendAttachment(QTcpSocket* socket, QString filePath);



private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QUdpSocket *socket1;
    QUdpSocket *socket2;
    QUdpSocket *socket4;
    QUdpSocket *socket5;
    QUdpSocket *socket6;
    //QTcpServer* m_server;
    //QSet<QTcpSocket*> connection_set;


};
#endif // MAINWINDOW_H
