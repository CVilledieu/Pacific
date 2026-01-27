#include "render/draw.h"
#include "common/error.h"
#include "window/wnd.h"

int main(void){
    initCtx();
    
    draw();

    closeWindow();
}