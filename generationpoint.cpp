#include "generationpoint.h"

//class Map;

generationPoint::generationPoint()
{

}

generationPoint::generationPoint(double x, double y, Map* m):Object(x,y,m){
    //if(map->unmovableObjects[y][x+1] == roadr) way = roadr;
    //else if()
    type = 77;
}

void generationPoint::nextStep(double dt){    
    if(avaible){
        int x = int(this->x / CELL_SIZE);
        int y = int(this->y / CELL_SIZE);
        if(map->unmovableObjects[y][x+1] == roadr)
            if(map->movableObjects[y][x+1] == nullptr){
                map->movableObjects[y][x+1] = new Car((x + 1) * CELL_SIZE, y * CELL_SIZE, rand() % 10 + 1, 0.0, map);
                map->vobj.push_back(map->movableObjects[y ][x + 1]);
                avaible = false;
            }
            else;
        else if(map->unmovableObjects[y - 1][x] == roadu)
                if(map->movableObjects[y - 1][x] == nullptr){
                    map->movableObjects[y - 1][x] = new Car(x * CELL_SIZE, (y - 1) * CELL_SIZE, 0.0, -(rand() % 10 + 1), map);
                    map->vobj.push_back(map->movableObjects[y - 1][x]);
                    avaible = false;
                }
            else;
        else if(map->unmovableObjects[y + 1][x] == roadd)
                if(map->movableObjects[y + 1][x] == nullptr){
                    map->movableObjects[y + 1][x] = new Car(x * CELL_SIZE, (y + 1) * CELL_SIZE, 0.0, rand() % 10 + 1, map);
                    map->vobj.push_back(map->movableObjects[y + 1][x]);
                    avaible = false;
                }
            else;
        else if(map->unmovableObjects[y][x-1] == roadl)
                if(map->movableObjects[y][x-1] == nullptr){
                    map->movableObjects[y][x-1] = new Car((x - 1) * CELL_SIZE, y * CELL_SIZE, -(rand() % 10 + 1), 0.0, map);
                    map->vobj.push_back(map->movableObjects[y ][x - 1]);
                    avaible = false;
                }
                else;
        else;
        if(!avaible){
            pause = rand() % ((10 -(map->getStreamLevel())) * 100 + 1) + 1;
        }
    }
    else{
        pause--;
        if(pause == 0) avaible = true;
    }

}

void generationPoint::update(){
    pause = 0;
    avaible = true;
}
