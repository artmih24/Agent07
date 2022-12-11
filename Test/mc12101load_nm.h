////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// mc12101_load_nm.h -                                                        //
//                                                                            //
//      Header file for synchronization and exchange library for MC121.01     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef __MC12101_LOAD_NM__H__
#define __MC12101_LOAD_NM__H__

#include <stdlib.h>

#define MC12101_SYNC "3.0"
#define MC12101_SYNC_MAJOR_VERSION 3
#define MC12101_SYNC_MINOR_VERSION 0

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// Return processor number on board
	int ncl_getProcessorNo(void);

	// Barrier sync with host PC
	int ncl_hostSync(int value);

	// Barrier sync with host PC with array exchange
	int ncl_hostSyncArray(
		int value,        // Sync value
		void *outAddress, // Sended array address (can be NULL)
		size_t outLen,    // Sended array length (can be 0)
		void **inAddress, // Received array address pointer (can be NULL)
		size_t *inLen);   // Received array size pointer (can be NULL)

	// Send interrupt to PC
	void ncl_sendInterrupt(void);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __MC12101_LOAD_NM__H__
