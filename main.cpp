#include <iostream>
#include <QtWidgets>
#include <QtNetwork>
#include <QApplication>
#include <QtGui>

#include "client.h"

using namespace std;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    client crc;
    crc.show();

    return app.exec();
}
