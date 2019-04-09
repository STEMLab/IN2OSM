//
// Created by byeonggon on 2018-11-02.
//


#include "IndoorGML_Writer.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "string.h"
namespace INDOOR{
    const std::string height="0.0";
    const std::string boundedby_value="true";
    const std::string srsDimension="3";
    const std::string weight="0.0";
    int min_storey=99999;
    void Min_storey(std::vector<CONVERTER::IC*> input){
        for(auto it:input) {
            if(it->type!=1)continue;
            min_storey = std::min(((CONVERTER::CellSpace*)it)->storey, min_storey);
        }
    }
    std::vector<std::string> split(std::string& strToSplit, char delimeter) {
        std::stringstream ss(strToSplit);
        std::string item;
        std::vector<std::string> splittedStrings;
        while (std::getline(ss, item, delimeter)) {
            if(item.length()==0)continue;
            if(item.at(item.length()-1)=='\n')
                item=item.substr(0,item.length()-1);
            splittedStrings.push_back(item);
        }
        return splittedStrings;
    }

    std::string trim(const std::string& str) {
        std::string result;
        std::string whitespaces=" \t\r\n";
        size_t begin = str.find_first_not_of(whitespaces);
        size_t end = str.find_last_not_of(whitespaces);
        if (begin != std::string::npos && end != std::string::npos)
            result = str.substr(begin, end - begin + 1);
        return result;
    }
    void Write(std::vector<CONVERTER::IC*> IC_vector,std::string PATH){
        std::cout<<"Indoorgml"<<std::endl;
        rapidxml::xml_document<> doc1;
        rapidxml::xml_node<>* root = doc1.allocate_node(rapidxml::node_element, "core:IndoorFeatures");
        root->append_attribute(doc1.allocate_attribute("xmlns:gml", "http://www.opengis.net/gml/3.2"));
        root->append_attribute(doc1.allocate_attribute("xmlns:xlink", "http://www.w3.org/1999/xlink"));
        root->append_attribute(doc1.allocate_attribute("xmlns:core", "http://www.opengis.net/indoorgml/1.0/core"));
        root->append_attribute(doc1.allocate_attribute("xmlns:navi", "http://www.opengis.net/indoorgml/1.0/navigation"));
        root->append_attribute(doc1.allocate_attribute("xmlns:storeyext", "http://indoorgml.net/extensions/storeyext"));
        root->append_attribute(doc1.allocate_attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance"));
        root->append_attribute(doc1.allocate_attribute("gml:id", "h9cc9b77-ae31-6074-2fe7-0c91a90f08f9"));
        root->append_attribute(doc1.allocate_attribute("xsi:schemaLocation", "http://www.opengis.net/indoorgml/1.0/core http://schemas.opengis.net/indoorgml/1.0/indoorgmlcore.xsd http://www.opengis.net/indoorgml/1.0/navigation http://schemas.opengis.net/indoorgml/1.0/indoorgmlnavi.xsd http://indoorgml.net/extensions/storeyext http://www.indoorgml.net/extensions/indoorgmlstoreyextension.xsd"));
        rapidxml::xml_node<>* xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
        xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
        root->append_node(xml_bound);
        rapidxml::xml_node<>* xml_primalSpaceFeatures = doc1.allocate_node(rapidxml::node_element, "core:primalSpaceFeatures");
        rapidxml::xml_node<>* xml_PrimalSpaceFeatures = doc1.allocate_node(rapidxml::node_element, "core:PrimalSpaceFeatures");
        xml_PrimalSpaceFeatures->append_attribute(doc1.allocate_attribute("gml:id", "PrimalSpaceFeuatres"));

        xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
        xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
        rapidxml::xml_node<>* xml_multiLayeredGraph=doc1.allocate_node(rapidxml::node_element, "core:multiLayeredGraph");
        rapidxml::xml_node<>* xml_MultiLayeredGraph=doc1.allocate_node(rapidxml::node_element, "core:MultiLayeredGraph");
        xml_MultiLayeredGraph->append_node(xml_bound);
        xml_MultiLayeredGraph->append_attribute(doc1.allocate_attribute("gml:id", "MultiLayeredGraph"));
        rapidxml::xml_node<>* xml_spaceLayers=doc1.allocate_node(rapidxml::node_element, "core:spaceLayers");
        xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
        xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
        xml_spaceLayers->append_node(xml_bound);
        xml_spaceLayers->append_attribute(doc1.allocate_attribute("gml:id", "spaceLayers"));
        rapidxml::xml_node<>* xml_spaceLayerMember=doc1.allocate_node(rapidxml::node_element, "core:spaceLayerMember");
        rapidxml::xml_node<>* xml_SpaceLayer=doc1.allocate_node(rapidxml::node_element, "core:SpaceLayer");
        xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
        xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
        xml_SpaceLayer->append_node(xml_bound);
        xml_SpaceLayer->append_attribute(doc1.allocate_attribute("gml:id", "SpaceLayer"));
        xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
        xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
        xml_PrimalSpaceFeatures->append_node(xml_bound);

        rapidxml::xml_node<>* xml_nodes=doc1.allocate_node(rapidxml::node_element, "core:nodes");
        xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
        xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
        xml_nodes->append_node(xml_bound);
        xml_nodes->append_attribute(doc1.allocate_attribute("gml:id", "nodes"));
        rapidxml::xml_node<>* xml_edges=doc1.allocate_node(rapidxml::node_element, "core:edges");
        xml_edges->append_attribute(doc1.allocate_attribute("gml:id", "edges"));
        xml_MultiLayeredGraph->append_node(xml_spaceLayers);
        xml_spaceLayers->append_node(xml_spaceLayerMember);
        xml_spaceLayerMember->append_node(xml_SpaceLayer);
        xml_SpaceLayer->append_node(xml_nodes);
        xml_SpaceLayer->append_node(xml_edges);
        Min_storey(IC_vector);
        for(auto it : IC_vector) {//cellspace
            if(it->type!=1)continue;
            if(it->outer!=1)continue;
            rapidxml::xml_node<>* xml_cellSpaceMember = doc1.allocate_node(rapidxml::node_element, "core:cellSpaceMember");
//            rapidxml::xml_node<>* xml_CellSpace = doc1.allocate_node(rapidxml::node_element, "storeyext:CellSpaceStorey");
            rapidxml::xml_node<>* xml_CellSpace = doc1.allocate_node(rapidxml::node_element, "core:CellSpace");
            xml_CellSpace->append_attribute(doc1.allocate_attribute("gml:id",doc1.allocate_string(it->gml_id.c_str())));
            rapidxml::xml_node<>* xml_description= doc1.allocate_node(rapidxml::node_element, "gml:description");

            rapidxml::xml_node<>* xml_name= doc1.allocate_node(rapidxml::node_element, "gml:name");

            rapidxml::xml_node<>* xml_Cellspace_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
            xml_Cellspace_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
            rapidxml::xml_node<>* xml_cellSpaceGeometry = doc1.allocate_node(rapidxml::node_element, "core:cellSpaceGeometry");
            rapidxml::xml_node<>* xml_Geometry2D = doc1.allocate_node(rapidxml::node_element, "core:Geometry2D");
            rapidxml::xml_node<>* xml_Polygon = doc1.allocate_node(rapidxml::node_element, "gml:Polygon");
            xml_Polygon->append_attribute(doc1.allocate_attribute("gml:id", doc1.allocate_string(("CG-"+it->gml_id).c_str())));
            rapidxml:: xml_node<>* xml_exterior = doc1.allocate_node(rapidxml::node_element, "gml:exterior");
            rapidxml::xml_node<>* xml_LinearRing = doc1.allocate_node(rapidxml::node_element, "gml:LinearRing");
            rapidxml::xml_node<>* xml_duality = doc1.allocate_node(rapidxml::node_element, "core:duality");
            if(it->duality!=NULL&&strcmp(it->duality->gml_id.c_str(),"")!=0)
                xml_duality->append_attribute(doc1.allocate_attribute("xlink:href",doc1.allocate_string(("#"+it->duality->gml_id).c_str())));
            xml_description->value(doc1.allocate_string(trim(it->Description).c_str()));
            xml_name->value(doc1.allocate_string((((CONVERTER::CellSpace*)it)->name).c_str()));
            double EACH_HEIGHT=0.0;
            EACH_HEIGHT=EACH_HEIGHT+0.0003*(((CONVERTER::CellSpace*)it)->storey-min_storey);
            for(auto it1 : ((CONVERTER::CellSpace*)it)->pos_vector){
                rapidxml::xml_node<>* xml_pos = doc1.allocate_node(rapidxml::node_element, "gml:pos");
                xml_pos->append_attribute(doc1.allocate_attribute("srsDimension",srsDimension.c_str()));
                xml_pos->value(doc1.allocate_string((it1->longitude+" "+it1->latitude+" "+std::to_string(EACH_HEIGHT)).c_str()));
                xml_LinearRing->append_node(xml_pos);
            }
            rapidxml::xml_node<>* xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");

            rapidxml::xml_node<>* xml_storey = doc1.allocate_node(rapidxml::node_element, "storeyext:storey");
            if(((((CONVERTER::CellSpace*)it)->storey))!=99999){
                xml_description->value(doc1.allocate_string(("storey="+std::to_string((((CONVERTER::CellSpace*)it)->storey))).c_str()));
            }
//                xml_storey->value(doc1.allocate_string(std::to_string((((CONVERTER::CellSpace*)it)->storey)).c_str()));
            xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));

            xml_CellSpace->append_node(xml_description);
            xml_CellSpace->append_node(xml_name);
            xml_CellSpace->append_node(xml_bound);


            xml_exterior->append_node(xml_LinearRing);
            xml_Polygon->append_node(xml_exterior);
            for(auto it1:it->inner){
                rapidxml:: xml_node<>* xml_interior = doc1.allocate_node(rapidxml::node_element, "gml:interior");
                rapidxml::xml_node<>* xml_LinearRing = doc1.allocate_node(rapidxml::node_element, "gml:LinearRing");
                for(auto it2: ((CONVERTER::CellSpace*)it1)->pos_vector){
                    rapidxml::xml_node<>* xml_pos = doc1.allocate_node(rapidxml::node_element, "gml:pos");
                    xml_pos->append_attribute(doc1.allocate_attribute("srsDimension",srsDimension.c_str()));
                    xml_pos->value(doc1.allocate_string((it2->longitude+" "+it2->latitude+" "+std::to_string(EACH_HEIGHT)).c_str()));
                    xml_LinearRing->append_node(xml_pos);
                }
                xml_interior->append_node(xml_LinearRing);
                xml_Polygon->append_node(xml_interior);
            }
            xml_Geometry2D->append_node(xml_Polygon);
            xml_cellSpaceGeometry->append_node(xml_Geometry2D);
            xml_CellSpace->append_node(xml_cellSpaceGeometry);
            xml_CellSpace->append_node(xml_duality);
            //xml_CellSpace->append_node(xml_storey);
            for(auto it1:it->partialboundedBy){
                rapidxml::xml_node<>* xml_partialboundedBy= doc1.allocate_node(rapidxml::node_element, "partialboundedBy");
                xml_partialboundedBy->append_attribute(doc1.allocate_attribute("xlink:href",doc1.allocate_string(("#"+it1->gml_id).c_str())));
                xml_CellSpace->append_node(xml_partialboundedBy);
            }
            xml_cellSpaceMember->append_node(xml_CellSpace);
            xml_PrimalSpaceFeatures->append_node(xml_cellSpaceMember);
        }
        for(auto it : IC_vector){//CellspaceBoundary
            if(it->type!=2)continue;
            rapidxml::xml_node<>* xml_cellSpaceBoundaryMember = doc1.allocate_node(rapidxml::node_element, "core:cellSpaceBoundaryMember");
            rapidxml::xml_node<>* xml_CellSpaceBoundary = doc1.allocate_node(rapidxml::node_element, "core:CellSpaceBoundary");
            rapidxml::xml_node<>* xml_CellSpaceBoundary_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
            xml_CellSpaceBoundary_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
            rapidxml::xml_node<>* xml_duality = doc1.allocate_node(rapidxml::node_element, "core:duality");
            rapidxml::xml_node<>* xml_name= doc1.allocate_node(rapidxml::node_element, "gml:name");
            xml_name->value(doc1.allocate_string((((CONVERTER::CellSpaceBoundary*)it)->name).c_str()));
            if(it->duality!=NULL)
                xml_duality->append_attribute(doc1.allocate_attribute("xlink:href",doc1.allocate_string(("#"+it->duality->gml_id).c_str())));
            rapidxml::xml_node<>* xml_cellSpaceBoundaryGeometry = doc1.allocate_node(rapidxml::node_element, "core:cellSpaceBoundaryGeometry");
            rapidxml::xml_node<>* xml_Geometry2D = doc1.allocate_node(rapidxml::node_element, "core:geometry2D");
            rapidxml::xml_node<>* xml_LineString = doc1.allocate_node(rapidxml::node_element, "gml:LineString");
            xml_LineString->append_attribute(doc1.allocate_attribute("gml:id",doc1.allocate_string(("CBG-"+it->gml_id).c_str())));
            for(auto it1 : ((CONVERTER::CellSpaceBoundary*)it)->pos_vector){
                rapidxml::xml_node<>* xml_pos = doc1.allocate_node(rapidxml::node_element, "gml:pos");
                xml_pos->append_attribute(doc1.allocate_attribute("srsDimension",srsDimension.c_str()));
                xml_pos->value(doc1.allocate_string((it1->longitude+" "+it1->latitude+" "+height).c_str()));
                xml_LineString->append_node(xml_pos);
            }
            xml_CellSpaceBoundary->append_attribute(doc1.allocate_attribute("gml:id",it->gml_id.c_str()));
            rapidxml::xml_node<>* xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
            xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
            if(((CONVERTER::CellSpaceBoundary*)it)->name!="")
                xml_CellSpaceBoundary->append_node(xml_name);
            xml_CellSpaceBoundary->append_node(xml_bound);
            xml_Geometry2D->append_node(xml_LineString);
            xml_cellSpaceBoundaryGeometry->append_node(xml_Geometry2D);
            if(it->duality!=NULL)
                xml_CellSpaceBoundary->append_node(xml_duality);
            xml_CellSpaceBoundary->append_node(xml_cellSpaceBoundaryGeometry);
            xml_cellSpaceBoundaryMember->append_node(xml_CellSpaceBoundary);

            xml_PrimalSpaceFeatures->append_node(xml_cellSpaceBoundaryMember);
        }//cellspaceboundary

        for(auto it : IC_vector){
            if(it->type!=3)continue;
            rapidxml::xml_node<>* xml_stateMember=doc1.allocate_node(rapidxml::node_element, "core:stateMember");
            rapidxml::xml_node<>* xml_State=doc1.allocate_node(rapidxml::node_element, "core:State");
            xml_State->append_attribute(doc1.allocate_attribute("gml:id",doc1.allocate_string(it->gml_id.c_str())));
            rapidxml::xml_node<>* xml_State_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
            rapidxml::xml_node<>* xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
            xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
            xml_State->append_node(xml_bound);
            if(it->duality!=NULL) {
                rapidxml::xml_node < > *xml_duality = doc1.allocate_node(rapidxml::node_element, "core:duality");
                xml_duality->append_attribute(doc1.allocate_attribute("xlink:href", doc1.allocate_string(("#" + it->duality->gml_id).c_str())));
                xml_State->append_node(xml_duality);
            }
            for(auto it1 : it->connects){
                rapidxml::xml_node < > *xml_connects = doc1.allocate_node(rapidxml::node_element, "core:connects");
                xml_connects->append_attribute(doc1.allocate_attribute("xlink:href", doc1.allocate_string(("#" + it1->gml_id).c_str())));
                xml_State->append_node(xml_connects);
            }
            rapidxml::xml_node<>* xml_geometry = doc1.allocate_node(rapidxml::node_element, "core:geometry");
            rapidxml::xml_node<>* xml_gml_Point = doc1.allocate_node(rapidxml::node_element, "gml:Point");
            xml_gml_Point->append_attribute(doc1.allocate_attribute("gml:id", doc1.allocate_string(("SG-"+ it->gml_id).c_str())));
            rapidxml::xml_node<>* xml_pos = doc1.allocate_node(rapidxml::node_element, "gml:pos");
            xml_pos->append_attribute(doc1.allocate_attribute("srsDimension",srsDimension.c_str()));
            double EACH_HEIGHT=0.0;
            EACH_HEIGHT=EACH_HEIGHT+0.0003*(((CONVERTER::State*)it)->storey-min_storey);
            xml_pos->value(doc1.allocate_string((((CONVERTER::State*)it)->pos->longitude+" "+((CONVERTER::State*)it)->pos->latitude+" "+std::to_string(EACH_HEIGHT)).c_str()));
            xml_gml_Point->append_node(xml_pos);
            xml_geometry->append_node(xml_gml_Point);
            xml_State->append_node(xml_geometry);
            xml_stateMember->append_node(xml_State);
            xml_nodes->append_node(xml_stateMember);
        }//State
        for(auto it : IC_vector){//Transition
            if(it->type!=4)continue;
            rapidxml::xml_node<>* xml_transitionMember=doc1.allocate_node(rapidxml::node_element, "transitionMember");
            rapidxml::xml_node<>* xml_Transition=doc1.allocate_node(rapidxml::node_element, "Transition");
            xml_Transition->append_attribute(doc1.allocate_attribute("gml:id",doc1.allocate_string(it->gml_id.c_str())));
            rapidxml::xml_node<>* xml_bound = doc1.allocate_node(rapidxml::node_element, "gml:boundedBy");
            xml_bound->append_attribute(doc1.allocate_attribute("xsi:nil", boundedby_value.c_str()));
            xml_Transition->append_node(xml_bound);
            rapidxml::xml_node<>* xml_weight = doc1.allocate_node(rapidxml::node_element, "weight");
            xml_weight->value(doc1.allocate_string(weight.c_str()));
            xml_Transition->append_node(xml_weight);
            rapidxml::xml_node<>* xml_geometry = doc1.allocate_node(rapidxml::node_element, "geometry");
            rapidxml::xml_node<>* xml_LineString = doc1.allocate_node(rapidxml::node_element, "gml:LineString");
            rapidxml::xml_node<>* xml_description= doc1.allocate_node(rapidxml::node_element, "gml:description");
            xml_description->value(doc1.allocate_string(trim(it->Description).c_str()));
            xml_LineString->append_attribute(doc1.allocate_attribute("gml:id", doc1.allocate_string(("TG-" + it->gml_id).c_str())));
            rapidxml::xml_node<>* xml_gml_pos = doc1.allocate_node(rapidxml::node_element, "gml:pos");

            for(auto it1 : it->connects){
                rapidxml::xml_node < > *xml_connects = doc1.allocate_node(rapidxml::node_element, "connects");
                xml_connects->append_attribute(doc1.allocate_attribute("xlink:href", doc1.allocate_string(("#" + it1->gml_id).c_str())));
                xml_Transition->append_node(xml_connects);
            }
            if(it->duality!=NULL) {
                rapidxml::xml_node < > *xml_duality = doc1.allocate_node(rapidxml::node_element, "duality");
                xml_duality->append_attribute(doc1.allocate_attribute("xlink:href", doc1.allocate_string(("#" + it->duality->gml_id).c_str())));
                xml_Transition->append_node(xml_duality);
            }
            for(auto it1 : ((CONVERTER::Transition*)it)->pos_vector){
                double EACH_HEIGHT=0.0;
                EACH_HEIGHT=EACH_HEIGHT+0.0003*(((CONVERTER::Transition*)it)->storey-min_storey);
                rapidxml::xml_node<>* xml_pos = doc1.allocate_node(rapidxml::node_element, "gml:pos");
                xml_pos->append_attribute(doc1.allocate_attribute("srsDimension",srsDimension.c_str()));
                xml_pos->value(doc1.allocate_string((it1->longitude+" "+it1->latitude+" "+std::to_string(EACH_HEIGHT)).c_str()));
                xml_LineString->append_node(xml_pos);
            }

            xml_geometry->append_node(xml_LineString);
            xml_Transition->append_node(xml_description);
            xml_Transition->append_node(xml_geometry);
            xml_transitionMember->append_node(xml_Transition);
            xml_edges->append_node(xml_transitionMember);
        }//Transition

        xml_multiLayeredGraph->append_node(xml_MultiLayeredGraph);
        xml_primalSpaceFeatures->append_node(xml_PrimalSpaceFeatures);
        root->append_node(xml_primalSpaceFeatures);
        root->append_node(xml_multiLayeredGraph);
        doc1.append_node(root);

        std::ofstream file_stored(PATH);
        file_stored << doc1;
        file_stored.close();
        doc1.clear();
        std::cout<<"SUCESS"<<std::endl;
    }
}