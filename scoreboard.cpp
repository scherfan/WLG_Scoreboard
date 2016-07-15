#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QCloseEvent>
#include <string>

int away_score_value;
int home_score_value;

Scoreboard::Scoreboard(QWidget *parent) : QWidget(parent), ui(new Ui::Scoreboard)
{
    home_score_value = 0;
    away_score_value = 0;
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
    ui->home_lcd->display(QString::number(home_score_value));
    ui->away_lcd->display(QString::number(away_score_value));
}

Scoreboard::~Scoreboard()
{
    delete ui;
}

void Scoreboard::showTime()
{
    QTime timeValue = QTime(0,0,0);
    QString time_text;
    for(int i = 0; i < 5; i++)
    {
        timeValue.addSecs(1);
        qDebug() << timeValue;
        time_text = timeValue.toString("hh:mm:ss");
        time_text = "999:99:99";
        ui->clock->display(time_text);
    }
}

void Scoreboard::change_home(QString name)
{
    ui->home_label->setText(name);
}

void Scoreboard::change_away(QString name)
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
