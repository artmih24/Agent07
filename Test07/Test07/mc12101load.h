////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// mc12101load.h -                                                            //
//                                                                            //
//      Load and exchange library function declaration                        //
//      (for one-processor board MC121.01)                                    //
//                                                                            //
// Copyright (c) 2018 RC Module                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef __MC12101LOAD__H__
#define __MC12101LOAD__H__

#include <windows.h>

#define PLOAD_VERSION "3.4"
#define PLOAD_MAJOR_VERSION 3
#define PLOAD_MINOR_VERSION 4

#ifdef _MAKE_DLL
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// 32 bit unsigned NM memory element type
	typedef unsigned long PL_Word;

	// 32 bit unsigned NM address type
	typedef unsigned long PL_Addr;

	// Board descriptor
	struct PL_Board;

	// Processor on board descriptor
	struct PL_Access;

	// Library functions return values (all library functions return result code)
	enum RetValue
	{
		PL_OK              = 0, // Ok
		PL_ERROR           = 1, // Error
		PL_TIMEOUT         = 2, // Timeout of wait for operation
		PL_FILE            = 3, // Cannot find file for load
		PL_BADADDRESS      = 4, // Bad address ranges
		PL_NOT_IMPLEMENTED = -1 // Not implemented
	};

	// Flag of the user's program work end
	const PL_Word PROGRAM_FINISHED = 0x2;

	//------------------//
	// Common functions //
	//------------------//

	// Return version of library in variable pointed by 'version'
	DECLSPEC int PL_GetVersion(unsigned int *version);

	// Return number of detected boards in variable pointed by 'count'
	DECLSPEC int PL_GetBoardCount(unsigned int *count);

	// Create descriptor for board number 'index'
	// Return descriptor in variable pointed by 'board'
	// Boards index count from 0
	DECLSPEC int PL_GetBoardDesc(unsigned int index, PL_Board **board);

	// Close board descriptor and free descriptor memory
	DECLSPEC int PL_CloseBoardDesc(PL_Board *board);

	//-----------------//
	// Board functions //
	//-----------------//

	// Get version of firmware of board
	DECLSPEC int PL_GetFirmwareVersion(PL_Board *board, unsigned int *version_major, unsigned int *version_minor);

	// Send RESET signal to board and all processors on board
	DECLSPEC int PL_ResetBoard(PL_Board *board);

	// Get mask of processors on board
	DECLSPEC unsigned int PL_GetProcMask(PL_Board *board);

	// Set mask of processors on board
	DECLSPEC unsigned int PL_SetProcMask(PL_Board *board, unsigned int mask);

	// Load init code to board
	// Call this function after reset board and before loading user program to processors.
	DECLSPEC int PL_LoadInitCode(PL_Board *board);

	// Create descriptor for processor number 'procNo' on board
	// Return processor descriptor in variable pointed by 'access'
	// Processor number is 0
	DECLSPEC int PL_GetAccess(PL_Board *board, unsigned int procNo, PL_Access **access);

	// Close processor descriptor
	DECLSPEC int PL_CloseAccess(PL_Access *access);

	//---------------------//
	// Processor functions //
	//---------------------//

	// Load user program on processor and start execution
	DECLSPEC int PL_LoadProgramFile(PL_Access *access, const char *filename);

	// Read array from shared memory
	// block   - Pointer to destination buffer in PC memory
	// len     - Size of array in 32-bit words
	// address - Address of source array in NM memory
	DECLSPEC int PL_ReadMemBlock(PL_Access *access, PL_Word *block, PL_Addr address, PL_Word len);

	// Write array in shared memory
	// block   - Pointer to source array in PC memory
	// len     - Size of array in 32-bit words
	// address - Address of destination array in NM memory
	DECLSPEC int PL_WriteMemBlock(PL_Access *access, PL_Word *block, PL_Addr address, PL_Word len);

	// Barrier syncronization with program on board processor
	// value       - value sent to processor
	// returnValue - value received from processor
	DECLSPEC int PL_Sync(PL_Access *access, int value, int *returnValue);

	// Barrier syncronization with program on board processor
	// Additionally perform two values exchange
	// value       - value sent to processor
	// outAddress  - address sent to processor
	// outLen      - size sent to processor
	// returnValue - value received from processor
	// inAddress   - address received from processor
	// inLen       - size received from processor
	// Values return only if pointers are not NULL
	DECLSPEC int PL_SyncArray(
		PL_Access *access,  // Processor descriptor

		int value,          // Value sent to processor
		PL_Addr outAddress, // Address sent to processor
		PL_Word outLen,     // Size sent to processor

		int *returnValue,   // Value received from processor
		PL_Addr *inAddress, // Address received from processor
		PL_Word *inLen);    // Size received from processor

	// Set timeout in milliseconds for waiting function
	// Used in all PL_SyncXXX functions
	DECLSPEC int PL_SetTimeout(DWORD timeout);

	// Send interrupt on processor
	DECLSPEC int PL_Interrupt(PL_Access *access);

	// Return status bits in variable 'status'
	DECLSPEC int PL_GetStatus(PL_Access *access, PL_Word *status);

	// Return user program return value in variable 'result'
	DECLSPEC int PL_GetResult(PL_Access *access, PL_Word *result);

	//-----------------------------------------------------//
	// Board to host interrupt functions (Board functions) //
	//-----------------------------------------------------//

	// Enable / disable interrupt from processors
	// board - board descriptor
	// mask - bitwise processor mask (0 - disable, 1 - enable)
	// prev - previous bitwise mask (returned)
	// Return PL_OK, PL_ERROR
	DECLSPEC int PL_MaskInterrupt(PL_Board *board, DWORD mask, DWORD *prev);

	// Wait for interrupt from board
	// board - board descriptor
	// timeOut - time-out interval, in milliseconds
	//	If timeOut is zero, function returns immediately.
	//	If timeOut is INFINITE (0xFFFFFFFF), the function's time-out interval never elapses.
	// ProcMask - interrupt source processors (bitwise mask, returned)
	// Return PL_OK, PL_TIMEOUT, PL_ERROR
	DECLSPEC int PL_WaitInterrupt(PL_Board *board, DWORD timeOut, DWORD *ProcMask);

	// Cancel all waits for interrupt from board
	// board - board descriptor
	// Returns PL_OK, PL_ERROR
	DECLSPEC int PL_CancelWaitInterrupt(PL_Board *board);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // __MC12101LOAD__H__
