IN2OSM
=============

IN2OSM is an open source C++ program that provides tools for simple converter Indoorgml<->osm.
* Prerequisites
       - Openlevelup : (https://openlevelup.net) <br>
       Verify that osm indoor data is present or not.<br>
        <img width="500" src="Photo/shopping_mall.png" style="margin:10px"></img>
        
## Quick Start <br><br>*OSM->IndoorGML*
A simple example to create IndoorGML from OSM data.
1. Download osm data using josm(https://josm.openstreetmap.de).<br>
   <img width="500" src="Photo/download_josm.PNG" style="margin:10px"></img>
   
2. Save osm data<br>
    <img width="500" src="Photo/save_osmdata.PNG" style="margin:10px"></img>
    
3. IN2OSM OSM Indoorgml [inputfile_path] [outputfile_path].<br>
    <img width="500" src="Photo/cmd.png" style="margin:10px"></img>


## *IndoorGML->OSM*
* Only support core module Indoorgml
1. IN2OSM Indoorgml OSM [inputfile_path] [outputfile_path].<br>
   <img width="500" src="Photo/cmd2.png" style="margin:10px"></img>
