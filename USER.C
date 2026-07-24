/* File HELLOSVG.C: User selective link version for 800x600x16 mode */

#include <hanlib.h>

void userinithan(void)
{
//    inithanlib(HIRESSTDMODE, HANSVGA800HI, HAN212GD1, ENGMD3);
    inithanlib(FIXRESMODE, HANDETECT, HAN212GD1, ENGMD3);
}

