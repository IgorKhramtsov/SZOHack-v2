#include <Windows.h>
#include <DbgHelp.h>
#include <Mmsystem.h>
#include "cMain.h"
#include "cHacks.h"
#include "hider.h"
#include "color.h"
#include "textures.h"
#include "asm_Fun.h"
#include <stdio.h>
#include "Demo.h"
#include "keys.h"
#include "cFont.h"
#include "stdafx.h"
#include "Color.h"
#include <D3DX9Shader.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Ks.h>

#define D3DparamX		, UINT paramx
#define D3DparamvalX	, paramx

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment (lib, "DbgHelp.lib")
#pragma comment (lib, "Winmm.lib")

#define VK_B 0x42

char key;

char *GetDirFile(char *filename);

char DopMenu_WH_EN[]="Visual";
char DopMenu3[]="asd";
char DopMenu5[]="dsa";
int AccuracyC;

cMenu Menu;
copt opt;
bool hExitThread;
LPDIRECT3DTEXTURE9 White,Red,Green,Blue,Black,Purple,Grey,Yellow,Orange,DeepSkyBlue,Chocolate2,Gold2;
unsigned int m_Stride;
bool Color=true;
D3DVIEWPORT9 viewport;
IDirect3DPixelShader9* psTemp;

    float SHNull[4]={1.0f,1.0f,1.0f,0.15f};     // clNull       :  0
    float SHWhite[4]={1.0f,1.0f,1.0f,1.0f };     // clWhite      :  1
    float SHSvYellow[4]={1.0f,1.0f,0.5f,1.0f };     // clSvYellow   :  2
    float SHYellow[4]={1.0f,1.0f,0.0f,1.0f };     // clYellow     :  3
    float SHOrange[4]={1.0f,0.5f,0.0f,1.0f };     // clOrange     :  4
    float SHSvGreen[4]={0.5f,1.0f,0.5f,1.0f };     // clSvGreen    :  5
    float SHGreen[4]={0.0f,1.0f,0.0f,1.0f };     // clGreen      :  6
    float SHSalat[4]={0.5f,1.0f,0.0f,1.0f };     // clSalat      :  7
    float SHSvBlue[4]={0.0f,0.5f,1.0f,1.0f };     // clSvBlue     :  8
    float SHBlue[4]={0.0f,0.0f,1.0f,1.0f };     // clBlue       :  9
    float SHSvRed[4]={1.0f,0.0f,0.5f,1.0f };     // clSvRed      : 10
    float SHRed[4]={1.0f,0.0f,0.0f,1.0f };     // clRed        : 11
    float SHSvRose[4]={1.0f,0.5f,1.0f,1.0f };     // clSvRose     : 12
    float SHRose[4]={1.0f,0.0f,1.0f,1.0f };     // clRose       : 13
    float SHSvAqua[4]={0.5f,1.0f,1.0f,1.0f };     // clSvAqua     : 14
    float SHAqua[4]={0.0f,1.0f,1.0f,1.0f };     // clAqua       : 15
    float SHSer[4]={0.8f,0.8f,0.8f,1.0f };      // clSer        : 16

HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
    if(FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
        return E_FAIL;
    
    WORD colour16 = ((WORD)((colour32>>28)&0xF)<<12)
	            	|(WORD)(((colour32>>20)&0xF)<<8)
	             	|(WORD)(((colour32>>12)&0xF)<<4)
                 	|(WORD)(((colour32>>4)&0xF)<<0);

    D3DLOCKED_RECT d3dlr;    
    (*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
    WORD *pDst16 = (WORD*)d3dlr.pBits;

    for(int xy=0; xy < 8*8; xy++)
        *pDst16++ = colour16;

    (*ppD3Dtex)->UnlockRect(0);

    return S_OK;
}
void PreReset( LPDIRECT3DDEVICE9 pDevice )
{
	Menu.PreReset();
	return;
}
void PostReset( LPDIRECT3DDEVICE9 pDevice )
{
	Menu.PostReset(pDevice);
	return;
}


int blo;
float intint=600;

typedef HRESULT (WINAPI* oDrawIndexedPrimitive) (LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
oDrawIndexedPrimitive pDrawIndexedPrimitive;

int ololo=0;

HRESULT WINAPI  myDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{

//	_asm pushad; //opt.d3d.WalHack
if(Color)
{
GenerateTexture(pDevice, &White,  WHITE);
GenerateTexture(pDevice, &Red,    RED);
GenerateTexture(pDevice, &Green,  GREEN);
GenerateTexture(pDevice, &Blue,   BLUE);
GenerateTexture(pDevice, &Black,  BLACK);
GenerateTexture(pDevice, &Purple, PURPLE);
GenerateTexture(pDevice, &Grey,   GREY);
GenerateTexture(pDevice, &Yellow, YELLOW);
GenerateTexture(pDevice, &Orange, ORANGE);
GenerateTexture(pDevice, &DeepSkyBlue, DEEPSKYBLUE); 
GenerateTexture(pDevice, &Chocolate2, CHOCOLATE2); 
GenerateTexture(pDevice, &Gold2, GOLD2);  
Color = false;
}
/*
float texCol1[4]={0.0f,1.0f,1.0f,1.0f };
float texCol2[4]={1.0f,0.0f,1.0f,1.0f };
*/

/*
if(opt.D3D.WalHack)
  {
	if(htani_DJINS || htani_BL || perchatki || kurtka1 || kurtka2 || kurtka3 || kurtka_HORVAT || kurtka_CHAK || telogreika || specovka 
		|| htani_LONGI || htani_PARTIZAN || htani_tah_horvat || htani_HAKI || htani_HIZ || htani_CHAK || kostum_MARS || kostum_UGOR
		|| kostum_PACHKA || KB_ORDEN_SVOBOD || KB_ODINOCHKI || KB_KK || KB_atom || KB_himer || KB_slince || KB_VOENSTAL
		|| botinki || hapka_KOZIR || hapka_BERET || hapka_VYAZANKA || hlem_VIKING || HIZ_OCHKARIK || maska_bandito || maska_JABA
		|| maska_GRAFFITI || maska_INGLISH || face1 || face2 || face3 || weapons_PM || weapons_MP5 || weapons_drob || weapons_MOSIN
		|| weapons_M4 || weapons_AK107 || weapons_G36 || wa2000 || weapon_GROZA || glock18 || weapon_MK48 | weapon_TT || weapon_RPG
		|| weapon_SVD || weapon_SIG_DONAT || weapon_DIGL || weapon_AK74 || weapon_AK47 || weapon_FNFAL || BERX_HIZ || dragun || tah 
		|| hpinat || krisa || bron_vorot || arm_rukzak || rukzak_odinochki || rukzak_KOLOBOK || rukzak_sekvoia || rukzak_PARTIZAN
		|| bron_KAIZER || bron_hkurka || sandal || omlet || bron_BL || bron_CHAK || bron_FAUNA || halat || шакал_куртка || КБ_свобода
		|| ниндзя || шлем_ВЛ || шашкаТ || каменьТ || lajka || mutant_krisa || mutant_sobaka || KABAN || mutant_studen || mutant_domovoi 
		|| mutant_Pauk || mutant_verla|| mutant_otverj || mutant_miha || mutant_blyak || mutant_brutor || Бес
		|| ящикиТ || travi || Vez || Stab || marevo_provodnik || Poduhka || ekran || Hit || Антиграв
		|| грибыТ)
	{
       pDevice->SetRenderState(D3DRS_ZENABLE,0);
       pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
       pDevice->SetRenderState(D3DRS_ZENABLE,1);
	}
  }
  */
if (opt.D3D.Listva==1)
{
	if (ListvaT))
	{
		return S_OK;
	}
}

if (opt.D3D.Svet)
{
	if ((NumVertices == 12601) && (primCount == 20800))
	{
		pDevice->SetRenderState(D3DRS_ZENABLE,0);
		pDevice->SetPixelShader(NULL);
		pDevice->SetPixelShader(psTemp);
		pDevice->SetPixelShaderConstantF(0,SHNull,1);
       pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
       pDevice->SetRenderState(D3DRS_ZENABLE,1);
	   pDevice->SetPixelShader(NULL);
		pDevice->SetPixelShader(psTemp);
		pDevice->SetPixelShaderConstantF(0,SHNull,1);
	}
}

if(opt.D3D.pvp) // PvP
{
	/*
	if(htani_DJINS || htani_BL || perchatki || kurtka1 || kurtka2 || kurtka3 || kurtka_HORVAT || kurtka_CHAK || telogreika || specovka 
		|| htani_LONGI || htani_PARTIZAN || htani_tah_horvat || htani_HAKI || htani_HIZ || htani_CHAK || kostum_MARS || kostum_UGOR
		|| kostum_PACHKA || KB_ORDEN_SVOBOD || KB_ODINOCHKI || KB_KK || KB_atom || KB_himer || KB_slince || KB_VOENSTAL
		|| botinki || hapka_KOZIR || hapka_BERET || hapka_VYAZANKA || hlem_VIKING || HIZ_OCHKARIK || maska_bandito || maska_JABA
		|| maska_GRAFFITI || maska_INGLISH || face1 || face2 || face3 || weapons_PM || weapons_MP5 || weapons_drob || weapons_MOSIN
		|| weapons_M4 || weapons_AK107 || weapons_G36 || wa2000 || weapon_GROZA || glock18 || weapon_MK48 | weapon_TT || weapon_RPG
		|| weapon_SVD || weapon_SIG_DONAT || weapon_DIGL || weapon_AK74 || weapon_AK47 || weapon_FNFAL || BERX_HIZ || dragun || tah 
		|| hpinat || krisa || bron_vorot || arm_rukzak || rukzak_odinochki || rukzak_KOLOBOK || rukzak_sekvoia || rukzak_PARTIZAN
		|| bron_KAIZER || bron_hkurka || sandal || omlet || bron_BL || bron_CHAK || bron_FAUNA || halat || шакал_куртка || КБ_свобода
		|| ниндзя || шлем_ВЛ)
		*/
	    if (PersT))
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.pvp==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.pvp==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.pvp==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.pvp==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.pvp==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.pvp==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.pvp==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.pvp==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.pvp==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.pvp==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.pvp==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.pvp==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.pvp==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.pvp==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.pvp==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.pvp==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.pvp==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.pvp==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
	}
}

if(opt.D3D.Mob) // PvE
{
	//if(mutant_krisa || mutant_sobaka || KABAN || mutant_studen || mutant_domovoi || mutant_Pauk || mutant_verla 
	//	|| mutant_otverj || mutant_miha || mutant_blyak || mutant_brutor || Бес)
	if (MobT))
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Mob==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Mob==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Mob==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Mob==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Mob==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Mob==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Mob==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Mob==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Mob==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Mob==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Mob==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Mob==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Mob==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Mob==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Mob==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Mob==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Mob==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Mob==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);

	}
}

if(opt.D3D.Art) //арты
{
	if ((Vez || Stab || marevo_provodnik || Poduhka || ekran || Hit || Antigrav||Resin))
{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Art==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Art==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Art==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Art==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Art==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Art==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Art==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Art==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Art==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Art==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Art==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Art==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Art==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Art==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Art==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Art==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Art==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Art==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
	}
}



if (opt.D3D.Drop) // Дроп
{
	if (lajka)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Drop==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Drop==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Drop==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Drop==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Drop==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Drop==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Drop==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Drop==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Drop==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Drop==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Drop==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Drop==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Drop==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Drop==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Drop==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Drop==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Drop==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Drop==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
	}
}

if (opt.D3D.Nichki) // Нычки
{
	if (yashikT)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Nichki==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Nichki==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Nichki==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Nichki==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Nichki==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Nichki==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Nichki==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Nichki==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Nichki==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Nichki==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Nichki==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Nichki==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Nichki==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Nichki==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Nichki==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Nichki==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Nichki==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Nichki==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
	}
}

if (opt.D3D.Travi) // Травы
{
	if (travi)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
if(opt.D3D.Travi==1)pDevice->SetTexture(0,Yellow);
if(opt.D3D.Travi==2)pDevice->SetTexture(0,DeepSkyBlue);
if(opt.D3D.Travi==3)pDevice->SetTexture(0,Purple);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE, 1);
if(opt.D3D.Travi==1)pDevice->SetTexture(0,Yellow);
if(opt.D3D.Travi==2)pDevice->SetTexture(0,DeepSkyBlue);
if(opt.D3D.Travi==3)pDevice->SetTexture(0,Purple);
	}
}

if (opt.D3D.Grib) // грибы
{
	if (gribsT)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Grib==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Grib==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Grib==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Grib==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Grib==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Grib==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Grib==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Grib==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Grib==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.D3D.Grib==1)pDevice->SetPixelShaderConstantF(0,SHWhite,1);
if (opt.D3D.Grib==2)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
if (opt.D3D.Grib==3)pDevice->SetPixelShaderConstantF(0,SHOrange,1);
if (opt.D3D.Grib==4)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
if (opt.D3D.Grib==5)pDevice->SetPixelShaderConstantF(0,SHSalat,1);
if (opt.D3D.Grib==6)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
if (opt.D3D.Grib==7)pDevice->SetPixelShaderConstantF(0,SHRed,1);
if (opt.D3D.Grib==8)pDevice->SetPixelShaderConstantF(0,SHRose,1);
if (opt.D3D.Grib==9)pDevice->SetPixelShaderConstantF(0,SHAqua,1);
	}
}




if ((opt.D3D.WireFrame)||(GetAsyncKeyState(VK_CAPITAL))) // WireFrame
{

		{
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
			}
			else
			{
		{
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
}

if (opt.Logger.logerpc==1) 
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber-opt.Logger.PCstep;
}
///////////////////////////////
	if (primCount == opt.Logger.CountNumber)

	{
//if (opt.Logger.logerpc==3){return 0;}
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if (opt.Logger.logerpc==2) 
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber-opt.Logger.PCstep;
}
///////////////////////////////
	if (primCount >= opt.Logger.CountNumber)// Logger pcount>Значения

	{
//if (opt.Logger.logerpc==3){return 0;}
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if (opt.Logger.logerpc==3)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber-opt.Logger.PCstep;
}
///////////////////////////////
	if (primCount >= opt.Logger.CountNumber)// pcount <Значения
	{
//if (opt.Logger.logerpc==3){return 0;}
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if (opt.Logger.logerpc==4)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.CountNumber=opt.Logger.CountNumber-opt.Logger.PCstep;
}
///////////////////////////////
	if (primCount != opt.Logger.CountNumber)// pcoun=всё кроме=значения
	{
//if (opt.Logger.logerpc==3){return 0;}
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerpc)pDevice->SetPixelShaderConstantF(0,SHRed,1);
//if (opt.Logger.logerpc==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}


if (opt.Logger.VerticsNumber==1)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (NumVertices == opt.Logger.VerticsNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}


else if (opt.Logger.VerticsNumber==2)
{

///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (NumVertices <= opt.Logger.VerticsNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if (opt.Logger.VerticsNumber==3)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (NumVertices >= opt.Logger.VerticsNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if (opt.Logger.VerticsNumber==4)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.VerticsNumber=opt.Logger.VerticsNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (NumVertices != opt.Logger.VerticsNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logervn)pDevice->SetPixelShaderConstantF(0,SHGreen,1);
//if (opt.Logger.logervn==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}


if (opt.Logger.logerstr==1)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (m_Stride == opt.Logger.StrideNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if (opt.Logger.logerstr==2)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (m_Stride <= opt.Logger.StrideNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

if (opt.Logger.logerstr==3)
{
///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (m_Stride >= opt.Logger.StrideNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

if (opt.Logger.logerstr==4)
{

///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StrideNumber=opt.Logger.StrideNumber-opt.Logger.PCstep;
}
///////////////////////////////
if (m_Stride != opt.Logger.StrideNumber)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logerstr)pDevice->SetPixelShaderConstantF(0,SHYellow,1);
//if (opt.Logger.logerstr==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}


if(opt.Logger.logersi==1)
{

///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex-opt.Logger.PCstep;
}
///////////////////////////////
if (startIndex == opt.Logger.StartIndex)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

else if(opt.Logger.logersi==2)
{

///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex-opt.Logger.PCstep;
}
///////////////////////////////
if (startIndex <= opt.Logger.StartIndex)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

if(opt.Logger.logersi==3)
{

///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex-opt.Logger.PCstep;
}
///////////////////////////////
if (startIndex >= opt.Logger.StartIndex)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}

if(opt.Logger.logersi==4)
{

///////////////////////////////
if(GetAsyncKeyState(VK_UP)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex+opt.Logger.PCstep;
}
if(GetAsyncKeyState(VK_DOWN)&1)
{
	opt.Logger.StartIndex=opt.Logger.StartIndex-opt.Logger.PCstep;
}
///////////////////////////////
if (startIndex != opt.Logger.StartIndex)
	{
pDevice->SetRenderState(D3DRS_ZENABLE,0);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE,1);
pDevice->SetPixelShader(NULL);
pDevice->SetPixelShader(psTemp);
if (opt.Logger.logersi)pDevice->SetPixelShaderConstantF(0,SHBlue,1);
//if (opt.Logger.logersi==2)pDevice->SetPixelShaderConstantF(0,SHSer,1);
	}
}


if(GetAsyncKeyState(VK_DELETE)&1)
{
	opt.Logger.CountNumber=0;
	opt.Logger.StartIndex=0;
	opt.Logger.StrideNumber=0;
	opt.Logger.VerticsNumber=0;
}

//char key1;
//GetKeyNameText(24,(LPSTR)(char)key,19);
//key1=key;
//key =getch();
//char key1[MAX_PATH];
//sprintf(key1,"key=%d",key);
//if (key==(!0))
//{
//	MessageBox(0,(LPSTR)(char)key,"",MB_OK);
//}

//const DWORD Addres_TUSA=				0x5D17EB;
const DWORD Addres_TUSA=				0x5CEF7B;
	  //_____(Тусовка мобов)____//
if (GetAsyncKeyState(VK_END)&1) {opt.memhack.TUSA_MOB=(!opt.memhack.TUSA_MOB);}
if(opt.memhack.TUSA_MOB==1)
{
//DetourCreate((PBYTE)Addres_TUSA,(PBYTE)TUSA_MOB_on,5);//Вкл
}
else
{
//DetourCreate((PBYTE)Addres_TUSA,(PBYTE)TUSA_MOB_off,5);//Выкл
}

//////////////////////////////////////////////////////////////////////////////////
DWORD FrezeH = 0x563791;
DWORD Camera = 0x849182;
DWORD WallNot = 0x9B7E68;
DWORD Adr_WRNC1=0x004332A3; 
DWORD Adr_WRNC2=0x00433B60;

if(GetAsyncKeyState(VK_DIVIDE)&1){opt.memhack.frezeHeigth=(!opt.memhack.frezeHeigth);}
if(GetAsyncKeyState(VK_NUMPAD4)&1){opt.memhack.WallShot=(!opt.memhack.WallShot);}

if(opt.memhack.frezeHeigth==1)MEMwrite((void *)(FrezeH),(void *)"\x90\x90\x90",3);
if(opt.memhack.frezeHeigth==0) MEMwrite((void *)(FrezeH),(void *)"\x89\x51\x24",3);

if(opt.memhack.Camera==1)MEMwrite((void *)(Camera),(void *)"\xEB\x0D",2);
if(opt.memhack.Camera==0) MEMwrite((void *)(Camera),(void *)"\x7B\x0D",2);

if (opt.memhack.WallShot==0) MEMwrite((void *)(WallNot),(void *)"\x75\x03",2);
if (opt.memhack.WallShot==1) MEMwrite((void *)(WallNot),(void *)"\x74\x03",2);

if (opt.memhack.Accuracy_addr==244||opt.memhack.Accuracy_addr==116)
{
	if (opt.memhack.Accuracy==0)
	{
		MEMwrite((void *)(opt.memhack.AccuracyVoll+0x13E),(void *)"\xF4",1);
		DetourCreate((PBYTE)Adr_WRNC1,(PBYTE)WRNC_on1,6);//Вкл
		DetourCreate((PBYTE)Adr_WRNC2,(PBYTE)WRNC_on2,6);//Вкл
	}
	if (opt.memhack.Accuracy==1)
	{
		MEMwrite((void *)(opt.memhack.AccuracyVoll+0x13E),(void *)"\x74",1);
		DetourCreate((PBYTE)Adr_WRNC1,(PBYTE)WRNC_off1,6);//Выкл
		DetourCreate((PBYTE)Adr_WRNC2,(PBYTE)WRNC_off2,6);//Выкл
	}
}



     // CloseHandle(HandleWindow);
  
 



///////////////// ПОИНТЕР И ОФФСЕТ//////////////////////////////
/*
DWORD WINAPI HackPointBlank(LPVOID param)
{
DWORD Module=NULL;
while(Module==NULL)
Module=(DWORD)GetModuleHandleA("pointblank.i3exec"); //модуль
DWORD Pointer_Room=(DWORD)Module+0x00000; //поинт

int Address_funkc;

while(1)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++//
if(funkc==1)//функция
{
ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) Pointer_Room, &Address_funkc, sizeof(Address_funkc), NULL);
MEMwrite((void *)(Address_funkc + 0x0000),(void *)"\xFF" , 1); //где 0x|0000| - оффсет , где "\x|FF|" - байт на что менять
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++//
Sleep(500);
}
*/


/*
if(opt.glavnay.Jump==0)DetourCreate((PBYTE)ADDRES_hook,(PBYTE)hook_OFF,5);
if(opt.glavnay.Jump==1)DetourCreate((PBYTE)ADDRES_hook,(PBYTE)hook_ON,5);

if(GetAsyncKeyState(VK_INSERT)&1)
{
HMODULE StalkerOnline = GetModuleHandleA("StalkerOnline.exe");
DWORD adress = (BYTE)StalkerOnline+0x00CEAA38;
DWORD adress2 = adress+0xA8;
DWORD adress3 = adress2+74;
DWORD ptr1= 0xA8;
DWORD ptr2=0x74;
	
/*
ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (adress), &bufer, sizeof(bufer), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (bufer+0xA8), &bufer, sizeof(bufer), NULL);
ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (bufer+0x74), &bufer, sizeof(bufer), NULL);
WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (bufer),&bufer, sizeof(bufer),NULL);
*/
//MEMwrite((void *)adress3,(void*)(PBYTE)"\xFF",1);
//MEMwrite((void *)(adress),(void*)(PBYTE)"\xFF",2);
//}
/*
HMODULE StalkerOnline = GetModuleHandleA("StalkerOnline.exe");
DWORD Zpos1 = (BYTE)GetModuleHandleA("StalkerOnline.exe")+0x00C8DF20;
DWORD Zpos2 = Zpos1+0x50;
DWORD Zpos3 = Zpos2+0x24;
char Zpos[100];
sprintf(Zpos,"Z possition = %d",Zpos3);
*/
//MEMwrite((void *)(Zpos3),(void*)(PBYTE)"\x74\x07",2);



//procedure WTeleportFB(bForward:boolean);

// unsigned  HandleWindow;
/*
 int Possition =1;
 unsigned  write;
 DWORD ipbuf;
 float X,Y,X_,Y_,Asimut;
 float Heigth,Vertical;
 const float pi=3.1415926535f;
//const 
  const DWORD base_addr=0x0108DF20;
  const DWORD H_offset=0x24;
  const DWORD X_offset=0x20;
  const DWORD Y_offset=0x28;
  const DWORD Asimut_offset=0x2C;
  const DWORD Vertical_offset=0x30;


{
 	//HMODULE HandleWindow = GetModuleHandleA("StalkerOnline.exe");
 // HandleWindow == OpenProcess(PROCESS_ALL_ACCESS,false,OpenProcess("StalkerOnline.exe"));
  //if HandleWindow<>0 then
if (Possition = 1)
  {

	  //ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) Pointer, &ipbuf, sizeof(ipbuf), BytesCount);   
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (base_addr), &ipbuf, sizeof(ipbuf), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+0x50), &ipbuf, sizeof(ipbuf), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+X_offset), &X, sizeof(X), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+Y_offset), &Y, sizeof(Y), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+Asimut_offset), &Asimut, sizeof(Asimut), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+Vertical_offset), &Vertical, sizeof(Vertical), NULL);
	  
	  char Zpos[100];
	  sprintf(Zpos,"Heigth possition = %d",Heigth);
if(GetAsyncKeyState(VK_DELETE)&1) 
{
	MessageBox(0,Zpos,"Приватная версия!",MB_OK);
}

	  
      Heigth==Heigth+pi/18;

      if abs(Asimut)<=pi/2 then X_==Asimut
      else if Asimut>=0 then X_==pi/2-(abs(Asimut)-pi/2)
      else                   X_==-1*pi/2+(abs(Asimut)-pi/2);
      if abs(Asimut)<=pi/2 then {
               if X_>0 then Y_==pi/2-X_ else Y_==pi/2+X_;
	  } else if X_>0 then Y_==X_-pi/2 else Y_==-1*(X_+pi/2);

      if not bForward then {
      X_==X_*-1;
	  Y_==Y_*-1;
      }
      X==X+X_/5;
      Y==Y+Y_/5;

      Sleep(10);
      WriteProcessMemory(HandleWindow, Pointer(ipbuf+H_offset), &Heigth, sizeof(Heigth),write);
      Sleep(20);
      WriteProcessMemory(HandleWindow,Pointer(ipbuf+X_offset),&X, sizeof(X),write);
      WriteProcessMemory(HandleWindow,Pointer(ipbuf+Y_offset),&Y, sizeof(Y),write);
	  
     // CloseHandle(HandleWindow);
  }
}
*/
/*
int pectator = 1;
int gagaga = 1;
//________(GM Спекатор)_________//
DWORD GM = 0x473a13;
if(pectator==0)
{
MEMwrite((void *)(GM),(void*)(PBYTE)"\x74\x07",2);
}else{
MEMwrite((void *)(GM),(void*)(PBYTE)"\x75\x07",2);
}

DWORD PointerGM = 0x48A2A5;//48A285;
 if(gagaga==1)MEMwrite((void *)(PointerGM),(void *)"\x90\x90",2);
 if(gagaga==0)MEMwrite((void *)(PointerGM),(void *)"\x75\x07",2);


///////////

//===минирование===//
DWORD C41= 0x8F1A34; // 8D58E4; 
if(opt.glavnay.minirovanie)
{
MEMwrite((void *)(C41),(int*)(PBYTE)"\x00\x00\xA0\x00",4);}else
{
MEMwrite((void *)(C41),(int*)(PBYTE)"\x00\x00\xA0\x40",4);}
//---------------разминирование-----------------------------------///
DWORD C42= 0x8FE568;
if(opt.glavnay.minirovanie1)
{
MEMwrite((void *)(C42),(int*)(PBYTE)"\x00\x00\xE0\x00",4);}else
{
MEMwrite((void *)(C42),(int*)(PBYTE)"\x00\x00\xE0\x40",4);}



//______(WallShot)_____//
DWORD WallShot = 0x62A8AD; //
if(opt.glavnay.WallShot)
{
if(GetAsyncKeyState(VK_SHIFT))
{
MEMwrite((void *)(WallShot),(void*)(PBYTE)"\x90\x90",2);
}else{
MEMwrite((void *)(WallShot),(void*)(PBYTE)"\x75\x1F",2);
}
}else{
MEMwrite((void *)(WallShot),(void*)(PBYTE)"\x75\x1F",2);
}

DWORD antikik = 0x725C53;//
if (opt.glavnay.nevedimka==0)
{
MEMwrite((void*)(antikik),(void*)"\x0F\ x85",2);
}
if (opt.glavnay.nevedimka==1)
{
MEMwrite((void*)(antikik),(void*)"\x0F\ x84",2);
}

DWORD Подбор_Пух = 0x6430C9;//
if(opt.glavnay.ESP)
{
MEMwrite((void *)(Подбор_Пух),(void*)(PBYTE)"\x90\x90",2);
}else{
MEMwrite((void *)(Подбор_Пух),(void*)(PBYTE)"\x76\x1A",2);
}

//________(GM Спекатор)_________//
DWORD GM = 0x473a13;
if(opt.glavnay.spectator==0)
{
MEMwrite((void *)(GM),(void*)(PBYTE)"\x74\x07",2);
}else{
MEMwrite((void *)(GM),(void*)(PBYTE)"\x75\x07",2);
}




//------------------Показ ников и хп--------------------// обновил
//int AHPN = 0x690006;   //...
int HP1  = 0x66488F;//
if(opt.D3D.ESP==0)
{
//MEMwrite((void*)(AHPN),(void*)"\x0F\x84\x8E\x00\x00\x00",6);
MEMwrite((void*)(HP1),(void*)"\x0F\x85\x51\x01\x00\x00",6);
}
if(opt.D3D.ESP==1)
{
//MEMwrite((void*)(AHPN),(void*)"\x90\x90\x90\x90\x90\x90",6);
MEMwrite((void*)(HP1),(void*)"\x90\x90\x90\x90\x90\x90",6);
}
//----------------Показ ников и хп--------------------//

int HP3  = 0x691E96;//
if(opt.D3D.ESP_new==0)
{
MEMwrite((void*)(HP3),(void*)"\x0F\x85\x51\x01\x00\x00",6);
}

if(opt.D3D.ESP_new==1)
{
MEMwrite((void*)(HP3),(void*)"\x90\x90\x90\x90\x90\x90",6);
}
////////////////////////////////////////////


int HP4  = 0x662A8F;
if(opt.D3D.ESP==0)
{
MEMwrite((void*)(HP4),(void*)"\x0F\x84\x8E\x00\x00\x00",6);
}

if(opt.D3D.ESP==1)
{
MEMwrite((void*)(HP4),(void*)"\x90\x90\x90\x90\x90\x90",6);
}



//_____(Анти-Одача)____//
if(opt.glavnay.Testa)
{
DetourCreate((PBYTE)ADDRES_Antioda_1,(PBYTE)Antioda_1_on,5);//Вкл
DetourCreate((PBYTE)ADDRES_Antioda_2,(PBYTE)Antioda_2_on,5);//Вкл
}
else
{
DetourCreate((PBYTE)ADDRES_Antioda_1,(PBYTE)Antioda_1_off,5);//Выкл
DetourCreate((PBYTE)ADDRES_Antioda_2,(PBYTE)Antioda_2_off,5);//Выкл
}

///_________(Купоны 40%)__________//
DWORD Cupon = 0x639012; //; "int __thiscall WeaponBase::GetMaxBullet"... 5 блоков вниз //
if(opt.glavnay.Купон==0){
MEMwrite((void *)(Cupon),(int*)(PBYTE)"\x0F\x84\x80\x01\x00\x00", 6);
}
if(opt.glavnay.Купон==1){
MEMwrite((void *)(Cupon),(int*)(PBYTE)"\x90\x90\x90\x90\x90\x90", 6);
}

//_______Невидимая Граната________/////
DWORD xgrena = 0x638D33;
if (opt.glavnay.netgrenu==1)
{
MEMwrite((void *)(xgrena),(void *)"\x90\x90\x90",3);
}
if (opt.glavnay.netgrenu==0)
{
MEMwrite((void *)(xgrena),(void *)"\xD9\x45\xF8",3);// 545            638DC9
}


//===убиваем всех с грены и подбор====//
DWORD KillGrenage = 0x414C3D;
if(opt.glavnay.granata)
{
if(GetAsyncKeyState(VK_LCONTROL))
{
MEMwrite((void*)(KillGrenage),(void*)"\xD9\x45\xFF",3);
}else{
MEMwrite((void*)(KillGrenage),(void*)"\xD9\x45\xFC",3);
}
}

//________(Купоны 110 ХП)_______//
DWORD HP110 = 0x440F97;//440F97
if (opt.glavnay.xp3==1)
{
MEMwrite((void*)(HP110),(void *) "\x75",1);
}else {
MEMwrite((void*)(HP110),(void *) "\x74",1);
}


//________(Набор купонов)_______//
DWORD Cupon_nab = 0x639012;
DWORD HP_nab= 0x440F97;//440F97
if (opt.glavnay.nabor==1)
{
MEMwrite((void*)(HP_nab),(void *) "\x75",1);
MEMwrite((void *)(Cupon_nab),(int*)(PBYTE)"\x90\x90\x90\x90\x90\x90", 6);
}else {
MEMwrite((void*)(HP_nab),(void *) "\x74",1);
MEMwrite((void *)(Cupon_nab),(int*)(PBYTE)"\x0F\x84\x80\x01\x00\x00", 6);
}








 //___(Прижки в Вздух)___//
DWORD Prizhok4 = 0x5c7533; 
DWORD Prizhok5 = 0x5c7557; 
DWORD Prizhok6 = 0x5c75e7;
if (opt.glavnay.zoomm==0)
{
MEMwrite((void*)(Prizhok4),(void*)"\x74",1);
MEMwrite((void*)(Prizhok5),(void*)"\x74",1);
MEMwrite((void*)(Prizhok6),(void*)"\x75\x2F",2);
}
if (opt.glavnay.zoomm==1)
{
MEMwrite((void*)(Prizhok4),(void*)"\xEB",1);
MEMwrite((void*)(Prizhok5),(void*)"\xEB",1);
MEMwrite((void*)(Prizhok6),(void*)"\x90\x90",2);
}
if (opt.glavnay.zoomm==2)
{
DetourCreate((PBYTE)Addres_Up_Jump, (PBYTE)Up_Jump_On, 5); 
if(opt.glavnay.Test==2) jumpv=1;
MEMwrite((void*)(Prizhok4),(void*)"\xEB",1);
MEMwrite((void*)(Prizhok5),(void*)"\xEB",1);
MEMwrite((void*)(Prizhok6),(void*)"\x90\x90",2);
}

if (opt.glavnay.zoomm==3)
{
DetourCreate((PBYTE)Addres_Up_Jump, (PBYTE)Up_Jump_On, 5); 
if(opt.glavnay.Test==3) jumpv=2;
MEMwrite((void*)(Prizhok4),(void*)"\xEB",1);
MEMwrite((void*)(Prizhok5),(void*)"\xEB",1);
MEMwrite((void*)(Prizhok6),(void*)"\x90\x90",2);
}
//___(Анлим Патроны)___//
if(opt.glavnay.ammo == 1)DetourCreate((PBYTE)ADDRES_Max_Bullet, (PBYTE)Max_Bullet_on, 5); //Вкл
if(opt.glavnay.ammo == 0)DetourCreate((PBYTE)ADDRES_Max_Bullet, (PBYTE)Max_Bullet_off, 5);//Выкл


//____(Длиный Нож)_____
if(opt.glavnay.assasa==1)DetourCreate((PBYTE)ADDRES_Knife,(PBYTE)knife_on,5); //Вкл
if(opt.glavnay.assasa==0)DetourCreate((PBYTE)ADDRES_Knife,(PBYTE)knife_off,5);//Выкл
*/


	if(opt.glavnay.OptionsSave==1)
{

WritePPI(DopMenu_WH_EN,"opt.D3D.pvp",opt.D3D.pvp,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.Mob",opt.D3D.Mob,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.Art",opt.D3D.Art,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.Drop",opt.D3D.Drop,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.Nichki",opt.D3D.Nichki,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.Travil",opt.D3D.Travi,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.Grib",opt.D3D.Grib,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"opt.D3D.cross",opt.D3D.cross,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"Листва",opt.D3D.Listva,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu_WH_EN,"Ночн_Свет",opt.D3D.Svet,GetDirFile("Stalker_option.ini"));

WritePPI(DopMenu3,"Прыжок",opt.memhack.Jump,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu3,"Прыжок1",opt.memhack.Jump1,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu3,"Точность",opt.memhack.Accuracy,GetDirFile("Stalker_option.ini"));
WritePPI(DopMenu3,"Камера",opt.memhack.Camera,GetDirFile("Stalker_option.ini"));

opt.glavnay.OptionsSave=0;
}
	if(opt.glavnay.OptionsLoad==1)
{

opt.D3D.pvp=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.pvp",opt.D3D.pvp,GetDirFile("Stalker_option.ini"));

opt.D3D.Mob=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.Mob",opt.D3D.Mob,GetDirFile("Stalker_option.ini"));
opt.D3D.Art=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.Art",opt.D3D.Art,GetDirFile("Stalker_option.ini"));
opt.D3D.Drop=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.Drop",opt.D3D.Drop,GetDirFile("Stalker_option.ini"));
opt.D3D.Nichki=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.Nichki",opt.D3D.Nichki,GetDirFile("Stalker_option.ini"));
opt.D3D.Travi=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.Travi",opt.D3D.Travi,GetDirFile("Stalker_option.ini"));
opt.D3D.Grib=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.Grib",opt.D3D.Grib,GetDirFile("Stalker_option.ini"));
opt.D3D.cross=GetPrivateProfileIntA(DopMenu_WH_EN,"opt.D3D.cross",opt.D3D.cross,GetDirFile("Stalker_option.ini"));
opt.D3D.Listva=GetPrivateProfileIntA(DopMenu_WH_EN,"Листва",opt.D3D.Listva,GetDirFile("Stalker_option.ini"));
opt.D3D.Svet=GetPrivateProfileIntA(DopMenu_WH_EN,"Ночн_Свет",opt.D3D.Svet,GetDirFile("Stalker_option.ini"));

opt.memhack.Jump=GetPrivateProfileIntA(DopMenu3,"Прыжок",opt.memhack.Jump,GetDirFile("Stalker_option.ini"));
opt.memhack.Jump1=GetPrivateProfileIntA(DopMenu3,"Прыжок1",opt.memhack.Jump1,GetDirFile("Stalker_option.ini"));
opt.memhack.Accuracy=GetPrivateProfileIntA(DopMenu3,"Точность",opt.memhack.Accuracy,GetDirFile("Stalker_option.ini"));
opt.memhack.Camera=GetPrivateProfileIntA(DopMenu3,"Камера",opt.memhack.Camera,GetDirFile("Stalker_option.ini"));
opt.glavnay.OptionsLoad=0;
}
	if(opt.glavnay.OptionsResset==1)
{

opt.D3D.pvp=0;
opt.D3D.Mob=0;
opt.D3D.Art=0;
opt.D3D.Drop=0;
opt.D3D.Nichki=0;
opt.D3D.Travi=0;
opt.D3D.Grib=0;
opt.D3D.cross=0;
opt.D3D.Listva=0;
opt.D3D.Svet=0;
opt.D3D.WireFrame=0;
////////////////
opt.memhack.Jump=0;
opt.memhack.Jump1=0;
opt.memhack.Accuracy=0;
opt.memhack.Camera=0;
opt.memhack.TUSA_MOB=0;
opt.memhack.WallShot=0;
opt.memhack.frezeHeigth=0;
//**************************//
opt.glavnay.OptionsResset=0;
}


return pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex,  MinVertexIndex,  NumVertices, startIndex, primCount);
}
/*
HRESULT GenerateShader( IDirect3DDevice9 *pDevice, IDirect3DPixelShader9 **pShader, float r, float g, float b, bool setzBuf )
{
    char szShader[ 256 ];
    ID3DXBuffer *pShaderBuf = NULL;

    sprintf( szShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", r, g, b, 1.0f );
    if( D3DXAssembleShader( szShader, sizeof( szShader ), NULL, NULL, 0, &pShaderBuf, NULL ) == D3D_OK )
        pDevice->CreatePixelShader( ( const DWORD* )pShaderBuf->GetBufferPointer(), pShader );
    else
        return E_FAIL;

    return S_OK;
}
*/
	char *VERSPX1 = (char*) calloc(200, sizeof(char));
	char *VERSPX2 = (char*) calloc(200, sizeof(char));
	char *VERSPX = (char*) calloc(200, sizeof(char));
	char STRASM [256];
bool asd=false;
void initp( LPDIRECT3DDEVICE9 pDevice )
{
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);

	sprintf( STRASM, "ps_%d_%d\nmov oC0,c0\n",D3DSHADER_VERSION_MAJOR(caps.PixelShaderVersion),D3DSHADER_VERSION_MINOR(caps.PixelShaderVersion));

	LPD3DXBUFFER psbTemp=NULL;

    if (D3DXAssembleShader(STRASM,sizeof(STRASM),NULL,NULL,0,&psbTemp,NULL)==D3D_OK)
	{
    pDevice->CreatePixelShader((DWORD*)psbTemp->GetBufferPointer(),&psTemp);
	asd=true;
	}
}
typedef HRESULT	( WINAPI* oEndScene )( LPDIRECT3DDEVICE9 pDevice );
oEndScene pEndScene;

HRESULT APIENTRY myEndScene( LPDIRECT3DDEVICE9 pDevice )
{

	if (!asd)
	{
		initp(pDevice);
	}

if(opt.D3D.cross)
{
D3DVIEWPORT9 viewP;
pDevice->GetViewport(&viewP);
DWORD ScreenCenterX = viewP.Width / 2;
DWORD ScreenCenterY = viewP.Height / 2;

D3DRECT rec16 = {ScreenCenterX-5, ScreenCenterY, ScreenCenterX+ 5, ScreenCenterY+1};
D3DRECT rec17 = {ScreenCenterX, ScreenCenterY-5, ScreenCenterX+ 1,ScreenCenterY+5};
pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(0.0, 1.0, 1.0, 1.0), 0,  0 );
pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(0.0, 1.0, 1.0, 1.0), 0,  0 );  
}

	//memhack();

	PostReset(pDevice);
	Menu.ShowMenu(pDevice);

    PreReset(pDevice);
return pEndScene( pDevice );}

HRESULT APIENTRY Start_key(LPDIRECT3DDEVICE9 pDevice)
{
while(1)
{

if(opt.glavnay.ButtonTestEx){ExitProcess(0);}

if(GetAsyncKeyState(VK_F12)){ExitProcess(0);}

Sleep(1);
}
}

int HookpDevice(void)
{
DWORD*vtbl=0;
DWORD hD3D9=(DWORD)LoadLibraryA("d3d9.dll");
DWORD table=FindPattern(hD3D9,0x128000,(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86","xx????xx????xx");
memcpy(&vtbl,(void*)(table+2),4);
pEndScene=(oEndScene)DetourCreate((PBYTE)vtbl[42],(PBYTE)myEndScene,7);
//pDrawIndexedPrimitive=(oDrawIndexedPrimitive)DetourCreate((PBYTE)vtbl[82],(PBYTE)myDrawIndexedPrimitive,5);
return 0;
}


void MainProc()
{
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)HookpDevice,NULL,NULL,NULL);  
CreateThread(0,0,(LPTHREAD_START_ROUTINE)Start_key,0,0,0);
ExitThread(hExitThread);
}


void StartHookpDevice()//
{
while(1)
{
if(GetAsyncKeyState(VK_HOME)&1)
{
MainProc(); 
}
}
}


BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hDll);
if (dwReason==DLL_PROCESS_ATTACH)
{
DisableThreadLibraryCalls(hDll);
//link();
//EraseHeaders(hDll);
//HideModule(hDll);

CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)MainProc,NULL,NULL,NULL);
}
return TRUE;
}
