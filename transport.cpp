#include "transport.h"
#include "map.h"

Transport::Transport()
{    

}
Transport::Transport(double x, double y, double ax, double ay, Map *m):Object(x, y, m){
    vx = 0;
    vy = 0;
    this->color = abs(rand() * rand()) | 0xA0A0A0;
    currDirection = map->unmovableObjects[(int)y/CELL_SIZE][(int)x / CELL_SIZE];
    nextDirection = 0;
    this->ax = ax;
    this->ay = ay;
    if(fabs(ax) > fabs(ay)) newa = fabs(ax);
    else newa = fabs(ay);

}
void Transport::nextStep(double dt){
    if(crashed){
        crashedTime -= dt;
        if(crashedTime <= 0){
            deathf();
        }
        return;
    }

    if(currDirection != roadu && currDirection != roadl)
        map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] = nullptr;
    else map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE] = nullptr;

    Object* reas = nullptr;
    int destToObj = 0;

    //узнаем, какая след. причина для торможения
    destToNextDirection = 0;
    if(currDirection == roadr || currDirection == roadd)
        map->getInformation(nextDirection, x, y, destToNextDirection, choosenWay, reas, destToObj);
    else map->getInformation(nextDirection, x + 9, y + 9, destToNextDirection, choosenWay,  reas, destToObj);



    //скоро перекресток
    if(nextDirection > 4 && nextDirection < 50){
        if(choosenWay == 0){
            //выбираем направление на след. перекрестке
            nextDirection = chooseWay(nextDirection);
            choosenWay = nextDirection;
            destToNextDirection = 0;
            if(currDirection == roadr || currDirection == roadd)
                map->getInformation(nextDirection, x, y, destToNextDirection, choosenWay,  reas, destToObj);
            else map->getInformation(nextDirection, x + 9, y + 9, destToNextDirection, choosenWay,  reas, destToObj);
        }
        else {
          nextDirection = choosenWay;
        }
    }


    if(destToNextDirection > primordialDest) primordialDest = destToNextDirection;



    if(reas != nullptr && destToObj < 3){
        destToObj--;
        if(destToObj < 3){
            if(destToObj > 0){
                if(currDirection == roadr) ax = -vx*vx/((destToObj * CELL_SIZE) / 2);
                else if(currDirection == roadl) ax = vx*vx/((destToObj * CELL_SIZE) / 2);
                else if(currDirection == roadu) ay = vy*vy/((destToObj * CELL_SIZE) / 2);
                else if(currDirection == roadd) ay = -vy*vy/((destToObj * CELL_SIZE) / 2);
            }
            //полностью останавливаемся, если перед нами объект
            else if(destToObj == 0){
                ax = 0;
                ay = 0;
                vy = 0;
                vx = 0;
            } else;/*{
                //если появилось расстояние между машинами, то
                if(destToObj == 1){
                    if(fabs(vx) < 0.001 && fabs(vy) < 0.001){
                        if(currDirection == roadu) ay = ((Transport*)reas)->getAy();
                        else if(currDirection == roadd) ay = ((Transport*)reas)->getAy();
                        else if(currDirection == roadr) ax = ((Transport*)reas)->getAx();
                        else if(currDirection == roadl) ax = ((Transport*)reas)->getAx();

                        else
                            qDebug() << currDirection << " " << length++ << " " << color << endl;
                        //vx += ax * dt;
                        //vy += ay * dt;
                        primordialDest = destToNextDirection;

                    }
                }
            }*/
        }
    }
    else{
        //если после предыдущего торможения скорость слишком низкая, а препятствия больше нет, то
        //для разгона дается ускорение и половина расстояния до след. выбранного поворота
        if(fabs(vx) < 2 && fabs(vy) < 2){
            if(currDirection == roadu) ay = -newa;
            else if(currDirection == roadd) ay = newa;
            else if(currDirection == roadr) ax = newa;
            else if(currDirection == roadl) ax = -newa;
            else;
            vx += ax * dt;
            vy += ay * dt;
            primordialDest = destToNextDirection;

        }
        if(destToNextDirection < 3 && destToNextDirection < (double)primordialDest / 2){
            if(destToNextDirection == 0) destToNextDirection = 1;
            if(currDirection == roadr /*&& vx > -minv*/)
                ax = -vx*vx/((destToNextDirection * CELL_SIZE) / 2);
            else if(currDirection == roadl /*&& vx < -minv*/)
                ax = vx*vx/((destToNextDirection * CELL_SIZE) / 2);
            else if(currDirection == roadu /*&& vy < -minv*/)
                ay = vy*vy/((destToNextDirection * CELL_SIZE) / 2);
            else if(currDirection == roadd /*&& vy > minv*/)
                ay = -vy*vy/((destToNextDirection * CELL_SIZE) / 2);
            else;
        }
        //исправление погрешностей
        //если торможение перед машиной началось, но ускорение оказалось слишком большим и оттолкнуло
        else{
            if(currDirection == roadu)
                if(vy > 0 && fabs(vy) > 0.000001){
                    ay = 0;
                    vy = 0;
                }
                else;
            else if(currDirection == roadd)
                if(vy < 0 && fabs(vy) > 0.000001){
                    vy = 0;
                    ay = 0;
                }
                else;
            else if(currDirection == roadr)
                if(vx < 0 && fabs(vx) > 0.000001){
                    vx = 0;
                    ax = 0;
                }
                else;
            else if(currDirection == roadu)
                if(vx > 0 && fabs(vx) > 0.000001){
                    vx = 0;
                    ax = 0;
                }
        }
    }

    //изменение координат и скорости
    x += (ax*dt*dt/2 + vx*dt);
    if((fabs(vx) < maxv && vx / ax > 0) || fabs(vx) < 0.00001 || vx / ax < 0) vx += ax * dt;
    y += (ay*dt*dt/2 + vy*dt);
    if((fabs(vy) < maxv && vy / ay > 0) || fabs(vy) < 0.00001 || vy / ay < 0) vy += ay * dt;

    if(x > 1000 || y > 1000 || y < 0 || x < 0){
        deathf();
        return;
    }

    if(map->getCarCrashing()){
        if(map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE] != nullptr){
            //((Transport*)map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE])->
            ((Transport*)map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE])->crash();
            crash();
        }
        if(map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] != nullptr){
            ((Transport*)map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE])->crash();
            if(!this->crashed) crash();
        }
        if(crashed) return;


    }


    if(currDirection == roadr || currDirection == roadd)
        currDirection = map->unmovableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE];
    else currDirection = map->unmovableObjects[(int)(y + 9)/ CELL_SIZE][(int)(x + 9) / CELL_SIZE];


    if(currDirection > 4 && currDirection < 50)
        if(choosenWay != 0)
            currDirection = choosenWay;



    if(currDirection != roadu && currDirection != roadl)
        if(map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] == nullptr)
            map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] = this;
    else;
    else
        map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE] = this;



    if(nextDirection == currDirection){        
        if(map->unmovableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] <= 4)
            if(choosenWay != 0)
                choosenWay = 0;
        primordialDest = 0;
        if(nextDirection == roadu || nextDirection == roadd){
            ax = 0;
            vx = 0;

            if(nextDirection == roadd){
                ay = newa;
            }
            else if(nextDirection == roadu)
                ay = -newa;
            vy += ay * dt;
        }
        else if(nextDirection == roadr || nextDirection == roadl){
            ay = 0;
            vy = 0;
            if(nextDirection == roadl) ax = -newa;
            else if(nextDirection == roadr)
                ax = newa;

            vx += ax * dt;
        }
        else if(currDirection == death){
            deathf();
        }
    }

}





int Transport::getColor(){
    return color;
}

int Transport::chooseWay(int var){
    int pr = rand() % 2;
    if(pr) return var % 10;
    else return var / 10;
}



int Transport::getX(){ return x;}
int Transport::getY(){ return y;}

double Transport::getAx(){ return ax;}
double Transport::getAy(){ return ay;}

bool Transport::isCrashed(){ return crashed;}

void Transport::crash(){
    crashed = true;
    ax = vx = vy = ay = 0;
    crashedTime = crtime;
}

void Transport::deathf(){
    if(map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] == this)
        map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] = nullptr;
    //map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE] = this;
    if(map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE] == this){
        map->movableObjects[(int)(y + 0.9 * CELL_SIZE) / CELL_SIZE][(int)(x + 0.9*CELL_SIZE) / CELL_SIZE] = nullptr;
        qDebug() << "1";
    }
    map->movableObjects[(int)y / CELL_SIZE][(int)x / CELL_SIZE] = nullptr;
    map->vobj.erase(std::remove(map->vobj.begin(), map->vobj.end(), this), map->vobj.end());

}
