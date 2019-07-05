#include "map.h"
#include "ctime"
#include <QApplication>
#include "QDir"
#include "string.h"
#include "generationpoint.h"
//u - 1, r - 2, d - 3, l - 4


Map::Map()
{
    //movableObjects[3][2] = new Car(20, 30, 0xFF0000, this);
    //vobj.push_back(movableObjects[3][2]);
    //movableObjects[20][45] = new Car(450, 200, 0xFF0000, this);
    //vobj.push_back(movableObjects[20][45]);
    ReadMap();
}

void Map::ReadMap(){

    QString v = QDir::currentPath() + "/res/Map.txt";
    QFile f(":/res/Map.txt");
    f.open(QIODevice::ReadOnly);
    if(f.isOpen()) qDebug("opened");
    else qDebug("not opened");

    srand(time(nullptr));

    QTextStream file(&f);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            int temp;
            file >> temp;
            unmovableObjects[i][j] = temp;
            if(temp == 77){
                generationPoint *g = new generationPoint(j * CELL_SIZE, i * CELL_SIZE, this);
                vobj.push_back(g);
                amOfGP++;
            }
        }
    }

}

void Map::NextStep(double dt){
    /*for(Object* obj : vobj){
        if(obj->getType() == 77)
            obj->nextStep(dt);
    }*/
    for(int i = 0, s = vobj.size(); i < s; i++){
        vobj[i]->nextStep(dt);
    }
    timePassed += dt;

}

void Map::getInformation(int &nextReasonToStop, int x, int y, int &dest, int choosenWay, Object* &reas, int &destToObj){
    int currWay = unmovableObjects[y / CELL_SIZE][x / CELL_SIZE];

    if(currWay > 4 && currWay < 50){
        if(choosenWay > 0)
            currWay = choosenWay;
        else if(choosenWay == -1) currWay %= 10;
    }

    if(currWay == roadr){
        recCore(x, y, 1, 0, dest, nextReasonToStop, choosenWay,  reas, destToObj);
    }
    else if(currWay == roadd){
        recCore(x, y, 0, 1, dest, nextReasonToStop, choosenWay,  reas, destToObj);
    }
    else if(currWay == roadu){
        recCore(x, y, 0, -1, dest, nextReasonToStop, choosenWay, reas, destToObj);
    }
    else if(currWay == roadl){
        recCore(x, y, -1, 0, dest, nextReasonToStop, choosenWay, reas, destToObj);
    }


}

void Map::recCore(int x, int y, int dx, int dy, int &dest, int &nextReasonToStop, int choosenWay, Object* &reas, int &destToObj){


    dest++;
    int currWay = unmovableObjects[y / CELL_SIZE][x / CELL_SIZE];
    int nextWay = unmovableObjects[y / CELL_SIZE + dy][x / CELL_SIZE + dx];
    if(choosenWay > 0){
        if(currWay > 4 && currWay < 50){
            currWay = choosenWay;
            choosenWay = -1;

        }
        else if(nextWay > 4 && nextWay< 50){
            nextWay = choosenWay;
        }
        else;
    }
    else
        if(choosenWay == -1 && nextWay > 4 && nextWay < 50) nextWay %= 10;
        else if(choosenWay == -1 && currWay > 4 && currWay < 50) currWay %= 10;
    if(movableObjects[y / CELL_SIZE + dy][x / CELL_SIZE + dx] != nullptr){
        if(reas == nullptr){
            reas = movableObjects[y / CELL_SIZE + dy][x / CELL_SIZE + dx];
            destToObj = dest;
        }
    }
    if(nextWay != currWay){
        nextReasonToStop = nextWay;
    }
    else {
        getInformation(nextReasonToStop, x + dx * CELL_SIZE, y + dy * CELL_SIZE, dest, choosenWay,  reas, destToObj);
    }

}




double Map::getTime(){return timePassed;}

void Map::setStreamLevel(int val){
    streamLevel = val;
    for(int i = 0, s = vobj.size(); i < s; i++){
        if(vobj[i]->getType() == 77)
            ((generationPoint*)vobj[i])->update();
    }
}
int Map::getStreamLevel(){return streamLevel;}
bool Map::getCarCrashing(){return carCrashing;}

void Map::setCarCrashing(bool val){
    carCrashing = val;
}


/*void f (Transport* transport){

}*/
