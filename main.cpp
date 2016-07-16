#include "controls.h"
#include "scoreboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controls w;
    Scoreboard s;

    QObject::connect(&w, SIGNAL(home_name_changed(QString)), &s, SLOT(change_home(QString)));
    QObject::connect(&w, SIGNAL(away_name_changed(QString)), &s, SLOT(change_away(QString)));
    //QObject::connect(&w, SIGNAL(away_score_change(amount)), &s, SLOT(change_away_score(amount)));
    //QObject::connect(&w, SIGNAL(home_score_change(amount)), &s, SLOT(change_home_score(amount)));

    w.show();
    s.show();
    //s.showFullScreen();

    return a.exec();
}
