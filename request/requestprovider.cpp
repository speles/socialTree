#include "requestprovider.h"
#include "core/corehandler.h"
#include <iostream>
#include <QTcpSocket>
#include <QDateTime>
#include "../opengl/MainWidget.h"
#include <stdexcept>
#undef DELETE

RequestProvider::RequestProvider(coreHandler* _corehandler) :
    QObject(0)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClient()));
    if (!tcpServer->listen(QHostAddress::Any, 4747) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    } else {
        server_status=1;
        qDebug() << QString::fromUtf8("Server Started");
    }
    handler = _corehandler;
}

void RequestProvider::onNewClient() {
    if(server_status==1){
        qDebug() << QString::fromUtf8("new connection");
        QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
        int idusersocs=clientSocket->socketDescriptor();
        SClients[idusersocs]=clientSocket;
        QTextStream os(clientSocket);
        os.setAutoDetectUnicode(true);
        os << "Connection established"
        << QDateTime::currentDateTime().toString() << "\n";
        connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(readClient()));
    }

}

void RequestProvider::readClient() {
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    while (clientSocket->bytesAvailable())
    {
        QString clientMsg(clientSocket->readLine());
        qDebug() << clientMsg;
        if (clientMsg == "BYE\n")
        {
            os << "DISCONNECTED.";
            clientSocket->close();
            SClients.remove(idusersocs);
            return;
        }
        try
        {
            sRequest req = ProcessLine(clientMsg);
            handler->processRequest(req);
            os << "OK\n";
        }
        catch (...)
        {
            os << "Failed.\n";
        }
    }
}

sRequest RequestProvider::ProcessLine(QString line) {
    QStringList requestList = line.split(" ", QString::SkipEmptyParts);
    QString cmdString, filePath,
            nameString, parentNameString;
    if (requestList.size() < 2)
        throw std::invalid_argument("invalid input");
    cmdString = requestList[0];
    nameString = requestList[1].trimmed();
    parentNameString = "";
    filePath = "";
    if ((requestList.size() >= 2) && (requestList.size() < 4))
        throw std::invalid_argument("invalid input");
    if (requestList.size() >= 4) {
        parentNameString = requestList[2];
        filePath = requestList[3];
    }

    sRequest req = sRequest::getNullRequest();
    if (cmdString == "ADD")
    {
        qDebug() << filePath << "\n";
        req.id = widget->loadTexture(filePath.trimmed());
        req.cmd = ADD;
    } else
    {
        req.id = 0;
        req.cmd = DELETE;
    }
    req.name = nameString;
    req.parentName = parentNameString;
    return req;
}
