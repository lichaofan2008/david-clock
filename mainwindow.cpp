#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <QTimer>
#include <MyLog.h>
#include <QThread>

#ifdef _WIN32
#include <windows.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uiInit();
    //resize(1366, 768);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        exit(0);
        return;
    }

    if (event->key() == Qt::Key_Up) {
        int _sizeOrig = ui->time->font().pointSize();
        int _size     = (int)(_sizeOrig * 1.1F);
        QFont _font = ui->time->font();
        _font.setPointSize(_size);
        logi("font pointSize(%d => %d)", _sizeOrig, _size);
        ui->time->setFont(_font);
        mSettings.setValue("font_size", _size);
        return;
    }

    if (event->key() == Qt::Key_Down) {
        int _sizeOrig = ui->time->font().pointSize();
        int _size     = (int)(_sizeOrig * 0.9F);
        QFont _font = ui->time->font();
        _font.setPointSize(_size);
        logi("font pointSize(%d => %d)", _sizeOrig, _size);
        if (_size < 10) {
            return;
        }

        ui->time->setFont(_font);
        mSettings.setValue("font_size", _size);
        return;
    }

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        int _sizeOrig = ui->time->font().pointSize();
        int _size     = 200;
        QFont _font = ui->time->font();
        _font.setPointSize(_size);
        logi("font pointSize(%d => %d)", _sizeOrig, _size);
        ui->time->setFont(_font);
        mSettings.setValue("font_size", _size);
        return;
    }

    QWidget::keyReleaseEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    ui->time->resize(ui->centralwidget->size());
}

void MainWindow::uiInit() {
    setCursor(QCursor(Qt::BlankCursor));
    //ui->time->setScaledContents(true);
    ui->time->setStyleSheet("background:black;color:white;");
    ui->date->setStyleSheet("color:white;");
    getTime();
    getDate();

    if (mSettings.contains("font_size")) {
        QFont _font = ui->time->font();
        _font.setPointSize(mSettings.value("font_size", 200).toInt());
        ui->time->setFont(_font);
    }

    avoidScreenSaver();
}

void MainWindow::getTime() {
    QDateTime _dateTime = QDateTime::currentDateTime();
    QString _time = _dateTime.toString("hh:mm:ss");
    logi("time(%s)", CHAR(_time));
    ui->time->setText(_time);

    QTimer::singleShot(1000, this, &MainWindow::getTime);
}

void MainWindow::getDate() {
    QDateTime _dateTime = QDateTime::currentDateTime();
    QString _date = _dateTime.toString("yyyy-MM-dd");
    logi("date(%s)", CHAR(_date));
    ui->date->setText(_date);

    QTimer::singleShot(60 * 1000, this, &MainWindow::getDate);
}

void MainWindow::avoidScreenSaver() {
#ifdef _WIN32
    keybd_event(VK_SCROLL, 0, KEYEVENTF_EXTENDEDKEY, 0);
    QThread::msleep(10);
    keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);
    QTimer::singleShot(60 * 1000, this, MainWindow::avoidScreenSaver);
#endif
}
