//
// Created by byeonggon on 2018-11-02.
//
#include "IndoorGML_Reader/IndoorGML_Reader.h"
#include "IndoorGML_Writer/IndoorGML_Writer.h"
#include "OSM_Reader/OSM_Reader.h"
#include "OSM_Writer/OSM_Writer.h"
#include "IMDF_Reader/IMDF_Reader.h"
#include "IO/IO.h"
#include <iostream>
#include <string.h>
#include <io.h>
#include "assert.h"
int main(int argc, char **argv) {
    try{
        if(!IO::ISNOT_INDOORGML(argv))
            throw argv;
        if(strcmp(IO::lowercase(argv[1]),"indoorgml")==0 && strcmp(IO::lowercase(argv[2]),"osm")==0){
            OSM::Write(INDOOR::Read(argv[3]),argv[4]);
        }
        if(strcmp(IO::lowercase(argv[1]),"osm")==0 && strcmp(IO::lowercase(argv[2]),"indoorgml")==0){
            INDOOR::Write(OSM::Read(argv[3]),argv[4]);
        }
    } catch(char **argv) {
        IO::ISNOT_INDORGML_MESSAGE();
    }
    return 0;
}