#include "controls.h"
#include "scoreboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controls c;
    Scoreboard s;

    QObject::connect(&c, SIGNAL(home_name_changed(QString)), &s, SLOT(change_home_name(QString)));
    QObject::connect(&c, SIGNAL(away_name_changed(QString)), &s, SLOT(change_away_name(QString)));
    QObject::connect(&c, SIGNAL(away_score_changed(int)), &s, SLOT(change_away_score(int)));
    QObject::connect(&c, SIGNAL(home_score_changed(int)), &s, SLOT(change_home_score(int)));
    QObject::connect(&c, SIGNAL(clock_stopped()), &s, SLOT(stop_clock()));
    QObject::connect(&c, SIGNAL(clock_started()), &s, SLOT(start_clock()));
    QObject::connect(&s, SIGNAL(update_clock(QString)), &c, SLOT(clock_label_updated(QString)));

    c.show();
    s.show();
    //s.showFullScreen();

    return a.exec();
}
