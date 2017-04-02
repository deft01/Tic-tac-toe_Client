#include "client.h"

client::client()
{

    setupUi(this);
    socket= new QTcpSocket(this);
    Sstatus = false;

    QMovie *movie = new QMovie("base.gif");
    label->setMovie(movie);
    movie->start();

    morp = QList<QString>();

    connect(socket,SIGNAL(readyRead()),this,SLOT(donneeRecue()));
    connect(socket,SIGNAL(connected()),this,SLOT(connecte()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(deconnecte()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(aboutToClose()),this,SLOT(gonnaclose()));
    connect(play11,SIGNAL(clicked(bool)),this,SLOT(on_play11()));
    connect(play12,SIGNAL(clicked(bool)),this,SLOT(on_play12()));
    connect(play13,SIGNAL(clicked(bool)),this,SLOT(on_play13()));
    connect(play21,SIGNAL(clicked(bool)),this,SLOT(on_play21()));
    connect(play22,SIGNAL(clicked(bool)),this,SLOT(on_play22()));
    connect(play23,SIGNAL(clicked(bool)),this,SLOT(on_play23()));
    connect(play31,SIGNAL(clicked(bool)),this,SLOT(on_play31()));
    connect(play32,SIGNAL(clicked(bool)),this,SLOT(on_play32()));
    connect(play33,SIGNAL(clicked(bool)),this,SLOT(on_play33()));


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

        if(messageRecu.contains("_")){
            morp.push_back(" ");
        }

        if(messageRecu == ("O ")){
            morp.push_back("O");
        }

        if(messageRecu.contains("X")){
            morp.push_back("X");
        }

        if(messageRecu.contains("+++")){
            play11->setText(morp[0]);
            play12->setText(morp[1]);
            play13->setText(morp[2]);
            play21->setText(morp[3]);
            play22->setText(morp[4]);
            play23->setText(morp[5]);
            play31->setText(morp[6]);
            play32->setText(morp[7]);
            play33->setText(morp[8]);
            morp.clear();
        }


        tailleMessage = 0;
    }
}

void client::on_play11(){
    envoyerServer("/play 1,1");
}

void client::on_play12(){
    envoyerServer("/play 1,2");
}

void client::on_play13(){
    envoyerServer("/play 1,3");
}

void client::on_play21(){
    envoyerServer("/play 2,1");
}

void client::on_play22(){
    envoyerServer("/play 2,2");
}

void client::on_play23(){
    envoyerServer("/play 2,3");
}

void client::on_play31(){
    envoyerServer("/play 3,1");
}

void client::on_play32(){
    envoyerServer("/play 3,2");
}

void client::on_play33(){
    envoyerServer("/play 3,3");
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




