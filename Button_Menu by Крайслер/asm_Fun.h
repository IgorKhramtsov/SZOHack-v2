#ifndef asm_Fun_h
#define asm_Fun_h

#include "memhack.h"

HMODULE StalkerOnline = GetModuleHandleA("StalkerOnline.exe");

DWORD WRNC;
const DWORD WRNC_Return1=0x4332A9;
const DWORD WRNC_Return2=0x433B66;
DWORD adrwrncs;
DWORD adrwrs;

__declspec(naked) void WRNC_on1()
{
adrwrncs=opt.memhack.adrWRNC;
adrwrs=opt.memhack.adrWR;
 __asm 
 {

cmp EAX,dword ptr [adrwrncs]
jne a
sub esp,0x08
fstp qword ptr [esp]
inc [WRNC]
cmp dword ptr [WRNC],0x00000001
jne b
push eax
mov eax, dword ptr [adrwrs]
mov [eax],0x74CCCCCC
pop eax
jmp        [WRNC_Return1]

b:
jmp        [WRNC_Return1]

a:
sub esp,0x08
fstp qword ptr [esp]
jmp        [WRNC_Return1]
 }
}

__declspec(naked) void WRNC_off1()
{
 __asm 
 {
sub esp,0x08
fstp qword ptr [esp]
jmp        [WRNC_Return1]
}
}

__declspec(naked) void WRNC_on2()
{
adrwrncs=opt.memhack.adrWRNC;
adrwrs=opt.memhack.adrWR;
 __asm 
 {


fldz
mov eax,[esp+0x04]
cmp EAX,dword ptr [adrwrncs]
jne c
push eax
mov eax, dword ptr [adrwrs]
mov [eax],0xF4CCCCCC
pop eax
mov [WRNC],0x0
jmp        [WRNC_Return2]

 c:
jmp        [WRNC_Return2]
 }
}

__declspec(naked) void WRNC_off2()
{
adrwrs=opt.memhack.adrWR;
 __asm 
 {
push eax
mov eax, dword ptr [adrwrs]
mov [eax],0xF4CCCCCC
pop eax
fldz
mov eax,[esp+0x04]
jmp        [WRNC_Return2]
 }
}



/*
///////////////////////////_____(Адресса)______//////////////////////////////////////////
//DWORD AdressTusa_Return=0x5D17FC;
DWORD AdressTusa_Return=0x5CEF8C;
DWORD AdressFrezeHeigthReturn=0x005DE886;
DWORD AdressZoomReturn=0xC00810;
DWORD AdrsssfastZoomReturn=0xC0081B;
///////////////////////////_____(Переменные)___//////////////////////////////////////////
float fastZoom=0;
char a;
////////////////////////////МгнZoom//////////////////////////////////////////
__declspec(naked) void fastZoomHack_on()
{
 __asm 
 {
movss			[fastZoom],xmm0
jmp		[AdrsssfastZoomReturn]
 }
}
__declspec(naked) void fastZoomHack_off()
{
 __asm 
 {
movss			[esi+0x14],xmm0
jmp 	[AdrsssfastZoomReturn]
 }
}
////////////////////////////ZoomHack//////////////////////////////////////////
__declspec(naked) void ZoomHack_on()
{
 __asm 
 {
mov byte ptr		[esi+0x08],01
jmp		[AdressZoomReturn]
 }
}
__declspec(naked) void ZoomHack_off()
{
 __asm 
 {
mov byte ptr		[esi+0x08],01
jmp 	[AdressZoomReturn]
 }
}
////////////////////////////Тусовка Мобов/////////////////////////////////////
__declspec(naked) void TUSA_MOB_on()
{
 __asm 
 {
mov				edi,[playerXmob]
mov				[eax+0x10],edi
mov				edi,[Heigthmob]
lea				ecx,[eax+0x10]
mov				[ecx+0x04],edi
mov				edx,[playerYmob]
jmp		[AdressTusa_Return]
 }
}
__declspec(naked) void TUSA_MOB_off()
{
 __asm 
 {
mov				edi,[edx]
mov				[eax+0x10],edi
mov				edi,[edx+0x04]
lea				ecx,[eax+0x10]
mov				[ecx+0x04],edi
mov				edx,[edx+0x08]


jmp 	[AdressTusa_Return]
 }
}

////////////////////////////////////////////
*/

/*
HMODULE PointBlank = GetModuleHandleA("PointBlank.exe");

DWORD Addres_GetMoveSpe         = (DWORD)PointBlank + 0x6379BC;
DWORD Addres_GetJumpPenaltyTime = (DWORD)PointBlank + 0x65B8CC;


//________________(Высота Прижка)____________________//65bc80
DWORD Addres_Up_Jump = Addres_GetJumpPenaltyTime + 0x3B4;
DWORD RETURN_Up_Jump = Addres_Up_Jump + 0x5;
//__________________(Длиный Нож)_____________________//
DWORD ADDRES_Knife      =  Addres_GetMoveSpe + 0x960;
DWORD RETURN_Long_Knife =  ADDRES_Knife + 0x5;
//_________________(Анлим Патроны)__________________//
DWORD ADDRES_Max_Bullet = Addres_GetMoveSpe + 0x17DC;
DWORD RETURN_Max_Bullet = ADDRES_Max_Bullet + 0x6;
 //_______________(Длиный Нож)________________//


//_________________(Анти-Отдача)____________________//
DWORD ADDRES_Antioda_1 = Addres_GetMoveSpe + 0x65E;
DWORD ADDRES_Antioda_2 = Addres_GetMoveSpe + 0x4FE;
DWORD RETURN_Antioda_1 = ADDRES_Antioda_1 + 0x5;
DWORD RETURN_Antioda_2 = ADDRES_Antioda_2 + 0x5;




float logm=300;

float patron=1;
float jumpv=20;
float jumpd=0.01;
float ant;



//__________________(Анти-Одача)__________________//
__declspec( naked ) void Antioda_1_on()
{
 _asm
 {
  fld dword ptr [ant]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_1]
 }
}
__declspec( naked ) void Antioda_1_off()
{
 _asm
 {
  fld dword ptr [ebp-8]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_1]
 }
}
__declspec( naked ) void Antioda_2_on()
{
 _asm
 {
  fld dword ptr [ant]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_2]
 }
}
__declspec( naked ) void Antioda_2_off()
{
 _asm
 {
  fld dword ptr [ebp-8]
  mov esp,ebp
  jmp dword ptr [RETURN_Antioda_2]
 }
}
//////////////////////////////////////
__declspec(naked)void knife_on()
{
_asm
{
fld dword ptr[logm]
mov esp,ebp
jmp dword ptr[RETURN_Long_Knife]
}
}
__declspec(naked)void knife_off()
{
_asm
{
fld dword ptr[ebp-04]
mov esp,ebp
jmp dword ptr[RETURN_Long_Knife]
}
}

//
//_______________(Анлим Патроны)________________//
__declspec( naked ) void Max_Bullet_on()
{
 _asm
 {
  mov eax,[patron]
  pop esi
  mov esp,ebp
  jmp dword ptr [RETURN_Max_Bullet]
 }
}
__declspec( naked ) void Max_Bullet_off()
{
 _asm
 {
  mov     eax, [ebp-4]
  pop esi
  mov esp,ebp
  jmp dword ptr [RETURN_Max_Bullet]
 }
}




//______________(Высота Прыжка)_________________//
__declspec(naked)void Up_Jump_On()
{
_asm
{
movss   xmm0, [jumpv]
jmp dword ptr[RETURN_Up_Jump]
}
}
__declspec(naked)void Up_Jump_off()
{
_asm
{
movss   xmm0, [ebp-5Ch]
jmp dword ptr[RETURN_Up_Jump]
}
}

*/





#endif