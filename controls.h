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


#ifndef CONTROLS_H
#define CONTROLS_H

#include <QMainWindow>

namespace Ui
{
class Controls;
class QAction;
class QActionGroup;
class QMenu;
}

class Controls : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controls(QWidget *parent = 0);
    ~Controls();

signals:
    void home_name_changed(QString name);
    void away_name_changed(QString name);
    void home_score_changed(int amount);
    void away_score_changed(int amount);
    void clock_started();
    void clock_stopped();

public slots:
    void clock_label_updated(QString);

private slots:
    void update_home_score(int num);
    void update_away_score(int num);
    void change_home_board_score();
    void change_away_board_score();
    void start_clock();
    void stop_clock();
    
private:
    Ui::Controls *ui;
    void createActions();
    void get_HomeTeamName();
    void get_AwayTeamName();
    void closeEvent(QCloseEvent *event);
    void sb_fullscreen();

    QMenu *fileMenu;
    QMenu *editMEnu;
    QAction *exitAct;
    QAction *fullAct;
    QAction *editHomeTeamAct;
    QAction *editAwayTeamAct;
};

#endif // CONTROLS_H
