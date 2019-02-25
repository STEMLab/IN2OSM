//
// Created by byeonggon on 2018-11-02.
//
#include "IndoorGML_Reader.h"
#include "OSM_Writer/OSM_Writer.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
namespace INDOOR{
    template <class T1>
    T1 matching_id(std::vector<T1> &a, std::string b) {
        T1 result;
        for(auto iter=a.begin();iter!=a.end();++iter){
            if((*iter)->gml_id==b){
                result=*iter;
            }
        }
        return result;
    }


    std::vector<CONVERTER::IC*> Read(std::string PATH){
        std::vector <CONVERTER::CellSpace*> CellSpace_vector;
        std::vector <CONVERTER::CellSpaceBoundary*>CellSpaceBoundary_vector;
        std::vector <CONVERTER::State*>State_vector;
        std::vector <CONVERTER::Transition*>Transition_vector;
        std::vector <CONVERTER::IC*>IC_vector;
        cout << "Indoorgml to ..."<<endl ;
        xml_document<> doc;//input
        xml_document<> doc1;//output
        xml_node<> * root_node;
        ifstream theFile (PATH);
        vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);
        root_node = doc.first_node("IndoorFeatures");

        xml_node<> * PrimalSpaceFeatures = root_node->first_node("primalSpaceFeatures")->first_node("PrimalSpaceFeatures");
        xml_node<> * SpaceLayer = root_node->first_node("multiLayeredGraph")->first_node("MultiLayeredGraph")->first_node("spaceLayers")->first_node("spaceLayerMember")->first_node("SpaceLayer");
        xml_node<> * nodes = SpaceLayer->first_node("nodes");
        xml_node<> * edges = SpaceLayer->first_node("edges");

        for (xml_node<> * cellSpaceMember = PrimalSpaceFeatures->first_node("cellSpaceMember"); cellSpaceMember; cellSpaceMember = cellSpaceMember->next_sibling("cellSpaceMember")) {
            CONVERTER::CellSpace *cellSpace_input=new CONVERTER::CellSpace();
            xml_node<> *CellSpace = cellSpaceMember->first_node("CellSpace");
            xml_node<> *Description = CellSpace->first_node("gml:description");
            xml_node<> *name = CellSpace->first_node("gml:name");
            cellSpace_input->gml_id=OSM::trim(CellSpace->first_attribute("gml:id")->value());
            cellSpace_input->name=OSM::trim(name->value());
            if(Description!=NULL)
                cellSpace_input->Description=OSM::trim(Description->value());
            cellSpace_input->osm_id=to_string(OSM_WAY_ID--);
            xml_node<> *LinearRing = CellSpace->first_node("cellSpaceGeometry")->first_node("Geometry2D")->first_node("gml:Polygon")->first_node("gml:exterior")->first_node("gml:LinearRing");
            for(xml_node<>*gml_pos=LinearRing->first_node("gml:pos"); gml_pos; gml_pos= gml_pos->next_sibling("gml:pos")){
                CONVERTER::Pos *pos_input=new CONVERTER::Pos();
                string erase_space = OSM::trim(gml_pos->value());
                std::vector<std::string> splittedStrings = OSM::split(erase_space, ' ');
                pos_input->longitude=splittedStrings[0];
                pos_input->latitude=splittedStrings[1];
                pos_input->height=splittedStrings[2];
                pos_input->osm_id=to_string(OSM_NODE_ID--);
                cellSpace_input->pos_vector.push_back(pos_input);
                IC_vector.push_back(pos_input);
            }
            CellSpace_vector.push_back(cellSpace_input);
            IC_vector.push_back(cellSpace_input);
        }//CellSpace

        for (xml_node<> * cellSpaceBoundaryMember = PrimalSpaceFeatures->first_node("cellSpaceBoundaryMember"); cellSpaceBoundaryMember; cellSpaceBoundaryMember = cellSpaceBoundaryMember->next_sibling("cellSpaceBoundaryMember")) {

            CONVERTER::CellSpaceBoundary *CellSpaceBoundary_input=new CONVERTER::CellSpaceBoundary();
            xml_node<> *CellSpaceBoundary = cellSpaceBoundaryMember->first_node("CellSpaceBoundary");
            xml_node<> *name = CellSpaceBoundary->first_node("gml:name");
            if(name!=NULL)
                CellSpaceBoundary_input->name=OSM::trim(name->value());
            xml_node<> *Description = CellSpaceBoundary->first_node("gml:description");
            if(Description!=NULL)
                CellSpaceBoundary_input->Description=OSM::trim(Description->value());
            CellSpaceBoundary_input->osm_id=to_string(OSM_WAY_ID--);
            CellSpaceBoundary_input->gml_id=CellSpaceBoundary->first_attribute("gml:id")->value();
            xml_node<> *LineString = CellSpaceBoundary->first_node("cellSpaceBoundaryGeometry")->first_node("geometry2D")->first_node("gml:LineString");
            for(xml_node<>*gml_pos=LineString->first_node("gml:pos"); gml_pos; gml_pos= gml_pos->next_sibling("gml:pos")){
                CONVERTER::Pos *pos_input=new CONVERTER::Pos();
                string erase_space = OSM::trim(gml_pos->value());
                std::vector<std::string> splittedStrings = OSM::split(erase_space, ' ');
                pos_input->longitude=splittedStrings[0];
                pos_input->latitude=splittedStrings[1];
                pos_input->height=splittedStrings[2];
                pos_input->osm_id=to_string(OSM_NODE_ID--);
                CellSpaceBoundary_input->pos_vector.push_back(pos_input);
                IC_vector.push_back(pos_input);
            }
            CellSpaceBoundary_vector.push_back(CellSpaceBoundary_input);
            IC_vector.push_back(CellSpaceBoundary_input);
        }//CellSpaceBoundary

        for (xml_node<> * stateMember = nodes->first_node("stateMember"); stateMember; stateMember = stateMember->next_sibling("stateMember")) {

            CONVERTER::State *State_input=new CONVERTER::State();

            xml_node<> *State = stateMember->first_node("State");
            xml_node<> *Description = State->first_node("gml:description");
            if(Description!=NULL)
                State_input->Description=OSM::trim(Description->value());
            State_input->gml_id=State->first_attribute("gml:id")->value();
            xml_node<> *Point = State->first_node("geometry")->first_node("gml:Point")->first_node("gml:pos");
            CONVERTER::Pos *pos_input=new CONVERTER::Pos();
            string erase_space = OSM::trim(Point->value());
            std::vector<std::string> splittedStrings = OSM::split(erase_space, ' ');
            pos_input->longitude=splittedStrings[0];
            pos_input->latitude=splittedStrings[1];
            pos_input->height=splittedStrings[2];
            State_input->pos=pos_input;
            pos_input->osm_id=to_string(OSM_NODE_ID--);
            State_input->osm_id=pos_input->osm_id;
            IC_vector.push_back(pos_input);
            State_vector.push_back(State_input);
            IC_vector.push_back(State_input);
        }//State


        for (xml_node<> * transitionMember = edges->first_node("transitionMember"); transitionMember; transitionMember = transitionMember->next_sibling("transitionMember")) {

            CONVERTER::Transition *Transition_input=new CONVERTER::Transition();
            xml_node<> *Transition = transitionMember->first_node("Transition");
            xml_node<> *Description = Transition->first_node("gml:description");
            if(Description!=NULL)
                Transition_input->Description=OSM::trim(Description->value());
            Transition_input->osm_id=to_string(OSM_WAY_ID--);
            Transition_input->gml_id=Transition->first_attribute("gml:id")->value();
            xml_node<> *LineString = Transition->first_node("geometry")->first_node("gml:LineString");

            for(xml_node<>*gml_pos=LineString->first_node("gml:pos"); gml_pos; gml_pos= gml_pos->next_sibling("gml:pos")){
                CONVERTER::Pos *pos_input=new CONVERTER::Pos();
                string erase_space = OSM::trim(gml_pos->value());
                std::vector<std::string> splittedStrings = OSM::split(erase_space, ' ');
                pos_input->longitude=splittedStrings[0];
                pos_input->latitude=splittedStrings[1];
                pos_input->height=splittedStrings[2];
                pos_input->osm_id=to_string(OSM_NODE_ID--);
                Transition_input->pos_vector.push_back(pos_input);
                IC_vector.push_back(pos_input);
            }
            Transition_vector.push_back(Transition_input);
            IC_vector.push_back(Transition_input);
        }//Transition

        for (xml_node<> * cellSpaceMember = PrimalSpaceFeatures->first_node("cellSpaceMember"); cellSpaceMember; cellSpaceMember = cellSpaceMember->next_sibling("cellSpaceMember")) {
            xml_node<> *CellSpace = cellSpaceMember->first_node("CellSpace");
            xml_node<> *partialboundedBy = CellSpace->first_node("partialboundedBy");
            if(partialboundedBy==NULL)
                continue;
            for(xml_node<> *partialboundedBy = CellSpace->first_node("partialboundedBy");partialboundedBy;partialboundedBy=partialboundedBy->next_sibling("partialboundedBy")) {
                string partialboundedBy_id;
                partialboundedBy_id = partialboundedBy->first_attribute("xlink:href")->value();
                partialboundedBy_id = partialboundedBy_id.substr(1, partialboundedBy_id.length());
                matching_id(IC_vector, CellSpace->first_attribute("gml:id")->value())->partialboundedBy.push_back(matching_id(IC_vector, partialboundedBy_id));
            }
        }//Partial_bounded_by
        for (xml_node<> * stateMember = nodes->first_node("stateMember"); stateMember; stateMember = stateMember->next_sibling("stateMember")) {
            xml_node<> *xml_State = stateMember->first_node("State");
            xml_node<> *xml_duality = xml_State->first_node("duality");
            xml_node<> *xml_connects = xml_State->first_node("connects");
            if(xml_duality!=NULL){
                string duality_id;
                duality_id=xml_duality->first_attribute("xlink:href")->value();
                duality_id=duality_id.substr(1,duality_id.length());
                matching_id(IC_vector,xml_State->first_attribute("gml:id")->value())->duality=matching_id(IC_vector,duality_id);
                matching_id(IC_vector,duality_id)->duality=matching_id(IC_vector,xml_State->first_attribute("gml:id")->value());
            }
            if(xml_connects!=NULL){
                for(xml_node<> *xml_connects = xml_State->first_node("connects");xml_connects;xml_connects=xml_connects->next_sibling("connects")) {
                    string connects_id;
                    connects_id = xml_connects->first_attribute("xlink:href")->value();
                    connects_id = connects_id.substr(1, connects_id.length());
                    matching_id(IC_vector, xml_State->first_attribute("gml:id")->value())->connects.push_back(matching_id(IC_vector, connects_id));
                    matching_id(IC_vector, connects_id)->connects.push_back(matching_id(IC_vector, xml_State->first_attribute("gml:id")->value()));
                }
            }
        }//State duality<->connects

        for (xml_node<> * transitionMember = edges->first_node("transitionMember"); transitionMember; transitionMember = transitionMember->next_sibling("transitionMember")) {
            xml_node<> *Transition = transitionMember->first_node("Transition");
            xml_node<> *xml_duality = Transition->first_node("duality");
            if(xml_duality!=NULL){
                string duality_id;
                duality_id=xml_duality->first_attribute("xlink:href")->value();
                duality_id=duality_id.substr(1,duality_id.length());
                matching_id(IC_vector,Transition->first_attribute("gml:id")->value())->duality=matching_id(IC_vector,duality_id);
                matching_id(IC_vector,duality_id)->duality=matching_id(IC_vector,Transition->first_attribute("gml:id")->value());
            }
        }//Transition duality
        doc.clear();
        return IC_vector;
    }
}
