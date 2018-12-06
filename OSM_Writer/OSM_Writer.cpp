//
// Created by byeonggon on 2018-11-02.
//

#include "OSM_Writer.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace OSM {
        std::vector<std::string> split(std::string& strToSplit, char delimeter) {
        std::stringstream ss(strToSplit);
        std::string item;
        std::vector<std::string> splittedStrings;
        while (std::getline(ss, item, delimeter)) {
            if(item.length()==0)continue;
            for(int i=0;i<item.length();i++) {
                if (item.at(i) == '\n') {
                    item.at(i)=' ';
                }
            }
            item=trim(item);
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
    std::string Write_tag(std::string &input){
        std::string out;
        out=input;
        if(input=="storey")
            out="level";
        return out;
    }
    void Write(std::vector<CONVERTER::IC*>IC_vector, std::string PATH){
        rapidxml::xml_document<> doc1;
        rapidxml::xml_node<>* decl = doc1.allocate_node(rapidxml::node_declaration);
        decl->append_attribute(doc1.allocate_attribute("version", "1.0"));
        decl->append_attribute(doc1.allocate_attribute("encoding", "UTF-8"));
        doc1.append_node(decl);

// root node
        rapidxml::xml_node<>* root = doc1.allocate_node(rapidxml::node_element, "osm");
        root->append_attribute(doc1.allocate_attribute("version", "0.6"));
        root->append_attribute(doc1.allocate_attribute("generator", "PNU_STEM_LAB"));
        doc1.append_node(root);

        for(auto it:IC_vector){
            if(it->type!=0)continue;
            rapidxml::xml_node<> *node = doc1.allocate_node(rapidxml::node_element, "node");
            node->append_attribute(doc1.allocate_attribute("action", "modify"));
            node->append_attribute(doc1.allocate_attribute("visible", "true"));
            node->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(it->osm_id.c_str())));
            node->append_attribute(doc1.allocate_attribute("lat", doc1.allocate_string((((CONVERTER::Pos*)it)->latitude).c_str())));
            node->append_attribute(doc1.allocate_attribute("lon", doc1.allocate_string((((CONVERTER::Pos*)it)->longitude).c_str())));
            root->append_node(node);
        }//append node


        for(auto it :IC_vector){//Cellspace
            if(it->type!=1)continue;
            rapidxml::xml_node<> *way  = doc1.allocate_node(rapidxml::node_element, "way");
            way->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(it->osm_id.c_str())));
            way->append_attribute(doc1.allocate_attribute("action", "modify"));
            way->append_attribute(doc1.allocate_attribute("visible", "true"));
            for(int i=0;i < ((CONVERTER::CellSpace*)it)->pos_vector.size(); i++) {
                rapidxml::xml_node<> *nd = doc1.allocate_node(rapidxml::node_element, "nd");
                nd->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string(((CONVERTER::CellSpace*)it)->pos_vector[i]->osm_id.c_str())));
                way->append_node(nd);
            }
            if(((CONVERTER::CellSpace*)it)->name.c_str()!=NULL) {
                rapidxml::xml_node<> *tag = doc1.allocate_node(rapidxml::node_element, "tag");
                tag->append_attribute(doc1.allocate_attribute("k", "name"));
                tag->append_attribute(doc1.allocate_attribute("v", doc1.allocate_string((((CONVERTER::CellSpace *) it)->name).c_str())));
                way->append_node(tag);
            }//name이 있으면 name추가

            if(((CONVERTER::CellSpace*)it)->Description.c_str()!=NULL) {
                std::vector<std::string> splittedStrings = split(it->Description, ';');
                for (auto it : splittedStrings) {
                    std::vector<std::string> token = split(it, '=');
                    rapidxml::xml_node<> *tag = doc1.allocate_node(rapidxml::node_element, "tag");
                    tag->append_attribute(doc1.allocate_attribute("k", doc1.allocate_string(Write_tag(token[0]).c_str())));
                    tag->append_attribute(doc1.allocate_attribute("v", doc1.allocate_string((token[1].c_str()))));
                    way->append_node(tag);
                }
            }//Description이 있으면 Description 추가
            root->append_node(way);
        }//append Cellspace

        for(auto it:IC_vector){//CellspaceBoundary
            if(it->type!=2)continue;
            rapidxml::xml_node<> *way  = doc1.allocate_node(rapidxml::node_element, "way");
            way->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(it->osm_id.c_str())));
            way->append_attribute(doc1.allocate_attribute("action", "modify"));
            way->append_attribute(doc1.allocate_attribute("visible", "true"));
            for(int i=0;i < ((CONVERTER::CellSpaceBoundary*)it)->pos_vector.size(); i++) {
                rapidxml::xml_node<> *nd = doc1.allocate_node(rapidxml::node_element, "nd");
                nd->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((((CONVERTER::CellSpaceBoundary*)it)->pos_vector[i]->osm_id).c_str())));
                way->append_node(nd);
            }
            if(((CONVERTER::CellSpaceBoundary*)it)->name!="") {
                rapidxml::xml_node<> *tag = doc1.allocate_node(rapidxml::node_element, "tag");
                tag->append_attribute(doc1.allocate_attribute("k", "name"));
                tag->append_attribute(doc1.allocate_attribute("v", doc1.allocate_string((((CONVERTER::CellSpaceBoundary*) it)->name).c_str())));
                way->append_node(tag);
            }//name이 있으면 name 추가
            if(((CONVERTER::CellSpace*)it)->Description.c_str()!=NULL) {
                std::vector<std::string> splittedStrings = split(it->Description, ';');
                for (auto it : splittedStrings) {
                    std::vector<std::string> token = split(it, '=');
                    rapidxml::xml_node<> *tag = doc1.allocate_node(rapidxml::node_element, "tag");
                    tag->append_attribute(doc1.allocate_attribute("k", doc1.allocate_string(Write_tag(token[0]).c_str())));
                    tag->append_attribute(doc1.allocate_attribute("v", doc1.allocate_string((token[1].c_str()))));
                    way->append_node(tag);
                }
            }//Description이 있으면 Description 추가
            root->append_node(way);
        }//append Cellspaceboundary

        for(auto it:IC_vector){//Transition
            if(it->type!=4)continue;
            rapidxml::xml_node<> *way  = doc1.allocate_node(rapidxml::node_element, "way");
            way->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string((it->osm_id).c_str())));
            way->append_attribute(doc1.allocate_attribute("action", "modify"));
            way->append_attribute(doc1.allocate_attribute("visible", "true"));
            for(int i=0;i < ((CONVERTER::Transition*)it)->pos_vector.size(); i++) {
                rapidxml::xml_node<> *nd = doc1.allocate_node(rapidxml::node_element, "nd");
                nd->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((((CONVERTER::Transition*)it)->pos_vector[i]->osm_id).c_str())));
                way->append_node(nd);
            }
            if(((CONVERTER::CellSpace*)it)->Description.c_str()!=NULL) {
                std::vector<std::string> splittedStrings = split(it->Description, ';');
                for (auto it : splittedStrings) {
                    std::vector<std::string> token = split(it, '=');
                    rapidxml::xml_node<> *tag = doc1.allocate_node(rapidxml::node_element, "tag");
                    tag->append_attribute(doc1.allocate_attribute("k", doc1.allocate_string(Write_tag(token[0]).c_str())));
                    tag->append_attribute(doc1.allocate_attribute("v", doc1.allocate_string((token[1].c_str()))));
                    way->append_node(tag);
                }
            }//Description이 있으면 Description 추가
            root->append_node(way);
        }//append Transition


        rapidxml::xml_node<> *relation_cellspace  = doc1.allocate_node(rapidxml::node_element, "relation");
        relation_cellspace->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
        relation_cellspace->append_attribute(doc1.allocate_attribute("action", "modify"));
        relation_cellspace->append_attribute(doc1.allocate_attribute("visible", "true"));

        for(auto it:IC_vector){
            if(it->type!=1)continue;
            rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "way"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
            relation_cellspace->append_node(member);
        }
        rapidxml::xml_node<> *tag = doc1.allocate_node(rapidxml::node_element, "tag");
        tag->append_attribute(doc1.allocate_attribute("k",  "type"));
        tag->append_attribute(doc1.allocate_attribute("v", "CellSpace"));
        relation_cellspace->append_node(tag);
        root->append_node(relation_cellspace);//Cellspace entity

        rapidxml::xml_node<> *relation_cellspaceboundary  = doc1.allocate_node(rapidxml::node_element, "relation");
        relation_cellspaceboundary->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
        relation_cellspaceboundary->append_attribute(doc1.allocate_attribute("action", "modify"));
        relation_cellspaceboundary->append_attribute(doc1.allocate_attribute("visible", "true"));
        for(auto it:IC_vector){
            if(it->type!=2)continue;
            rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "way"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
            relation_cellspaceboundary->append_node(member);
        }
        tag = doc1.allocate_node(rapidxml::node_element, "tag");
        tag->append_attribute(doc1.allocate_attribute("k",  "type"));
        tag->append_attribute(doc1.allocate_attribute("v", "CellSpaceBoundary"));
        relation_cellspaceboundary->append_node(tag);
        root->append_node(relation_cellspaceboundary);//CellspaceBoundary entity

        rapidxml::xml_node<> *relation_state  = doc1.allocate_node(rapidxml::node_element, "relation");
        relation_state->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
        relation_state->append_attribute(doc1.allocate_attribute("action", "modify"));
        relation_state->append_attribute(doc1.allocate_attribute("visible", "true"));
        for(auto it:IC_vector){
            if(it->type!=3)continue;
            rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "node"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
            relation_state->append_node(member);
        }
        tag = doc1.allocate_node(rapidxml::node_element, "tag");
        tag->append_attribute(doc1.allocate_attribute("k",  "type"));
        tag->append_attribute(doc1.allocate_attribute("v", "State"));
        relation_state->append_node(tag);
        root->append_node(relation_state);//State entity

        rapidxml::xml_node<> *relation_transition  = doc1.allocate_node(rapidxml::node_element, "relation");
        relation_transition->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
        relation_transition->append_attribute(doc1.allocate_attribute("action", "modify"));
        relation_transition->append_attribute(doc1.allocate_attribute("visible", "true"));
        for(auto it:IC_vector){
            if(it->type!=4)continue;
            rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "way"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
            relation_transition->append_node(member);
        }
        tag = doc1.allocate_node(rapidxml::node_element, "tag");
        tag->append_attribute(doc1.allocate_attribute("k",  "type"));
        tag->append_attribute(doc1.allocate_attribute("v", "Transition"));
        relation_transition->append_node(tag);
        root->append_node(relation_transition);//State entity

        for(auto it:IC_vector){
            if(it->type!=3)continue;
            if(it->duality==NULL)continue;
            rapidxml::xml_node<> *relation = doc1.allocate_node(rapidxml::node_element, "relation");
            relation->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
            relation->append_attribute(doc1.allocate_attribute("action", "modify"));
            relation->append_attribute(doc1.allocate_attribute("visible", "true"));
            rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "node"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
            member->append_attribute(doc1.allocate_attribute("role", "State"));
            relation->append_node(member);
            member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "way"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->duality->osm_id).c_str())));
            member->append_attribute(doc1.allocate_attribute("role", "CellSpace"));
            relation->append_node(member);
            tag = doc1.allocate_node(rapidxml::node_element, "tag");
            tag->append_attribute(doc1.allocate_attribute("k",  "type"));
            tag->append_attribute(doc1.allocate_attribute("v", "duality"));
            relation->append_node(tag);
            root->append_node(relation);
        }//State<->Cellspace Duality

        for(auto it:IC_vector){
            if(it->type!=4)continue;
            if(it->duality==NULL)continue;
            rapidxml::xml_node<> *relation = doc1.allocate_node(rapidxml::node_element, "relation");
            relation->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
            relation->append_attribute(doc1.allocate_attribute("action", "modify"));
            relation->append_attribute(doc1.allocate_attribute("visible", "true"));
            rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
            member->append_attribute(doc1.allocate_attribute("type", "way"));
            member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
            member->append_attribute(doc1.allocate_attribute("role", "Transition"));
            rapidxml::xml_node<> * member_1  = doc1.allocate_node(rapidxml::node_element, "member");
            member_1->append_attribute(doc1.allocate_attribute("type", "way"));
            member_1->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->duality->osm_id).c_str())));
            member_1->append_attribute(doc1.allocate_attribute("role", "CellSpaceBoundary"));
            relation->append_node(member);
            relation->append_node(member_1);
            tag = doc1.allocate_node(rapidxml::node_element, "tag");
            tag->append_attribute(doc1.allocate_attribute("k",  "type"));
            tag->append_attribute(doc1.allocate_attribute("v", "duality"));
            relation->append_node(tag);
            root->append_node(relation);
        }//Transition<->CellSpaceBoundary duality

        for(auto it:IC_vector){
            if(it->type!=3)continue;
            if(it->connects.size()==0)continue;
            for(auto it1:it->connects) {
                rapidxml::xml_node<> *relation = doc1.allocate_node(rapidxml::node_element, "relation");
                relation->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
                relation->append_attribute(doc1.allocate_attribute("action", "modify"));
                relation->append_attribute(doc1.allocate_attribute("visible", "true"));
                rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
                member->append_attribute(doc1.allocate_attribute("type", "node"));
                member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
                member->append_attribute(doc1.allocate_attribute("role", "State"));
                rapidxml::xml_node<> *member_1 = doc1.allocate_node(rapidxml::node_element, "member");
                member_1->append_attribute(doc1.allocate_attribute("type", "way"));
                member_1->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it1->osm_id).c_str())));
                member_1->append_attribute(doc1.allocate_attribute("role", "Transition"));
                relation->append_node(member);
                relation->append_node(member_1);
                tag = doc1.allocate_node(rapidxml::node_element, "tag");
                tag->append_attribute(doc1.allocate_attribute("k", "type"));
                tag->append_attribute(doc1.allocate_attribute("v", "connects"));
                relation->append_node(tag);
                root->append_node(relation);
            }
        }//State<->Transition Connect

        for(auto it:IC_vector){
            if(it->type!=1)continue;
            if(it->partialboundedBy.size()==0)continue;
            for(auto it1:it->partialboundedBy) {
                rapidxml::xml_node<> *relation = doc1.allocate_node(rapidxml::node_element, "relation");
                relation->append_attribute(doc1.allocate_attribute("id", doc1.allocate_string(std::to_string(OSM_RELATION_ID--).c_str())));
                relation->append_attribute(doc1.allocate_attribute("action", "modify"));
                relation->append_attribute(doc1.allocate_attribute("visible", "true"));
                rapidxml::xml_node<> *member  = doc1.allocate_node(rapidxml::node_element, "member");
                member->append_attribute(doc1.allocate_attribute("type", "way"));
                member->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it->osm_id).c_str())));
                member->append_attribute(doc1.allocate_attribute("role", "CellSpace"));
                rapidxml::xml_node<> *member_1 = doc1.allocate_node(rapidxml::node_element, "member");
                member_1->append_attribute(doc1.allocate_attribute("type", "way"));
                member_1->append_attribute(doc1.allocate_attribute("ref", doc1.allocate_string((it1->osm_id).c_str())));
                member_1->append_attribute(doc1.allocate_attribute("role", "CellSpaceBoundary"));
                relation->append_node(member);
                relation->append_node(member_1);
                tag = doc1.allocate_node(rapidxml::node_element, "tag");
                tag->append_attribute(doc1.allocate_attribute("k", "type"));
                tag->append_attribute(doc1.allocate_attribute("v", "partialboundedBy"));
                relation->append_node(tag);
                root->append_node(relation);
            }
        }//CellSpace<->CellSpaceboundary partialboundedby


        std::ofstream file_stored(PATH);
        file_stored << doc1;
        file_stored.close();
        doc1.clear();
        std::cout<<"SUCESS"<<std::endl;
    }
}