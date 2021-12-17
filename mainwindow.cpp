#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_channell = new connectYt(this);

    connect(ui->queryWin, &QLineEdit::textChanged, this, &MainWindow::textProc);
    connect(this, &MainWindow::sendRequest, m_channell, &connectYt::fetchData);
    connect(m_channell, &connectYt::sendData, this, &MainWindow::showResult);

    startFunc();
}

MainWindow::~MainWindow()
{
    delete ui;    
}

void MainWindow::showResult(bool flagReq, unsigned long num)
{
    if(flagReq)
        successConn(num);

    else
        errorConn(num);
}

void MainWindow::startFunc()
{
    ui->label_error->setText("Insert YouTube video link");
    ui->label_count->setText("0");

    QImage imgLikePng(":/images/question.png");
    ui->label_pic->setPixmap(QPixmap::fromImage(imgLikePng));
}

void MainWindow::successConn(unsigned long num)
{
    ui->label_error->setText("All right. Communication is correct");
    ui->label_count->setText(QString::number(num));

    QImage imgLikePng(":/images/thumb-up.png");
    ui->label_pic->setPixmap(QPixmap::fromImage(imgLikePng));
}

void MainWindow::errorConn(unsigned long num)
{
    ui->label_error->setText("Ooops... something went wrong");
    ui->label_count->setText(QString::number(num));

    QImage imgLikePng(":/images/close.png");
    ui->label_pic->setPixmap(QPixmap::fromImage(imgLikePng));
}

void MainWindow::textProc(const QString &str)
{
    int size = str.length();

    if(!size)  {       
        startFunc();
        return;
    }

    else if(size <= SIZE_PREAM)
        return;

    QString tmp_str(strProc(str));

    emit sendRequest(tmp_str);
}

QString MainWindow::strProc(const QString &str)
{
    QString tmp_str;

    int posit = str.indexOf('&'),
        size  = str.size();

    if(posit == -1)
        tmp_str = str.trimmed().mid(SIZE_PREAM, size - SIZE_PREAM);

    else
        tmp_str = str.trimmed().mid(SIZE_PREAM, posit - SIZE_PREAM);

    return tmp_str;
}

