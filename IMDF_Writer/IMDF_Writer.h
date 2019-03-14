//
// Created by byeonggon on 2019-03-13.
//

#ifndef IN2OSM_IMDF_WRITER_H
#define IN2OSM_IMDF_WRITER_H
#include "TRANSFORM/Transform.h"
using namespace rapidxml;
namespace IMDF{
    void Write_manifest(std::vector<CONVERTER::IC*> IC_vector,std::string PATH);
    void Write_address(std::vector<CONVERTER::IC*> IC_vector,std::string PATH);
    void Write_venue(std::vector<CONVERTER::IC*> IC_vector,std::string PATH);
    void Write_unit(std::vector<CONVERTER::IC*> IC_vector,std::string PATH);
}
#endif //IN2OSM_IMDF_WRITER_H
