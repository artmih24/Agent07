#ifndef  __NM_BOARD_H_INCLUDED__
#define  __NM_BOARD_H_INCLUDED__

//#include "nm2load.h"
#include "mc12101load.h"

enum NM1_Retval {
        NM_OK                 = 0,    // OK.
        NM_DRIVER_OPEN_ERR    = 1,
		NM_NOBOARD_ERR        = 2,
		NM_RESET_BOARD_ERR    = 3,
		NM_INIT_BOARD_ERR     = 4,
		NM_CPU1_ACCESS_ERR    = 5,
		NM_CPU2_ACCESS_ERR    = 6,
		NM_LOAD_FILE1_ERR     = 7,
		NM_LOAD_FILE2_ERR     = 8
};


class NMBoard
{

public:
	NMBoard() :board(0), access1(0), access2(0) {}
	~NMBoard(void) { Release(); };


	int Load (unsigned boardNumber, unsigned timeout,const char *file1,const char* file2);
	int Reset(unsigned boardNumber);
	void Release() 
	{

		if (access1)
		{
			PL_CloseAccess(access1);
			access1 = 0;
		}
		if (access2)
		{
			PL_CloseAccess(access2);
			access2 = 0;
		}

		if (board)
		{
			PL_CloseBoardDesc(board);
			board = 0;
		}
	};
	
	
	int SyncArray( 
            int cpu,                // Processor number.0-first,1-second
            int value,              // Value sent to processor.
            PL_Addr outAddress,     // Address sent to processor.
            PL_Word outLen,         // Size sent to processor.
            int * returnValue,      // Value received from processor.
            PL_Addr * inAddress,    // Address received from processor.
            PL_Word *inLen          // Size received from processor.
        );

	// Barrier syncronization with program on board processor.
    // value        - value sent to processor.
    // returnValue  - value received from processor.
	int Sync( int cpu, int value, int * returnValue );
	

	int ReadMemBlock(int cpu, void *dest, PL_Addr nm_addr, int size32);
	int WriteMemBlock(int cpu, void* source, PL_Addr nm_addr, int size32);

	///////////// ABSOLETTE ////////////////////////////////////////
	//Frame exchange (with Sync,convenient but very slow  )
	int GetFrameFromSharedMemory(int cpu,unsigned char *dest,int width,int height );
	int PutFrameToSharedMemory(int cpu,unsigned char *source,int width,int height );
	//Read-Write operations(in word32,convenient but very slow  )
    int ReadMemBlock(int cpu, void *dest , int size);
	int WriteMemBlock(int cpu, void* source, int size );
	PL_Access *GetAccess(int cpu) const;	
	PL_Board* GetBoard() ;
	


private:  
	PL_Board  *board;   //  Board descriptor;
	PL_Access *access1; //  First  processor descriptor;
	PL_Access *access2; //  Second processor descriptor;
	unsigned number;
	unsigned timeout;

};

#endif