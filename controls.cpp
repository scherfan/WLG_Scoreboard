#include "controls.h"
#include "ui_controls.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>


Controls::Controls(QWidget *parent) : QMainWindow(parent), ui(new Ui::Controls)
{
    ui->setupUi(this);
    createActions();
}

Controls::~Controls()
{
    delete ui;
}

void Controls::createActions()
{
    ui->exitAct->setStatusTip(tr("Exit the application"));
    connect(ui->exitAct, &QAction::triggered, this, &Controls::closeEvent);

    ui->fullAct->setStatusTip(tr("Make Scoreboard full screen"));
    connect(ui->fullAct, &QAction::triggered, this, &Controls::sb_fullscreen);

    connect(ui->editHomeTeamAct, &QAction::triggered, this, &Controls::get_HomeTeamName);
    connect(ui->editAwayTeamAct, &QAction::triggered, this, &Controls::get_AwayTeamName);
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
        ui->guest_label->setText(name);

    emit away_changed(name);
}

void Controls::sb_fullscreen()
{

}
