#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//конструктор
{
    ui->setupUi(this);                
    this->setWindowState(Qt::WindowMaximized);//Установка размера главного окна
    setWindowIcon(QIcon("C:/Qt/project/project_2.1/free-icon-sand-clock-3240637.ico"));//Установка иконки приложения
    //startTimer(500);//установка тайемра
    //int t2 = startTimer(1500);
    setWindowTitle("Timer and stopwatch");//Установка названия окна
    //killTimer();//удаляет таймер

    timer = new QTimer(this);//выделяем память для таймера
    timer->setInterval(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTicked()));//соединяем секундомер

    timerBoom = new QTimer(this);//выделяем память для таймера
    connect(timerBoom,SIGNAL(timeout()),this,SLOT(timerTicked_BOOM()));//соединяем таймер взрыва

    delaytimer = new QTimer(this);//выделяем память для таймера
    connect(delaytimer,SIGNAL(timeout()), this, SLOT(timerDelay()));//соединяем таймер задержки

    real_time = new QTimer(this);//выделяем память для часов
    connect(real_time,SIGNAL(timeout()),this, SLOT(time_real()));
    real_time->start(100);

}
//деструктор
MainWindow::~MainWindow()
{
    delete ui;
}
//кнопка старт
void MainWindow::on_pushButton_start_clicked()
{
    if (!timer->isActive())
    {
        counter=0;
        ui->pushButton_start->setText("Pause");
        timer->start(10);
        ui->pushButton_restart->show();
    }
    else
    {
        ui->pushButton_start->setText("Start");
        timer->stop();
    }
}
//кнопка рестарт
void MainWindow::on_pushButton_restart_clicked()
{
    timer->stop();
    counter = 0;
    int msec = counter*10;

    QTime time = QTime::fromMSecsSinceStartOfDay(msec);
    QString text = time.toString("mm:ss.zzz");
    ui->lcdNumber_sec->display(text);

    ui -> pushButton_start -> setText("Start");
}
//часы в реальном времени
void MainWindow::time_real()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("HH:mm:ss");//создаем маску для вывода чисел
    ui->lcdNumber_realtime->display(text);//выводим
}
//секундомер
void MainWindow::timerTicked()
{
    counter++;
    int msec = counter*10;

    QTime time = QTime::fromMSecsSinceStartOfDay(msec);
    QString text = time.toString("HH:mm:ss.zzz");//создаем маску для вывода чисел
    ui->lcdNumber_sec->display(text);//выводим
}
//кнопка взрыва
void MainWindow::on_pushButton_boom_clicked()
{
    kBoom=ui->dial->value();//считываем значение dial
    timerBoom->start(1000);
}
//таймер для взрыва
void MainWindow::timerTicked_BOOM()
{
    kBoom--;
    QTime time = QTime::fromMSecsSinceStartOfDay(kBoom*1000);
    QString text = time.toString("mm:ss.zzz");//создаем маску для вывода чисел
    ui->lcdNumber_boom->display(text);//выводим
    if (kBoom==0)
    {
        ui->pushButton_boom->setEnabled(false);
        ui->pushButton_start->setEnabled(false);
        ui->pushButton_start_delay->setEnabled(false);
        ui->pushButton_restart->setEnabled(false);
        ui->pushButton_boom->hide();
        ui->label_boom->hide();
        ui->label_delay->hide();
        ui->label_sec->hide();
        ui->label_input_iform->hide();
        ui->pushButton_start->hide();
        ui->pushButton_start_delay->hide();
        ui->pushButton_restart->hide();
        ui->spinBox->hide();
        ui->lcdNumber_sec->hide();
        ui->lcdNumber_boom->hide();        
        ui->lcdNumber_startIN->hide();
        ui->lcdNumber_realtime->hide();
        ui->dial->hide();

        timer->stop();
        timerBoom->stop();
        delaytimer->stop();
        QMessageBox::information(this,"Вы взорвались!","Чтобы воспользоваться программой снова, закройте ее и запустите снова!");
    }
}
//таймер задержки
void MainWindow::timerDelay()
{   
    int spinbox_value = ui->spinBox->value();//считываем значение spinBox    
    if (delayed_counter != spinbox_value*100)
    {
        int msec = delayed_counter*10;
        delayed_counter++;
        QTime time = QTime::fromMSecsSinceStartOfDay(msec);
        QString text = time.toString("mm:ss.zzz");//создаем маску для вывода чисел
        ui->lcdNumber_startIN->display(text);//выводим
        true_delayed_counter=ui->dial->value();
    }
    else
    {
        delaytimer->start(1000);
        true_delayed_counter--;
        QTime time = QTime::fromMSecsSinceStartOfDay(true_delayed_counter*1000);
        QString text = time.toString("mm:ss.zzz");//создаем маску для вывода чисел
        ui->lcdNumber_startIN->display(text);//выводим

        if (true_delayed_counter == 0)
        {
            delaytimer -> stop();
        }
    }
}
//кнопка активации таймера
void MainWindow::on_pushButton_start_delay_clicked()
{
    delaytimer->start(10);
    delayed_counter = 0;
    true_delayed_counter = 0;
}


