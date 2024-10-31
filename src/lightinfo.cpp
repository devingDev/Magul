


#include "lightinfo.h"


LightInfo::LightInfo(Vector3 dir, Color col, LightType lType, double _tMax){
    this->direction = dir;
    this->incomingColor = col;
    this->lightType = lType;
    this->tMax = _tMax;
}
