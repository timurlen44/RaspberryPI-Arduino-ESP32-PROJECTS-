#include "mainwindow.h"
#include "ui_mainwindow.h"

#define	RED	5
#define GREEN 6
#define ServoPin 18

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wiringPiSetupGpio () ;
    pinMode (RED, OUTPUT) ;
    pinMode (GREEN, OUTPUT) ;
    pinMode (ServoPin, PWM_OUTPUT) ;
    digitalWrite (RED, LOW) ;
    digitalWrite (GREEN, LOW) ;
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    digitalWrite(RED,HIGH);
}
void MainWindow::on_pushButton_2_clicked()
{
    digitalWrite(RED,LOW);
}
void MainWindow::on_pushButton_3_clicked()
{
    digitalWrite(GREEN,HIGH);
}

void MainWindow::on_pushButton_4_clicked()
{
    digitalWrite(GREEN,LOW);
}

void MainWindow::on_pushButton_5_clicked()
{

        int servo_acisi = ui->lineEdit->text().toInt();
        servo_acisi +=1;

        if(servo_acisi<0){
            pwmWrite(ServoPin,40);
        }
        else if(servo_acisi>180){

            pwmWrite(ServoPin,240);
        }
        else {
            double f_servo_aci = ((double)servo_acisi)*(200.0/180.0);
            servo_acisi = (int)f_servo_aci + 40;
            pwmWrite(ServoPin,servo_acisi);
        }
}
