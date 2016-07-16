#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QTimer>
#include <QDebug>
#include <QCloseEvent>
#include <string>

int away_score_value;
int home_score_value;
int time_value;

Scoreboard::Scoreboard(QWidget *parent) : QWidget(parent), ui(new Ui::Scoreboard)
{

    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    time_value = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    // If file doesn't exist then init score, else load last score
    home_score_value = 0;
    away_score_value = 0;
    ui->home_lcd->display(QString::number(home_score_value));
    ui->away_lcd->display(QString::number(away_score_value));
}

Scoreboard::~Scoreboard()
{
    delete ui;
}

void Scoreboard::showTime()
{
    time_value++;
    int hour = (time_value / 60) / 60;
    int minute = time_value / 60;
    int second = time_value;
    QString time_text = QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second);
    ui->clock->display(time_text);
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
