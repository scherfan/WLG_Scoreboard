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

#ifndef APP_H
#define APP_H

#include <QObject>
#include "scoreboard.h"


class App : public QObject
{
    Q_OBJECT

public:
    int run(int argc, char** argv);
    
signals:
    void home_name_changed(QString name);
    void away_name_changed(QString name);
    void home_score_changed(int amount);
    void away_score_changed(int amount);
    void update_clock(QString time);
    void change_time_label(QString time);
    void change_home_score(int amount);
    void change_away_score(int amount);
    void change_home_label(QString name);
    void change_away_label(QString name);
    
public slots:
//    void sb_fullscreen(Scoreboard s);
};

#endif // APP_H
