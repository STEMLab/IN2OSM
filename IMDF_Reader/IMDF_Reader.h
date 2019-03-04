//
// Created by byeonggon on 2019-02-20.
//

#ifndef IN2OSM_IMDF_READER_H
#define IN2OSM_IMDF_READER_H
#include "TRANSFORM/Transform.h"
using namespace rapidxml;
namespace IMDF{
    std::vector <CONVERTER::IC*> READ(std::string folder_path);
    void Read_UNIT(std::vector<CONVERTER::IC*>*input,std::string path);
    void Read_OPENING(std::vector<CONVERTER::IC*>*input,std::string path);
    void Read_LEVEL(std::vector<CONVERTER::IC*>,std::string path);

    void Read_JSON_FILE(std::vector<CONVERTER::IC*> *,std::string folder_path,std::string FILE_NAME);
}
#endif //IN2OSM_IMDF_READER_H
