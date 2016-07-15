#include "controls.h"
#include "scoreboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controls w;
    Scoreboard s;

    QObject::connect(&w, SIGNAL(home_changed(QString)), &s, SLOT(change_home(QString)));
    QObject::connect(&w, SIGNAL(away_changed(QString)), &s, SLOT(change_away(QString)));

    w.show();
    s.showFullScreen();
    s.~Scoreboard();

    return a.exec();
}
