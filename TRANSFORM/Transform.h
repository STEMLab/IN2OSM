//
// Created by byeonggon on 2018-11-02.
//

#ifndef INDOORGML2OSM_TRANSFORM_H
#define INDOORGML2OSM_TRANSFORM_H

#include <string>
#include <vector>
#include <ostream>
#include "Rapidxml/rapidxml_print.hpp"
#include "Rapidxml/rapidxml.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

extern int CellSpace_ID;
extern int CellSpaceBoundary_ID;
extern int State_id;
extern int Transition_id;
extern int OSM_NODE_ID;
extern int OSM_WAY_ID;
extern int OSM_RELATION_ID;
namespace CONVERTER {
    /**
     * @ingroup geo_features
     * @brief Parent class both Indoorgml and OSM
     * @details Parent class of Pos, CellSpace, CellSpaceBoundary , State , Transition
     * @param osm_id OSM ID
     * @param type Classification of Pos(0), CellSpace(1), CellSpaceBoundary(2) , State(3) , Transition(4)
     * @param gml_id IndoorGML gml ID
     * @param Description gml:description in IndoorGML
     * @param duality duality in IndoorGML
     * @param connects connects in IndoorGML
     *
     *
    */
    class IC {
    public:
        int type;
        int outer=0;//0 아무것도 아님 1 outer 2 inner
        int storey=99999;
        std::string gml_id;
        std::string osm_id;
        std::string Description;
        IC *duality = NULL;
        std::vector<IC *> partialboundedBy;
        std::vector<IC *> connects;
        std::vector<IC *> inner;

    };
    /**
     * @ingroup geo_features
     * @brief Pos class in IndoorGML, Node in OSM
     * @latitude latitude in OSM and IndoorGML
     * @longitude longitude in OSM and IndoorGML
     * @height height in InoodrGML
     */
    class Pos : public IC {
    public:
        std::string latitude;
        std::string longitude;
        std::string height;
        Pos(){
            latitude="0";
            longitude="0";
            type=0;
        }
    };
     /**
     * @ingroup geo_features
     * @brief CellSpace class in IndoorGML, CellSpace(way) in OSM
     * @name Cellspace Name
     * @pos_vector Member of pos in Cellspace
     */
    class CellSpace : public IC {
    public:
        std::string name;
        std::vector<Pos *> pos_vector;
        CellSpace(){
            type=1;
        }
    };
    /**
    * @ingroup geo_features
    * @brief CellSpaceBoundary class in IndoorGML, CellSpaceBoundary(way) in OSM
    * @pos_vector Member of pos in CellSpaceBoundary
    */
    class CellSpaceBoundary : public IC {
    public:
        std::string name;
        std::vector<Pos *> pos_vector;
        CellSpaceBoundary(){
            type=2;
        }
    };
    /**
    * @ingroup geo_features
    * @brief State class in IndoorGML, State(Node) in OSM
    * @pos State Pos
    */
    class State : public IC {
    public:
        Pos *pos;
        State(){
            type=3;
        }
    };
     /**
     * @ingroup geo_features
     * @brief Transition class in IndoorGML, Transition(way) in OSM
     * @weight weight in IndoorGML
     * @pos_vector Member of pos in Transition
     */
    class Transition : public IC {
    public:
        std::string name;
        std::string weight;
        std::vector<Pos *> pos_vector;
        Transition(){
            type=4;
        }
    };
    struct Point2D
    {
        double x;
        double y;
    };
}

#endif //INDOORGML2OSM_TRANSFORM_H
