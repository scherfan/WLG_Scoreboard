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

#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QDebug>
#include <QCloseEvent>

int away_score_value;
int home_score_value;

Scoreboard::Scoreboard(QWidget *parent) : QWidget(parent), ui(new Ui::Scoreboard)
{

    ui->setupUi(this);
    ui->clock->display("0:00:00");
    // If file doesn't exist then init score, else load last score
    home_score_value = 664136;
    away_score_value = 663908;
    ui->home_lcd->display(QString::number(home_score_value));
    ui->away_lcd->display(QString::number(away_score_value));
}

Scoreboard::~Scoreboard()
{
    delete ui;
}

void Scoreboard::change_home_name(QString name)
{
    ui->home_label->setText(name);
}

void Scoreboard::change_away_name(QString name)
{
    ui->away_label->setText(name);
}

void Scoreboard::change_home_score(int amount)
{
    ui->home_lcd->display(amount);
}

void Scoreboard::change_away_score(int amount)
{
    ui->away_lcd->display(amount);
}

void Scoreboard::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void Scoreboard::set_time_value(QString time)
{
    ui->clock->display(time);
}
