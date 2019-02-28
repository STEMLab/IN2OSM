//
// Created by byeonggon on 2019-02-20.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <io.h>
#include "IMDF_Reader.h"
#include "rapidjson/filereadstream.h"
#include "TRANSFORM/IMDF_FILE.h"

using namespace rapidjson;
using namespace std;

namespace IMDF {
    std::vector <CONVERTER::IC*> READ(std::string folder_path);
    std::vector<CONVERTER::IC*> Read_UNIT(std::string path);
    std::vector<CONVERTER::IC*> Read_OPENING(std::vector<CONVERTER::IC*>,std::string path);
    std::vector <CONVERTER::IC*> READ(std::string folder_path){
        cout<<"IMDF to ... ";
        vector <CONVERTER::IC*> IC_vector;
        struct _finddata_t fd;
        intptr_t handle;
        string FIND_PATH = folder_path+"\\*.geojson";
        if ((handle = _findfirst(FIND_PATH.c_str(), &fd)) == -1L)

            cout << "No IMDF unit.geojson in directory!" << endl;
        do{
            //cout << fd.name << endl;
            if(strcmp(fd.name,"unit.geojson")==0){
                FIND_PATH=folder_path+"\\"+"unit.geojson";
                IC_vector = Read_UNIT(FIND_PATH);
            }

        } while (_findnext(handle, &fd) == 0);
        _findclose(handle);
        //unit.geojson 입력받기
        //
        //
        FIND_PATH = folder_path+"\\*.geojson";
        if ((handle = _findfirst(FIND_PATH.c_str(), &fd)) == -1L)
            cout << "No IMDF opening.geojson in directory!" << endl;
        do{
            //cout << fd.name << endl;
            if(strcmp(fd.name,"opening.geojson")==0) {
                FIND_PATH=folder_path+"\\"+"opening.geojson";
                IC_vector = Read_OPENING(IC_vector,FIND_PATH);

            }
        } while (_findnext(handle, &fd) == 0);
        _findclose(handle);
        return IC_vector;
    }

    std::vector<CONVERTER::IC*> Read_UNIT(std::string path) {
        vector <CONVERTER::CellSpace*> CellSpace_vector;
        vector <CONVERTER::CellSpaceBoundary*>CellSpaceBoundary_vector;
        vector <CONVERTER::State*>State_vector;
        vector <CONVERTER::Transition*>Transition_vector;
        vector <CONVERTER::Pos*> node_vector;
        vector <CONVERTER::IC*> IC_vector;


        FILE* fp = fopen(path.c_str(), "rb"); // non-Windows use "r"
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);
//        cout<<d["features"][0]["id"].GetString();
        UNIT::unit *INPUT_UNIT=new UNIT::unit();
        INPUT_UNIT->type=d["type"].GetString();
        INPUT_UNIT->name=d["name"].GetString();

        for(auto &it : d["features"].GetArray()){
            UNIT::feature *FEATURE_INPUT=new UNIT::feature();
            FEATURE_INPUT->feature_geometry=new UNIT::geometry();
            FEATURE_INPUT->feature_properties=new UNIT::properties();
            FEATURE_INPUT->feature_properties->properties_display_point=new UNIT::display_point();
            //cout<<it["type"].GetString()<<endl;
            FEATURE_INPUT->type=it["type"].GetString();

            //cout<<it["id"].GetString()<<endl;
            FEATURE_INPUT->id=it["id"].GetString();
            FEATURE_INPUT->feature_type=it["feature_type"].GetString();

            FEATURE_INPUT->feature_geometry->type=it["geometry"]["type"].GetString();
            UNIT::point * STATE_INPUT=new UNIT::point();
            STATE_INPUT->pointx=it["properties"]["display_point"]["coordinates"][0].GetDouble();
            STATE_INPUT->pointy=it["properties"]["display_point"]["coordinates"][1].GetDouble();

            FEATURE_INPUT->feature_properties->properties_display_point->display_points.push_back(STATE_INPUT);

            cout.precision(11);
            for(auto &it1 :it["geometry"]["coordinates"][0].GetArray()) {
                UNIT::point * POINT_INPUT=new UNIT::point();
                POINT_INPUT->pointx=it1[0].GetDouble();
                POINT_INPUT->pointy=it1[1].GetDouble();
                FEATURE_INPUT->feature_geometry->coordinates_out.push_back(POINT_INPUT);
            }//outerring
            if(it["geometry"]["coordinates"].Capacity()==2){//inner ring 이 있을 경우
                for(auto &it1 :it["geometry"]["coordinates"][1].GetArray()) {
                    UNIT::point * POINT_INPUT=new UNIT::point();
                    POINT_INPUT->pointx=it1[0].GetDouble();
                    POINT_INPUT->pointy=it1[1].GetDouble();
                    FEATURE_INPUT->feature_geometry->coordinates_in.push_back(POINT_INPUT);
                }
            }//innerring
            FEATURE_INPUT->feature_properties->category=it["properties"]["category"].GetString();
            //FEATURE_INPUT->feature_properties->restriction=it["properties"]["restriction"].GetString();
            //FEATURE_INPUT->feature_properties->accessibility=it["properties"]["accessibility"].GetString();
            if(it["properties"]["name"].GetType()!=0)
                FEATURE_INPUT->feature_properties->name=it["properties"]["name"]["en"].GetString();

            //FEATURE_INPUT->feature_properties->alt_name=it["properties"]["alt_name"].GetString();
            FEATURE_INPUT->feature_properties->level_id=it["properties"]["level_id"].GetString();
            INPUT_UNIT->features.push_back(FEATURE_INPUT);
        }

        //////------------IMDF ---------------------->IC_Vector///
        for(auto it:INPUT_UNIT->features){
            CONVERTER::CellSpace *CELLSPACE_INPUT=new CONVERTER::CellSpace();
            CELLSPACE_INPUT->gml_id="C_"+it->id;
            CELLSPACE_INPUT->outer=1;
            for(auto it1 :it->feature_geometry->coordinates_out){
                CONVERTER::Pos * POS_INPUT= new CONVERTER::Pos();
                POS_INPUT->longitude=to_string(it1->pointx);
                POS_INPUT->latitude=to_string(it1->pointy);
                CELLSPACE_INPUT->pos_vector.push_back(POS_INPUT);
            }
            CONVERTER::CellSpace *CELLSPACE_INNER_INPUT=new CONVERTER::CellSpace();
            for(auto it1 :it->feature_geometry->coordinates_in){
                CELLSPACE_INNER_INPUT->outer=2;
                CONVERTER::Pos * POS_INNER_INPUT= new CONVERTER::Pos();
                POS_INNER_INPUT->longitude=to_string(it1->pointx);
                POS_INNER_INPUT->latitude=to_string(it1->pointy);
                CELLSPACE_INNER_INPUT->pos_vector.push_back(POS_INNER_INPUT);
            }
            if(!CELLSPACE_INNER_INPUT->pos_vector.empty())
                CELLSPACE_INPUT->inner.push_back(CELLSPACE_INNER_INPUT);

            if(!it->feature_properties->properties_display_point->display_points.empty()){
                CONVERTER::State *STATE_INPUT=new CONVERTER::State();
                CONVERTER::Pos * POS_INNER_INPUT= new CONVERTER::Pos();

                POS_INNER_INPUT->longitude=to_string(it->feature_properties->properties_display_point->display_points[0]->pointx);
                POS_INNER_INPUT->latitude=to_string(it->feature_properties->properties_display_point->display_points[0]->pointy);
                STATE_INPUT->pos=POS_INNER_INPUT;

                STATE_INPUT->gml_id="S_"+CELLSPACE_INPUT->gml_id;
                STATE_INPUT->duality=CELLSPACE_INPUT;
                CELLSPACE_INPUT->duality=STATE_INPUT;
                IC_vector.push_back(STATE_INPUT);
            }

           IC_vector.push_back(CELLSPACE_INPUT);
        }
        return IC_vector;
    }
    std::vector<CONVERTER::IC*> Read_OPENING(std::vector<CONVERTER::IC*>input,std::string path){
        FILE* fp = fopen(path.c_str(), "rb"); // non-Windows use "r"
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);

        OPENING::opening *INPUT_OPENING=new OPENING::opening();
        INPUT_OPENING->type=d["type"].GetString();
        INPUT_OPENING->name=d["name"].GetString();
        //cout<<INPUT_OPENING->type<<endl;

        for(auto &it : d["features"].GetArray()){
            OPENING::feature *FEATURE_INPUT=new OPENING::feature();
            FEATURE_INPUT->feature_geometry=new OPENING::geometry();
            FEATURE_INPUT->feature_properties=new OPENING::properties();
            FEATURE_INPUT->id=it["id"].GetString();
            for(auto &it1 :it["geometry"]["coordinates"].GetArray()) {
                OPENING::point * POINT_INPUT=new OPENING::point();
                POINT_INPUT->pointx=it1[0].GetDouble();
                POINT_INPUT->pointy=it1[1].GetDouble();
                FEATURE_INPUT->feature_geometry->coordinates.push_back(POINT_INPUT);
            }//outerring
            FEATURE_INPUT->feature_properties->level_id=it["properties"]["level_id"].GetString();
            INPUT_OPENING->features.push_back(FEATURE_INPUT);
        }
        //////------------IMDF ---------------------->IC_Vector///Cellspace_Boundary
        for(auto it:INPUT_OPENING->features){
            CONVERTER::CellSpaceBoundary *CELLSPACEBOUNDARY_INPUT=new CONVERTER::CellSpaceBoundary();
            CELLSPACEBOUNDARY_INPUT->gml_id="B_"+it->id;
            for(auto it1 :it->feature_geometry->coordinates){
                CONVERTER::Pos * POS_INPUT= new CONVERTER::Pos();
                POS_INPUT->longitude=to_string(it1->pointx);
                POS_INPUT->latitude=to_string(it1->pointy);
                CELLSPACEBOUNDARY_INPUT->pos_vector.push_back(POS_INPUT);
            }
            input.push_back(CELLSPACEBOUNDARY_INPUT);
        }

        return input;
    }

    std::vector<CONVERTER::IC*> Read_LEVEL(std::vector<CONVERTER::IC*>,std::string path){

    }
}