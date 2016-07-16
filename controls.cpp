#include "controls.h"
#include "ui_controls.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

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

    emit home_name_changed(name);
}

void Controls::get_AwayTeamName()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Change Away team name"), tr("Team name:"),
                                         QLineEdit::Normal, 0, &ok);

    if(ok && !name.isEmpty())
        ui->away_label->setText(name);

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
/**
 **/


void Controls::sb_fullscreen()
{

}
