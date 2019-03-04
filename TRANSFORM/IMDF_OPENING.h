//
// Created by byeonggon on 2019-03-04.
//
#include <iostream>
#include <vector>
#ifndef IN2OSM_IMDF_OPENING_H
#define IN2OSM_IMDF_OPENING_H
namespace IMDF {
    namespace OPENING {
        class point {
        public:
            double pointx;
            double pointy;
        };

        class display_point {
        public:
            std::string type;
            std::vector<point *> display_points;
        };

        class geometry {
        public:
            std::string type;
            std::vector<point *> coordinates;
        };

        class properties {
        public:
            std::string category;
            std::string accessibility;
            std::string access_control;
            std::string door;
            std::string name;
            std::string alt_name;
            display_point *properties_display_point;
            std::string level_id;
        };

        class feature {
        public:
            std::string type;
            std::string id;
            std::string feature_type;
            geometry *feature_geometry;
            properties *feature_properties;
        };

        class opening {
        public:
            std::string type;
            std::string name;
            std::vector<feature *> features;
        };
    }
}
#endif //IN2OSM_IMDF_OPENING_H
