#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setMouseTracking(true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setWindowFlag(Qt::Tool);      //hide application icon
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->resize(400,800);

    sw = new SubWin();
    initSystemTray();
    connect(sw,&SubWin::addModelSignal,this,[this]()
    {
        QString filepath = QFileDialog::getOpenFileName(this,"add Live2d Model","","JSON(*.model3.json)");
        if(!filepath.isEmpty())
        {
             this->loadModelFromJson(filepath);
             ui->openGLWidget->addModel(filepath);
        }
    });

    connect(sw,&SubWin::changeRate,this,[this](int rate)
    {
       ui->openGLWidget->setRate(rate*30);
    });


    //hotkey
    QHotkey * hotkey = new QHotkey(QKeySequence("Ctrl+W"), true);   //switch next model

    connect(hotkey, &QHotkey::activated,this,[this]()
    {
        ui->openGLWidget->nextModel();
    });


    QString curDir = QApplication::applicationDirPath();
    curDir+="/Resources";

    ui->openGLWidget->addInitModel(QString("%1/%2").arg(curDir,"Mao/Mao.model3.json"));
    ui->openGLWidget->addInitModel(QString("%1/%2").arg(curDir,"fangcao/fangcao.model3.json"));
    ui->openGLWidget->addInitModel(QString("%1/%2").arg(curDir,"Hiyori/Hiyori.model3.json"));
    ui->openGLWidget->addInitModel(QString("%1/%2").arg(curDir,"lafei/lafei_4.model3.json"));
    ui->openGLWidget->addInitModel(QString("%1/%2").arg(curDir,"taiyuan/taiyuan_2.model3.json"));
    ui->openGLWidget->addInitModel(QString("%1/%2").arg(curDir,"yichui/yichui_2.model3.json"));

}


void MainWindow::switchNextModel()
{

    ui->openGLWidget->nextModel();
}


MainWindow::~MainWindow()
{


    sw->close();
    delete trayIcon;
    delete ui;
}

void MainWindow::initSystemTray()
{

    trayIcon = new QSystemTrayIcon();


    QThread * trayThread = new QThread();
    trayIcon->moveToThread(trayThread);
    trayThread->start();


    trayIcon->setIcon(QIcon(":/icons/panda.png"));

    QMenu* trayMenu = new QMenu();


    QAction* settingAction = trayMenu->addAction("设置");
    QAction* addAction = trayMenu->addAction("添加模型");
    QAction* nextAction = trayMenu->addAction("下一个");
    QAction* quitAction = trayMenu->addAction("退出");


    // QMenu QSS
    QString menuQSS = "QMenu {background-color: #ffffff; border: 1px solid #ccc;} "
                      "QMenu::item {padding: 13px 20px 13px 20px; border-bottom: 1px solid #ccc;} "
                      "QMenu::item:selected {background-color: #def;}"
                      "QMenu::icon:checked {background: gray;}"
                      "QMenu::icon {padding:10px;}";


    trayMenu->setStyleSheet(menuQSS);


    quitAction->setIcon(style()->standardIcon(QStyle::SP_MessageBoxCritical));
    addAction->setIcon(style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
    nextAction->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    settingAction->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView));


    trayIcon->setContextMenu(trayMenu);
    connect(settingAction,&QAction::triggered,[this]()
    {
        sw->show();
    });
    connect(nextAction,&QAction::triggered,this,[this]()
    {
       ui->openGLWidget->nextModel();
    });
    connect(quitAction,&QAction::triggered,[]()
    {
        qApp->quit();
    });

    connect(addAction,&QAction::triggered,this,[this]()
    {
        QString filepath = QFileDialog::getOpenFileName(this,"Add Live2d model","","JSON(*.model3.json)");
        if(!filepath.isEmpty())
        {
             this->loadModelFromJson(filepath);
             ui->openGLWidget->addModel(filepath);
        }
    });
    trayIcon->show();

}



void MainWindow::mouseMoveEvent(QMouseEvent*event)
{
    if(isPressed)
    {
        this->move(event->pos()-curPos+this->pos());
    }

}
void MainWindow::mousePressEvent(QMouseEvent*event)
{
    if(event->button()==Qt::LeftButton)
    {
        isPressed=true;
        curPos=event->pos();
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent*event)
{
    isPressed=false;
}


void MainWindow::changeAllMotion(const QString filepath)
{

    QFileInfo info(filepath);
    QString path = QString("%1/%2").arg(info.path(),"motions");
    QDir mPath(path);
    if (mPath.exists())
    {
        mPath.setFilter(QDir::Files);
        QFileInfoList fileList = mPath.entryInfoList();

        for(QFileInfo & fileInfo : fileList)
        {
            QString path = fileInfo.absoluteFilePath();
            changeMotionJson(path);
        }
    }
}

void MainWindow::changeMotionJson(const QString filepath)
{

    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly))
    {

        QByteArray data = file.readAll();

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data,&error);
        file.close();
        if(error.error == QJsonParseError::NoError)
        {
            QJsonObject json = doc.object();
            QJsonObject meta = json["Meta"].toObject();
            int cnt = 0;
            if(meta.contains("CurveCount"))
            {
                cnt = meta["CurveCount"].toInt();
                if(meta.contains("TotalSegmentCount"))
                {

                    meta["TotalSegmentCount"]=cnt*1000;
                }
                if(meta.contains("TotalPointCount"))
                {

                    meta["TotalPointCount"]=cnt*1000;
                }

                json["Meta"]=meta;
                file.setFileName(filepath);
                file.open(QIODevice::WriteOnly);
                file.write(QJsonDocument(json).toJson());
                file.close();
            }

        }
    }

}
void MainWindow::readJsonData(const QString filepath,const QString ext,QJsonArray&jsonArr)
{


    QFileInfo info(filepath);
    QString path = QString("%1/%2").arg(info.path(),ext);
    QDir mPath(path);
    if (mPath.exists())
    {
        mPath.setFilter(QDir::Files);
        QFileInfoList fileList = mPath.entryInfoList();
        QJsonObject tmp;
        for(QFileInfo & fileInfo : fileList)
        {
            qDebug()<<fileInfo.fileName();
            tmp["File"]=ext+"/"+fileInfo.fileName();
            if(ext=="expressions")
            {
                tmp["Name"]=fileInfo.baseName();
            }
            jsonArr.append(tmp);
        }
    }
}
void MainWindow::loadModelFromJson(QString filepath)
{


    changeAllMotion(filepath);

    //read all motions and create json obj
    QJsonArray mArr;    //motions
    QJsonArray expArr;  //expressions

    readJsonData(filepath,"motions",mArr);
    readJsonData(filepath,"expressions",expArr);

    if(!filepath.isEmpty())
    {
        QFile file(filepath);
        if(file.open(QIODevice::ReadOnly))
        {

            QByteArray data = file.readAll();

            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(data,&error);
            if(error.error == QJsonParseError::NoError)
            {
                QJsonObject json = doc.object();
                QJsonObject fileRef = json["FileReferences"].toObject();
                QJsonObject motions = fileRef["Motions"].toObject();

                motions["Idle"] = mArr;
                fileRef["Motions"]=motions;

                fileRef["Expressions"]=expArr;
                json["FileReferences"]=fileRef;
                file.close();

                file.setFileName(filepath);
                file.open(QIODevice::WriteOnly);
                file.write(QJsonDocument(json).toJson());
                file.close();
            }
        }
    }
}





