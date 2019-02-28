//
// Created by byeonggon on 2018-11-12.
//

#include "IO.h"
#include "TRANSFORM/Transform.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>
int CellSpace_ID=1;
int CellSpaceBoundary_ID=1;
int State_id=1;
int Transition_id=1;
int OSM_NODE_ID=-1;
int OSM_WAY_ID=-30000;
int OSM_RELATION_ID=-60000;
namespace IO{
    char * lowercase(char *input){
        int i=0;
        char c;
        while(input[i]){
            c=input[i];
            input[i]=tolower(c);
            i++;
        }
        return input;
    }
    bool ISNOT_INDOORGML(char **input){
        bool output=false;
        if (strcmp(lowercase(input[1]),"indoorgml")==0||strcmp(lowercase(input[2]),"indoorgml")==0)
            output=true;
        return output;
    }
    void ISNOT_INDORGML_MESSAGE(){
        std::cout<<"INDOORGML FILE is not included among INPUT values.";
    }
}