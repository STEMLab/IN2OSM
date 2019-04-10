# IndoorData Converter

IndoorGML data <-> OSM data
* **This Converter handles only 2D IndoorGML data.**

## Author
Byeonggon Kim(byeonggon@pnu.edu), Pusan National University

## Dependencies
- InFactory (https://github.com/STEMLab/InFactory) : To generate IndoorGML.
- OSM (https://wiki.openstreetmap.org/wiki/Main_Page) : OSM wiki
- rapidxml (http://rapidxml.sourceforge.net) : To read OSM(.osm),IndoorGML(.gml) file
- rapidjson (http://rapidjson.org/) :  To read IMDF(.geojson) file
## Building

Dependencies should be pre-installed in your environment.
- Linux
```
mkdir build
cd build
cmake ..
make
```
- Windows
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```
## Usage

```
IN2OSM [inputfile_type] [outputfile_type] [inputfile_path] [outputfile_path].
```

For example,

```
IN2OSM OSM IndoorGML ./TEST.osm ./TEST.gml
IN2OSM IndoorGML OSM ./TEST.gml ./TEST.osm
```

-   [Video how to work](https://youtu.be/xzT3sgQjprg)<br>
-   [Simple User Guide](https://github.com/STEMLab/IN2OSM/blob/master/GUIDE/index.md)<br>
-   [Handling indoorgml in josm](https://github.com/STEMLab/IN2OSM/blob/master/GUIDE/IndoorGML_JOSM.md)
-   [IMDF to IndoorGML Video (Not official)](https://youtu.be/G_ohrdM1cAk)

## Development
For Developer, we document source code description. see : [MANUAL](https://stemlab.github.io/IN2OSM/)
