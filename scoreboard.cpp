#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QCloseEvent>

Scoreboard::Scoreboard(QWidget *parent) : QWidget(parent), ui(new Ui::Scoreboard)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
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

    ui->home_lcd->display(12000);
    ui->away_lcd->display(15000);
}

void Scoreboard::change_home(QString name)
{
    ui->home_label->setText(name);
}

void Scoreboard::change_away(QString name)
{
    ui->away_label->setText(name);
}

void Scoreboard::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
