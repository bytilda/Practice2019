#include "mapwidget.h"
#include "ui_mapwidget.h"


MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWidget)
{
    ui->setupUi(this);

    //map.movableObjects[10][10] = new Transport(10,10, 0x00FF00);
    //update();
    //setUpdatesEnabled(false);
}

MapWidget::~MapWidget()
{
    delete ui;
}
void MapWidget::setHasStarted(bool val){
    hasStarted = val;
}

void MapWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    //отрисовка сетки
    painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::FlatCap));
    //!!
    for(int i = 0; i < 100; i++){
        for(int k = 0; k < 100; k++){
                painter.drawRect(i * CELL_SIZE, k * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
    if(hasStarted){
        //painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
        //painter.drawLine(a,0,this->height(),this->width());
        for(int y = 0; y < 100; y++){
            for(int x = 0; x < 100; x++){
                //отрисовка дороги
                //обочина
                if(map.unmovableObjects[y][x] == border){
                    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
                    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
                    painter.drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

                }
                if(map.unmovableObjects[y][x] == 77){
                    painter.setPen(QPen(Qt::yellow, 3, Qt::SolidLine, Qt::FlatCap));
                    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
                    painter.drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 2, CELL_SIZE - 2);
                    /*if(rand() % 100 == 1){
                        map.createTransport(x, y);
                    }*/
                }
                if(map.unmovableObjects[y][x] == 66){
                    painter.setPen(QPen(Qt::yellow, 3, Qt::SolidLine, Qt::FlatCap));
                    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                    painter.drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 2, CELL_SIZE - 2);
                }

            }
        }
        for(Object* obj : map.vobj){
            if(obj->getType() == 100){
                if(((Transport*)obj)->isCrashed()){
                    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                    painter.setPen(QPen(QColor(QRgb(0xFC0FC0)), 3, Qt::SolidLine, Qt::FlatCap));
                }
                else{
                    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                    painter.setPen(QPen(QColor(QRgb(((Transport*)(obj))->getColor())), 3, Qt::SolidLine, Qt::FlatCap));
                }
                painter.drawRect(((Transport*)(obj))->getX() + 1, ((Transport*)(obj))->getY(), 0.8* CELL_SIZE,  0.8 * CELL_SIZE);
            }
        }

    }



}
double MapWidget::getTime(){return map.getTime();}
void MapWidget::nextStep(double dt){
    map.NextStep(dt);
    this->update();
}

int MapWidget::getInfoaboutAmountOfTransport(){
    return map.vobj.size() - map.amOfGP;;
}

void MapWidget::enableCrashes(){ map.setCarCrashing(true);}
