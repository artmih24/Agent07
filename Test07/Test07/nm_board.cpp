#include "pch.h"
#include "nm_board.h"
#include <assert.h>
#include <stdio.h>


//-------------------------------------------------------------------------------------------------------
int NMBoard::Load(unsigned boardNumber, unsigned timeout,const char *file1, const char *file2)
{
	assert(file1 != 0 || file2 != 0);

	PL_SetTimeout(timeout);

	number = boardNumber;

    if ( PL_LoadInitCode( board ) != PL_OK )
		return NM_INIT_BOARD_ERR;

	if (file1 != 0)
	{

		int res = PL_GetAccess(board, 0, &access1);
		if (res != PL_OK) return NM_CPU1_ACCESS_ERR;
		printf("-- ");

		res = PL_LoadProgramFile(access1, file1); printf("--\n"); // Здесь зависает на макете!
		if (res != PL_OK)	return NM_LOAD_FILE1_ERR;

	}


	if(file2!=0)
	{

		int res = PL_GetAccess(board, 1, &access2);
		if (res != PL_OK) return NM_CPU1_ACCESS_ERR;

		res = PL_LoadProgramFile(access2, file2);
		if (res != PL_OK)	return NM_LOAD_FILE1_ERR;

	}


	return NM_OK;
	
}

//-------------------------------------------------------------------------------------------------------
int NMBoard::SyncArray(int cpu,int value, PL_Addr outAddress,PL_Word outLen,
               int * returnValue,PL_Addr * inAddress,PL_Word *inLen)
{

	PL_Access * access;
	access=(cpu==0)?access1:access2;

	return PL_SyncArray(access,value,outAddress,outLen,returnValue,inAddress,inLen);

}

//-------------------------------------------------------------------------------------------------------
int NMBoard::Sync( int cpu, int value, int * returnValue )
{
	PL_Access * access;
	access=(cpu==0)?access1:access2;
	
	return PL_Sync( access, value, returnValue );

}

//-------------------------------------------------------------------------------------------------------
int NMBoard::ReadMemBlock(int cpu, void *dest, PL_Addr nm_addr, int size32)
{
	PL_Access * access;
	access = (cpu == 0) ? access1 : access2;
	return PL_ReadMemBlock(access, (PL_Word*)(dest), (PL_Addr)nm_addr, size32);
}

//-------------------------------------------------------------------------------------------------------
int NMBoard::WriteMemBlock(int cpu, void* source, PL_Addr nm_addr, int size32)
{
	PL_Access * access;
	access = (cpu == 0) ? access1 : access2;
	return PL_WriteMemBlock(access, (PL_Word*)source, nm_addr, size32);
}

//-------------------------------------------------------------------------------------------------------
int NMBoard::Reset(unsigned boardNumber)
{
	Release();

	unsigned boardCount;
	number = boardNumber;

	if (PL_GetBoardCount(&boardCount) != PL_OK)
		return NM_DRIVER_OPEN_ERR;

	if (boardCount < 1 + boardNumber)
		return NM_NOBOARD_ERR;


	if (PL_GetBoardDesc(boardNumber, &board) != PL_OK)
		return NM_NOBOARD_ERR;


	// if ( PL_ResetBoard( board ) != PL_OK )
	//	return NM_RESET_BOARD_ERR;

	PL_ResetBoard(board);

	return NM_OK;

}


