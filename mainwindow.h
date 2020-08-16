#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QThread>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Worker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void startThread();

    void on_convertButton_clicked();
signals:
    void triggerPicConversion();
    void sendImagePath(const QString);
private:
    Ui::MainWindow *ui;
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;

//    QThread *thread;
    std::unique_ptr<QThread> thread;
    std::unique_ptr<Worker> worker;

};

class Worker : public QObject{
    Q_OBJECT
public:
    Worker();
    ~Worker();
private:
    QImage  *imageObject;
    QPixmap image;
    QString mImagePath;
public slots:
    void convertPic();
    void setImagePath(const QString);
signals:
    void conversionComplete();
};
#endif // MAINWINDOW_H
