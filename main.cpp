#include "controls.h"
#include "scoreboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controls w;
    Scoreboard s;

    QObject::connect(&w, SIGNAL(home_name_changed(QString)), &s, SLOT(change_home_name(QString)));
    QObject::connect(&w, SIGNAL(away_name_changed(QString)), &s, SLOT(change_away_name(QString)));
    QObject::connect(&w, SIGNAL(away_score_changed(int)), &s, SLOT(change_away_score(int)));
    QObject::connect(&w, SIGNAL(home_score_changed(int)), &s, SLOT(change_home_score(int)));

    w.show();
    s.show();
    //s.showFullScreen();

    return a.exec();
}
