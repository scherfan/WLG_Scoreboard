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
    QTimer *timer;
    
public:
    explicit Scoreboard(QWidget *parent = 0);
    ~Scoreboard();

public slots:
    void change_home_name(QString name);
    void change_away_name(QString name);
    void change_home_score(int amount);
    void change_away_score(int amount);
    void start_clock();
    void stop_clock();
    
private slots:
    void showTime();

private:
    Ui::Scoreboard *ui;
    void closeEvent(QCloseEvent *event);

};

#endif // SCOREBOARD_H
