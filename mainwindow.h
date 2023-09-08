#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QTime>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_pause_clicked();

    void timerTicked();

    void on_pushButton_boom_clicked();

    void timerTicked_BOOM();

    void timerDelay();

    void on_pushButton_start_delay_clicked();

    void reverse_timerDelay();

    void on_pushButton_restart_clicked();

    void time_real();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QTimer *timerBoom;
    QTimer *delaytimer;
    QTimer *reverse_delaytimer;
    QTimer *real_time;

    int delayed_counter;
    int counter;
    int true_delayed_counter;

    QElapsedTimer elapsidTimer;
    int kBoom;
};
#endif // MAINWINDOW_H
