Handling IndoorGML in JSOM
=============
*   If you want to handle the Indoorgml file in JOSM, you have to follow some rules.

*   All Indoorgml relationships are defined as osm [relation](https://wiki.openstreetmap.org/wiki/Relation).

*   This approach can help to study the real coordinates of Indoorgml.

## Quick Start 
- We create one cellspace and one state and define duality.
1. Create polygon in JOSM<br>
   <img width="500" src="Photo/JOSM_CELLSPACE.PNG" style="margin:10px"></img>
2. The generated polygon is assigned to the cellspace using the relation of osm.<br>
   <img width="500" src="Photo/josm_cellspace_relation.PNG" style="margin:10px"></img>
3. If you use a tag in josm, it is reflected in indoorgml.
   <img width="500" src="Photo/josm_cellspace_tag.PNG" style="margin:10px"></img>
4. Create Point in JOSM<br>
     <img width="500" src="Photo/josm_create_state.PNG" style="margin:10px"></img>
5. The generated point is assigned to the state using the relation of osm.<br>
   <img width="500" src="Photo/josm_state_relation.PNG" style="margin:10px"></img>
6. The duality is defined using the relation of osm.<br>
   <img width="500" src="Photo/download_josm.PNG" style="margin:10px"></img>
7. Save osm file<br>
   <img width="500" src="Photo/save_osmdata.PNG" style="margin:10px"></img>
8. Convert osm -> Indoorgml
   <img width="500" src="Photo/cmd.png" style="margin:10px"></img>