//
// Created by byeonggon on 2018-11-12.
//

#ifndef INDOORGML2OSM_IO_H
#define INDOORGML2OSM_IO_H
#include <vector>
#include <string>
namespace IO{
    /**
     * @brief change char * to lower case
     * @return char*
     */
    char * lowercase(char *input);
    bool ISNOT_INDOORGML(char **input);
    void ISNOT_INDORGML_MESSAGE();
    std::vector <std::string> IMDF_FILE_LIST(std::string path);
}
#endif //INDOORGML2OSM_IO_H
