//
// Created by byeonggon on 2018-11-02.
//
#include "OSM_Reader.h"
#include "IO/IO.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "string.h"

using namespace std;
namespace OSM{
    template <class T1>
    T1 matching_id(std::vector<T1> &a, string b) {
        T1 result=NULL;
        for(auto iter=a.begin();iter!=a.end();++iter){
            if(b.compare((*iter)->osm_id)==0){
                result=*iter;
            }
        }
        return result;
    }

    string Read_tag(string input){
        if(input =="level")
            return string("storey");
        else
            return input;
    }

    bool Cellspace_check(std::vector<CONVERTER::IC*>input){
        bool result=false;
        if(input.front()->osm_id==input.back()->osm_id){
            result=true;
        }
        return result;
    }
    std::vector<CONVERTER::IC*> Read(std::string PATH){
        vector <CONVERTER::CellSpace*> CellSpace_vector;
        vector <CONVERTER::CellSpaceBoundary*>CellSpaceBoundary_vector;
        vector <CONVERTER::State*>State_vector;
        vector <CONVERTER::Transition*>Transition_vector;
        vector <CONVERTER::Pos*> node_vector;
        vector <CONVERTER::IC*> IC_vector;
        cout << "OSM to IndoorGML..."<<endl ;
        xml_document<> doc;//input
        xml_node<> * root_node;
        ifstream theFile (PATH);
        vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);
        root_node = doc.first_node("osm");

        for (xml_node<> * xml_node = root_node->first_node("node"); xml_node; xml_node = xml_node->next_sibling("node")) {
            if(xml_node->first_attribute("action")!=NULL)
                if(strcmp(xml_node->first_attribute("action")->value(),"delete")==0)continue;
            CONVERTER::Pos *node_input = new CONVERTER::Pos();
            std::string osm_str(xml_node->first_attribute("id")->value());
            node_input->osm_id=osm_str;
            node_input->latitude=xml_node->first_attribute("lat")->value();
            node_input->longitude=xml_node->first_attribute("lon")->value();
            node_vector.push_back(node_input);
            IC_vector.push_back(node_input);
        }//node input


        for (xml_node<> * xml_relation = root_node->first_node("relation"); xml_relation; xml_relation = xml_relation->next_sibling("relation")) {
            if(xml_relation->first_attribute("action")!=NULL)
                 if(strcmp(xml_relation->first_attribute("action")->value(),"delete")==0)continue;
            xml_node<> * xml_tag = xml_relation->first_node("tag");
            if(xml_tag==NULL)continue;
            if (strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()),"cellspace") == 0){
                for(xml_node<> * xml_member = xml_relation->first_node("member"); xml_member; xml_member = xml_member->next_sibling("member")){
                    CONVERTER::CellSpace *cellspace_input = new CONVERTER::CellSpace();
                    std::string osm_str(xml_member->first_attribute("ref")->value());
                    cellspace_input->osm_id=osm_str;
                    cellspace_input->gml_id="C"+to_string(CellSpace_ID++);
                    cellspace_input->outer=1;
                    CellSpace_vector.push_back(cellspace_input);
                    IC_vector.push_back(cellspace_input);
                }
            }
            else if (strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()), "cellspaceboundary") == 0) {
                for(xml_node<> * xml_member = xml_relation->first_node("member"); xml_member; xml_member = xml_member->next_sibling("member")){
                    CONVERTER::CellSpaceBoundary *cellspaceboundary_input = new CONVERTER::CellSpaceBoundary();
                    std::string osm_str(xml_member->first_attribute("ref")->value());
                    cellspaceboundary_input->osm_id=osm_str;
                    cellspaceboundary_input->gml_id="B"+to_string(CellSpaceBoundary_ID++);
                    CellSpaceBoundary_vector.push_back(cellspaceboundary_input);
                    IC_vector.push_back(cellspaceboundary_input);
                }
            }
            else if (strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()), "state") == 0) {
                for(xml_node<> * xml_member = xml_relation->first_node("member"); xml_member; xml_member = xml_member->next_sibling("member")){
                    CONVERTER::State *state_input = new CONVERTER::State();
                    std::string osm_str(xml_member->first_attribute("ref")->value());
                    state_input->pos=matching_id(node_vector,osm_str);
                    state_input->osm_id=state_input->pos->osm_id;
                    state_input->gml_id="S"+to_string(State_id++);
                    State_vector.push_back(state_input);
                    IC_vector.push_back(state_input);
                }
            }
            else if (strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()), "transition") == 0) {
                for(xml_node<> * xml_member = xml_relation->first_node("member"); xml_member; xml_member = xml_member->next_sibling("member")){
                    CONVERTER::Transition *transition_input=new CONVERTER::Transition();
                    std::string osm_str(xml_member->first_attribute("ref")->value());
                    transition_input->osm_id=osm_str;
                    transition_input->gml_id="T"+to_string(Transition_id++);
                    Transition_vector.push_back(transition_input);
                    IC_vector.push_back(transition_input);
                }
            }
        }//cellspace, cellspaceboundary,state,transition push->Relation 이 들어왔다는 가정함.
        for (xml_node<> * xml_way = root_node->first_node("way"); xml_way; xml_way = xml_way->next_sibling("way")) {
            if(xml_way->first_attribute("action")!=NULL)
                if(strcmp(xml_way->first_attribute("action")->value(),"delete")==0)continue;
            std::vector<CONVERTER::IC*>close;
            for(xml_node<> *xml_nd=xml_way->first_node("nd");xml_nd;xml_nd=xml_nd->next_sibling("nd")){
                std::string osm_str(xml_nd->first_attribute("ref")->value());
                close.push_back(matching_id(IC_vector,osm_str));
            }
            if(Cellspace_check(close)==false)continue;
            std::string osm_str(xml_way->first_attribute("id")->value());
            if(matching_id(CellSpace_vector,osm_str)!=NULL)continue;
            CONVERTER::CellSpace *cellspace_input = new CONVERTER::CellSpace();
            cellspace_input->osm_id=osm_str;
            cellspace_input->gml_id="C"+to_string(CellSpace_ID++);
            for(xml_node<>*xml_tag=xml_way->first_node("tag");xml_tag;xml_tag=xml_tag->next_sibling("tag")){
                if(strcmp(xml_tag->first_attribute("k")->value(),"level")==0){
                    cellspace_input->outer=1;
                }
            }
            CellSpace_vector.push_back(cellspace_input);
            IC_vector.push_back(cellspace_input);
        }

        for (xml_node<> * xml_way = root_node->first_node("way"); xml_way; xml_way = xml_way->next_sibling("way")) {
            std::string osm_str(xml_way->first_attribute("id")->value());
            if(matching_id(CellSpace_vector,osm_str)!=NULL){
                CONVERTER::CellSpace * CellSpace_Pointer=matching_id(CellSpace_vector,osm_str);
                for(xml_node<>*xml_nd=xml_way->first_node("nd");xml_nd;xml_nd=xml_nd->next_sibling("nd")){
                    std::string nd_str(xml_nd->first_attribute("ref")->value());
                    CellSpace_Pointer->pos_vector.push_back(matching_id(node_vector,nd_str));
                }
                for(xml_node<>*xml_tag=xml_way->first_node("tag");xml_tag;xml_tag=xml_tag->next_sibling("tag")){
                    if(strcmp(xml_tag->first_attribute("k")->value(),"name")==0){
                        CellSpace_Pointer->name=xml_tag->first_attribute("v")->value();
                        continue;
                    }
                    string str = Read_tag(string(xml_tag->first_attribute("k")->value()));
                    CellSpace_Pointer->Description.append(str);
                    CellSpace_Pointer->Description.append("=");
                    if(strcmp(xml_tag->first_attribute("k")->value(),"level")==0){
                        CellSpace_Pointer->storey=atoi(xml_tag->first_attribute("v")->value());
                    }
                    CellSpace_Pointer->Description.append(xml_tag->first_attribute("v")->value());
                    CellSpace_Pointer->Description.append(";");
                }
            }//Cellspace_way
            if(matching_id(CellSpaceBoundary_vector,osm_str)!=NULL){
                CONVERTER::CellSpaceBoundary * CellSpaceBoundary_Pointer=matching_id(CellSpaceBoundary_vector,osm_str);
                for(xml_node<>*xml_nd=xml_way->first_node("nd");xml_nd;xml_nd=xml_nd->next_sibling("nd")){
                    std::string nd_str(xml_nd->first_attribute("ref")->value());
                    CellSpaceBoundary_Pointer->pos_vector.push_back(matching_id(node_vector,nd_str));
                }
                for(xml_node<>*xml_tag=xml_way->first_node("tag");xml_tag;xml_tag=xml_tag->next_sibling("tag")){
                    if(strcmp(xml_tag->first_attribute("k")->value(),"name")==0){
                        CellSpaceBoundary_Pointer->name=xml_tag->first_attribute("v")->value();
                        continue;
                    }
                }
            }//CellSpaceBoundary_way
            if(matching_id(Transition_vector,osm_str)!=NULL){
                CONVERTER::Transition * Transition_Pointer=matching_id(Transition_vector,osm_str);
                for(xml_node<>*xml_nd=xml_way->first_node("nd");xml_nd;xml_nd=xml_nd->next_sibling("nd")){
                    std::string nd_str(xml_nd->first_attribute("ref")->value());
                    Transition_Pointer->pos_vector.push_back(matching_id(node_vector,nd_str));
                }
                for(xml_node<>*xml_tag=xml_way->first_node("tag");xml_tag;xml_tag=xml_tag->next_sibling("tag")){
                    if(strcmp(xml_tag->first_attribute("k")->value(),"name")==0){
                        Transition_Pointer->name=xml_tag->first_attribute("v")->value();
                        continue;
                    }
                    string str = Read_tag(string(xml_tag->first_attribute("k")->value()));
                    Transition_Pointer->Description.append(str);
                    Transition_Pointer->Description.append("=");
                    if(strcmp(xml_tag->first_attribute("k")->value(),"level")==0){
                        Transition_Pointer->storey=atoi(xml_tag->first_attribute("v")->value());
                    }
                    Transition_Pointer->Description.append(xml_tag->first_attribute("v")->value());
                    Transition_Pointer->Description.append(";");
                }
                for(auto it:Transition_Pointer->pos_vector){
                    it->storey=Transition_Pointer->storey;
                }


            }//Transition_way
        }

        for (xml_node<> * xml_relation = root_node->first_node("relation"); xml_relation; xml_relation = xml_relation->next_sibling("relation")) {
            xml_node<> * xml_tag = xml_relation->first_node("tag");
            if(xml_tag==NULL)continue;
            if(strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()),"duality")==0){
                xml_node<> *xml_member=xml_relation->first_node("member");
                xml_node<> *xml_member_1=xml_member->next_sibling("member");
                std::string member(xml_member->first_attribute("ref")->value());
                std::string member_1(xml_member_1->first_attribute("ref")->value());
                if(matching_id(IC_vector,member)==NULL)continue;
                if(matching_id(IC_vector,member_1)==NULL)continue;
                matching_id(IC_vector,member)->duality=matching_id(IC_vector,member_1);
                matching_id(IC_vector,member_1)->duality=matching_id(IC_vector,member);
                if(matching_id(IC_vector,member)->storey!=99999)
                    matching_id(IC_vector,member_1)->storey=matching_id(IC_vector,member)->storey;
                if(matching_id(IC_vector,member_1)->storey!=99999)
                    matching_id(IC_vector,member)->storey=matching_id(IC_vector,member_1)->storey;
            }
            if(strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()),"connects")==0){
                xml_node<> *xml_member=xml_relation->first_node("member");
                xml_node<> *xml_member_1=xml_member->next_sibling("member");
                std::string member(xml_member->first_attribute("ref")->value());
                std::string member_1(xml_member_1->first_attribute("ref")->value());
                if(matching_id(IC_vector,member)==NULL)continue;
                if(matching_id(IC_vector,member_1)==NULL)continue;
                matching_id(IC_vector,member)->connects.push_back(matching_id(IC_vector,member_1));
                matching_id(IC_vector,member_1)->connects.push_back(matching_id(IC_vector,member));
            }
            if(strcmp(IO::lowercase(xml_tag->first_attribute("v")->value()),"partialboundedby")==0){
                xml_node<> *xml_member=xml_relation->first_node("member");
                xml_node<> *xml_member_1=xml_member->next_sibling("member");
                std::string member(xml_member->first_attribute("ref")->value());
                std::string member_1(xml_member_1->first_attribute("ref")->value());
                if(matching_id(IC_vector,member)==NULL)continue;
                if(matching_id(IC_vector,member_1)==NULL)continue;
                matching_id(IC_vector,member)->partialboundedBy.push_back(matching_id(IC_vector,member_1));
                matching_id(IC_vector,member_1)->partialboundedBy.push_back(matching_id(IC_vector,member));
            }
        }

        for (xml_node<> * xml_relation = root_node->first_node("relation"); xml_relation; xml_relation = xml_relation->next_sibling("relation")) {
            CONVERTER::IC * IC_POINTER;
            int level=99999;
            for(xml_node<>*xml_tag=xml_relation->first_node("tag");xml_tag;xml_tag=xml_tag->next_sibling("tag")){
                if(strcmp(xml_tag->first_attribute("k")->value(),"level")==0){
                    level=atoi(xml_tag->first_attribute("v")->value());
                }
            }
            if(level==99999)continue;
            for(xml_node<> *xml_member=xml_relation->first_node("member");xml_member;xml_member=xml_member->next_sibling("member")){
                if(strcmp(xml_member->first_attribute("role")->value(),"outer")==0){
                    IC_POINTER = matching_id(IC_vector,xml_member->first_attribute("ref")->value());
                    matching_id(IC_vector,xml_member->first_attribute("ref")->value())->outer= 1;
                    matching_id(IC_vector,xml_member->first_attribute("ref")->value())->Description.append("storey=");
                    ((CONVERTER::CellSpace*)matching_id(IC_vector,xml_member->first_attribute("ref")->value()))->storey=level;
                    matching_id(IC_vector,xml_member->first_attribute("ref")->value())->Description.append(to_string(level)+";");
                }
            }
            if(IC_POINTER==NULL)continue;
            for(xml_node<> *xml_member=xml_relation->first_node("member");xml_member;xml_member=xml_member->next_sibling("member")){
                if(strcmp(xml_member->first_attribute("role")->value(),"inner")==0){
                    IC_POINTER->inner.push_back(matching_id(IC_vector,xml_member->first_attribute("ref")->value()));
                    matching_id(IC_vector,xml_member->first_attribute("ref")->value())->outer= 2;
                }
            }
        }
        doc.clear();
        return IC_vector;
    }
}
