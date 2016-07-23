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

#include "controls.h"
#include "ui_controls.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

int ctrls_away_score_value;
int ctrls_home_score_value;
bool clock_running;

Controls::Controls(QWidget *parent) : QMainWindow(parent), ui(new Ui::Controls)
{
    ui->setupUi(this);
    createActions();

    // If file doesn't exist then init score values, else load last score
    ctrls_home_score_value = 0;
    ctrls_away_score_value = 0;
    clock_running = false;
    ui->clock_stop->setEnabled(false);
    ui->home_score->setText(QString::number(ctrls_home_score_value));
    ui->away_score->setText(QString::number(ctrls_away_score_value));
}

Controls::~Controls()
{
    delete ui;
}

void Controls::createActions()
{
    ui->exitAct->setStatusTip(tr("Exit the application"));
    connect(ui->exitAct, &QAction::triggered, this, &Controls::close);

    ui->fullAct->setStatusTip(tr("Make Scoreboard full screen"));
    connect(ui->fullAct, &QAction::triggered, this, &Controls::sb_fullscreen);

    connect(ui->editHomeTeamAct, &QAction::triggered, this, &Controls::get_HomeTeamName);
    connect(ui->editAwayTeamAct, &QAction::triggered, this, &Controls::get_AwayTeamName);
    
    // connect(ui->home_score, &QLineEdit::textChanged, this, &Controls::change_home_board_score);
    //connect(ui->away_score, &QLineEdit::textChanged, this, &Controls::change_away_board_score);

    connect(ui->home_plus1_button, &QAbstractButton::clicked, this, [this]{update_home_score(1);});
    connect(ui->home_minus1_button, &QAbstractButton::clicked, this, [this]{update_home_score(-1);});
    connect(ui->home_plus2_button, &QAbstractButton::clicked, this, [this]{update_home_score(2);});
    connect(ui->home_minus2_button, &QAbstractButton::clicked, this, [this]{update_home_score(-2);});
    connect(ui->home_plus3_button, &QAbstractButton::clicked, this, [this]{update_home_score(3);});
    connect(ui->home_minus3_button, &QAbstractButton::clicked, this, [this]{update_home_score(-3);});

    connect(ui->away_plus1_button, &QAbstractButton::clicked, this, [this]{update_away_score(1);});
    connect(ui->away_minus1_button, &QAbstractButton::clicked, this, [this]{update_away_score(-1);});
    connect(ui->away_plus2_button, &QAbstractButton::clicked, this, [this]{update_away_score(2);});
    connect(ui->away_minus2_button, &QAbstractButton::clicked, this, [this]{update_away_score(-2);});
    connect(ui->away_plus3_button, &QAbstractButton::clicked, this, [this]{update_away_score(3);});
    connect(ui->away_minus3_button, &QAbstractButton::clicked, this, [this]{update_away_score(-3);});

    connect(ui->clock_start, &QAbstractButton::clicked, this, &Controls::start_clock);
    connect(ui->clock_stop, &QAbstractButton::clicked, this, &Controls::stop_clock);
    
}


void Controls::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Exit"),
                                    tr("Are you sure you want to exit?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        event->ignore();
    else
        qApp->exit();
}

void Controls::get_HomeTeamName()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Change Home team name)"), tr("Team name:"),
                                         QLineEdit::Normal, 0, &ok);

    if(ok && !name.isEmpty())
        ui->home_label->setText(name + " Score");

    emit home_name_changed(name);
}

void Controls::get_AwayTeamName()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Change Away team name"), tr("Team name:"),
                                         QLineEdit::Normal, 0, &ok);

    if(ok && !name.isEmpty())
        ui->away_label->setText(name + " Score");

    emit away_name_changed(name);
}

void Controls::update_home_score(int num)
{
    ctrls_home_score_value += num;
    if(ctrls_home_score_value < 0)
	ctrls_home_score_value = 0;
    ui->home_score->setText(QString::number(ctrls_home_score_value));
    emit home_score_changed(ctrls_home_score_value);
}

void Controls::update_away_score(int num)
{
    ctrls_away_score_value += num;
    if(ctrls_away_score_value < 0)
	ctrls_away_score_value = 0;
    ui->away_score->setText(QString::number(ctrls_away_score_value));
    emit away_score_changed(ctrls_away_score_value);
}

/**
 * Might need these later for the pop up window
 **/
void Controls::change_home_board_score()
{
    emit home_score_changed(ctrls_home_score_value);
}

void Controls::change_away_board_score()
{
    emit away_score_changed(ctrls_away_score_value);
}

void Controls::start_clock()
{
    if(clock_running == false)
    {
        emit clock_started();
        clock_running = true;
	ui->clock_start->setEnabled(false);
	ui->clock_stop->setEnabled(true);
    }
}

void Controls::stop_clock()
{
    if(clock_running == true)
    {
        emit clock_stopped();
        clock_running = false;
	ui->clock_start->setEnabled(true);
	ui->clock_stop->setEnabled(false);
    }
}

void Controls::sb_fullscreen()
{
    emit make_sb_fullscreen();
}

void Controls::clock_label_updated(QString time)
{
    ui->clock->setText(time);
}

