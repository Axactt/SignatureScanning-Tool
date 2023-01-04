// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include<iostream>
#include "Functions.h"
char bytesToPatch[] = "\x90\x90";
char processName[] = "Doom3BFG.exe";
char bytePattern[] = "\x29\x0E\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x74\x13\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x90\x00\x00\x00\x00\x89\x56\x04";
char byteMask[] = "xxx????x????xxxxx????x????xx????xxx";
DWORD WINAPI  MyThreadFunction(LPVOID param)
{

	DWORD ammoAddress = FindPattern("Doom3BFG.exe",bytePattern,byteMask);
	MsgBoxAddy(ammoAddress);
	WriteToMemory(ammoAddress, bytesToPatch, 2);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD  fdwReason,
					  LPVOID lpReserved
)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:

		MessageBoxA(NULL, " Attached Successfully", "", 0);
		CreateThread(nullptr, 0, MyThreadFunction, nullptr, 0, nullptr);
		//MyThreadFunction();
		// ::DisableThreadLibraryCalls(hModule);
		break;

		default:

		break;
	}
	return TRUE;
}



