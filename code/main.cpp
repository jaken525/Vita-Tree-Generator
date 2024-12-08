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

#include "settings.h"

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#define CHECK_BIN(x) ((pad.buttons & x) && (!(old_buttons & x)))

int currentPos = 0;

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

        vita2d_start_drawing();
		vita2d_clear_screen();

        tree.Draw();

        vita2d_pgf_draw_text(pvf, 10, 30, RGBA8(255,255,255,255), 1.0f, "Made by JaKeN");
        vita2d_pgf_draw_text(pvf, 10, 50, RGBA8(255,255,255,255), 1.0f, "X - Generate new tree.");
        vita2d_pgf_draw_textf(pvf, 10, 80, currentPos == 0 ? RGBA8(0,255,0,255) : RGBA8(255,255,255,255), 1.0f, "Recursion Depth: %d", recursionDepth);
        vita2d_pgf_draw_textf(pvf, 10, 100, currentPos == 1 ? RGBA8(0,255,0,255) : RGBA8(255,255,255,255), 1.0f, "Branch Probability: %.2f", branchProbability);
        vita2d_pgf_draw_textf(pvf, 10, 120, currentPos == 2 ? RGBA8(0,255,0,255) : RGBA8(255,255,255,255), 1.0f, "Base Angle: %.2f", baseAngle);
        vita2d_pgf_draw_textf(pvf, 10, 140, currentPos == 3 ? RGBA8(0,255,0,255) : RGBA8(255,255,255,255), 1.0f, "Branch Per Node: %d", branchPerNode);

        if (CHECK_BIN(SCE_CTRL_CROSS))
            tree.Generate();

        currentPos += CHECK_BIN(SCE_CTRL_UP) ? -1 : (CHECK_BIN(SCE_CTRL_DOWN) ? 1 : 0);
        if (currentPos < 0)
            currentPos = 3;
        else if (currentPos > 3)
            currentPos = 0;

        switch (currentPos)
        {
            case 0:
                if (CHECK_BIN(SCE_CTRL_LEFT))
                    recursionDepth--;
                else if (CHECK_BIN(SCE_CTRL_RIGHT))
                    recursionDepth++;

                if (recursionDepth < 0)
                    recursionDepth = 0;
                else if (recursionDepth > 5)
                    recursionDepth = 5;
            break;

            case 1:
                if (CHECK_BIN(SCE_CTRL_LEFT))
                    branchProbability -= 0.1f;
                else if (CHECK_BIN(SCE_CTRL_RIGHT))
                    branchProbability += 0.1f;

                if (branchProbability < 0)
                    branchProbability = 0;
                else if (branchProbability > 1)
                    branchProbability = 1;
            break;

            case 2:
                if (pad.buttons & SCE_CTRL_LEFT)
                    baseAngle--;
                else if (pad.buttons & SCE_CTRL_RIGHT)
                    baseAngle++;

                if (baseAngle < -180)
                    baseAngle = -180;
                else if (baseAngle > 180)
                    baseAngle = 180;
            break;

            case 3:
                if (CHECK_BIN(SCE_CTRL_LEFT))
                    branchPerNode--;
                else if (CHECK_BIN(SCE_CTRL_RIGHT))
                    branchPerNode++;

                if (branchPerNode < 0)
                    branchPerNode = 0;
                else if (branchPerNode > 7)
                    branchPerNode = 7;
            break;
        }

        vita2d_end_drawing();
		vita2d_swap_buffers();
        old_buttons = pad.buttons;
    }

    vita2d_fini();
    vita2d_free_pgf(pvf);

    sceKernelExitProcess(0);
	return 0;
}