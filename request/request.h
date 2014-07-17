#ifndef REQUEST_H
#define REQUEST_H
typedef unsigned long long int ull;
#undef DELETE

#include <vector>
#include <QString>
#include <QFile>
#include <QString>

enum eCommand {
    ADD, DELETE
};

struct sRequest {
    ull timestamp;
    eCommand cmd;
    QString name;
    QString parentName;

    sRequest(ull _timestamp,
             eCommand _cmd,
             QString _name,
             QString _parentName)
    {
        timestamp = _timestamp;
        cmd = _cmd;
        name = _name;
        parentName = _parentName;
    }

    bool isNull() {
        return
                this->timestamp == 0 &&
                this->cmd == ADD &&
                this->name == "" &&
                this->parentName == "";
    }

    static sRequest getNullRequest() {
        sRequest req(0, ADD, "", "");
        return req;
    }
};


class RequestManager {
public:
    static RequestManager* GetRequestManagerInstance();
    sRequest getNextRequest(ull time);
private:
    int requestIndex;
    RequestManager();
    static RequestManager* RequestManagerInstance;
    std::vector <sRequest> Requests;
    QFile input;
    void ProcessLine(QString line);
    void ReadDb();
};
#endif // REQUEST_H
