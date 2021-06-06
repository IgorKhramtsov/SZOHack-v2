#include "stdafx.h"
#include "cFont.h"

#include "d3dx9core.h"//////

#pragma once


#define ITEM_ARRAY 64 


#define MC_MAXX					    (X+WIDTH)         
#define MC_MAXX1					(X1+WIDTH) 
#define MC_MAXX2					(X2+WIDTH) 
#define MC_MAXX3				    (X3+WIDTH) 

#define MC_FCTR(x,y)			    ((x+y)/2)												
#define MC_ITEMY(index)			    (Y+(index*I_SPC)+T_SPC+(T_SPC/2))
#define MC_ITEMY1(index)			(Y1+(index*I_SPC)+T_SPC+(T_SPC/2))						
#define MC_ITEMY2(index)			(Y2+(index*I_SPC)+T_SPC+(T_SPC/2))
#define MC_ITEMY3(index)			(Y3+(index*I_SPC)+T_SPC+(T_SPC/2))

#define MC_MSY					    (Y)							
#define MC_MSY1					    (Y1+T_SPC+(T_SPC/2))	
#define MC_MSY2					    (Y2+T_SPC+(T_SPC/2))	
#define MC_MSY3					    (Y3)

INT WINAPI SkanBYTE();



//--------Класс Menu

class cMenu
{

public:
	struct sitem
	{
			char title[50];		
			char state[50];	
			int	 type;			
			int  max;			
			int  no;			
			int	 *val;		
	} items[ITEM_ARRAY];


	enum I_TYPES{
		T_TEXT = 0,
		T_ITEM = 1,
		T_CAT  = 2
	};

	CD3DFont *font;
	int  X,X1,X2,X3;
	int  Y,Y1,Y2,Y3;
	POINT  mofs;			
	POINT  mpos;			
	int   M_DRAG;		
	int   WIDTH;		
	int   I_OFS,S_OFS;	
	int   I_SPC,I_TSPC;  
	int   T_SPC,F_SPC;	
	int   NO;			
	int  I_CUR;		
	bool  SHOW;		
	bool  INIT;	
	int   ABOR;			
	int   BTEX,BDIR;		
	char*	fps[5];



//---Прототипы
    BOOL IsInBox(int x,int y,int w,int h);
	void Draw_Button_Test(int x ,int y , int w , int h ,bool &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice);
	void Draw_ColorChams_4(int x ,int y ,char *Text,int &funkc_color_hams ,LPDIRECT3DDEVICE9 pDevice);
	void Draw_ColorChams_3(int x ,int y ,char *Text,int &funkc_color_hams ,LPDIRECT3DDEVICE9 pDevice);





	void TrialVersions(LPDIRECT3DDEVICE9 pDevice);

	/////////////МЕНЮ//////////////
	void	Draw_Button_Menu(int x ,int y , int w , int h ,bool &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice);
	void	Draw_Button_TestWH(int x ,int y , int w , int h ,int &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice);
	void	Draw_Button_TestTEXT(int x ,int y , int w , int h ,bool &Var ,char *Button_Text,char *Info,LPDIRECT3DDEVICE9 pDevice);

	void	Draw_Button_Teleport(int x ,int y ,int &Var,int &VAR ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice);

	void    Draw_Button_Scrol(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice);
	void    Draw_Button_ScrolCH(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice);
	void	Draw_Button_ScrolLG(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice);
	void    Scroll(float x,float y,float w,float h,int &GetCurrent ,char* Text,D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice);
	void	MapColor(int x,int y,int &R_col,int &G_col,int &B_col,LPDIRECT3DDEVICE9 pDevice);

	void    Draw_Scroll(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice);
	void 	DrawText( int x, int y, int w, int h, D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice);	
	void 	DrawMouse(int x, int y,LPDIRECT3DDEVICE9 pDevice);
	char*	oprintf (const char *fmt, ...);
	void 	PostReset(LPDIRECT3DDEVICE9 pDevice);
	void 	PreReset(void);
	void 	ShowMenu(LPDIRECT3DDEVICE9 pDevice);
	void 	Menu_1ShowMenu(LPDIRECT3DDEVICE9 pDevice);
	void    Menu_3ShowMenu(LPDIRECT3DDEVICE9 pDevice);
	void	Draw_Button(int x ,int y , int w , int h ,int &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice);
	void	ShowBox(LPDIRECT3DDEVICE9 pDevice);
    char*	TIME(void);
	void    DrawBorder(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice);
	void    DrawBox( int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice);
	void 	acat(char *title, char *states, int *var);
	void 	aitem(char *title, char *states,int *var, int show, int when);
	void 	atext(char *title, char *states,int show, int when);
	void 	atext(char *title, char *states, D3DCOLOR Color);
	void 	additem(char *title, char *states,int type, int *var, int show, int when);
	void 	getfield(char *str,char *dst,int no);
	int	 	nofields(char *str);
	


	void 	Init(void);
	void 	Menu_1Init(void);//D3D
	void    Menu_3Init(void);//Weapon Control


private:




};



//-------------Структуры меню
struct copt
{
int texting; 
int main;

struct sglavnay/*Главное меню*/
{

bool OptionsSave; //Переменная Сохранения настроек
bool OptionsLoad; //Переменная Загрузки настроек
bool OptionsResset;
				
				int DopMenu;

				int main;	
				int ButtonTestEx;
	
				int ButtonTestMenu;

				int D3D;
				int weaponC;//
				int plyerH;//
				int otherH;//
				int InfO;//
				int DopMenu1;//
				int DopMenu2;//
				int DopMenu3;//
				int DopMenu4;//
				int DopMenu5;//
				int DopMenu6;//
				int DopMenu7;//
				bool DopMenu_WH_EN;//
				bool DopMenu_WH_RU;
				int DopMenu_logger;
				int DopMenu_Info;
				bool DopMenu_option_EN;
				bool DopMenu_option_RU;
				int DopMenu_Teleport;
				int DopMenu_Teleport_Luba;
				int DopMenu_Teleport_Ryaba;
				int DopMenu_Teleport_LubaCrv;
				int DopMenu_Teleport_NZ;
				bool DopMenu_other_EN;
				bool DopMenu_other_RU;

				int assasa;
				int BSmea;
				int tsdaa;
				//int tesфывt;

				DWORD Key;

				bool RUS;
				bool ENG;
				bool ChoseServer;

			}glavnay;


struct sD3D/*Визуал*/
{
				int main;
				int cross;
				int ESP;
				int ESP_new;
				int WalHack;
				int pvp;
				int Mob;
				int Drop;
				int Art;
				int Nichki;
				int Travi;
				int Grib;
				int WireFrame;
				int exit;
				int FPS_SHOW;
				int Listva;
				int Svet;

				int minimaze;
				int maximazed;
				int EXIT;
				int MinimazeMenu;
				
}D3D;
			
struct smemhack
{			


float Xplayer;
float Yplayer;
float HeigthPlayer;
float AsimutPlayer;
float VerticalPlayer;

float Xplayer1;
float Yplayer1;
float HeigthPlayer1;
float AsimutPlayer1;
float VerticalPlayer1;

byte Accuracy_addr;
DWORD AccuracyVoll;
DWORD adrWRNC;
DWORD adrWR;

			int WallShot;	
			int CoordMob;
			int FastZoom;
			int Zoom;
			int main;
			int Possition_Death;
			int TUSA_MOB;
			int Jump;
			int Jump1;
			int frezeHeigth;
			int Camera;
			int Accuracy;
			int AccuracyDop;

			int GurmanTP;
			int GurmanPos;
			int Gorod3;
			int Gorod3Pos;
			int Laba;
			int LabaPos;
			int Boloto;
			int BolotoPos;
			int inputRyab;
			int inputRyabPos;
			int Himka;
			int HimkaPos;
			int Sanatorka;
			int SanatorkaPos;
			int White;
			int WhitePos;
			int Bandits;
			int BanditsPos;
			int Provodnik;
			int ProvodnikPos;
			int Paukan;
			int PaukanPos;
			int Paukan2;
			int Paukan2Pos;
			int Psiha;
			int PsihaPos;
			int ProvodnikInCrv;
			int ProvodnikInCrvPos;
			int UkrepH4;
			int UkrepH4Pos;
			///////Караван//////
			int Anomaly;
			int AnomalyPos;
			int ProvodnikCrv;
			int ProvodnikCrvPos;
			int ProvodnikCrv2;
			int ProvodnikCrv2Pos;
			int ProvodnikCrv3;
			int ProvodnikCrv3Pos;

}memhack;

struct sLogger
{			
				int main;
				int logerpc;
				int logervn;
				int logerstr;
				int logersi;
				int VerticsNumber;
				int StrideNumber;
				int CountNumber;
				int StartIndex;

				int SIstep;
				int PCstep;
				int VNstep;
				int STRstep;

}Logger;

struct sweaponC/*Weapon Control*/
{
	int main;

	int activ;
	 int ocnownoe;
	     int ocnowSt;
	     int ocnowSn;
	     int ocnowAv;
		 int ocnowDr;
    int Pistols;

}weaponC;





				
};
extern copt opt;