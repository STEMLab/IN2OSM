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
//    namespace address {
//        class propertires {
//        public:
//            std::string address;
//            std::string unit;
//            std::string locality;
//            std::string province;
//            std::string country;
//            std::string postal_code;
//            std::string code_ext;
//            std::string postal_code_vanity;
//        };
//
//        class feature {
//        public:
//            std::string type;
//            std::string id;
//            std::string feature_type;
//            std::string geometry;
//
//            class propertires propertires;
//        };
//        class features {
//        public:
//            std::vector<feature*> features;
//        };
//        class address{
//        public:
//            std::string type;
//            std::string name;
//            features *features;
//        };
//    }
//
//    namespace amenity{
//        class properties{
//            std::string category;
//            std::string accesibility;
//            std::string name;
//            std::string alt_name;
//            std::string hours;
//            std::string phone;
//            std::string website;
//            std::vector<std::string>ids;
//            std::string address_id;
//            std::string correlation_id;
//        };
//        class point{
//        public:
//            double pointx;
//            double pointy;
//        };
//        class coordinates{
//        public:
//            std::vector<point*> point;
//        };
//        class geometry{
//        public:
//            std::string type;
//            coordinates * coordi;
//        };
//        class feature{
//            std::string type;
//            std::string id;
//            std::string feature_type;
//            geometry geometry;
//            properties *properties;
//        };
//        class amenity{
//        public:
//            std::string type;
//            std::string name;
//            std::vector <feature*>features;
//        };
//    }

}
#endif //IN2OSM_IMDF_FILE_H
