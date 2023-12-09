#ifndef SUBWIN_H
#define SUBWIN_H

#include "preDefine.h"
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class SubWin;
}

class SubWin : public QWidget
{
    Q_OBJECT

public:
    explicit SubWin(QWidget *parent = nullptr);
    ~SubWin();

    void hideWin();
    void onCloseBtn();
    void loadQss();
protected:

    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void addModelSignal();
    void changeRate(int rate);


private:
    Ui::SubWin *ui;
    bool isPressed;
    QPoint curPos;
};

#endif // SUBWIN_H
