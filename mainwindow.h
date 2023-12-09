#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <subwin.h>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QStyle>
#include <QHotKey>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void initSystemTray();

    void readJsonData(const QString filepath,const QString ext,QJsonArray&jsonArr);
    void loadModelFromJson(QString filepath);
    void changeMotionJson(const QString filepath);
    void changeAllMotion(const QString filepath);
    void switchNextModel();
protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent* event);
   // bool eventFilter(QObject *target, QEvent *event);

private:
    Ui::MainWindow *ui;
    bool isPressed;
    QPoint curPos;
    SubWin * sw;
    QSystemTrayIcon* trayIcon;


};
#endif // MAINWINDOW_H
