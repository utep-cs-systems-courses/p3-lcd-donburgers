#ifndef DARKSOULS_BONFIRE_H
#define DARKSOULS_BONFIRE_H

#include "grlib.h"

static const unsigned char pixel_darksouls_bonfire4BPP_COMP_RLE4[] =
{
  //... the rest of the pixel data...
};

static const unsigned long palette_darksouls_bonfire4BPP_COMP_RLE4[]=
{
	//... the rest of the palette data...
};

const tImage darksouls_bonfire4BPP_COMP_RLE4 =
{
	IMAGE_FMT_4BPP_COMP_RLE4,
	637,
	358,
	16,
	palette_darksouls_bonfire4BPP_COMP_RLE4,
	pixel_darksouls_bonfire4BPP_COMP_RLE4,
};

#endif /* DARKSOULS_BONFIRE_H */