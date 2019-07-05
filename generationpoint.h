#ifndef GENERATIONPOINT_H
#define GENERATIONPOINT_H

#include "object.h"
#include "map.h"

class generationPoint : public Object
{
private:
    bool avaible = true;
    int pause = 0;
    int way;
public:
    generationPoint();
    generationPoint(double x, double y, Map* m);
    void nextStep(double dt) override;
    void update();
};

#endif // GENERATIONPOINT_H
