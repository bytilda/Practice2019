#include "object.h"

Object::Object()
{

}

Object::~Object(){

}

Object::Object(double x, double y, Map *m){
    this->map = m;
    this->x = x;
    this->y = y;
}

int Object::getType(){
    return type;
}
