#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <iostream>
#include <qdebug.h>


QString mimagePath;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageObject = new QImage();
    scene = new QGraphicsScene(this);
    thread.reset(new QThread);
    worker.reset(new Worker);
    ui->convertButton->setEnabled(false);

    connect(this,&MainWindow::triggerPicConversion,this,&MainWindow::startThread);
    connect(thread.get(),&QThread::started,worker.get(),&Worker::convertPic);
    connect(worker.get(),&Worker::conversionComplete,thread.get(),&QThread::quit);
    connect(thread.get(),&QThread::finished,worker.get(),&Worker::deleteLater);

    worker.get()->moveToThread(thread.get());


}

MainWindow::~MainWindow()
{
    delete ui;
}

//tr("JPEG (*.jpg *.jpeg);BMP(*.bmp);PNG (*.png)" )
void MainWindow::on_openButton_clicked()
{
     mimagePath = QFileDialog::getOpenFileName(this,tr("Open File"),"","");
    qDebug() <<"Image File Path is:"<<mimagePath;

    ui->convertButton->setEnabled(true);


}

void MainWindow::startThread()
{

    thread.get()->start();

}

Worker::Worker()
{
    imageObject = new QImage();
}

Worker::~Worker()
{

}


void Worker::convertPic(){

    qDebug() <<"Image File Path is:"<< mimagePath;;
    if(!imageObject->load(mimagePath,"BMP")){
        qDebug() <<"Image File Could not be loaded";
    }
    if (!imageObject->save("D:/Shivam/QtProjectsRepo/ImageConverter0/convertedTestImg16Aug2.png", "PNG")){
        qDebug() << "Could not save the image";
    }


    qDebug() << "Conversion completed successfully.";

    emit conversionComplete();
}

void Worker::setImagePath(const QString img)
{
    mImagePath = img;
}

void MainWindow::on_convertButton_clicked()
{
   emit triggerPicConversion();
}
