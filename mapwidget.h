#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "qpainter.h"
#include "map.h"
#include "transport.h"
#include "object.h"
//#define CELL_SIZE 10

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();
    void paintEvent(QPaintEvent *event);
    void setHasStarted(bool val);
    void nextStep(double dt);
    int getInfoaboutAmountOfTransport();
    double getTime();
    void setStreamLevel(int val) {map.setStreamLevel(val);}
    void enableCrashes();


private:
    Ui::MapWidget *ui;
    Map map;
    bool hasStarted = false;

};

#endif // MAPWIDGET_H
