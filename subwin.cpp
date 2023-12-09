#include "subwin.h"
#include "ui_subwin.h"
#include <QDebug>
SubWin::SubWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWin)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);


    connect(ui->btnAdd,&QPushButton::clicked,[this]()
    {
        emit addModelSignal();
    });

    ui->comRate->addItem("30");
    ui->comRate->addItem("60");
    ui->comRate->addItem("90");
    ui->comRate->addItem("120");
    ui->comRate->setCurrentIndex(1);
    connect(ui->comRate,QOverload<int>::of(&QComboBox::currentIndexChanged),[this](int index)
    {
        emit changeRate(index+1);
    });
    connect(ui->btnClose,&QPushButton::clicked,[this]()
    {
        this->hide();
    });
    ui->btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    loadQss();
}



SubWin::~SubWin()
{
    delete ui;
}


void SubWin::loadQss()
{
//    QFile file(":/style/subWin.qss");
//    if(file.open(QIODevice::ReadOnly))
//    {
//        this->setStyleSheet(file.readAll());
//    }
}


void SubWin::mouseMoveEvent(QMouseEvent*event)
{
    if(isPressed)
    {
        this->move(event->pos()-curPos+this->pos());
    }
}




void SubWin::mousePressEvent(QMouseEvent*event)
{
    if(event->button()==Qt::LeftButton)
    {
        isPressed=true;
        curPos=event->pos();
    }
}

void SubWin::mouseReleaseEvent(QMouseEvent*event)
{
    isPressed=false;
}

void SubWin::hideWin()
{
    this->hide();
}
