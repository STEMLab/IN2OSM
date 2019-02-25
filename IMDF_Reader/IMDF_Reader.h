//
// Created by byeonggon on 2019-02-20.
//

#ifndef IN2OSM_IMDF_READER_H
#define IN2OSM_IMDF_READER_H
#include "TRANSFORM/Transform.h"
using namespace rapidxml;
namespace IMDF{
    std::vector<CONVERTER::IC*> Read_UNIT(std::string path);
}
#endif //IN2OSM_IMDF_READER_H
