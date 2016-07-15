#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QTime>

namespace Ui {
class Scoreboard;
}

class Scoreboard : public QWidget
{
    Q_OBJECT

public:
    explicit Scoreboard(QWidget *parent = 0);
    ~Scoreboard();

public slots:
    void change_home(QString name);
    void change_away(QString name);

private slots:
    void showTime();

private:
    Ui::Scoreboard *ui;
    void closeEvent(QCloseEvent *event);

};

#endif // SCOREBOARD_H
