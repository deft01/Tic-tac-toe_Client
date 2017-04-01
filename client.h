#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <QtWidgets>
#include <QtNetwork>
#include <QApplication>
#include <QtGui>

#include "ui_win.h"

using namespace std;

class client : public QDialog, private Ui::Win
{
    Q_OBJECT

public:
    client();
private slots:
    void boutonAuth();

    void gonnaclose();
    void donneeRecue();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError);

    void on_pushButtonSend_clicked();
    void on_pushButton_2Ok_clicked();

private:
    void envoyerServer(const QString &message);
    bool Sstatus;

    QTcpSocket *socket;
    quint16 tailleMessage;
    QString messageRecu;

};

#endif // CLIENT_H
