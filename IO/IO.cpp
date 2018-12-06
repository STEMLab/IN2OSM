//
// Created by byeonggon on 2018-11-12.
//

#include "IO.h"
#include "TRANSFORM/Transform.h"
#include <stdio.h>
#include <ctype.h>

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
}