/*
    Director:
        contains the central logic for game engine.


*/

#include "root.h"
#include "primitives/wnd.h"
#include "primitives/vertex.h"


void initDirector(void){
    createWindow();

    initShaders();
    unsigned int VAO = createVertexObject(PRIM_SQUARE);

}

void draw(void){
    while(keepDrawing()){

    }
}