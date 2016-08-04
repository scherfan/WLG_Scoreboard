/**
 WLG_Scoreboard is a basketball scoreboard program to allow for triple digit hours and 5 digit scores.
 Copyright (C) 2016 Steven Cherfan

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <QApplication>
#include <QObject>
#include "controls.h"
#include "scoreboard.h"
#include "app.h"


int App::run(int argc, char** argv)
{
    QApplication a(argc, argv);
    Controls c;
    Scoreboard s;
    QObject::connect(&c, SIGNAL(home_name_changed(QString)), &s, SLOT(change_home_name(QString)));
    QObject::connect(&c, SIGNAL(away_name_changed(QString)), &s, SLOT(change_away_name(QString)));
    // Changes from buttons
    QObject::connect(&c, SIGNAL(away_score_changed(int)), &s, SLOT(change_away_score(int)));
    QObject::connect(&c, SIGNAL(home_score_changed(int)), &s, SLOT(change_home_score(int)));
    
    QObject::connect(&c, SIGNAL(clock_stopped()), &s, SLOT(stop_clock()));
    QObject::connect(&c, SIGNAL(clock_started()), &s, SLOT(start_clock()));
    QObject::connect(&c, SIGNAL(change_time(int)), &s, SLOT(set_time_value(int)));
    QObject::connect(&s, SIGNAL(update_clock(QString)), &c, SLOT(clock_label_updated(QString)));
    QObject::connect(&c, SIGNAL(make_sb_fullscreen()), this, SLOT(sb_fullscreen(Scoreboard s)));
    c.show();
    s.show();



    return a.exec();
}

/*void App::sb_fullscreen(Scoreboard s)
{
    s.showFullScreen();
}
*/
