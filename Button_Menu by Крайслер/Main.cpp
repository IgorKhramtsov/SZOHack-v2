#include <time.h>
#include "stdafx.h"
#include "cMain.h"
#include "Color.h"
#define	lm	   GetAsyncKeyState(VK_LBUTTON)&1
#define	rm     GetAsyncKeyState(VK_RBUTTON)&1

int cR;
int cG;
int cB;
DWORD TempColor = D3DCOLOR_ARGB(255,cR, cG, cB);
//Меню
int menu1 =108;
int menu2 =22;
int menu3 =380;
int menu4 =250;

int x_;
int y_;

int CHcolor;

	char Xpos[MAX_PATH];
	char Ypos[100];
	char Heigth[100];
	char Vertical[MAX_PATH];
	char Asimut[100];
	char pCount[100];
	char nVertics[100];
	char mStride[100];
	char sIndex[100];
	char Xpos1[MAX_PATH];
	char Ypos1[100];




int optoptLogger;
char *optDamage [] = { " OFF","  20","  25","  30","  35","  40"};
char *optzoomm  [] = { " OFF","   1","   2","   3","   4","   5","   6","   7","   8","   9","  10" };
char *optjampV  [] = { " OFF","   1","   2","   3","   4","   5","   6","   7"};
char *optLogger [100] = { "0"};
char *optWallHack [] = {"Выкл","Белый","Жёлт.","Оранж.","Зелён.","Салат.","Синий","Красн.","Розов.","Морск."};
char *optTP  [14] = { " OFF","Гурман","Вход в город КП-3","Лагерь учёных","Болота О10","Переход на рябу","Химка","Санаторка","Деревня Белых","Пещера бандитов","Проводник","Паукан костёр","Паукан респ","Штакет"};
char *optJump[6] = {"OFF","1","5","10","15","150"};
char *optJump1[6] = {"OFF","1","5","10","15","150"};
char *optZoom[6] = {"OFF","X1","X2","X3","X4","X5"};
char *optLogStep[5]={"0","1","10","100","1000"};

char *smena  [] = { " OFF","   1","   2","   3","   4","   5","   6","   7","   8","   9","  10"};

void  cMenu::PostReset(LPDIRECT3DDEVICE9 pDevice)
{
	font = new CD3DFont("Arial",8, D3DFONT_BOLD);
	font->InitDeviceObjects(pDevice);
	font->RestoreDeviceObjects();
	
}
void  cMenu::PreReset       (void)
{
	font->InvalidateDeviceObjects();
	font->DeleteDeviceObjects();
	delete font;
	font = NULL;
}
void  cMenu::Init()
{
	if(!INIT)
	{
		X=Y=0;			        
	//	WIDTH=160;		
		I_OFS=4;			   
		S_OFS=WIDTH-2;			
		T_SPC=16;				
		F_SPC=16;				
		I_SPC=15;				
		I_CUR=0;				
		ABOR=0;					
		BDIR=0;					
		SHOW=0;				// 1 = пакозывать автоматически  0 = Скрывать при запуске
		INIT=true;				
	}
}
void  cMenu::Menu_1Init()
{
	if(INIT)
	{
		X1=1;
		Y1=124;			       
		WIDTH=159;		
		I_OFS=4;			   
		S_OFS=WIDTH-2;			
		T_SPC=16+5;				
		F_SPC=16;				
		I_SPC=15;				
		I_CUR=0;				
		ABOR=0;					
		BDIR=0;					
		SHOW=true;				
		INIT=true;				
	}
}
void  cMenu::Menu_3Init()
{
if(INIT)
{
}
}
char* FPS(void)
{

static int	 FPScounter = 0;
static float FPSfLastTickCount = 0.0f;
static float FPSfCurrentTickCount;
static char  cfps[6] = "";
static char  cFPS[6] = "";

FPSfCurrentTickCount = clock() * 0.001f;
FPScounter++;
if((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f)
{
   FPSfLastTickCount = FPSfCurrentTickCount;
   sprintf(cfps,"FPS  %d",FPScounter);
   sprintf(cFPS,"FPS  %d",FPScounter);
   FPScounter = 0;
}


return cfps;
return cFPS;
}
char* cMenu::TIME           (void)
{
	static char ctime[20] = "" ;
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	if(current_tm->tm_hour>12)
		sprintf( ctime, "Часы  %d:%02d:%02d", current_tm->tm_hour - 12, current_tm->tm_min, current_tm->tm_sec );
	else
		sprintf( ctime, "Часы %d:%02d:%02d", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return ctime;
}
char* cMenu::oprintf        (const char *fmt, ...)
{
	static char buffer[225] = "";
	va_list va_alist;
	va_start (va_alist, fmt);
	_vsnprintf (buffer,sizeof(buffer), fmt, va_alist);
	va_end (va_alist);
	return buffer;

}
void  cMenu::additem        (char *title, char *states,int type, int *var, int show, int when)
{
	if(show==when)
	{
		strcpy(items[NO].title,title);
		getfield(states,items[NO].state,*var+1);
		items[NO].type=type;
		items[NO].max=nofields(states);
		items[NO].val=var;
	
		NO++;
	}
	
}
void  cMenu::acat           (char *title, char *states,int *var)
{
	additem(title,states,T_CAT,var,0,0);
}
void  cMenu::aitem          (char *title, char *states,int *var,int show,int when)
{
	additem(title,states,T_ITEM,var,show,when);
}
void  cMenu::atext(char *title, char *states,int show,int when)
{
	additem(title,states,T_TEXT,&opt.texting,show,when);
}
void  cMenu::atext(char *title, char *states, D3DCOLOR Color)
{
	additem(title,states,T_TEXT,&opt.texting,1,1);
}
int   cMenu::nofields        (char *str)
{
	char *ptr;
	int  no;
	for(no=1; (ptr=strchr(str,(char)'|'))!=NULL; no++)str=ptr+1;
	
	return no;
}
void  cMenu::getfield       (char *str,char *dst,int no)
{
	char *ptr;
	int  i;
	for(i=1; (ptr=strchr(str,(char)'|'))!=NULL ; i++) 
	{
		if(i==no) break;
		str=ptr+1;
	}
	if(ptr)
	{
		i=(int)(ptr-str);
		strncpy(dst,str,i);
		dst[i]=0;
	}
	else
		strcpy(dst,str);
}
BOOL cMenu::IsInBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}


void cMenu::Draw_Button_TestWH(int x ,int y , int w , int h ,int &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice)
{
if(IsInBox(x+360,y,10,10))
{
DrawBorder(x+360,y,10,10,DEEPSKYBLUE,pDevice);
if(GetAsyncKeyState(VK_LBUTTON)&1)
{
DrawBorder(x+360,y,10,10,GREEN,pDevice);
if(Var == 1 && Var !=0)
{
Var = 0;
}
else if(Var == 0)
{
Var = 1;
}
}
}
if(Var == 0)
{
font->DrawText(x,y,Maintext,Button_Text,DT_LEFT|DT_SHADOW);
DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if(Var == 1)
{
DrawBox(x+360,y,10,10,GREEN,pDevice);
font->DrawText(x,y,RED,Button_Text,DT_LEFT|DT_SHADOW);
DrawBorder(x+360,y,10,10,RED,pDevice);
}
}

void cMenu::Draw_Button_Test(int x ,int y , int w , int h ,bool &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice)
{
if(Var == 0)
{
DrawBox(x,y,60,30,Ser,pDevice);//темнее
font->DrawText(w,y+10,WHITE,Button_Text,NULL);
DrawBorder(x-1,y-1,62,32,BLACK,pDevice);
}
if(Var == 1)
{
DrawBox(x,y,60,30,Ser_2,pDevice);//Светлее
font->DrawText(w,y+10,WHITE,Button_Text,NULL);
DrawBorder(x-1,y-1,62,32,BLACK,pDevice);
}
if(IsInBox(x,y,60,30))
	{
	if(GetAsyncKeyState(VK_LBUTTON)&1)
		{
		DrawBorder(x-1,y-1,62,32,TEXT,pDevice);
		if(Var == 0)
			{
			Var = opt.glavnay.RUS=opt.glavnay.ENG=0;
			Var =1;
			}
		}
	DrawBorder(x-1,y-1,62,32,WHITE,pDevice);
	}
}

void cMenu::Draw_Button_TestTEXT(int x ,int y , int w , int h ,bool &Var ,char *Button_Text,char *Info ,LPDIRECT3DDEVICE9 pDevice)
{
	POINT mpos; 
	GetCursorPos(&mpos); 
	ScreenToClient(GetForegroundWindow(),&mpos);
DrawBorder(x-1,y-1,11,11,Ser_2,pDevice);
if(IsInBox(x,y,10,10))
{
	DrawBorder(x-1,y-1,11,11,BLUE_2,pDevice);
	if (GetAsyncKeyState(VK_LBUTTON)&1)
	{
		if (Var==0)
		{
			Var=1;
		}
		else 
		{
			Var=0;
		}
	}
	if (Var==1)
	{
		DrawBox(x,y,10,10,Ser_2,pDevice);
	}
	else if(Var==0)
	{
		DrawBox(x,y,10,10,GREEN_2,pDevice);
	}
	//*******Info*******//
	DrawBox(mpos.x+5,mpos.y+15,150,30,WHITE_A,pDevice);
	DrawBorder(mpos.x+4,mpos.y+14,152,32,Ser,pDevice);
	font->DrawText(mpos.x+7,mpos.y+17,BLACK,Info,NULL);
	//******************//
}
font->DrawText(x+2,y-1,WHITE,Button_Text,NULL);
}


void cMenu::Draw_Button_Teleport(int x ,int y ,int &Var ,int &VAR,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice)
{
if(IsInBox(x,y,100,10)&&GetAsyncKeyState(VK_LBUTTON)&1)
	{
	if(Var == 1 && Var !=0)
			{
			Var = 0;
			}
	else if(Var == 0)
			{
			Var = 1;
			}
	}
if(IsInBox(x,y,100,10)&&GetAsyncKeyState(VK_RBUTTON)&1)
	{
	if(VAR == 1 && VAR !=0)
			{
			VAR = 0;
			}
	else if(VAR == 0)
			{
			VAR = 1;
			}
	}
if(VAR == 0)
{
font->DrawText(x,y,WHITE,Button_Text,NULL);
}
if(VAR == 1)
{
font->DrawText(x,y,RED,Button_Text,NULL);
}
}

void cMenu::Draw_ColorChams_3(int x ,int y ,char *Text,int &funkc_color_hams ,LPDIRECT3DDEVICE9 pDevice)
{
#define zire_x_smehenie 13
//----------------------------------------------------------
DrawBox(x + (zire_x_smehenie),y,10,10,  WHITE,pDevice);
DrawBox(x + (zire_x_smehenie*2),y,10,10,RED,pDevice);
DrawBox(x + (zire_x_smehenie*3),y,10,10,BLUE,pDevice);
DrawBorder(x + (zire_x_smehenie*4),y,10,10,RED,pDevice);
//----------------------------------------------------------

if(IsInBox(x + (zire_x_smehenie),y+2,10,10))
{
DrawBorder(x + (zire_x_smehenie),y,10,10,WHITE,pDevice);
if(GetAsyncKeyState(VK_LBUTTON)&1){funkc_color_hams=1;}
}

if(IsInBox(x + (zire_x_smehenie*2),y+2,10,10))
{
DrawBorder(x + (zire_x_smehenie*2),y,10,10,WHITE,pDevice);
if(GetAsyncKeyState(VK_LBUTTON)&1){funkc_color_hams=2;}
}

if(IsInBox(x + (zire_x_smehenie*3),y+2,10,10))
{
DrawBorder(x + (zire_x_smehenie*3),y,10,10,WHITE,pDevice);
if(GetAsyncKeyState(VK_LBUTTON)&1){funkc_color_hams=3;}
}

if(IsInBox(x + (zire_x_smehenie*4),y+2,10,10))
{
DrawBorder(x + (zire_x_smehenie*4),y,10,10,WHITE,pDevice);
if(GetAsyncKeyState(VK_LBUTTON)&1){funkc_color_hams=0;}
}
font->DrawText(x + (zire_x_smehenie*5)+1, y, Maintext, Text, DT_LEFT | DT_SHADOW);
}
void cMenu::Draw_Button_Scrol(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice)
{
 Scroll(x,y,255,10,Var ,text,BLUE,  pDevice);
}
 void cMenu::Draw_Button_ScrolCH(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice)
{
if (Var ==0)
{
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==1)
{
	DrawBox(x+360,y,10,10,WHITE,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==2)
{
	DrawBox(x+360,y,10,10,YELLOW,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==3)
{
	DrawBox(x+360,y,10,10,ORANGE,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==4)
{
	DrawBox(x+360,y,10,10,GREEN,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==5)
{
	DrawBox(x+360,y,10,10,SALAT,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==6)
{
	DrawBox(x+360,y,10,10,BLUE,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==7)
{
	DrawBox(x+360,y,10,10,RED,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==8)
{
	DrawBox(x+360,y,10,10,ROSE,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if (Var==9)
{
	DrawBox(x+360,y,10,10,AQUA,pDevice);
	DrawBorder(x+360,y,10,10,BLACK,pDevice);
}
if(IsInBox(x+360,y,10,10))
{
 DrawBorder(x+360,y,10,10,BLUE, pDevice);
  if(GetAsyncKeyState(VK_RBUTTON)&1)
   {
    if(Var!=0)
     {
      Var--;
      Sleep(100);
     }
   }
}
if(IsInBox(x+360,y,10,10))
{
	DrawBorder(x+360,y,10,10,BLUE, pDevice);
    if(GetAsyncKeyState(VK_LBUTTON)&1)
    {
     if(Var>=0 && Var<max)
     {
       Var++;
       Sleep(100);
     }
   }
}
font->DrawText(x,y,GREEN,text,DT_SHADOW);
}

void cMenu::Draw_Button_ScrolLG(int x,int y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice)
{
if(IsInBox(x,y,65,10))
{
 //DrawBorder(x+360,y,10,10,BLUE, pDevice);
  if(GetAsyncKeyState(VK_RBUTTON)&1)
   {
    if(Var!=0)
     {
      Var--;
      Sleep(100);
     }
   }
}

if(IsInBox(x,y,65,10))
{
	//DrawBorder(x+360,y,10,10,BLUE, pDevice);
    if(GetAsyncKeyState(VK_LBUTTON)&1)
    {
     if(Var>=0 && Var<max)
     {
       Var++;
       Sleep(100);
     }
   }
}

font->DrawText(x,y,GREEN,text,DT_SHADOW);
}

void cMenu::Scroll(float x,float y,float w,float h,int &GetCurrent,char* Text ,D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice)
{
DrawBox(x,y, w,10,GREY, pDevice);
DrawBorder(x,y, w,10, WHITE,pDevice);
	POINT mpos; 
	GetCursorPos(&mpos); 
	ScreenToClient(GetForegroundWindow(),&mpos);

	if(GetAsyncKeyState(VK_LBUTTON))
		{
			if(IsInBox(x,y,w,h))
			{
			GetCurrent = mpos.x-(x);
			Sleep(10);
			}
		}
	 char test[MAX_PATH];
     sprintf(test, " %d" , GetCurrent);

     DrawBorder(x,y, w,10, WHITE,pDevice);
     DrawBox(x+1,y+2, GetCurrent,7,Color, pDevice);
	 DrawBox(x+GetCurrent,y-2, 5,14,GREEN, pDevice);
	 DrawBorder(x+GetCurrent,y-2, 5,14, WHITE,pDevice);
	 font->DrawText(x+(w/2),y-2, WHITE,test,DT_CENTER);
	 font->DrawText(x+w+15-380,y-2, WHITE,Text,DT_LEFT);
}

/*
void cMenu::MapColor(int x,int y,int &R_col,int &G_col,int &B_col,LPDIRECT3DDEVICE9 pDevice)
{
 Scroll(x,y,     255,10,R_col ,RED,   pDevice);
 Scroll(x,y+20,255,10,G_col ,GREEN, pDevice);	 
 Scroll(x,y+40,255,10,B_col ,BLUE,  pDevice);	 
}
*/

void cMenu::Draw_Button(int x ,int y , int w , int h ,int &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice)
{
if(IsInBox(x,y,w,h))
{
if(GetAsyncKeyState(VK_LBUTTON)&1)
{
if(Var == 1 && Var !=0)
{
Var = 0;
}
else if(Var == 0)
{
if(Var == 0)
{
opt.glavnay.DopMenu_Teleport_Luba=opt.glavnay.DopMenu_Teleport_LubaCrv=opt.glavnay.DopMenu_Teleport_Ryaba=opt.glavnay.DopMenu_Teleport_NZ=0;//
Var = 1;
}
}
}
}
if(Var == 0)
{
font->DrawText(x,y,Maintext,Button_Text,NULL);
//font->DrawText(x__,y__,Maintext,offon[0],DT_CENTER|DT_SHADOW);
}
if(Var == 1)
{
//DrawBox(x,y,50,10,Mainfun,pDevice);
font->DrawText(x,y,Maintext,Button_Text,NULL);
//font->DrawText(x__,y__,Maintext,offon[1],DT_CENTER|DT_SHADOW);
}
}
void cMenu::Draw_Button_Menu(int x ,int y , int w , int h ,bool &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice)
{
char *offon[] = {"" ,""};
if(IsInBox(x,y,w,h))
{
if(GetAsyncKeyState(VK_LBUTTON)&1)
{
if(Var == 1 && Var !=0)
{
Var = 0;
}
else if(Var == 0)
{
if(Var == 0)
{
	opt.glavnay.DopMenu_WH_EN=opt.glavnay.DopMenu_WH_RU=opt.glavnay.D3D=opt.glavnay.DopMenu3=opt.glavnay.DopMenu2=opt.glavnay.DopMenu5=opt.glavnay.DopMenu6=opt.glavnay.DopMenu7=opt.glavnay.DopMenu_logger=opt.glavnay.DopMenu_Teleport=opt.glavnay.DopMenu_Info=opt.glavnay.DopMenu_option_EN=opt.glavnay.DopMenu_other_EN=opt.glavnay.DopMenu_option_RU=opt.glavnay.DopMenu_other_RU=0;//
Var = 1;
}
}
}
}
if(Var == 0)
{
DrawBox(x-1,y,w+31,20,namehack,pDevice);
DrawBorder(x-1,y,w+31,20,BLACK,pDevice);
font->DrawText(x+10,y+2,Maintext,Button_Text,NULL);
//font->DrawText(x+15,y,Maintext,offon[0],DT_CENTER|DT_SHADOW);
}
if(Var == 1)
{
DrawBox(x-1,y,w+31,20,Main,pDevice);
DrawBorder(x-1,y,w+31,20,BLACK,pDevice);
font->DrawText(x+10,y+2,Maintext,Button_Text,NULL);
//font->DrawText(x+15,y,Maintext,offon[1],DT_CENTER|DT_SHADOW);
}
}

void  cMenu::DrawBorder(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice)
{
	DrawBox(x,  y, 1,  h,Color,pDevice);
	DrawBox(x,y+h, w,  1,Color,pDevice);
	DrawBox(x,  y, w,  1,Color,pDevice);
	DrawBox(x+w,y, 1,h+1,Color,pDevice);
}
void  cMenu::DrawBox( int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1); 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);   
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	D3DPT_TRIANGLESTRIP);
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 1, 1 );
}



char  Special_key_RU[100];
char  Special_key_EN[100];

//---Главное меню
void  cMenu::ShowMenu       (LPDIRECT3DDEVICE9 pDevice)
{	
	/*
	opt.memhack.Xplayer=opt.memhack.Xplayer/10;
	opt.memhack.Yplayer=opt.memhack.Yplayer/10;
	if(opt.memhack.Xplayer<0){opt.memhack.Xplayer=opt.memhack.Xplayer*-1;}
	if(opt.memhack.Yplayer<0){opt.memhack.Yplayer=opt.memhack.Yplayer*-1;}



	char Xpos[MAX_PATH];
	char Ypos[100];
    sprintf(Xpos, "X=%f" , opt.memhack.Xplayer);
	sprintf(Ypos,"Y=%f",opt.memhack.Yplayer);

	DrawBox(1,1,(400),(400),BLACK,pDevice);
	DrawBox(0,  200, 400,  1,GREEN,pDevice);
	DrawBox(200,  0, 1,  400,GREEN,pDevice);
	//DrawBox(static_cast<int>(opt.memhack.Xplayer),static_cast<int>(opt.memhack.Yplayer),4,4,WHITE,pDevice);
	DrawBox(198,198,5,5,WHITE,pDevice);
	font->DrawText(400,33,WHITE,Xpos,NULL/);
	font->DrawText(500,33,WHITE,Ypos,NULL);
	*/


	//font->DrawText(400,33,WHITE,Xpos,NULL);
	//font->DrawText(400,43,WHITE,Ypos,NULL);
	//font->DrawText(400,53,WHITE,Heigth,NULL);

	//font->DrawText(400,63,WHITE,Asimut,NULL);
	//font->DrawText(400,73,WHITE,Vertical,NULL);
	//font->DrawText(400,83,WHITE,Xpos1,NULL);
	//font->DrawText(400,93,WHITE,Ypos1,NULL);
	sprintf(Xpos, "X=%f" , opt.memhack.Xplayer);
	sprintf(Ypos,"Y=%f",opt.memhack.Yplayer);
	sprintf(Heigth,"Heigth=%f",opt.memhack.HeigthPlayer);
	sprintf(Asimut,"Asimut=%f",opt.memhack.AsimutPlayer);
	sprintf(Vertical,"Vertical=%f",opt.memhack.VerticalPlayer);
    sprintf(Xpos1, "X_=%f" , opt.memhack.Xplayer1);
	sprintf(Ypos1,"Y_=%f",opt.memhack.Yplayer1);
	sprintf(Special_key_RU,"Ваш код (%d)",opt.glavnay.Key);
	sprintf(Special_key_EN,"Your code  (%d)",opt.glavnay.Key);
	/*
	DrawBox(720,10,100,10,WHITE,pDevice);

	DrawBox(500,30,100,10,WHITE,pDevice);
	DrawBox(610,30,100,10,WHITE,pDevice);
	DrawBox(720,30,100,10,WHITE,pDevice);
	DrawBox(830,30,100,10,WHITE,pDevice);
	DrawBox(940,30,100,10,WHITE,pDevice);
	*/

	/*
	if (opt.D3D.cross==1)
	{
	DrawBox(50,10,640,640,NULL,pDevice);
	if (i<10)
	{

		Box=Box+40;
		i++;
		if (b<10)
		{

			Box1=Box1+40;
			b++;
		}
	}
	if (c<10)
	{
		DrawBorder(50,10,Box,Box1,RED,pDevice);
		c++;
	}
	//DrawBorder(50,10,40,40,RED,pDevice);
	}
	*/



		//font->DrawText(400,33,WHITE,Xpos,NULL);
	//font->DrawText(400,43,WHITE,Ypos,NULL);
	//font->DrawText(400,53,WHITE,Heigth,NULL);

	
		 if (opt.D3D.FPS_SHOW)
	 {
		 font->DrawText(500,33,Maintext,FPS(),NULL/*DT_LEFT|DT_SHADOW*/);
	 }

	Init();

		if (opt.D3D.EXIT) 
	{
			SHOW=0;
			opt.D3D.MinimazeMenu = 0;
			opt.D3D.EXIT =0;
	}

			if (opt.D3D.minimaze) 
	{
			opt.D3D.minimaze =0;
			opt.D3D.MinimazeMenu = 1;
	}
			if (opt.D3D.maximazed)
			{
				opt.D3D.MinimazeMenu = 0;
				SHOW=1;
				opt.D3D.maximazed=0;
			}

			if (opt.D3D.MinimazeMenu)
{
	SHOW=1;
	opt.glavnay.main=1;
	//Название/////////////////////////////////////////////////////////////////////////////////
	DrawBox(108,8,380,15,namehack, pDevice);
	font->DrawText(115,8,Maintext,"MultiHack for StalkerOnline Minimaze",DT_LEFT|DT_SHADOW);
	//Выход
	font->DrawText(475,8,Maintext,"X",DT_LEFT|DT_SHADOW);
	Draw_Button(473,10,10,10,opt.D3D.EXIT,"",pDevice);
	//---------------------------------------
	//Увеличить
		font->DrawText(465,7,Maintext,"+",DT_LEFT|DT_SHADOW);
		Draw_Button(460,10,10,10,opt.D3D.maximazed,"",pDevice);
	//---------------------------------------
	//Конец названия///////////////////////////////////////////////////////////////////////////
}
			
			if (SHOW==0)
			{
				opt.D3D.FPS_SHOW=0;
			}

			//aitem("CrossHair","Off|_1|_2",&opt.D3D.cross,opt.D3D.main,1);

	if(GetAsyncKeyState(VK_HOME)&1) SHOW=(!SHOW);//---Кнопка появления меню
	if(SHOW)
	{
	opt.glavnay.main=1;

	opt.D3D.FPS_SHOW=1;
	font->DrawText(500,43,WHITE,Xpos,NULL);
	font->DrawText(500,53,WHITE,Ypos,NULL);
	font->DrawText(500,63,WHITE,Heigth,NULL);

	//Название/////////////////////////////////////////////////////////////////////////////////
    DrawBox(108,8,380,15,namehack, pDevice);
	font->DrawText(115,8,Maintext,"MultiHack for StalkerOnline By Игоръ",DT_LEFT|DT_SHADOW);
	font->DrawText(465,7,Maintext,"_",DT_LEFT|DT_SHADOW);
	font->DrawText(475,8,Maintext,"X",DT_LEFT|DT_SHADOW);
	DrawBox(menu1-100,menu2-14,menu3-300,30,namehack,pDevice);
	font->DrawText(menu1-98,menu2-14,Maintext,"Menu",DT_LEFT|DT_SHADOW);
	//Конец названия///////////////////////////////////////////////////////////////////////////
	DrawBox(menu1,menu2,menu3,menu4,Mainfun, pDevice); // Menu
	DrawBox(8,22,80,80,Mainfun,pDevice);
	DrawBorder(8,8,80,93,BLACK,pDevice);

		Draw_Button(473,10,10,10,opt.D3D.EXIT,"",pDevice);
		Draw_Button(460,10,10,10,opt.D3D.minimaze,"",pDevice);
	//Навигация////////////////////////////////////////////////////////////////////////////////
		if(opt.glavnay.ENG==1)
		{
	Draw_Button_Menu(menu1-96,25,43,20,opt.glavnay.DopMenu_WH_EN,"Visual",pDevice);
	Draw_Button_Menu(menu1-96,50,43,20,opt.glavnay.DopMenu_other_EN,"Other" , pDevice);
    //Draw_Button_Menu(menu1-96,75,43,20,opt.glavnay.DopMenu_option_EN,"Menu" , pDevice);
	Draw_Button_Menu(menu1-96,75,43,20,opt.glavnay.ChoseServer,"Language" , pDevice);
		}
		if(opt.glavnay.RUS==1)
		{
	Draw_Button_Menu(menu1-96,25,43,20,opt.glavnay.DopMenu_WH_RU,"Визуал",pDevice);
	Draw_Button_Menu(menu1-96,50,43,20,opt.glavnay.DopMenu_other_RU,"Остальное" , pDevice);
    //Draw_Button_Menu(menu1-96,75,43,20,opt.glavnay.DopMenu_option_RU,"Меню" , pDevice);
	Draw_Button_Menu(menu1-96,75,43,20,opt.glavnay.ChoseServer,"Язык" , pDevice);
		}
	DrawBorder(107,7,381,menu4+14,BLACK,pDevice);
	//Draw_Button_Menu(menu1-96,100,43,20,opt.glavnay.DopMenu_Info,"Info",pDevice);
	//Draw_Button_Menu(menu1-96,100,43,20,opt.glavnay.DopMenu_logger,"Logger",pDevice);
	 //Draw_Button_Menu(menu1-96,50,43,20,opt.glavnay.DopMenu_Teleport,"Телепорт",pDevice);

	if (opt.glavnay.RUS==0 && opt.glavnay.ENG ==0)
	{
	opt.glavnay.DopMenu_option_EN=opt.glavnay.DopMenu_option_RU=opt.glavnay.DopMenu_other_EN=opt.glavnay.DopMenu_other_RU=opt.glavnay.DopMenu_WH_EN=opt.glavnay.DopMenu_WH_RU=0;
	font->DrawText(210,70,TEXT,"Chose Language / Выберите Язык ",NULL);
	Draw_Button_Test(220,100,230,NULL,opt.glavnay.RUS,"Russian",pDevice);
	Draw_Button_Test(300,100,310,NULL,opt.glavnay.ENG,"English",pDevice);
	}
	else if(opt.glavnay.RUS==1&&opt.glavnay.DopMenu_WH_EN==0&&opt.glavnay.DopMenu_WH_RU==0&&opt.glavnay.DopMenu_option_EN==0&&opt.glavnay.DopMenu_other_EN==0&&opt.glavnay.DopMenu_option_RU==0&&opt.glavnay.DopMenu_other_RU==0)
	{
		font->DrawText(115,25,TEXT_2,"Это вх для SZone-Online от Игоръ.Спасибо за покупку",NULL);
		font->DrawText(115,36,TEXT_2,"Вы можете зароботать.",NULL);
		font->DrawText(115,47,TEXT_2,"Расскажите о этом вх другу и если он купит его,то вы получите 100р.",NULL);
		font->DrawText(115,58,TEXT_2,"При добавлении ко мне в скайп он должен отослать мне ваш код",NULL);
		font->DrawText(115,69,TEXT_2,Special_key_RU,NULL);
	}
		else if(opt.glavnay.ENG==1&&opt.glavnay.DopMenu_WH_EN==0&&opt.glavnay.DopMenu_WH_RU==0&&opt.glavnay.DopMenu_option_EN==0&&opt.glavnay.DopMenu_other_EN==0&&opt.glavnay.DopMenu_option_RU==0&&opt.glavnay.DopMenu_other_RU==0)
	{
		font->DrawText(115,25,TEXT_2,"It is WH for SZone-Online by Игоръ.Thanks for buy.",NULL);
		font->DrawText(115,36,TEXT_2,"You can earn.",NULL);
		font->DrawText(115,47,TEXT_2,"Tell about it cheat to the friend and if he buy it, you get 100р.",NULL);
		font->DrawText(115,58,TEXT_2,"At addition to me in Skype he must send me your code",NULL);
		font->DrawText(115,69,TEXT_2,Special_key_EN,NULL);
	}
	if (opt.glavnay.ChoseServer==1){opt.glavnay.RUS=opt.glavnay.ENG=0;opt.glavnay.ChoseServer=0;}

/*
if(opt.glavnay.DopMenu_logger)
{
		opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
		if (opt.Logger.logersi==0)
		{
			sprintf(sIndex,"StartIndex",opt.Logger.StartIndex);
		}
		else if (opt.Logger.logersi==1)
		{
		sprintf(sIndex,"StartIndex == %d",opt.Logger.StartIndex);
		}
		else if (opt.Logger.logersi==2)
		{
		sprintf(sIndex,"StartIndex <= %d",opt.Logger.StartIndex);
		}
		else if (opt.Logger.logersi==3)
		{
		sprintf(sIndex,"StartIndex >= %d",opt.Logger.StartIndex);
		}
		else if (opt.Logger.logersi==4)
		{
		sprintf(sIndex,"StartIndex != %d",opt.Logger.StartIndex);
		}
		if (opt.Logger.logerstr==0)
		{
			sprintf(mStride,"m_Stride",opt.Logger.StrideNumber);
		}
		else if(opt.Logger.logerstr==1)
		{
		sprintf(mStride,"m_Stride == %d",opt.Logger.StrideNumber);
		}
		else if(opt.Logger.logerstr==2)
		{
		sprintf(mStride,"m_Stride <= %d",opt.Logger.StrideNumber);
		}
		else if(opt.Logger.logerstr==3)
		{
		sprintf(mStride,"m_Stride >= %d",opt.Logger.StrideNumber);
		}
		else if(opt.Logger.logerstr==4)
		{
		sprintf(mStride,"m_Stride != %d",opt.Logger.StrideNumber);
		}
		if (opt.Logger.logervn==0)
		{
			sprintf(nVertics,"NumVertices",opt.Logger.VerticsNumber);
		}
		else if (opt.Logger.logervn==1)
		{
		sprintf(nVertics,"NumVertices == %d",opt.Logger.VerticsNumber);
		}
		else if (opt.Logger.logervn==2)
		{
		sprintf(nVertics,"NumVertices <= %d",opt.Logger.VerticsNumber);
		}
		else if (opt.Logger.logervn==3)
		{
		sprintf(nVertics,"NumVertices >= %d",opt.Logger.VerticsNumber);
		}
		else if (opt.Logger.logervn==4)
		{
		sprintf(nVertics,"NumVertices != %d",opt.Logger.VerticsNumber);
		}
		if (opt.Logger.logerpc==0)
		{
			sprintf(pCount,"primCount",opt.Logger.CountNumber);
		}
		else if (opt.Logger.logerpc==1)
		{
		sprintf(pCount,"primCount == %d",opt.Logger.CountNumber);
		}
		else if (opt.Logger.logerpc==2)
		{
		sprintf(pCount,"primCount <= %d",opt.Logger.CountNumber);
		}
		else if (opt.Logger.logerpc==3)
		{
		sprintf(pCount,"primCount >= %d",opt.Logger.CountNumber);
		}
		else if (opt.Logger.logerpc==4)
		{
		sprintf(pCount,"primCount != %d",opt.Logger.CountNumber);
		}
		char STRstep[100];
		sprintf(STRstep,"Шаг = %d",opt.Logger.PCstep);
		if (opt.Logger.STRstep==1)
		{
			opt.Logger.PCstep=1;
		}
		else if (opt.Logger.STRstep==2)
		{
			opt.Logger.PCstep=10;
		}
		else if (opt.Logger.STRstep==3)
		{
			opt.Logger.PCstep=100;
		}
		else if (opt.Logger.STRstep==4)
		{
			opt.Logger.PCstep=1000;
		}
		Draw_Button_ScrolLG(menu1+5,menu2+10,opt.Logger.logerpc,optWallHack,4,pCount,pDevice);
		Draw_Button_ScrolLG(menu1+5,menu2+25,opt.Logger.logervn,optWallHack,4,nVertics,pDevice);
		Draw_Button_ScrolLG(menu1+5,menu2+40,opt.Logger.logerstr,optWallHack,4,mStride,pDevice);
		Draw_Button_ScrolLG(menu1+5,menu2+55,opt.Logger.logersi,optWallHack,4,sIndex,pDevice);
		Draw_Button_Scrol(menu1+5,menu2+70,opt.Logger.STRstep,optLogStep,4,STRstep,pDevice);
}
*/
if(opt.glavnay.DopMenu_other_EN)
{
	opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
		Draw_Button_TestWH(menu1+5,25 ,10 , 10 ,opt.memhack.TUSA_MOB ,  "Party mob" , pDevice);
		Draw_Button_TestWH(menu1+5,40 ,10 , 10 ,opt.memhack.frezeHeigth,"Freeze Heigth" , pDevice);
		Draw_Button_TestWH(menu1+5,55 ,10 , 10 ,opt.memhack.Camera,"Camera" , pDevice);
		Draw_Button_TestWH(menu1+5,70 ,10 , 10 ,opt.memhack.WallShot,"NoClip" , pDevice);
		Draw_Button_TestWH(menu1+5,85 ,10 , 10 ,opt.memhack.Accuracy,"Accuracy" , pDevice);
		Draw_Button_Scrol(menu1+5+110 ,100 ,			opt.memhack.Jump,optJump,5,  "Jump (PageUp)",pDevice);
		Draw_Button_Scrol(menu1+5+110 ,115 ,			opt.memhack.Jump1,optJump1,5,"Fall (PageDown)",pDevice);
}
if(opt.glavnay.DopMenu_other_RU)
{
	opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
		Draw_Button_TestWH(menu1+5,25 ,10 , 10 ,opt.memhack.TUSA_MOB ,  "Тусовка мобов" , pDevice);
		Draw_Button_TestWH(menu1+5,40 ,10 , 10 ,opt.memhack.frezeHeigth,"Заморозить высоту" , pDevice);
		Draw_Button_TestWH(menu1+5,55 ,10 , 10 ,opt.memhack.Camera,"Камера" , pDevice);
		Draw_Button_TestWH(menu1+5,70 ,10 , 10 ,opt.memhack.WallShot,"NoClip" , pDevice);
		Draw_Button_TestWH(menu1+5,85 ,10 , 10 ,opt.memhack.Accuracy,"Точность" , pDevice);
		Draw_Button_Scrol(menu1+5+110 ,100 ,			opt.memhack.Jump,optJump,5,  "Прыжок (PageUp)",pDevice);
		Draw_Button_Scrol(menu1+5+110 ,115 ,			opt.memhack.Jump1,optJump1,5,"Падение(PageDown)",pDevice);
}

/*
if(opt.glavnay.DopMenu_option_EN)
{
	opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
		Draw_Button_TestTEXT(menu1+5,menu2+10 ,10 , 10 ,opt.glavnay.OptionsSave ,  "Save option" , pDevice);
		Draw_Button_TestTEXT(menu1+5,menu2+30 ,10 , 10 ,opt.glavnay.OptionsLoad ,  "Load option" , pDevice);
}
if(opt.glavnay.DopMenu_option_RU)
{
	opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
		Draw_Button_TestTEXT(menu1+5,menu2+10 ,10 , 10 ,opt.glavnay.OptionsSave ,  "Сохр. настройки" , pDevice);
		Draw_Button_TestTEXT(menu1+5,menu2+30 ,10 , 10 ,opt.glavnay.OptionsLoad ,  "Загр. настройки" , pDevice);
}
/*
if(opt.glavnay.DopMenu6)
{
        DrawBox(13,42,370,145,Main, pDevice);


        Draw_Button(86 ,125 ,     70 , 24,opt.glavnay.DopMenu3 ,"Назад" , pDevice);
}*/

if(opt.glavnay.DopMenu_WH_EN)
{
		opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+10,		opt.D3D.pvp,optWallHack,9,"PvP",pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+25,		opt.D3D.Mob,optWallHack,9, "PvE",pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+40,		opt.D3D.Art,optWallHack,9,"Art`s",pDevice);
		Draw_Button_ScrolCH(menu1+5,menu2+55,		opt.D3D.Drop,optWallHack,9,"Dropp`s",pDevice);
		Draw_Button_ScrolCH(menu1+5,menu2+70,		opt.D3D.Nichki,optWallHack,9,"Cache",pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+85,		opt.D3D.Grib,optWallHack,9,"mushroom",pDevice);
		Draw_Button_TestWH(menu1+5,menu2+100,		10 , 10 ,opt.D3D.Listva,"Foliage",pDevice);
		Draw_Button_TestWH(menu1+5,menu2+115,		10 , 10 ,opt.D3D.Svet,"Night light",pDevice);
		Draw_Button_TestWH(menu1+5 ,menu2+130 ,     10 , 10 ,opt.D3D.cross , "Crosshair" , pDevice);
		Draw_Button_TestWH(menu1+5 ,menu2+145 ,     10 , 10 ,opt.D3D.WireFrame , "WireFrame" , pDevice);
}
if(opt.glavnay.DopMenu_WH_RU)
{
		opt.D3D.main=1;
        DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+10,		opt.D3D.pvp,optWallHack,9,"PvP",pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+25,		opt.D3D.Mob,optWallHack,9, "PvE",pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+40,		opt.D3D.Art,optWallHack,9,"Артефакты",pDevice);
		Draw_Button_ScrolCH(menu1+5,menu2+55,		opt.D3D.Drop,optWallHack,9,"Дроп",pDevice);
		Draw_Button_ScrolCH(menu1+5,menu2+70,		opt.D3D.Nichki,optWallHack,9,"Нычки",pDevice);
        Draw_Button_ScrolCH(menu1+5,menu2+85,		opt.D3D.Grib,optWallHack,9,"Грибы",pDevice);
		Draw_Button_TestWH(menu1+5,menu2+100,		10 , 10 ,opt.D3D.Listva,"Листва",pDevice);
		Draw_Button_TestWH(menu1+5,menu2+115,		10 , 10 ,opt.D3D.Svet,"Ночной свет",pDevice);
		Draw_Button_TestWH(menu1+5 ,menu2+130 ,     10 , 10 ,opt.D3D.cross , "Crosshair" , pDevice);
		Draw_Button_TestWH(menu1+5 ,menu2+145 ,     10 , 10 ,opt.D3D.WireFrame , "WireFrame" , pDevice);
}

		Draw_Button_TestTEXT(46,10,NULL,NULL,opt.glavnay.OptionsResset ,  "R" ,"Сбросить настройки", pDevice);
		Draw_Button_TestTEXT(60,10,NULL,NULL,opt.glavnay.OptionsSave   ,  "S" ,"Сохранить настройки", pDevice);
		Draw_Button_TestTEXT(74,10,NULL,NULL,opt.glavnay.OptionsLoad   ,  "L" ,"Загрузить настройки", pDevice);

if(opt.glavnay.DopMenu_Info)
{
	opt.D3D.main=1;
	 DrawBox(menu1,menu2,menu3,menu4,Main, pDevice);
	 font->DrawText(menu1+5,menu2+10,MENUCOLOR_F,"Информация о Dll:",NULL);
	 font->DrawText(menu1+5,menu2+25,MENUCOLOR_F,"By Игоръ",NULL);
	 font->DrawText(menu1+5,menu2+40,MENUCOLOR_F,TIME(),NULL);
	 //font->DrawText(300,63,Maintext,FPS(),DT_LEFT|DT_SHADOW);//ФПС	

	 //Draw_Button_TestWH(menu1+5,menu2+58,10,10,opt.D3D.FPS_SHOW,"Показ FPS",pDevice);
}
if (opt.glavnay.D3D)      Menu_1ShowMenu(pDevice);	
if (opt.glavnay.weaponC)  Menu_3ShowMenu(pDevice);
}
}

void cMenu::Menu_1ShowMenu(LPDIRECT3DDEVICE9 pDevice)
{
Menu_1Init();
if(!opt.glavnay.D3D) SHOW=(!SHOW);
if(SHOW)
{
		opt.D3D.main=1;
}
}
void cMenu::Menu_3ShowMenu (LPDIRECT3DDEVICE9 pDevice)
{
Menu_3Init();
if(!opt.glavnay.weaponC) SHOW=(!SHOW);
if(SHOW)
{
}
}
