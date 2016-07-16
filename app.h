#ifndef APP_H
#define APP_H

#include <QObject>

class App : public QObject
{
    Q_OBJECT

public:
    int run(int argc, char** argv);
};

#endif // APP_H
