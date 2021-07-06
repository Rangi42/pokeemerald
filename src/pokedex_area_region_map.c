#include "global.h"
#include "main.h"
#include "menu.h"
#include "bg.h"
#include "malloc.h"
#include "palette.h"
#include "pokedex_area_region_map.h"

static EWRAM_DATA u8 *sPokedexAreaMapBgNum = NULL;

extern const u16 sRegionMapBg_Pal[];
extern const u32 sRegionMapBg_GfxLZ[];
static const u32 sPokedexAreaMap_Tilemap[] = INCBIN_U32("graphics/interface/region_map.bin.lz");

void LoadPokedexAreaMapGfx(void)
{
    u8 bg = 3;
    sPokedexAreaMapBgNum = Alloc(4);

    SetBgAttribute(bg, BG_ATTR_METRIC, 0);
    DecompressAndCopyTileDataToVram(bg, sRegionMapBg_GfxLZ, 0, 0, 0);
    DecompressAndCopyTileDataToVram(bg, sPokedexAreaMap_Tilemap, 0, 0, 1);

    ChangeBgX(bg, 0, 0);
    ChangeBgY(bg, 0, 0);
    SetBgAttribute(bg, BG_ATTR_PALETTEMODE, 1);
    CpuCopy32(sRegionMapBg_Pal, &gPlttBufferUnfaded[0x70], 0x60);

    *sPokedexAreaMapBgNum = bg;
}

bool32 sub_81C4E90(void)
{
    if (!FreeTempTileDataBuffersIfPossible())
    {
        ShowBg(*sPokedexAreaMapBgNum);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void FreePokedexAreaMapBgNum(void)
{
    if (sPokedexAreaMapBgNum != NULL)
        FREE_AND_SET_NULL(sPokedexAreaMapBgNum);
}

void PokedexAreaMapChangeBgY(u32 a0)
{
    ChangeBgY(*sPokedexAreaMapBgNum, a0 * 0x100, 0);
}
