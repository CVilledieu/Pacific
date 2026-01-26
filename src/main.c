#include "window/wnd.h"
#include "render/ctx.h"
#include "util/err.h"


int main(void){
    if (createWindow()){
        return -1;
    }


    initCtx();
    
    drawLoop();

    closeWindow();
    printErrLog();
}