#include "cHacks.h"
#include "Coord.h"
#include "stdafx.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <Mmsystem.h>
#include "cMain.h"
#include <cmath>

#pragma comment (lib, "Winmm.lib")
//////////////////////////////////////////////////////////////////////////
 HMODULE SO = GetModuleHandleA("SZoneOnline.exe");
 //Буфферы
 DWORD ipbuf;
 DWORD buf1;
 DWORD buf2;
 DWORD buf3;
 DWORD Addr;
 //*******************

 //Переменные
 float zoom;
 float playerY;
 float playerX;
 float X_ =0;
 float Y_ =0;
 float Asimut;
 float Heigth;
 float Vertical;
 float playerXmob;
 float playerYmob;
 float Heigthmob;
 float persX;
 float persY;
 float persH;
 float persX_=0;
 float persY_=0;
 float persH_=0;
 //*******************

 //Адресса
 DWORD base_addr;
 DWORD adrCamera;
 DWORD base_addr_Accuracy;
 DWORD base_addr_Accuracy2=0x400000+0x0073D4D0;
 //*******************

 //Оффсеты
  DWORD H_offset=0x24;
  DWORD X_offset=0x20;
  DWORD Y_offset=0x28;
  DWORD Asimut_offset=0x20;
  DWORD Vertical_offset=0x1c;
  DWORD adrMobX=0x18F11C;
  DWORD adrMobY=0x18F120;
  DWORD adrMobH=0x18F124;
  //******************

  const float pi=3.1415926535f;
 //////////////////////////////////////////////////////////////////////////
void memhack()
{
  //Rus
  if(opt.glavnay.RUS==1)
  {
  base_addr=(DWORD)SO+0x783270;//Teleport
  adrCamera=(DWORD)SO+0x7E0160;//Camera
  base_addr_Accuracy=(DWORD)SO+0x0073D4D0;//Accuracy
  }
  //************

  //ENG
  if(opt.glavnay.ENG==1)
  {
  base_addr=(DWORD)SO+0x783270;//Teleport
  adrCamera=(DWORD)SO+0x7E0160;//Camera
  base_addr_Accuracy=(DWORD)SO+0x0073D4D0;//Accuracy
  }
  //************

	opt.memhack.Xplayer=playerX;
	opt.memhack.Yplayer=playerY;
	opt.memhack.HeigthPlayer=Heigth;
	opt.memhack.AsimutPlayer=Asimut;
	opt.memhack.VerticalPlayer=Vertical;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (base_addr), &ipbuf, sizeof(ipbuf), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (adrCamera), &buf1, sizeof(buf1), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (base_addr_Accuracy), &buf2, sizeof(buf2), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (base_addr_Accuracy2), &buf3, sizeof(buf3), NULL);

	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (buf2+0x194), &buf2, sizeof(buf2), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (buf2+0x1c), &opt.memhack.AccuracyVoll, sizeof(opt.memhack.AccuracyVoll), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (opt.memhack.AccuracyVoll+0x13e), &opt.memhack.Accuracy_addr, sizeof(opt.memhack.Accuracy_addr), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (buf3+0x194), &buf3, sizeof(buf3), NULL);
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (buf3+0x20), &buf3, sizeof(buf3), NULL);

	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+0x50), &ipbuf, sizeof(ipbuf), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+X_offset), &playerX, sizeof(playerX), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+Y_offset), &playerY, sizeof(playerY), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth), NULL);
      
	  ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (buf1+Asimut_offset), &Asimut, sizeof(Asimut), NULL);
      ReadProcessMemory(GetCurrentProcess(), (LPVOID*)(DWORD) (buf1+Vertical_offset), &Vertical, sizeof(Vertical), NULL);

	  
	  opt.memhack.adrWRNC=buf3+0x140;
	  opt.memhack.adrWR=buf3+0x14B;

      Heigth=Heigth+pi/18;

	  if (abs(Asimut)<=(pi/2)) { X_=Asimut;}
	  else if (Asimut>=0) { X_=(pi/2)-(abs(Asimut)-(pi/2));}
	  else  {X_=(-1*pi/2)+(abs(Asimut)-(pi/2));}
      if (abs(Asimut)<=(pi/2)) 
	  {
			  if (X_>0) 
			  {
				  Y_=(pi/2)-X_;
			  } 
			  else 
			  {
				  Y_=(pi/2)+X_;
			  }
	  } 
	  else if (X_>0) {Y_=X_-(pi/2);} 
	  else {Y_=-1*(X_+(pi/2));}

	opt.memhack.Xplayer1=X_;
	opt.memhack.Yplayer1=Y_;

      playerX==playerX+X_/5;
      playerY==playerY+Y_/5;

	  
			playerXmob=playerX+2;
			playerYmob=playerY+2;
			Heigthmob=Heigth;

	  
	  if(GetAsyncKeyState(VK_SUBTRACT)&1)
	  {
		  playerX=playerX+(X_/2);
		  playerY=playerY+(Y_/2);
		  Sleep (60);
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  }
	  	  if(GetAsyncKeyState(VK_ADD)&1)
	  {
		  playerX=playerX+(X_/2*-1);
		  playerY=playerY+(Y_/2)*-1;
		  Sleep (60);
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  }

	  if((GetAsyncKeyState(VK_SHIFT))&&(GetAsyncKeyState(VK_UP)&1))
	  {
		  playerX=playerX+(X_*40);
		  playerY=playerY+(Y_*40);
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  }
	  	  if((GetAsyncKeyState(VK_SHIFT))&&(GetAsyncKeyState(VK_DOWN)&1))
	  {
		  playerX=playerX+(X_*40)*-1;
		  playerY=playerY+(Y_*40)*-1;
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  }
			  

		  		  if(opt.memhack.GurmanTP==1)
				  {
	  if(opt.memhack.GurmanPos==1)
	  {
		  playerX=GurX;
		  playerY=GurY;
		  Heigth=GurH-150;
	  }
	  else if (opt.memhack.GurmanPos==0)
	  {
		  playerX=GurX;
		  playerY=GurY;
		  Heigth=GurH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.GurmanTP=0;
				  }

				  if(opt.memhack.Gorod3==1)
				  {
	  if(opt.memhack.Gorod3Pos==1)
	  {
		  playerX=KP3X;
		  playerY=KP3Y;
		  Heigth=KP3H-150;
	  }
	  else if (opt.memhack.Gorod3Pos==0)
	  {
		  playerX=KP3X;
		  playerY=KP3Y;
		  Heigth=KP3H;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Gorod3=0;
				  }

				  if (opt.memhack.UkrepH4==1)
				  {
					  playerX=UkrepH4X;
					  playerY=UkrepH4Y;
					  if(opt.memhack.UkrepH4Pos==1){Heigth=UkrepH4H-150;}
					  else {Heigth=UkrepH4H;}
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.UkrepH4=0;
				  }

				  if(opt.memhack.Laba==1)
				  {
	  if(opt.memhack.LabaPos==1)
	  {
		  playerX=SinceX;
		  playerY=SinceY;
		  Heigth=SinceH-150;
	  }
	  else if (opt.memhack.LabaPos==0)
	  {
		  playerX=SinceX;
		  playerY=SinceY;
		  Heigth=SinceH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Laba=0;
				  }
				  if(opt.memhack.Boloto==1)
				  {
	  if(opt.memhack.BolotoPos==1)
	  {
		  playerX=O10X;
		  playerY=O10Y;
		  Heigth=O10H-150;
	  }
	  else if (opt.memhack.BolotoPos==0)
	  {
		  playerX=O10X;
		  playerY=O10Y;
		  Heigth=O10H;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Boloto=0;
				  }
				  if(opt.memhack.inputRyab==1)
				  {
	  if(opt.memhack.inputRyabPos==1)
	  {
		  playerX=INRyabX;
		  playerY=INRyabY;
		  Heigth=INRyabH-150;
	  }
	  else if (opt.memhack.inputRyabPos==0)
	  {
		  playerX=INRyabX;
		  playerY=INRyabY;
		  Heigth=INRyabH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.inputRyab=0;
				  }
				  if(opt.memhack.Himka==1)
				  {
	  if(opt.memhack.HimkaPos==1)
	  {
		  playerX=HimX;
		  playerY=HimY;
		  Heigth=HimH-150;
	  }
	  else if (opt.memhack.HimkaPos==0)
	  {
		  playerX=HimX;
		  playerY=HimY;
		  Heigth=HimH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Himka=0;
				  }
				  if(opt.memhack.Sanatorka==1)
				  {
	  if(opt.memhack.SanatorkaPos==1)
	  {
		  playerX=SanatorX;
		  playerY=SanatorY;
		  Heigth=SanatorH-150;
	  }
	  else if (opt.memhack.SanatorkaPos==0)
	  {
		  playerX=SanatorX;
		  playerY=SanatorY;
		  Heigth=SanatorH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Sanatorka=0;
				  }
				  if(opt.memhack.White==1)
				  {
	  if(opt.memhack.WhitePos==1)
	  {
		  playerX=DWhiteX;
		  playerY=DWhiteY;
		  Heigth=DWhiteH-150;
	  }
	  else if (opt.memhack.WhitePos==0)
	  {
		  playerX=DWhiteX;
		  playerY=DWhiteY;
		  Heigth=DWhiteH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.White=0;
				  }
				  if(opt.memhack.Bandits==1)
				  {
	  if(opt.memhack.BanditsPos==1)
	  {
		  playerX=PBanditsX;
		  playerY=PBanditsY;
		  Heigth=PBanditsH-150;
	  }
	  else if (opt.memhack.BanditsPos==0)
	  {
		  playerX=PBanditsX;
		  playerY=PBanditsY;
		  Heigth=PBanditsH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Bandits=0;
				  }
				  if(opt.memhack.Provodnik==1)
				  {
	  if(opt.memhack.ProvodnikPos==1)
	  {
		  playerX=ProvodnikX;
		  playerY=ProvodnikY;
		  Heigth=ProvodnikH-150;
	  }
	  else if (opt.memhack.ProvodnikPos==0)
	  {
		  playerX=ProvodnikX;
		  playerY=ProvodnikY;
		  Heigth=ProvodnikH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Provodnik=0;
				  }
				  if(opt.memhack.Paukan==1)
				  {
	  if(opt.memhack.PaukanPos==1)
	  {
		  playerX=PaukRespX;
		  playerY=PaukRespY;
		  Heigth=PaukRespH-150;
	  }
	  else if (opt.memhack.PaukanPos==0)
	  {
		  playerX=PaukRespX;
		  playerY=PaukRespY;
		  Heigth=PaukRespH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Paukan=0;
				  }
				  if(opt.memhack.Paukan2==1)
				  {
	  if(opt.memhack.Paukan2Pos==1)
	  {
		  playerX=PaukKostX;
		  playerY=PaukKostY;
		  Heigth=PaukKostH-150;
	  }
	  else if (opt.memhack.Paukan2Pos==0)
	  {
		  playerX=PaukKostX;
		  playerY=PaukKostY;
		  Heigth=PaukKostH;
	  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Paukan2=0;
				  }
	  if (opt.memhack.Anomaly==1)
		{
					  if(opt.memhack.AnomalyPos==1)
					  {
						  playerX=crvAnomalyX;
						  playerY=crvAnomalyY;
						  Heigth=crvAnomalyH-150;
					  }
					  else if (opt.memhack.AnomalyPos==0)
					  {
						  playerX=crvAnomalyX;
						  playerY=crvAnomalyY;
						  Heigth=crvAnomalyH;
					  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Anomaly=0;
		}

	  	  if (opt.memhack.Psiha==1)
		{
					  if(opt.memhack.PsihaPos==1)
					  {
						  playerX=PsihaX;
						  playerY=PsihaY;
						  Heigth=PsihaH-150;
					  }
					  else if (opt.memhack.PsihaPos==0)
					  {
						  playerX=PsihaX;
						  playerY=PsihaY;
						  Heigth=PsihaH;
					  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.Psiha=0;
		}
		  	  	  if (opt.memhack.ProvodnikInCrv==1)
		{
					  if(opt.memhack.ProvodnikInCrvPos==1)
					  {
						  playerX=ProvodnikInCrvX;
						  playerY=ProvodnikInCrvY;
						  Heigth=ProvodnikInCrvH-150;
					  }
					  else if (opt.memhack.ProvodnikInCrvPos==0)
					  {
						  playerX=ProvodnikInCrvX;
						  playerY=ProvodnikInCrvY;
						  Heigth=ProvodnikInCrvH;
					  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.ProvodnikInCrv=0;
		}
		 if (opt.memhack.ProvodnikCrv==1)
		{
					  if(opt.memhack.ProvodnikCrvPos==1)
					  {
						  playerX=ProvodnikCrvX;
						  playerY=ProvodnikCrvY;
						  Heigth=ProvodnikCrvH-150;
					  }
					  else if (opt.memhack.ProvodnikCrvPos==0)
					  {
						  playerX=ProvodnikCrvX;
						  playerY=ProvodnikCrvY;
						  Heigth=ProvodnikCrvH;
					  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.ProvodnikCrv=0;
		}
		 		 if (opt.memhack.ProvodnikCrv2==1)
		{
					  if(opt.memhack.ProvodnikCrv2Pos==1)
					  {
						  playerX=ProvodnikCrv2X;
						  playerY=ProvodnikCrv2Y;
						  Heigth=ProvodnikCrv2H-150;
					  }
					  else if (opt.memhack.ProvodnikCrv2Pos==0)
					  {
						  playerX=ProvodnikCrv2X;
						  playerY=ProvodnikCrv2Y;
						  Heigth=ProvodnikCrv2H;
					  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.ProvodnikCrv2=0;
		}
				 		 if (opt.memhack.ProvodnikCrv3==1)
		{
					  if(opt.memhack.ProvodnikCrv3Pos==1)
					  {
						  playerX=ProvodnikCrv3X;
						  playerY=ProvodnikCrv3Y;
						  Heigth=ProvodnikCrv3H-150;
					  }
					  else if (opt.memhack.ProvodnikCrv3Pos==0)
					  {
						  playerX=ProvodnikCrv3X;
						  playerY=ProvodnikCrv3Y;
						  Heigth=ProvodnikCrv3H;
					  }
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
	  opt.memhack.ProvodnikCrv3=0;
		}


	  if(GetAsyncKeyState(VK_SHIFT))
	  {
		  if(GetAsyncKeyState(VK_RIGHT)&1)
		  {
			  playerX=-1658;
			  playerY=1183;
			  Heigth=-1;
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+X_offset),&playerX, sizeof(playerX),NULL); //X
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+Y_offset),&playerY, sizeof(playerY),NULL); //Y
	  WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL); //H
		  }
	  }

	  if(GetAsyncKeyState(VK_PRIOR)&1)
	  {
		  if (opt.memhack.Jump==1)
		  {
	  Heigth = Heigth+1;
		  }
		  if (opt.memhack.Jump==2)
		  {
	  Heigth = Heigth+5;
		  }
		  if (opt.memhack.Jump==3)
		  {
	  Heigth = Heigth+10;
		  }
		  if (opt.memhack.Jump==4)
		  {
	  Heigth = Heigth+15;
		  }
		  if (opt.memhack.Jump==5)
		  {
	  Heigth = Heigth+150;
		  }
		WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL);
	  }
	  if(GetAsyncKeyState(VK_NEXT)&1)
	  {
		  if (opt.memhack.Jump1==1)
		  {
	  Heigth = Heigth-1;
		  }
		  if (opt.memhack.Jump1==2)
		  {
	  Heigth = Heigth-5;
		  }
		  if (opt.memhack.Jump1==3)
		  {
	  Heigth = Heigth-10;
		  }
		  if (opt.memhack.Jump1==4)
		  {
	  Heigth = Heigth-15;
		  }
		  if (opt.memhack.Jump1==5)
		  {
	  Heigth = Heigth-150;
		  }
      WriteProcessMemory(GetCurrentProcess(),(LPVOID*)(DWORD) (ipbuf+H_offset), &Heigth, sizeof(Heigth),NULL);
	  }

}