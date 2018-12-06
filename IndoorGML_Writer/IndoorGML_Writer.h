//
// Created by byeonggon on 2018-11-02.
//

#ifndef INDOORGML2OSM_INDOORGML_WRITER_H
#define INDOORGML2OSM_INDOORGML_WRITER_H
#include "TRANSFORM/Transform.h"
namespace INDOOR{
    /**
     *
     * @param IC_vector Memory's IC vector
     * @param PATH - Path of Output IndoorGML data
     */
    void Write(std::vector<CONVERTER::IC*> IC_vector,std::string PATH);
    /**
     *
     * @brief trim string control IndoorGML Description
     */
    std::string trim(const std::string& str);
    /**
     *
     * @brief split string control IndoorGML Description
     */
    std::vector<std::string> split(std::string& strToSplit, char delimeter);
    void Min_storey(std::vector<CONVERTER::IC*>);
}

#endif //INDOORGML2OSM_INDOORGML_WRITER_H
