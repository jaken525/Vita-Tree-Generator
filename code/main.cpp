#include "random.h"
#include <vector>
#include <ctime>
#include "tree.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vita2d.h>
#include <vitasdk.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#define CHECK_BIN(x) ((pad.buttons & x) && (!(old_buttons & x)))

int main()
{
    srand(time(NULL));

    uint32_t old_buttons = 0;
    vita2d_pgf *pvf;
    Tree tree;

    vita2d_init();
	vita2d_set_clear_color(RGBA8(0x00, 0x9B, 0xCE, 0xFF));
    pvf = vita2d_load_default_pgf();

    SceCtrlData pad;
    memset(&pad, 0, sizeof(pad));

    while (1)
    {
        sceCtrlPeekBufferPositive(0, &pad, 1);
       // glClear(GL_COLOR_BUFFER_BIT);

        vita2d_start_drawing();
		vita2d_clear_screen();

        tree.Draw();

        vita2d_pgf_draw_text(pvf, 10, 30, RGBA8(255,255,255,255), 1.0f, "Made by JaKeN");

        if (CHECK_BIN(SCE_CTRL_CROSS))
            tree.Generate();
        /*if (CHECK_BIN(SCE_CTRL_CIRCLE))
            ClearScene();
        if (CHECK_BIN(SCE_CTRL_TRIANGLE))
            isWireFrame = !isWireFrame;

        criteria1 += CHECK_BIN(SCE_CTRL_UP) ? 1 : (CHECK_BIN(SCE_CTRL_DOWN) ? -1 : 0);
        criteria2 += CHECK_BIN(SCE_CTRL_RIGHT) ? 1 : (CHECK_BIN(SCE_CTRL_LEFT) ? -1 : 0);
       // vglSwapBuffers(GL_FALSE);*/

        vita2d_end_drawing();
		vita2d_swap_buffers();
        old_buttons = pad.buttons;
    }

    vita2d_fini();
    vita2d_free_pgf(pvf);
//    vglEnd();
    sceKernelExitProcess(0);
	return 0;
}