#ifndef CONTROLS_H
#define CONTROLS_H

#include <QMainWindow>

namespace Ui
{
class Controls;
class QAction;
class QActionGroup;
class QMenu;
}

class Controls : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controls(QWidget *parent = 0);
    ~Controls();

signals:
    void home_changed(QString name);
    void away_changed(QString name);

private:
    Ui::Controls *ui;
    void createActions();
    void get_HomeTeamName();
    void get_AwayTeamName();
    void closeEvent(QCloseEvent *event);
    void sb_fullscreen();

    QMenu *fileMenu;
    QMenu *editMEnu;
    QAction *exitAct;
    QAction *fullAct;
    QAction *editHomeTeamAct;
    QAction *editAwayTeamAct;
};

#endif // CONTROLS_H