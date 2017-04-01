#include "client.h"

client::client()
{

    setupUi(this);
    socket= new QTcpSocket(this);
    Sstatus = false;

    QMovie *movie = new QMovie("base.gif");
    label->setMovie(movie);
    movie->start();

    connect(socket,SIGNAL(readyRead()),this,SLOT(donneeRecue()));
    connect(socket,SIGNAL(connected()),this,SLOT(connecte()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(deconnecte()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(aboutToClose()),this,SLOT(gonnaclose()));

    connect(pushButtonAuth,SIGNAL(clicked()),this,SLOT(boutonAuth()));
    //connect(pushButton_2Ok,SIGNAL(clicked()),this,SLOT(boutonConnexion()));

    tailleMessage=0;
}

void client::gonnaclose()
{

    textEditText->append("Je vais fermer");
    envoyerServer("Je vais fermer");
}

void client::donneeRecue()
{
    QDataStream in(socket);

    for ( ; ; ) {
        if(tailleMessage==0)
        {
            if(socket->bytesAvailable()<(int)sizeof(quint16)){
                return;
            }

            in>>tailleMessage;
        }

        if(socket->bytesAvailable()<tailleMessage){
            return;
        }

        in >> messageRecu;

        //    if(messageRecu=="Une demande d'auth pour CRC a été ACCEPTEE"){
        //        textEditText->append("Une demande d'auth pour CRC a été ACCEPTEE");
        //        Sstatus=true;
        //        labell->setText("CRC");
        //    }

        textEditText->append(messageRecu);

        tailleMessage = 0;
    }


}


void client::on_pushButtonSend_clicked()
{
    QByteArray paquet;
    QDataStream out(&paquet,QIODevice::WriteOnly);

    QString message = (lineEdit_2Text->text());

    out<<(quint16)0;
    out<<message;
    out.device()->seek(0);
    out<<(quint16)(paquet.size()-sizeof(quint16));

    textEditText->append(lineEdit_2Text->text());
    socket->write(paquet);

    lineEdit_2Text->clear();
    lineEdit_2Text->setFocus();
}



void client::boutonAuth()
{
    textEditText->append("Envoie de la Key ...");
    envoyerServer(lineEditPass->text());
}



void client::envoyerServer(const QString &message)
{
    QByteArray paquet;
    QDataStream out(&paquet,QIODevice::WriteOnly);

    out<<(quint16)0;
    out<<message;
    out.device()->seek(0);
    out<<(quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}

void client::on_pushButton_2Ok_clicked()
{
    textEditText->append("Tentative de connexion ...");
    socket->abort();
    socket->connectToHost(lineEditIp->text(),spinBoxPort->value());
}


void client::connecte(){
    textEditText->append("Client(you) connecté au serveur");
}


void client::deconnecte(){
    textEditText->append("Client(you) déconnecté du serveur");
}


void client::erreurSocket(QAbstractSocket::SocketError erreur){

    switch (erreur) {
    case QAbstractSocket::HostNotFoundError:
        textEditText->append("erreur : le server n'a pas été toruvé");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        textEditText->append("connexion refusée");
    case QAbstractSocket::RemoteHostClosedError:
        textEditText->append("le server a coupé la connexion");
    default:
        textEditText->append("une erreur est advenue : "+socket->errorString());
        break;
    }
}




