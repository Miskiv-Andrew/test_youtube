#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connect.h"


#define SIZE_PREAM 32

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void showResult(bool, unsigned long);
    void startFunc();
    void successConn(unsigned long num);
    void errorConn(unsigned long num);

private slots:

    void textProc(const QString&);
    QString strProc(const QString&);

private:

    Ui::MainWindow *ui;
    connectYt * m_channell;

signals:

    void sendRequest(QString &);

};
#endif // MAINWINDOW_H
