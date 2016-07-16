#include "controls.h"
#include "ui_controls.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>

int ctrls_away_score_value;
int ctrls_home_score_value;

Controls::Controls(QWidget *parent) : QMainWindow(parent), ui(new Ui::Controls)
{
    ui->setupUi(this);
    createActions();
    
    // If file doesn't exist then init score values, else load last score
    ctrls_home_score_value = 0;
    ctrls_away_score_value = 0;
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

    //    ui->fullAct->setStatusTip(tr("Make Scoreboard full screen"));
    //    connect(ui->fullAct, &QAction::triggered, this, &Controls::sb_fullscreen);

    connect(ui->editHomeTeamAct, &QAction::triggered, this, &Controls::get_HomeTeamName);
    connect(ui->editAwayTeamAct, &QAction::triggered, this, &Controls::get_AwayTeamName);
    //    connect(ui->
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
        ui->home_label->setText(name);

    emit home_changed(name);
}

void Controls::get_AwayTeamName()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Change Away team name"), tr("Team name:"),
                                         QLineEdit::Normal, 0, &ok);

    if(ok && !name.isEmpty())
        ui->away_label->setText(name);

    emit away_changed(name);
}

void Controls::sb_fullscreen()
{

}
