#ifndef COREHANDLER_H
#define COREHANDLER_H
#include "../request/request.h"
#include "tree.h"
typedef unsigned long long int ull;

class coreHandler
{
public:
    void processRequest(sRequest r);
    tree* getTree();
private:
    QString gName;
    QString gParentName;
    eCommand gCmd;
    ull gTimestamp;
    uint image;

    tree Tree;

    void addCase();
    void deleteCase();
};

#endif // COREHANDLER_H
