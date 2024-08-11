#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFile>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUrl>
#include <QMediaContent>
#include <QMediaRecorder>
#include <QUdpSocket>
#include <QVariant>
#include <QtCore>
#include <QtGui>
#include <vlc/vlc.h>
#include <gst/gst.h>
#include <QRandomGenerator>

void MainWindow::playVideo(QUrl filepath){



    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    player->setMedia(filepath);
    player->setVolume(10);


    vw->setFixedSize(500,340);
    vw->move(2030,425);
    player->play();



}
/*
void MainWindow::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}


// TCP Soket listesine soket ekleyen fonksiyon
void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    qDebug()<<QString::number(socket->socketDescriptor());
    qDebug()<<QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor());
}


void MainWindow::readSocket()
{



    QTcpSocket* socket3 = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket3);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;


    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Verilerin gelmesi bekleniyor...").arg(socket3->socketDescriptor());
        emit newMessage(message);
        return;
    }

    buffer = buffer.mid(128);


            QString filePath ="C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/uyvid2.mpg";
            QFile file(filePath);
            if(file.open(QIODevice::WriteOnly)){
                file.write(buffer);

            }else
                QMessageBox::critical(this,"QTCPServer", "Dosya gönderilirken bir hata oluştu!");


}
void MainWindow::sendAttachment(QTcpSocket* socket)
{
        qDebug()<<"datagram";
    if(socket)
    {
        if(socket->isOpen())
        {

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);


            QByteArray byteArray ;
            byteArray.append(telemetri.rhrh>>8);
            byteArray.append(telemetri.rhrh);
            socketStream.setVersion(QDataStream::Qt_5_15);
            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");

    if(socket)
    {
        if(socket->isOpen())
        {
           QFile m_file(filePath);
            if(m_file.open(QIODevice::ReadOnly)){

                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());

                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
                header.resize(128);

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);

                socketStream << byteArray;



            }else
                QMessageBox::critical(this,"QTCPClient","Couldn't open the attachment!");
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");



}
*/
void MainWindow::readData()
{
    while (socket4->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket4->pendingDatagramSize());
        socket4->readDatagram(datagram.data(), datagram.size());


        qDebug() << "Datagram raw data:" << datagram.toHex()<<","<<datagram.size();
      //  qDebug()<<datagram<<","<<datagram.size();

     /*    QDataStream stream(datagram);
        stream.setByteOrder(QDataStream::LittleEndian);
       stream >>telemetri.pakNo>>telemetri.state>>telemetri.hataKodu>>telemetri.zaman>>telemetri.bas1>>telemetri.bas2
                >>telemetri.yuk1>>telemetri.yuk2>> telemetri.fark>> telemetri.hiz>>telemetri.sic>>telemetri.ger
                >>telemetri.lat>>telemetri.lon>>telemetri.alt>>telemetri.pitch
                >>telemetri.roll>>telemetri.yaw >> telemetri.rhrh >> telemetri.iot >>telemetri.takNo;

*/



            // Veriyi ayır ve struct'a aktar
            int index = 0;

            // short int pakNo
            telemetri.pakNo = qFromLittleEndian<short>(reinterpret_cast<const uchar*>(datagram.mid(index, 2).constData()));
            index += 2;

            // unsigned char state
            telemetri.state = static_cast<unsigned char>(datagram[index]);
            index += 1;

            // unsigned char hataKodu
            telemetri.hataKodu = static_cast<unsigned char>(datagram[index]);
            index += 1;

            // long int zaman
            telemetri.zaman = qFromLittleEndian<int64_t>(reinterpret_cast<const uchar*>(datagram.mid(index, 8).constData()));
            index += 8;

            // float bas1
            telemetri.bas1 = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float bas2
            telemetri.bas2 = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float yuk1
            telemetri.yuk1 = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float yuk2
            telemetri.yuk2 = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float fark
            telemetri.fark = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float hiz
            telemetri.hiz = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float sic
            telemetri.sic = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float ger
            telemetri.ger = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float lat
            telemetri.lat = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float lon
            telemetri.lon = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float alt
            telemetri.alt = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float pitch
            telemetri.pitch = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float roll
            telemetri.roll = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // float yaw
            telemetri.yaw = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // short int rhrh
            telemetri.rhrh = qFromLittleEndian<short>(reinterpret_cast<const uchar*>(datagram.mid(index, 2).constData()));
            index += 2;

            // float iot
            telemetri.iot = qFromLittleEndian<float>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
            index += 4;

            // int takNo
            telemetri.takNo = qFromLittleEndian<int>(reinterpret_cast<const uchar*>(datagram.mid(index, 4).constData()));
         //   index += 4;

}

}

//UDP prokolüyle veri atma
void MainWindow::writeData(){


    QByteArray datagram;
    datagram.append('1');
    QHostAddress receiverAddress("172.20.10.5");

    socket2->writeDatagram(datagram,datagram.size(),receiverAddress, 65433);



    //qDebug()<<datagram.size();
}

void MainWindow::rgbData()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::BigEndian);
    out << telemetri.rhrh;
    QHostAddress receiverAddress("172.20.10.5");

    socket1->writeDatagram(datagram, receiverAddress, 65432);
  //  qDebug()<<datagram.size()<<","<<datagram;

}

void MainWindow::iotData()
{
    float iot=31.31;
    QHostAddress receiverAddress("172.20.10.5");
    QByteArray datagram;
    datagram.resize(sizeof(float));

    // float değeri QByteArray'e yazma
    qToLittleEndian(iot, reinterpret_cast<uchar*>(datagram.data()));

    // Datagram boyutunu ve içeriğini kontrol etme
    //qDebug() << datagram.size() << "," << datagram.toHex();

    // Datagram'ı UDP ile gönderme
    socket5->writeDatagram(datagram, receiverAddress, 65434);
}

void MainWindow::baslat_transfer()
{
    QByteArray datagram;
    datagram.append('1');
    QHostAddress receiverAddress("172.20.10.5");

    socket6->writeDatagram(datagram,datagram.size(),receiverAddress, 65433);


}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->harita->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->harita->show();

    auto Obje =ui->harita->rootObject();
    connect(this,SIGNAL(setCenter(QVariant,QVariant)),Obje,SLOT(setCenter(QVariant,QVariant)));
    connect(this,SIGNAL(setLocMarker(QVariant,QVariant)),Obje,SLOT(setLocMarker(QVariant,QVariant)));

    emit setCenter(telemetri.lat,telemetri.lon);
    emit setLocMarker(telemetri.lat,telemetri.lon);

    QPixmap pix(":/img/img/TayfLogo.png");
    ui->logo->setPixmap(pix);

    ui->threed->setSource(QUrl(QStringLiteral("qrc:/durus.qml")));
    ui->threed->show();

    auto obj2 = ui->threed->rootObject();
    connect(this, SIGNAL(eulerFunction(QVariant,QVariant,QVariant)), obj2, SLOT(eulerFunction(QVariant,QVariant,QVariant)));
    emit eulerFunction(telemetri.roll, telemetri.yaw, telemetri.pitch);

/*
    //TCP Serverin açıldığı ve portun dinlenmeye başlandığı kısım
    m_server = new QTcpServer();

     if(m_server->listen(QHostAddress::Any, 9090))
    {

      connect(m_server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
        qDebug()<<"Server is listening...";
    }
    else
    {
      QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }

*/

    //Ayrılma komutunu gönderen udpsoketin açılması
    socket2 = new QUdpSocket(this);

    socket2->bind(QHostAddress::Any, 65433);

    //Filtreleme komutunu gönderen udpsoketin açılması
    socket1 = new QUdpSocket(this);

    socket1->bind(QHostAddress::Any, 65432);

    //Verileri alan udpsoketin açılması
    socket4 = new QUdpSocket(this);

    socket4->bind(QHostAddress::Any, 23456);

    //IoT verisini gönderen udpsoketin açılması
    socket5 = new QUdpSocket(this);

    socket5->bind(QHostAddress::Any, 65434);

    //Uçuş Yazılımını başlatan udpsoketin açılması
    socket6 = new QUdpSocket(this);

    socket6->bind(QHostAddress::Any, 65435);

    //Timer'ı oluşturan ve slotlarını bağlayan kısım
    timer = new QTimer(this);
    connect(timer, SIGNAL (timeout()),this,SLOT(timerFunc()));

    //Grafiklerin scatter ve fontlarını tanımlayan kısım
    QCPScatterStyle myScatter;
    myScatter.setShape(QCPScatterStyle::ssDisc);
    myScatter.setPen(QPen(Qt::black));
    myScatter.setSize(2);

    QFont plotFont= font();
    plotFont.setPointSize(6);


    //Grafiklerin ilk görünüşlerini ve fontlarını belirleyen kısım
    ui->bas1p->addGraph();

    ui->bas1p->graph(0)->setScatterStyle(myScatter);
    ui->bas1p->graph(0)->setLineStyle(QCPGraph::lsLine);

    QPen pen(QColor(169, 169, 169));
    pen.setWidth(4);

    QPen penB(QColor(169, 169, 169));
    pen.setWidth(13);

    ui->bas1p->graph(0)->setPen(pen);

    ui->bas1p->graph(0)->setPen(pen);

    ui->bas1p->setBackground(QBrush(Qt::transparent));

    ui->bas1p->xAxis->setLabel("Paket Numarası");
    ui->bas1p->yAxis->setLabel("Basınç(Pa)");
    ui->bas1p->xAxis->setLabelFont(plotFont);
    ui->bas1p->xAxis->setTickLabelFont(plotFont);
    ui->bas1p->yAxis->setLabelFont(plotFont);
    ui->bas1p->yAxis->setTickLabelFont(plotFont);
    ui->bas1p->xAxis->setTickLabelColor(Qt::white);
    ui->bas1p->xAxis->setLabelColor(Qt::white);
    ui->bas1p->xAxis->setSubTickPen(QPen(Qt::white));
    ui->bas1p->xAxis->setBasePen(QPen(Qt::white));
    ui->bas1p->yAxis->setTickLabelColor(Qt::white);
    ui->bas1p->yAxis->setLabelColor(Qt::white);
    ui->bas1p->yAxis->setSubTickPen(QPen(Qt::white));
    ui->bas1p->yAxis->setBasePen(QPen(Qt::white));
    ui->bas1p->xAxis->setRange(-55,-5);
    ui->bas1p->yAxis->setRange(1000,1200);

    ui->bas2p->addGraph();

    ui->bas2p->graph(0)->setScatterStyle(myScatter);
    ui->bas2p->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->bas2p->graph(0)->setPen(pen);
    ui->bas2p->setBackground(QBrush(Qt::transparent));


    ui->bas2p->xAxis->setLabel("Paket Numarası");
    ui->bas2p->yAxis->setLabel("Basınç(Pa)");
    ui->bas2p->xAxis->setLabelFont(plotFont);
    ui->bas2p->xAxis->setTickLabelFont(plotFont);
    ui->bas2p->yAxis->setLabelFont(plotFont);
    ui->bas2p->yAxis->setTickLabelFont(plotFont);
    ui->bas2p->xAxis->setTickLabelColor(Qt::white);
    ui->bas2p->xAxis->setLabelColor(Qt::white);
    ui->bas2p->xAxis->setSubTickPen(QPen(Qt::white));
    ui->bas2p->xAxis->setBasePen(QPen(Qt::white));
    ui->bas2p->yAxis->setTickLabelColor(Qt::white);
    ui->bas2p->yAxis->setLabelColor(Qt::white);
    ui->bas2p->yAxis->setSubTickPen(QPen(Qt::white));
    ui->bas2p->yAxis->setBasePen(QPen(Qt::white));
    ui->bas2p->xAxis->setRange(-55,5);
    ui->bas2p->yAxis->setRange(1000,1200);

           ui->yuk1p->addGraph();

           ui->yuk1p->graph(0)->setScatterStyle(myScatter);
           ui->yuk1p->graph(0)->setLineStyle(QCPGraph::lsLine);
           ui->yuk1p->graph(0)->setPen(penB);
           ui->yuk1p->setBackground(QBrush(Qt::transparent));


           ui->yuk1p->xAxis->setLabel("Paket Numarası");
           ui->yuk1p->yAxis->setLabel("Yükseklik(m)");
           ui->yuk1p->xAxis->setLabelFont(plotFont);
           ui->yuk1p->xAxis->setTickLabelFont(plotFont);
           ui->yuk1p->yAxis->setLabelFont(plotFont);
           ui->yuk1p->yAxis->setTickLabelFont(plotFont);
           ui->yuk1p->xAxis->setTickLabelColor(Qt::white);
           ui->yuk1p->xAxis->setLabelColor(Qt::white);
           ui->yuk1p->xAxis->setSubTickPen(QPen(Qt::white));
           ui->yuk1p->xAxis->setBasePen(QPen(Qt::white));
           ui->yuk1p->yAxis->setTickLabelColor(Qt::white);
           ui->yuk1p->yAxis->setLabelColor(Qt::white);
           ui->yuk1p->yAxis->setSubTickPen(QPen(Qt::white));
           ui->yuk1p->yAxis->setBasePen(QPen(Qt::white));
           ui->yuk1p->xAxis->setRange(-55,5);
           ui->yuk1p->yAxis->setRange(0,700);

           ui->yuk2p->addGraph();

           ui->yuk2p->graph(0)->setScatterStyle(myScatter);
           ui->yuk2p->graph(0)->setLineStyle(QCPGraph::lsLine);
           ui->yuk2p->graph(0)->setPen(penB);
           ui->yuk2p->setBackground(QBrush(Qt::transparent));


           ui->yuk2p->xAxis->setLabel("Paket Numarası");
           ui->yuk2p->yAxis->setLabel("Yükseklik(m)");
           ui->yuk2p->xAxis->setLabelFont(plotFont);
           ui->yuk2p->xAxis->setTickLabelFont(plotFont);
           ui->yuk2p->yAxis->setLabelFont(plotFont);
           ui->yuk2p->yAxis->setTickLabelFont(plotFont);
           ui->yuk2p->xAxis->setTickLabelColor(Qt::white);
           ui->yuk2p->xAxis->setLabelColor(Qt::white);
           ui->yuk2p->xAxis->setSubTickPen(QPen(Qt::white));
           ui->yuk2p->xAxis->setBasePen(QPen(Qt::white));
           ui->yuk2p->yAxis->setTickLabelColor(Qt::white);
           ui->yuk2p->yAxis->setLabelColor(Qt::white);
           ui->yuk2p->yAxis->setSubTickPen(QPen(Qt::white));
           ui->yuk2p->yAxis->setBasePen(QPen(Qt::white));
           ui->yuk2p->xAxis->setRange(-55,5);
           ui->yuk2p->yAxis->setRange(0,700);


                  ui->sicp->addGraph();

                  ui->sicp->graph(0)->setScatterStyle(myScatter);
                  ui->sicp->graph(0)->setLineStyle(QCPGraph::lsLine);
                  ui->sicp->graph(0)->setPen(pen);
                  ui->sicp->setBackground(QBrush(Qt::transparent));


                  ui->sicp->xAxis->setLabel("Paket Numarası");
                  ui->sicp->yAxis->setLabel("Sıcaklık(C°)");
                  ui->sicp->xAxis->setLabelFont(plotFont);
                  ui->sicp->xAxis->setTickLabelFont(plotFont);
                  ui->sicp->yAxis->setLabelFont(plotFont);
                  ui->sicp->yAxis->setTickLabelFont(plotFont);
                  ui->sicp->xAxis->setTickLabelColor(Qt::white);
                  ui->sicp->xAxis->setLabelColor(Qt::white);
                  ui->sicp->xAxis->setSubTickPen(QPen(Qt::white));
                  ui->sicp->xAxis->setBasePen(QPen(Qt::white));
                  ui->sicp->yAxis->setTickLabelColor(Qt::white);
                  ui->sicp->yAxis->setLabelColor(Qt::white);
                  ui->sicp->yAxis->setSubTickPen(QPen(Qt::white));
                  ui->sicp->yAxis->setBasePen(QPen(Qt::white));



                  ui->inisp->addGraph();

                  ui->inisp->graph(0)->setScatterStyle(myScatter);
                  ui->inisp->graph(0)->setLineStyle(QCPGraph::lsLine);
                  ui->inisp->graph(0)->setPen(pen);
                  ui->inisp->setBackground(QBrush(Qt::transparent));

                  ui->inisp->xAxis->setLabel("Paket Numarası");
                  ui->inisp->yAxis->setLabel("İniş Hızı(m/s)");
                  ui->inisp->xAxis->setLabelFont(plotFont);
                  ui->inisp->xAxis->setTickLabelFont(plotFont);
                  ui->inisp->yAxis->setLabelFont(plotFont);
                  ui->inisp->yAxis->setTickLabelFont(plotFont);
                  ui->inisp->xAxis->setTickLabelColor(Qt::white);
                  ui->inisp->xAxis->setLabelColor(Qt::white);
                  ui->inisp->xAxis->setSubTickPen(QPen(Qt::white));
                  ui->inisp->xAxis->setBasePen(QPen(Qt::white));
                  ui->inisp->yAxis->setTickLabelColor(Qt::white);
                  ui->inisp->yAxis->setLabelColor(Qt::white);
                  ui->inisp->yAxis->setSubTickPen(QPen(Qt::white));
                  ui->inisp->yAxis->setBasePen(QPen(Qt::white));



                         ui->farkp->addGraph();

                         ui->farkp->graph(0)->setScatterStyle(myScatter);
                         ui->farkp->graph(0)->setLineStyle(QCPGraph::lsLine);
                         ui->farkp->graph(0)->setPen(pen);
                         ui->farkp->setBackground(QBrush(Qt::transparent));


                         ui->farkp->xAxis->setLabel("Paket Numarası");
                         ui->farkp->yAxis->setLabel("Fark (m)");
                         ui->farkp->xAxis->setLabelFont(plotFont);
                         ui->farkp->xAxis->setTickLabelFont(plotFont);
                         ui->farkp->yAxis->setLabelFont(plotFont);
                         ui->farkp->yAxis->setTickLabelFont(plotFont);
                         ui->farkp->xAxis->setTickLabelColor(Qt::white);
                         ui->farkp->xAxis->setLabelColor(Qt::white);
                         ui->farkp->xAxis->setSubTickPen(QPen(Qt::white));
                         ui->farkp->xAxis->setBasePen(QPen(Qt::white));
                         ui->farkp->yAxis->setTickLabelColor(Qt::white);
                         ui->farkp->yAxis->setLabelColor(Qt::white);
                         ui->farkp->yAxis->setSubTickPen(QPen(Qt::white));
                         ui->farkp->yAxis->setBasePen(QPen(Qt::white));



                         ui->voltp->addGraph();

                         ui->voltp->graph(0)->setScatterStyle(myScatter);
                         ui->voltp->graph(0)->setLineStyle(QCPGraph::lsLine);
                         ui->voltp->graph(0)->setPen(pen);
                         ui->voltp->setBackground(QBrush(Qt::transparent));


                         ui->voltp->xAxis->setLabel("Paket Numarası");
                         ui->voltp->yAxis->setLabel("Gerilim (Volt)");
                         ui->voltp->xAxis->setLabelFont(plotFont);
                         ui->voltp->xAxis->setTickLabelFont(plotFont);
                         ui->voltp->yAxis->setLabelFont(plotFont);
                         ui->voltp->yAxis->setTickLabelFont(plotFont);
                         ui->voltp->xAxis->setTickLabelColor(Qt::white);
                         ui->voltp->xAxis->setLabelColor(Qt::white);
                         ui->voltp->xAxis->setSubTickPen(QPen(Qt::white));
                         ui->voltp->xAxis->setBasePen(QPen(Qt::white));
                         ui->voltp->yAxis->setTickLabelColor(Qt::white);
                         ui->voltp->yAxis->setLabelColor(Qt::white);
                         ui->voltp->yAxis->setSubTickPen(QPen(Qt::white));
                         ui->voltp->yAxis->setBasePen(QPen(Qt::white));
                         ui->voltp->xAxis->setRange(-55,5);
                         ui->voltp->yAxis->setRange(0,10);

                         ui->nemp->addGraph();

                         ui->nemp->graph(0)->setScatterStyle(myScatter);
                         ui->nemp->graph(0)->setLineStyle(QCPGraph::lsLine);
                         ui->nemp->graph(0)->setPen(pen);
                         ui->nemp->setBackground(QBrush(Qt::transparent));


                         ui->nemp->xAxis->setLabel("Paket Numarası");
                         ui->nemp->yAxis->setLabel("Nem (g/m^3)");
                         ui->nemp->xAxis->setLabelFont(plotFont);
                         ui->nemp->xAxis->setTickLabelFont(plotFont);
                         ui->nemp->yAxis->setLabelFont(plotFont);
                         ui->nemp->yAxis->setTickLabelFont(plotFont);
                         ui->nemp->xAxis->setTickLabelColor(Qt::white);
                         ui->nemp->xAxis->setLabelColor(Qt::white);
                         ui->nemp->xAxis->setSubTickPen(QPen(Qt::white));
                         ui->nemp->xAxis->setBasePen(QPen(Qt::white));
                         ui->nemp->yAxis->setTickLabelColor(Qt::white);
                         ui->nemp->yAxis->setLabelColor(Qt::white);
                         ui->nemp->yAxis->setSubTickPen(QPen(Qt::white));
                         ui->nemp->yAxis->setBasePen(QPen(Qt::white));
                         ui->nemp->xAxis->setRange(30,30);
                         ui->nemp->yAxis->setRange(0,20);


                         //Yeni verilerin geldiğini belirten uyarı yazısını csv'ye ekleyen kısım
                         QFile File("TMUY2024_ 1592571 _TLM.csv");

                         File.open(QIODevice::Append |QIODevice::WriteOnly);


                               QTextStream stream(&File);
                               stream<< "Pak No" <<","<<"State"<<","<<"Hata Kodu"<<","<<"Saat"<<","<<"Basinc1"<<","<<"Basinc2"<<","
                                     <<"Yukseklik1"<<","<<"Yukseklik2"<<","<<"Fark"<<","<<"Hiz"<<","<<"Sicaklik"<<","<<"Gerilim"
                                     <<","<<"Enlem"<<","<<"Boylam"<<","<<"GPS Yukseklik"<<","<<"Pitch"<<","<<"Roll"<<","
                                     <<"Yaw"<<","<<"RHRH"<<","<<"Nem"<<","<<"Takim No"<<","<<
                                       "\n";



                         File.close();

                        playVideo(QUrl::fromLocalFile("C:/Users/aali_/OneDrive/Masaüstü/Proje Takimi/2022-2023 Model Uydu Yarışması/Yer İstasyonu/Tools/uyvid1.mpg"));

    QPixmap dur_1(":/img/img/yesil.png");

    ui->kod1->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
    ui->kod2->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
    ui->kod3->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
    ui->kod4->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
    ui->kod5->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{


   delete ui;
}
//Ayrıl butonunun fonksiyonunun belirlendiği kısım
void MainWindow::on_ayril_clicked()
{

   writeData();

}
/*
//Gönder butonunun fonksiyonunun belirlendiği kısım
void MainWindow::on_gonder_clicked()
{

    QString receiver = "Broadcast";

    QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg *.mp4)"));

    if(filePath.isEmpty()){
        QMessageBox::critical(this,"QTCPClient","You haven't selected any attachment!");
        return;
    }

    if(receiver=="Broadcast")
    {
        foreach (QTcpSocket* socket,connection_set)
        {
            sendAttachment(socket, filePath);
        }
    }
    else
    {
        foreach (QTcpSocket* socket,connection_set)
        {
            if(socket->socketDescriptor() == receiver.toLongLong())
            {
                sendAttachment(socket, filePath);
                break;
            }
        }
    }

}
*/

//Başlat butonunun fonksiyonunun belirlendiği kısım
void MainWindow::on_baslat_clicked(bool checked)
{

    if(checked==true){

//  ui->baslat->setText("Durdur");


   timer->start(1000);
    baslat_transfer();

    }

 else{

//        ui->baslat->setText("Başlat");
        timer->stop();


    }

}

void MainWindow::on_rgb_clicked()
{


    telemetri.rhrh =0;

    QString rhrh_string= ui->rhrh_kod->text();


    if(rhrh_string.at(1)=='G'){

        telemetri.rhrh= telemetri.rhrh | 0x01;
    }

    if(rhrh_string.at(1)=='B'){

        telemetri.rhrh= telemetri.rhrh | 0x02;
    }

    if(rhrh_string.at(1)=='R'){

        telemetri.rhrh= telemetri.rhrh | 0x04;
    }
    if(rhrh_string.at(3)=='G'){

        telemetri.rhrh= telemetri.rhrh | (0x01<<8);
    }
    if(rhrh_string.at(3)=='B'){

        telemetri.rhrh= telemetri.rhrh | (0x02<<8);
    }
    if(rhrh_string.at(3)=='R'){

        telemetri.rhrh= telemetri.rhrh | (0x04<<8);
    }

    QChar sec_f=rhrh_string.at(0);
    QChar sec_s=rhrh_string.at(2);

    telemetri.rhrh= telemetri.rhrh | (sec_f.digitValue()<<3) | (sec_s.digitValue()<<11);

    rgbData();




}


void MainWindow::timerFunc(){

    telemetri.pakNo+=1;
    readData();
    iotData();

     emit setCenter(telemetri.lat,telemetri.lon);
     emit setLocMarker(telemetri.lat,telemetri.lon);
     emit eulerFunction(telemetri.roll, telemetri.yaw, telemetri.pitch);
    telemetri.roll+=10;
    telemetri.yaw+=10;
    telemetri.pitch+=10;

    //Gelen verilerin grafik için değişkenler atandığı kısım

    //telemetri.bas1 = QRandomGenerator::global()->bounded(1000, 1200);
    //telemetri.hataKodu=1;
    int  x=telemetri.pakNo;
    double  y1=telemetri.bas1;
    double  y2=telemetri.bas2;
    double  y3=telemetri.yuk1;
    double  y4=telemetri.yuk2;
    double  y5=telemetri.sic;
    double  y6=telemetri.hiz;
    double  y7=telemetri.fark;
    double  y8=telemetri.ger;





    //Verilerin grafiklerinin güncellenmesini ver düzgün gözükmesini sağlayan kısım
    ui->bas1p->addGraph();
    ui->bas1p->graph(0)->addData(x, y1);
    ui->bas1p->xAxis->setRange(x-55,x+5);
    ui->bas1p->yAxis->setRange(1000,1200);
         ui->bas1p->replot();
         ui->bas1p->update();


                 ui->bas2p->addGraph();
                 ui->bas2p->graph(0)->addData(x, y2);
                 ui->bas2p->xAxis->setRange(x-55,x+5);
                 ui->bas2p->yAxis->setRange(1000,1200);
                        ui->bas2p->replot();
                        ui->bas2p->update();


                  ui->yuk1p->addGraph();
                  ui->yuk1p->graph(0)->addData(x, y3);
                  ui->yuk1p->xAxis->setRange(x-55,x+5);
                  ui->yuk1p->yAxis->setRange(0,700);
                          ui->yuk1p->replot();
                          ui->yuk1p->update();


                          ui->yuk2p->addGraph();
                          ui->yuk2p->graph(0)->addData(x, y4);
                          ui->yuk2p->xAxis->setRange(x-55,x+5);
                          ui->yuk2p->yAxis->setRange(0,700);

                                  ui->yuk2p->replot();
                                  ui->yuk2p->update();


                          ui->sicp->addGraph();
                          ui->sicp->graph(0)->addData(x, y5);
                          ui->sicp->xAxis->setRange(x-55,x+5);
                          ui->sicp->yAxis->setRange(20,40);
                                  ui->sicp->replot();
                                  ui->sicp->update();


                                          ui->inisp->addGraph();
                                          ui->inisp->graph(0)->addData(x, y6);
                                          ui->inisp->xAxis->setRange(x-55,x+5);
                                          ui->inisp->yAxis->setRange(0,20);
                                                  ui->inisp->replot();
                                                  ui->inisp->update();


                                          ui->farkp->addGraph();
                                          ui->farkp->graph(0)->addData(x, y7);
                                          ui->farkp->xAxis->setRange(x-55,x+5);
                                          ui->farkp->yAxis->setRange(0,250);
                                                  ui->farkp->replot();
                                                  ui->farkp->update();


                                                          ui->voltp->addGraph();
                                                          ui->voltp->graph(0)->addData(x, y8);
                                                          ui->voltp->xAxis->setRange(x-55,x+5);
                                                          ui->voltp->yAxis->setRange(0,10);
                                                                  ui->voltp->replot();
                                                                  ui->voltp->update();


                                                                  ui->nemp->addGraph();
                                                                  ui->nemp->graph(0)->addData(x, y8);
                                                                  ui->nemp->xAxis->setRange(x-55,x+5);
                                                                  ui->nemp->yAxis->setRange(0,20);
                                                                          ui->nemp->replot();
                                                                          ui->nemp->update();




    // Yıl, ay, gün, saat, dakika ve saniye verilerini alıyoruz

    QString datetimeStr=QString::number(telemetri.zaman);

    QString year = datetimeStr.mid(0, 4);
    QString month = datetimeStr.mid(4, 2);
    QString day = datetimeStr.mid(6, 2);
    QString hour = datetimeStr.mid(8, 2);
    QString minute = datetimeStr.mid(10, 2);
    QString second = datetimeStr.mid(12, 2);

    // Formatlanmış string oluşturuyoruz
    QString formattedDateTime = day + "/" + month + "/" + year + " " + hour + ":" + minute + ":" + second;

    //Güncel verileri string haline getiren kısım, bu şekilde verileri csvye kaydetmek ve list widgeta eklemek daha kolay oluyor
    QString data= QString::number(telemetri.pakNo)+ ", " + QString::number(telemetri.state) + ", "
          + QString::number(telemetri.hataKodu) + ", "  + formattedDateTime + ", "
          + QString::number(telemetri.bas1) + ", "  + QString::number(telemetri.bas2) + ", " + QString::number(telemetri.yuk1) +
          ", " + QString::number(telemetri.yuk2) + ", " + QString::number(telemetri.fark) + ", " +
          QString::number(telemetri.hiz)+ ", " +QString::number(telemetri.sic) + ", " + QString::number(telemetri.ger) +
          ", " + QString::number(telemetri.lat) + ", " + QString::number(telemetri.lon) + ", " +
          QString::number(telemetri.alt) + ", " +QString::number(telemetri.pitch)+"," + QString::number(telemetri.roll)+
          ", " + QString::number(telemetri.yaw) + ", " + QString::number(telemetri.rhrh) + ", "
          + QString::number(telemetri.iot) + ", "+ QString::number(telemetri.takNo);


    //Verileri list widgeta ekleyen ve otomatik olarak kaydıran kısım
    ui->telemetry->addItem(data);
    ui->telemetry->scrollToBottom();




    //İrtifa Farkını güncelleyen kısım
    ui->irtifa->setText("İRTİFA FARKI: " + QString::number(telemetri.fark));


    //Verileri csv uzantılı dosyaya kaydeden kısım
    QFile File("TMUY2024_ 1592571 _TLM.csv");

    File.open(QIODevice::Append |QIODevice::WriteOnly);


          QTextStream stream(&File);
          stream<< data +"\n";



    File.close();


    QPixmap dur_1(":/img/img/yesil.png");
    QPixmap dur_2(":/img/img/kirmizi.png");

    QMediaPlayer *sound = new QMediaPlayer;
    sound->setMedia(QUrl::fromLocalFile("C:/Users/aali_/OneDrive/Belgeler/GroundStation1_1/img/buzzer.mp3"));
    sound->setVolume(50);




    if((telemetri.hataKodu & 0x01) ==1 )
    {
        ui->kod1->setPixmap(dur_2.scaled(35,35,Qt::KeepAspectRatio));
        sound->play();
    }
    else{
        ui->kod1->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
    }
    if(((telemetri.hataKodu & 0x02)>>1) ==1){

        ui->kod2->setPixmap(dur_2.scaled(35,35,Qt::KeepAspectRatio));
        sound->play();

    }
    else{
        ui->kod2->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));

    }
    if(((telemetri.hataKodu & 0x04)>>2) ==1){

        ui->kod3->setPixmap(dur_2.scaled(35,35,Qt::KeepAspectRatio));
        sound->play();

    }
    else{
        ui->kod3->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));

    }
    if(((telemetri.hataKodu & 0x08)>>3) ==1){

        ui->kod4->setPixmap(dur_2.scaled(35,35,Qt::KeepAspectRatio));
        sound->play();

    }
    else{
        ui->kod4->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));

    }
    if(((telemetri.hataKodu & 0x10)>>4) ==1){

        ui->kod5->setPixmap(dur_2.scaled(35,35,Qt::KeepAspectRatio));
        sound->play();

    }
    else{
        ui->kod5->setPixmap(dur_1.scaled(35,35,Qt::KeepAspectRatio));
    }

}



