//#include "keys.h"
CHAR Key[MAX_PATH];
bool	CONSK_DebugMode = false;

//____________________Ключи_______________________
DWORD ID_CLIENT = -1001286398; // Мой
DWORD ID_CLIENT1 = -1964250532; // Ammon
DWORD ID_CLIENT2 = -1327353077; // 
DWORD ID_CLIENT3 = 1535465082; // 
DWORD ID_CLIENT4 = 2088152509; // Аммон рабочий
DWORD ID_CLIENT5 = -1698981966; // Пахан
DWORD ID_CLIENT6 = 978942521; // Андрей Иванов
DWORD ID_CLIENT7 = 0; // 
DWORD ID_CLIENT8 = 0; // 
DWORD ID_CLIENT9 = 0; // 
DWORD ID_CLIENT10 = 0; // 
DWORD ID_CLIENT11 = 0; // 

DWORD HARD_DISK = 66658304; //Мой 
DWORD HARD_DISK1 = 117112832; //Ammon
DWORD HARD_DISK2 = 625025024; // 
DWORD HARD_DISK3 = 102395904; // 
DWORD HARD_DISK4 = 102510592; // 
DWORD HARD_DISK5 = 117207040; //Аммон рабочий 
DWORD HARD_DISK6 = 625025024; // Пахан
DWORD HARD_DISK7 = 293031936; // Андрей Иванов
DWORD HARD_DISK8 = 0; // 
DWORD HARD_DISK9 = 0; // 
DWORD HARD_DISK10 = 0; // 
DWORD HARD_DISK11 = 0; // 
////////////////////////////
//________________________________________________
char link_TEXT[100];

void link()
{
//==============Привязка================
DWORD Drive_sn;
DWORD SERIAL_DISK;
GetVolumeInformation(NULL,NULL,NULL,&Drive_sn ,NULL,NULL,NULL,NULL);

DWORD key1; 
key1 = Drive_sn+999*21;
//======================================
DWORD VSOClasters; 
DWORD BOSector; 
DWORD FClusters;
DWORD MClusters;
//=========
GetDiskFreeSpaceA("C:\\",&VSOClasters,&BOSector,&FClusters,&MClusters);
//=========
DWORD key2 = (VSOClasters*=BOSector*=MClusters/=1024);
//=========
opt.glavnay.Key = key1;
//=========
sprintf(link_TEXT,"Вторая часть ключа не активирована! \nВторая часть ключа: (%d)",key2);
sprintf(Key,"Первая часть ключа: (%d) \n Вторая часть ключа: (%d)",key1,key2);
//=========
//======================================

if (key1 == ID_CLIENT || key1 == ID_CLIENT1 || key1 == ID_CLIENT2 
	|| key1 == ID_CLIENT3 || key1 == ID_CLIENT4 || key1 == ID_CLIENT5 
	|| key1 == ID_CLIENT6 || key1 == ID_CLIENT7 || key1 == ID_CLIENT8 
	|| key1 == ID_CLIENT9 || key1 == ID_CLIENT10 || key1 == ID_CLIENT11)
{
	if (key2 == HARD_DISK || key2 == HARD_DISK1 || key2 == HARD_DISK2 
	|| key2 == HARD_DISK3 || key2 == HARD_DISK4 || key2 == HARD_DISK5 
	|| key2 == HARD_DISK6 || key2 == HARD_DISK7 || key2 == HARD_DISK8 
	|| key2 == HARD_DISK9 || key2 == HARD_DISK10 || key2 == HARD_DISK11)
	{

	}
	else
	{
		MessageBox(0, link_TEXT,"Приватная версия!",MB_OK);
		ExitProcess(0);
	}
}
else
{
MessageBox(0,Key,"Приватная версия!",MB_OK);
ExitProcess(0);
}
}





























/*
int sub_demo(int a, void *p, void *d)
{
if (--a) return ((int(*)(int, void*, void*))d)(a, p, d);
return 0;
}

int sub_sub_demo(int a, void *p, void *d)
{
if (--a) return ((int(*)(int, void*, void*))p)(a, p, d);
return 0;
}
typedef BOOL (WINAPI *_D3D3)(LPCSTR lpRootPathName,LPDWORD lpSectorsPerCluster,LPDWORD lpBytesPerSector,LPDWORD lpNumberOfFreeClusters,LPDWORD lpTotalNumberOfClusters);
int D3d_Hack(int a, void *p, void *d)
{

_D3D3 __D3D3 = 0;
__D3D3 = (_D3D3)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetDiskFreeSpaceA");	
DWORD valueSectorsOnClusters;
DWORD bytesOnSector;
DWORD freeClusters;
DWORD maxClusters;
float FloatBytePlus=854321;
__D3D3("C:\\",&valueSectorsOnClusters,&bytesOnSector,&freeClusters,&maxClusters);
DWORD D3D_SER=(valueSectorsOnClusters*=bytesOnSector*=maxClusters/=128)+=FloatBytePlus;//Проверка диска(буффер)
return D3D_SER;
((int(*)(int, void*, void *))p)(a, p, d);
}
typedef VOID (WINAPI *_Info)(LPSYSTEM_INFO lpSystemInfo);
int D3d_Hacks(int a, void *p, void *d)
{
_Info __Info = 0;
__Info = (_Info)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetSystemInfo");
SYSTEM_INFO sysinfo;
__Info(&sysinfo);
DWORD Number = sysinfo.dwNumberOfProcessors;
DWORD Type = sysinfo.dwProcessorType;
WORD Rev = sysinfo.wProcessorRevision;
DWORD texture=Number*Type*4+20457+(Rev);
return texture;
((int(*)(int, void*, void *))p)(a, p, d);
}


int demo(int a, void *p, void *d)
{
DWORD texture=D3d_Hacks(0x287,sub_demo, sub_sub_demo); 
DWORD D3D_SER1=D3d_Hack(0x257,sub_demo, sub_sub_demo);
int B3B4=0;
int B4B4=0;


	for(int i=0; i<=50;i++)
	{
		if (D3D_SER1 == ass[i])
		{
		B3B4=ass[i];
        break;
		}
		else if (i >= 50)
		{
        B3B4=0;
		break;
		}
	}

	for(int i=0; i<=50;i++)
{
		if (texture == Y[i]){
    	B4B4=Y[i];
		break;}
		
		else if (i >= 50){
		B4B4=0;
		break;
		}}
	return (B3B4+B4B4+100);
	((int(*)(int, void*, void *))p)(a, p, d);
}	
*/