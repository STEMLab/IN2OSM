//
// Created by byeonggon on 2018-11-02.
//

#ifndef INDOORGML2OSM_OSM_WRITER_H
#define INDOORGML2OSM_OSM_WRITER_H
#include "TRANSFORM/Transform.h"


namespace OSM{
    /**
     *
     * @param IC_vector - memory IC vector
     * @param PATH - Output OSM data Path
     */
    void Write(std::vector<CONVERTER::IC*> IC_vector,std::string PATH);
    /**
     *
     * @param str sting
     * @brief using because of IndoorGML Description
     * @return string
     */
    std::string trim(const std::string& str);
    /**
     *
     * @brief
     */
    std::vector<std::string> split(std::string& strToSplit, char delimeter);
    std::string Write_tag(std::string &input);
}

#endif //INDOORGML2OSM_OSM_WRITER_H
