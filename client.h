#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <QtWidgets>
#include <QtNetwork>
#include <QApplication>
#include <QtGui>
#define calculs "76 69 63 74 6f 72 20 70 6c 6f 75 68 69 6e 65 63"

#include "ui_win.h"

using namespace std;

class client : public QDialog, private Ui::Win
{
    Q_OBJECT

public:
    client();
    QMovie *movie;
    QMovie *movie2;
    QMovie *matchNul;
    QMovie *rip;
private slots:
    void boutonAuth();

    void gonnaclose();
    void donneeRecue();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError);

    void on_pushButtonSend_clicked();
    void on_pushButton_2Ok_clicked();

    void on_play11();
    void on_play12();
    void on_play13();
    void on_play21();
    void on_play22();
    void on_play23();
    void on_play31();
    void on_play32();
    void on_play33();

    void on_start();
    void on_status();
    void on_create();
    void on_timeout();
    void on_rules();

private:
    void envoyerServer(const QString &message);
    bool Sstatus;

    QTcpSocket *socket;
    quint16 tailleMessage;
    QString messageRecu;

    QList<QString> morp;

};

#endif // CLIENT_H







// ivpgbe cybhuvarp
