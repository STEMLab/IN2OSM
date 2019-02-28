//
// Created by byeonggon on 2019-02-21.
//

#ifndef IN2OSM_IMDF_FILE_H
#define IN2OSM_IMDF_FILE_H
#include <string>
#include <vector>
enum IMDF_INPUT {manifest,address,venue,amenity,anchor,building,detail,fixture,footprint,kiosk,level,occupant,opening,relationship,section,unit};
namespace IMDF{
    namespace UNIT{
        class point{
        public:
            double pointx;
            double pointy;
        };
        class display_point{
        public:
            std::string type;
            std::vector<point*> display_points;
        };
        class properties{
        public:
            std::string category;
            std::string restriction;
            std::string accessibility;
            std::string name;
            std::string alt_name;
            std::string level_id;
            display_point *properties_display_point;
        };
        class geometry{
        public:
            std::string type;
            std::vector<point*> coordinates_out;
            std::vector<point*> coordinates_in;
        };
        class feature{
        public:
            std::string type;
            std::string id;
            std::string feature_type;
            geometry *feature_geometry;
            properties *feature_properties;
        };
        class unit{
        public:
            std::string type;
            std::string name;
            std::vector<feature*>features;
        };
    }
    namespace OPENING{
        class point{
        public:
            double pointx;
            double pointy;
        };
        class display_point{
        public:
            std::string type;
            std::vector<point*> display_points;
        };
        class geometry{
        public:
            std::string type;
            std::vector<point*> coordinates;
        };
        class properties{
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
        class feature{
        public:
            std::string type;
            std::string id;
            std::string feature_type;
            geometry *feature_geometry;
            properties *feature_properties;
        };
        class opening{
        public:
            std::string type;
            std::string name;
            std::vector<feature*>features;
        };
    }
    namespace level{
        int ordinal;
        std::string id;
    }
}
#endif //IN2OSM_IMDF_FILE_H
