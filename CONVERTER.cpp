//
// Created by byeonggon on 2018-11-02.
//
#include "IndoorGML_Reader/IndoorGML_Reader.h"
#include "IndoorGML_Writer/IndoorGML_Writer.h"
#include "OSM_Reader/OSM_Reader.h"
#include "OSM_Writer/OSM_Writer.h"
//#include "IMDF_Reader/IMDF_Reader.h"
//#include "IMDF_Writer/IMDF_Writer.h"
#include "IO/IO.h"
#include <iostream>
#include <string.h>
//#include <io.h>
#include "assert.h"

const char *DATA[3] = {"indoorgml", "osm", "imdf"};

int main(int argc, char **argv) {
    std::vector<CONVERTER::IC *> IC_vector_MEMORY;
    int input;
    int output;
    try {
        if (!IO::ISNOT_INDOORGML(argv))
            throw argv;

        for (int i = 0; i < 3; i++) {
            if (strcmp(IO::lowercase(argv[1]), DATA[i]) == 0) {
                input = i;
            }
            if (strcmp(IO::lowercase(argv[2]), DATA[i]) == 0) {
                output = i;
            }
        }

        switch (input) {
            case 0:
                IC_vector_MEMORY = INDOOR::Read(argv[3]);
                break;
            case 1:
                IC_vector_MEMORY = OSM::Read(argv[3]);
                break;
//            case 2:
//                IC_vector_MEMORY = IMDF::READ(argv[3]);
                break;
        }
        switch (output) {
            case 0:
                INDOOR::Write(IC_vector_MEMORY, argv[4]);
                break;
            case 1:
                OSM::Write(IC_vector_MEMORY, argv[4]);
                break;
        }
    } catch (char **argv) {
        IO::ISNOT_INDORGML_MESSAGE();
    }
    return 0;
}