#include "window/wnd.h"
#include "render/draw.h"
#include "util/err.h"


int main(void){
    if (createWindow()){
        return -1;
    }


    initCtx();
    
    draw();

    closeWindow();
    printErrLog();
}