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
#include "scoreboard.h"
#include "ui_controls.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QShortcut>
#include <QTimer>
#include <QFile>

int ctrls_away_score_value;
int ctrls_home_score_value;
QString home_team, away_team;
bool clock_running;
int time_value;
QString filename = "WLG_2016_history.txt";

Controls::Controls(QWidget *parent) : QMainWindow(parent), ui(new Ui::Controls)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    clock_running = false;
    ui->clock_stop->setEnabled(false);

    QFile file(filename);
    if(!file.exists())
    {
	qDebug() << "Doesn't exist.";
	ctrls_home_score_value = 0;
	ctrls_away_score_value = 0;
	time_value = 0;
	ui->home_score->setText(QString::number(ctrls_home_score_value));
	ui->away_score->setText(QString::number(ctrls_away_score_value));
    }
    else    // If file doesn't exist then init score values, else load last score
    {
	qDebug() << "Exists.";
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
	    fprintf(stderr, "File IO error");
	    exit(-1);
	}
	QTextStream in(&file);
	QStringList list, last_line;
	while(!in.atEnd())
	{
	    QString line = in.readLine();
	    list.append(line);
	}
	file.close();
	
	last_line = (list.value(list.length() - 1).split(",", QString::SkipEmptyParts));
	time_value = last_line.value(0).toInt();
	ctrls_home_score_value = last_line.value(2).toInt();
	ctrls_away_score_value = last_line.value(4).toInt();
	home_team = last_line.value(1);
	away_team = last_line.value(3);
	
	QString time_update;
	int hour = (time_value / 60) / 60;
	int minute = (time_value / 60) % 60;
	int second = time_value % 60;
	time_update = QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second);
//	emit update_clock(time_text);
	clock_label_updated(time_update);
	ui->home_score->setText(QString::number(ctrls_home_score_value));
	ui->away_score->setText(QString::number(ctrls_away_score_value));
	ui->home_label->setText(home_team + " Score");
	ui->away_label->setText(away_team + " Score");
//	emit home_name_changed(home_team);
//	emit away_name_changed(away_team);
//	emit home_score_changed(ctrls_home_score_value);
//	emit away_score_changed(ctrls_away_score_value);
    }
    createActions();
}

Controls::~Controls()
{
    delete ui;
}

void Controls::createActions()
{
    // Exit application menu action
    ui->exitAct->setStatusTip(tr("Exit the application"));
    connect(ui->exitAct, &QAction::triggered, this, &Controls::close);

    // Make scoreboard fullscreen menu
    ui->fullAct->setStatusTip(tr("Make Scoreboard full screen"));
    connect(ui->fullAct, &QAction::triggered, this, &Controls::sb_fullscreen);

    // Set time menu
    ui->action_edit_time->setStatusTip(tr("Set current time"));
    connect(ui->action_edit_time, &QAction::triggered, this, &Controls::edit_clock);

    // Set team names menu
    connect(ui->editHomeTeamAct, &QAction::triggered, this, &Controls::get_HomeTeamName);
    connect(ui->editAwayTeamAct, &QAction::triggered, this, &Controls::get_AwayTeamName);

    // Set team scores menu
    ui->action_edit_home_team_score->setStatusTip(tr("Set home team score"));
    connect(ui->action_edit_home_team_score, &QAction::triggered, this, &Controls::edit_home_score);
    ui->action_edit_away_team_score->setStatusTip(tr("Set away team score"));
    connect(ui->action_edit_away_team_score, &QAction::triggered, this, &Controls::edit_away_score);

    // connect score buttons
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

    // connect clock buttons
    connect(ui->clock_start, &QAbstractButton::clicked, this, &Controls::start_clock);
    connect(ui->clock_stop, &QAbstractButton::clicked, this, &Controls::stop_clock);

    // connect score keyboard short cuts
    QShortcut *home_plus_one = new QShortcut(this);
    QShortcut *home_minus_one = new QShortcut(this);
    home_plus_one->setKey(Qt::Key_Q);
    home_minus_one->setKey(Qt::Key_A);
    QShortcut *home_plus_two = new QShortcut(this);
    QShortcut *home_minus_two = new QShortcut(this);
    home_plus_two->setKey(Qt::Key_W);
    home_minus_two->setKey(Qt::Key_S);
    QShortcut *home_plus_three = new QShortcut(this);
    QShortcut *home_minus_three = new QShortcut(this);
    home_plus_three->setKey(Qt::Key_E);
    home_minus_three->setKey(Qt::Key_D);

    QShortcut *away_plus_one = new QShortcut(this);
    QShortcut *away_minus_one = new QShortcut(this);
    away_plus_one->setKey(Qt::Key_U);
    away_minus_one->setKey(Qt::Key_J);
    QShortcut *away_plus_two = new QShortcut(this);
    QShortcut *away_minus_two = new QShortcut(this);
    away_plus_two->setKey(Qt::Key_I);
    away_minus_two->setKey(Qt::Key_K);
    QShortcut *away_plus_three = new QShortcut(this);
    QShortcut *away_minus_three = new QShortcut(this);
    away_plus_three->setKey(Qt::Key_O);
    away_minus_three->setKey(Qt::Key_L);


    connect(home_plus_one, &QShortcut::activated, this, [this]{update_home_score(1);});
    connect(home_minus_one, &QShortcut::activated, this, [this]{update_home_score(-1);});
    connect(home_plus_two, &QShortcut::activated, this, [this]{update_home_score(2);});
    connect(home_minus_two, &QShortcut::activated, this, [this]{update_home_score(-2);});
    connect(home_plus_three, &QShortcut::activated, this, [this]{update_home_score(3);});
    connect(home_minus_three, &QShortcut::activated, this, [this]{update_home_score(-3);});

    connect(away_plus_one, &QShortcut::activated, this, [this]{update_away_score(1);});
    connect(away_minus_one, &QShortcut::activated, this, [this]{update_away_score(-1);});
    connect(away_plus_two, &QShortcut::activated, this, [this]{update_away_score(2);});
    connect(away_minus_two, &QShortcut::activated, this, [this]{update_away_score(-2);});
    connect(away_plus_three, &QShortcut::activated, this, [this]{update_away_score(3);});
    connect(away_minus_three, &QShortcut::activated, this, [this]{update_away_score(-3);});

}

void Controls::show_time()
{
    time_value++;
    
    int hour = (time_value / 60) / 60;
    int minute = (time_value / 60) % 60;
    int second = time_value % 60;

    QString min_text, sec_text;
    
    if(minute < 10)
	min_text = "0" + QString::number(minute);
    else
	min_text = QString::number(minute);

    if(second < 10)
	sec_text = "0" + QString::number(second);
    else
	sec_text = QString::number(second);
    
    QString time_text = QString::number(hour) + ":" + min_text + ":" + sec_text;
    
    emit update_clock(time_text);
    clock_label_updated(time_text);
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
    qDebug() << "updated home score by: " << num;
    ctrls_home_score_value += num;
    if(ctrls_home_score_value < 0)
	ctrls_home_score_value = 0;
    ui->home_score->setText(QString::number(ctrls_home_score_value));
    emit home_score_changed(ctrls_home_score_value);
}

void Controls::update_away_score(int num)
{
    qDebug() << "updated away score by: " << num;
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
	timer->start(1000);
        clock_running = true;
	ui->clock_start->setEnabled(false);
	ui->clock_stop->setEnabled(true);
    }
}

void Controls::stop_clock()
{
    if(clock_running == true)
    {
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, tr("Stop the Clock"),
				      "Are you sure you want to stop the clock?\nIs the game over?",
				      QMessageBox::Yes | QMessageBox::Cancel);
	if(reply == QMessageBox::Yes)
	{
	    timer->stop();
	    clock_running = false;
	    ui->clock_start->setEnabled(true);
	    ui->clock_stop->setEnabled(false);
	}
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

void Controls::edit_clock()
{
    int hour, min, sec;
    QString time_string;
    if(clock_running == false)
    {
	bool ok;
	time_string = QInputDialog::getText(this, tr("Set new clock time"), tr("Time (hhh:mm:ss): "),
			      QLineEdit::Normal, 0, &ok);

	if(ok && !time_string.isEmpty())
	{
	    QStringList time_pieces = time_string.split(":", QString::SkipEmptyParts);
	    hour = time_pieces.value(0).toInt();
	    min = time_pieces.value(1).toInt();
	    sec = time_pieces.value(2).toInt();

	    if(hour < 1000 && min < 60 && sec < 60)
	    {
		QString min_text, sec_text;
    
		if(min < 10)
		    min_text = "0" + QString::number(min);
		else
		    min_text = QString::number(min);

		if(sec < 10)
		    sec_text = "0" + QString::number(sec);
		else
		    sec_text = QString::number(sec);
    
		QString time_text = QString::number(hour) + ":" + min_text + ":" + sec_text;
    
		emit update_clock(time_text);
		clock_label_updated(time_text);
	    
		int total = (hour * 60 * 60) + (min * 60) + sec;
		time_value = total;
	    }
	    else
		QMessageBox::information(this, tr("Invalid time"), tr("Invalid time entered."));
	}
	else
	    QMessageBox::information(this, tr("Invalid time"), tr("Invalid time entered."));
    }
    else
	QMessageBox::information(this, tr("Running Time"), tr("Stop the clock before changing."));
}

void Controls::edit_home_score()
{
    bool ok;
    QString score = QInputDialog::getText(this, tr("Set new home score"), tr("Score:"),
                                         QLineEdit::Normal, 0, &ok);

    if(ok && !score.isEmpty())
    {
	ctrls_home_score_value = score.toInt();
	ui->home_score->setText(QString::number(ctrls_home_score_value));
	emit home_score_changed(ctrls_home_score_value);
    }
}

void Controls::edit_away_score()
{
    bool ok;
    QString score = QInputDialog::getText(this, tr("Set new away score"), tr("Score:"),
                                         QLineEdit::Normal, 0, &ok);

    if(ok && !score.isEmpty())
    {
	ctrls_away_score_value = score.toInt();
	ui->away_score->setText(QString::number(ctrls_away_score_value));
	emit away_score_changed(ctrls_away_score_value);
    }
}
