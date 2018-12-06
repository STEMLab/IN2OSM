//
// Created by byeonggon on 2018-11-02.
//
#ifndef INDOORGML2OSM_INDOORGML_READER_H
#define INDOORGML2OSM_INDOORGML_READER_H
#include "TRANSFORM/Transform.h"
using namespace rapidxml;

namespace INDOOR{
    /**
     *
     * @tparam T1
     * @param a - IC* vector
     * @param b - indoorgml ID
     * @brief return IC* using indoorgml ID
     * @return - IC *
     */
    template<class T1>
    T1 matching_id(std::vector<T1> &a, std::string b);
    /**
     *
     * @param path input IndoorGML data
     * @return vector<IC *> - memory Integration data
     */
    std::vector<CONVERTER::IC*> Read(std::string path);
}
#endif //INDOORGML2OSM_INDOORGML_READER_H
