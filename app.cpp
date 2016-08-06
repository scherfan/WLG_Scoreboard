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
#include <QDesktopWidget>
#include <QObject>
#include <QWindow>
#include <QDebug>
#include <QFile>
#include "controls.h"
#include "scoreboard.h"
#include "app.h"

int App::run(int argc, char** argv)
{
    QApplication a(argc, argv);
    Controls* c = new Controls;
    Scoreboard* s = new Scoreboard;
    
    connect(c, SIGNAL(home_name_changed(QString)), s, SLOT(change_home_name(QString)));
    connect(c, SIGNAL(away_name_changed(QString)), s, SLOT(change_away_name(QString)));
    // Changes from buttons
    connect(c, SIGNAL(away_score_changed(int)), s, SLOT(change_away_score(int)));
    connect(c, SIGNAL(home_score_changed(int)), s, SLOT(change_home_score(int)));
    
    connect(c, SIGNAL(update_clock(QString)), s, SLOT(set_time_value(QString)));
    
    // Connections for updating values when a file is found
    connect(this, SIGNAL(home_name_changed(QString)), s, SLOT(change_home_name(QString)));
    connect(this, SIGNAL(away_name_changed(QString)), s, SLOT(change_away_name(QString)));

    connect(this, SIGNAL(away_score_changed(int)), s, SLOT(change_away_score(int)));
    connect(this, SIGNAL(home_score_changed(int)), s, SLOT(change_home_score(int)));
    
    connect(this, SIGNAL(update_clock(QString)), s, SLOT(set_time_value(QString)));
    
    connect(this, SIGNAL(change_time_label(QString)), c, SLOT(update_time_label(QString)));
    connect(this, SIGNAL(change_home_label(QString)), c, SLOT(update_home_label(QString)));
    connect(this, SIGNAL(change_away_label(QString)), c, SLOT(update_away_label(QString)));

    connect(this, SIGNAL(change_home_score(int)), c, SLOT(update_home_score(int)));
    connect(this, SIGNAL(change_away_score(int)), c, SLOT(update_away_score(int)));
    
    


    QFile file(filename);
    if(!file.exists())
	qDebug() << "Doesn't exist.";
    else    // If file doesn't exist then load last time, team names and scores
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
	QString away_team, home_team;
	int time_value, home_score_value, away_score_value;
	QRegExp re("^\\d*\\,[A-z]*\\,\\d*\\,[A-z]*\\,\\d*$"); // string contains a num,word,num,word,num

	if(re.exactMatch(list.value(list.length() - 1)))
	    qDebug() << "Match.";
	else
	{
	    fprintf(stderr, "String pattern invalid.");
	    exit(-1);
	}
	
	last_line = (list.value(list.length() - 1).split(",", QString::SkipEmptyParts));

	time_value = last_line.value(0).toInt();
	home_score_value = last_line.value(2).toInt();
	away_score_value = last_line.value(4).toInt();
	qDebug() << home_score_value << away_score_value;
	home_team = last_line.value(1);
	away_team = last_line.value(3);
		    
	QString time_update, min_text, sec_text;
	int hour = (time_value / 60) / 60;
	int minute = (time_value / 60) % 60;
	int second = time_value % 60;
	if(minute < 10)
	    min_text = "0" + QString::number(minute);
	else
	    min_text = QString::number(minute);
	if(second < 10)
	    sec_text = "0" + QString::number(second);
	else
	    sec_text = QString::number(second);
	
	time_update = QString::number(hour) + ":" + min_text + ":" + sec_text;
	emit update_clock(time_update);
	emit change_home_score(home_score_value);
	emit change_away_score(away_score_value);
	
	emit change_time_label(time_update);
	emit change_home_label(home_team + " Score");
	emit change_away_label(away_team + " Score"); 
	emit home_name_changed(home_team);
	emit away_name_changed(away_team);
	emit home_score_changed(home_score_value);
	emit away_score_changed(away_score_value);
    }
    


    if(QApplication::desktop()->screenCount() > 1)
    {
	s->show();
	s->windowHandle()->setScreen(qApp->screens()[1]);
	s->showFullScreen();
	c->show();
    }
    else
    {
	s->show();
        c->show();
    }
    return a.exec();
}
