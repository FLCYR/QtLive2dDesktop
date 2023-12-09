#ifndef LIVE2DWIDGET_H
#define LIVE2DWIDGET_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")



class Live2DWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit Live2DWidget(QWidget *parent = nullptr);
    ~Live2DWidget();
    void nextModel();
    void addInitModel(QString modelPath);
    void setRate(float rate);
    int getModelsSize();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


    void mousePressEvent(QMouseEvent *e );
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void enterEvent(QEvent*e);


public slots:
    void onTimerUpdate();
    void addModel(const QString  path);
private:

    float deltaTime;
    bool isPressed;
    QTimer * fpsTimer;

signals:

private:
   //QOpenGLFunctions glFunc;

};

#endif // LIVE2DWIDGET_H
