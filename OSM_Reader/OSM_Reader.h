//
// Created by byeonggon on 2018-11-02.
//

#ifndef INDOORGML2OSM_OSM_READER_H
#define INDOORGML2OSM_OSM_READER_H
#include "TRANSFORM/Transform.h"
using namespace rapidxml;

namespace OSM{
    /**
     *
     * @tparam T1
     * @param a - vector<IC*> IC vector
     * @param b - OSM id(Node, Way, Relation)
     * @return - IC*
     */
    template<class T1>
    T1 matching_id(std::vector<T1> &a, int b);
    /**
     *
     * @param path - input OSM data
     * @return - IC *
     */
    std::vector<CONVERTER::IC*> Read(std::string path);
    bool Cellspace_check(std::vector<CONVERTER::IC*>input);
    char* Read_tag(char* input);
}
#endif //INDOORGML2OSM_OSM_READER_H
