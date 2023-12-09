

#include "control/LAppDelegate.hpp" //set in the front
#include "control/LAppView.hpp"
#include "control/LAppPal.hpp"
#include "control/LAppLive2DManager.hpp"
#include "control/LAppDefine.hpp"
#include "live2dwidget.h"

#include <QOpenGLFunctions>
#include <QDebug>
#include <QThread>

Live2DWidget::Live2DWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);
    fpsTimer = new QTimer(this);
    isPressed = false;
    fpsTimer->start((1.0/60.0)*1000);
    connect(fpsTimer,&QTimer::timeout,this,&Live2DWidget::onTimerUpdate);
}

Live2DWidget::~Live2DWidget()
{

    LAppDelegate :: GetInstance()->Release();
    LAppDelegate::ReleaseInstance();
}
void Live2DWidget::nextModel()
{



    this->makeCurrent();
    LAppLive2DManager::GetInstance()->NextScene();
    this->doneCurrent();

}
void Live2DWidget::onTimerUpdate()
{
    update();
}

int Live2DWidget::getModelsSize()
{
    return  LAppDefine::ModelDir.size();
}
void Live2DWidget::addModel(const QString path)
{

    QFile file(path);
    if(file.exists())
    {
        LAppDefine::addModel(path);

        int index = LAppDefine::ModelDir.indexOf(path);
        index=(index==-1?LAppDefine::ModelDir.size()-1:index);
        this->makeCurrent();
        LAppLive2DManager::GetInstance()->ChangeScene(index);
        this->doneCurrent();

    }


}
void Live2DWidget::initializeGL()
{


    LAppDelegate::GetInstance()->Initialize(this);

}

void Live2DWidget::enterEvent(QEvent*e)
{

}
void Live2DWidget::resizeGL(int w, int h)
{
    LAppDelegate::GetInstance()->resize(w,h);

}

void Live2DWidget::paintGL()
{
    LAppDelegate::GetInstance()->update();
    deltaTime = LAppPal::GetDeltaTime();


}

void Live2DWidget::mouseMoveEvent(QMouseEvent *e)
{
     LAppDelegate::GetInstance()->GetView()->OnTouchesMoved(e->x(),e->y());
     update();
     e->ignore();
}
void Live2DWidget::mousePressEvent(QMouseEvent * e)
{


    if(e->button() == Qt::LeftButton)
    {
        isPressed = true;
        LAppDelegate::GetInstance()->GetView()->OnTouchesBegan(e->x(),e->y());

    }
     e->ignore();

}

void Live2DWidget::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        isPressed = false;
        LAppDelegate::GetInstance()->GetView()->OnTouchesEnded(e->x(), e->y());
        update();
    }
     e->ignore();
}

void Live2DWidget::addInitModel(QString modelPath)
{
    QFile file(modelPath);
    if(file.exists())
    {
        LAppDefine::addModel(modelPath);
    }
}

void Live2DWidget::setRate(float rate)
{
    fpsTimer->stop();
    fpsTimer->start((1.0/rate)*1000);
}
