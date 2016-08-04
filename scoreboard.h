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

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>

namespace Ui {
class Scoreboard;
}

class Scoreboard : public QWidget
{
    Q_OBJECT
    
public:
    explicit Scoreboard(QWidget *parent = 0);
    ~Scoreboard();

signals:
    void update_clock(QString);
    
public slots:
    void change_home_name(QString name);
    void change_away_name(QString name);
    void change_home_score(int amount);
    void change_away_score(int amount);
    void set_time_value(QString time);
    
private:
    Ui::Scoreboard *ui;
    void closeEvent(QCloseEvent *event);

};

#endif // SCOREBOARD_H
