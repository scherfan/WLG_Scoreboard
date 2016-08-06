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
#include <QTime>

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
    QTimer *timer;
public:
    explicit Controls(QWidget *parent = 0);
    ~Controls();

signals:
    void home_name_changed(QString name);
    void away_name_changed(QString name);
    void home_score_changed(int amount);
    void away_score_changed(int amount);
    void change_time(int time);
    void update_clock(QString time);

private slots:
    void show_time();

public slots:
    void update_time_label(QString time);
    void update_home_label(QString name);
    void update_away_label(QString name);
    void update_home_score(int num);
    void update_away_score(int num);

    
private:
    Ui::Controls *ui;
    void createActions();
    void get_HomeTeamName();
    void get_AwayTeamName();
    void closeEvent(QCloseEvent *event);
    void edit_clock();
    void edit_home_score();
    void edit_away_score();
    void clock_label_updated(QString);
    void start_clock();
    void stop_clock();
    void change_home_board_score(int num);
    void change_away_board_score(int num);
    void save_to_file();

    QMenu *fileMenu;
    QMenu *editMEnu;
    QAction *exitAct;
    QAction *editHomeTeamAct;
    QAction *editAwayTeamAct;
};

#endif // CONTROLS_H
