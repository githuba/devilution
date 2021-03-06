/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

#include "../types.h"

PALETTEENTRY logical_palette[256];
int palette_cpp_init_value; // weak
PALETTEENTRY system_palette[256];
PALETTEENTRY orig_palette[256];
UINT gdwPalEntries;

int palette_inf = 0x7F800000; // weak

/* rdata */

int gamma_correction = 100; // idb
int color_cycling_enabled = 1; // idb
bool sgbFadedIn = 1;

//----- (00448DFA) --------------------------------------------------------
struct palette_cpp_init
{
	palette_cpp_init()
	{
		palette_cpp_init_value = palette_inf;
	}
} _palette_cpp_init;
// 47F16C: using guessed type int palette_inf;
// 67DBCC: using guessed type int palette_cpp_init_value;

//----- (00448E05) --------------------------------------------------------
void __cdecl palette_save_gamme()
{
	SRegSaveValue("Diablo", "Gamma Correction", 0, gamma_correction);
	SRegSaveValue("Diablo", "Color Cycling", 0, color_cycling_enabled);
}

//----- (00448E33) --------------------------------------------------------
void __cdecl palette_init()
{
	int v0; // eax
	int v1; // eax

	palette_load_gamma();
	memcpy(system_palette, orig_palette, 0x400u);
	LoadSysPal();
	v0 = IDirectDraw_CreatePalette(lpDDInterface, DDPCAPS_ALLOW256|DDPCAPS_8BIT, system_palette, &lpDDPalette, NULL);
	if ( v0 )
		TermDlg(111, v0, "C:\\Src\\Diablo\\Source\\PALETTE.CPP", 143);
	v1 = IDirectDrawSurface_SetPalette(lpDDSPrimary, lpDDPalette);
	if ( v1 )
		TermDlg(111, v1, "C:\\Src\\Diablo\\Source\\PALETTE.CPP", 146);
}

//----- (00448EAB) --------------------------------------------------------
void __cdecl palette_load_gamma()
{
	int v3; // eax
	int value; // [esp+8h] [ebp-4h]

	value = gamma_correction;
	if ( !SRegLoadValue("Diablo", "Gamma Correction", 0, &value) )
		value = 100;
	if ( value >= 30 )
	{
		if ( value > 100 )
			value = 100;
	}
	else
	{
		value = 30;
	}
	gamma_correction = value - value % 5;
	if ( SRegLoadValue("Diablo", "Color Cycling", 0, &value) )
		v3 = value;
	else
		v3 = 1;
	color_cycling_enabled = v3;
}

//----- (00448F20) --------------------------------------------------------
void __cdecl LoadSysPal()
{
	HDC hDC; // ebx
	int i; // ecx
	int iStartIndex; // edi

	for(i = 0; i < 256; i++)
		system_palette[i].peFlags = PC_NOCOLLAPSE|PC_RESERVED;

	if ( !fullscreen )
	{
		hDC = GetDC(NULL);
		gdwPalEntries = GetDeviceCaps(hDC, NUMRESERVED) / 2;
		GetSystemPaletteEntries(hDC, 0, gdwPalEntries, system_palette);
		for ( i = 0; i < gdwPalEntries; i++ )
			system_palette[i].peFlags = 0;
		iStartIndex = 256 - gdwPalEntries;
		GetSystemPaletteEntries(hDC, iStartIndex, gdwPalEntries, &system_palette[iStartIndex]);
		if ( iStartIndex < 256 )
		{
			for(i = iStartIndex; i < 256; i++)
				system_palette[i].peFlags = 0;
		}
		ReleaseDC(NULL, hDC);
	}
}
// 484364: using guessed type int fullscreen;

//----- (00448FC9) --------------------------------------------------------
void __fastcall LoadPalette(char *pszFileName)
{
	int i; // eax
	char PalData[256][3]; // [esp+0h] [ebp-304h]
	void *pBuf; // [esp+300h] [ebp-4h]

	WOpenFile(pszFileName, &pBuf, 0);
	WReadFile(pBuf, (char *)PalData, 768);
	WCloseFile(pBuf);

	for(i = 0; i < 256; i++)
	{
		orig_palette[i].peFlags = 0;
		orig_palette[i].peRed = PalData[i][0];
		orig_palette[i].peGreen = PalData[i][1];
		orig_palette[i].peBlue = PalData[i][2];
	}
}

//----- (00449025) --------------------------------------------------------
void __fastcall LoadRndLvlPal(int l)
{
	char *pszPal; // ecx
	char szTemp[260]; // [esp+4h] [ebp-104h]

	if ( l )
	{
		sprintf(szTemp, "Levels\\L%iData\\L%i_%i.PAL", l, l, random(0, 4) + 1);
		pszPal = szTemp;
	}
	else
	{
		pszPal = "Levels\\TownData\\Town.pal";
	}
	LoadPalette(pszPal);
}

//----- (0044906C) --------------------------------------------------------
void __cdecl ResetPal()
{
	if ( !lpDDSPrimary
	  || IDirectDrawSurface_IsLost(lpDDSPrimary) != DDERR_SURFACELOST
	  || !IDirectDrawSurface_Restore(lpDDSPrimary) )
	{
		SDrawRealizePalette();
	}
}

//----- (00449097) --------------------------------------------------------
void __cdecl palette_inc_gamma()
{
	if ( gamma_correction < 100 )
	{
		gamma_correction += 5;
		if ( gamma_correction > 100 )
			gamma_correction = 100;
		palette_apply_gamma_correction(system_palette, logical_palette, 256);
		palette_update();
	}
}

//----- (004490D0) --------------------------------------------------------
void __cdecl palette_update()
{
	int v0; // ecx
	int v1; // eax

	if ( lpDDPalette )
	{
		v0 = 0;
		v1 = 256;
		if ( !fullscreen )
		{
			v0 = gdwPalEntries;
			v1 = 2 * (128 - gdwPalEntries);
		}
		SDrawUpdatePalette(v0, v1, &system_palette[v0], 0);
	}
}
// 484364: using guessed type int fullscreen;

//----- (00449107) --------------------------------------------------------
void __fastcall palette_apply_gamma_correction(PALETTEENTRY *dst, PALETTEENTRY *src, int n)
{
	PALETTEENTRY *v3; // edi
	PALETTEENTRY *v4; // esi
	double v5; // [esp+18h] [ebp-Ch]

	v3 = src;
	v4 = dst;
	v5 = (double)gamma_correction * 0.01;
	if ( n > 0 )
	{
		do
		{
			v4->peRed = pow(v3->peRed * 0.00390625, v5) * 256.0;
			v4->peGreen = pow(v3->peGreen * 0.00390625, v5) * 256.0;
			v4->peBlue = pow(v3->peBlue * 0.00390625, v5) * 256.0;
			++v4;
			++v3;
			--n;
		}
		while ( n );
	}
}

//----- (004491D0) --------------------------------------------------------
void __cdecl palette_dec_gamma()
{
	if ( gamma_correction > 30 )
	{
		gamma_correction -= 5;
		if ( gamma_correction < 30 )
			gamma_correction = 30;
		palette_apply_gamma_correction(system_palette, logical_palette, 256);
		palette_update();
	}
}

//----- (00449209) --------------------------------------------------------
int __fastcall palette_update_gamma(int gamma)
{
	if ( gamma )
	{
		gamma_correction = 130 - gamma;
		palette_apply_gamma_correction(system_palette, logical_palette, 256);
		palette_update();
	}
	return 130 - gamma_correction;
}

//----- (0044923E) --------------------------------------------------------
void __cdecl BlackPalette()
{
	SetFadeLevel(0);
}

//----- (00449245) --------------------------------------------------------
void __fastcall SetFadeLevel(int fadeval)
{
	int i; // eax

	if ( lpDDInterface )
	{
		for(i = 0; i < 255; i++)
		{
			system_palette[i].peRed = (fadeval * logical_palette[i].peRed) >> 8;
			system_palette[i].peGreen = (fadeval * logical_palette[i].peGreen) >> 8;
			system_palette[i].peBlue = (fadeval * logical_palette[i].peBlue) >> 8;
		}
		Sleep(3);
		IDirectDraw_WaitForVerticalBlank(lpDDInterface, DDWAITVB_BLOCKBEGIN, NULL);
		palette_update();
	}
}

//----- (004492B0) --------------------------------------------------------
void __fastcall PaletteFadeIn(int fr)
{
	int i; // ebp

	palette_apply_gamma_correction(logical_palette, orig_palette, 256);

	for(i = 0; i < 256; i += fr)
		SetFadeLevel(i);

	SetFadeLevel(256);
	memcpy(logical_palette, orig_palette, 0x400u);
	sgbFadedIn = 1;
}

//----- (00449306) --------------------------------------------------------
void __fastcall PaletteFadeOut(int fr)
{
	int i; // esi

	if ( sgbFadedIn )
	{
		for(i = 256; i > 0; i -= fr)
			SetFadeLevel(i);

		SetFadeLevel(0);
		sgbFadedIn = 0;
	}
}

//----- (00449336) --------------------------------------------------------
void __cdecl palette_update_caves()
{
	BYTE v0; // cx
	signed int v1; // esi
	signed int v2; // eax
	BYTE v4; // [esp+6h] [ebp-2h]
	BYTE v5;

	v0 = system_palette[1].peRed;
	v5 = system_palette[1].peGreen;
	v4 = system_palette[1].peBlue;
	v1 = 1;
	do
	{
		v2 = v1++;
		system_palette[v2].peRed = system_palette[v2 + 1].peRed;
		system_palette[v2].peGreen = system_palette[v2 + 1].peGreen;
		system_palette[v2].peBlue = system_palette[v2 + 1].peBlue;
	}
	while ( v1 < 31 );
	system_palette[v1].peRed = v0;
	system_palette[v1].peGreen = v5;
	system_palette[v1].peBlue = v4;
	palette_update();
}

//----- (00449398) --------------------------------------------------------
void __fastcall palette_update_quest_palette(int n)
{
	int i; // eax

	for ( i = 32 - n; i >= 0; --i )
		logical_palette[i] = orig_palette[i];
	palette_apply_gamma_correction(system_palette, logical_palette, 32);
	palette_update();
}

//----- (004493C6) --------------------------------------------------------
bool __cdecl palette_get_colour_cycling()
{
	return color_cycling_enabled;
}

//----- (004493CC) --------------------------------------------------------
void __fastcall palette_set_color_cycling(bool enabled)
{
	color_cycling_enabled = enabled;
}
