//
// Created by byeonggon on 2019-03-04.
//
#include "IMDF_UNIT.h"
#ifndef IN2OSM_IMDF_LEVEL_H
#define IN2OSM_IMDF_LEVEL_H
namespace IMDF{
    namespace LEVEL{
        class point{
        public:
            double pointx;
            double pointy;
        };
        class geometry{
        public:
            std::string type;
            std::vector<point*> coordinates;
        };
        class properties{
        public:
            std::string category;
            std::string restriction;
            std::string outdoor;
            int ordinal;
        };
        class feature{
        public:
            std::string type;
            std::string id;
            std::string feature_type;
            geometry *feature_geometry;
            properties *feature_properties;
        };
        class level{
        public:
            std::string type;
            std::string name;
            std::vector<feature*>faetures;
        };
    }
}
#endif //IN2OSM_IMDF_LEVEL_H
