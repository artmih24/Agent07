//----------------------------------------------------------------
//
// Copyright 1998-2010 (c) RC Module.
// NeuroChip NM6407.
//
// nc_int05.h
// Header file for low level library.
// Contain declaration of timer, comm. port and interrupt managing function
//
//----------------------------------------------------------------

#ifndef _NC_INT_H
#define _NC_INT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

///////////////////////////////////
//  �������
///////////////////////////////////

//  ��� ������� ������� ��������������� �����: ��� ���������
// �� ����� �������� ������� ������������� ���������� 
// ������������� ���� ������������ ���� 

//  ��������� �������� ������� 1, � ������������ � ����-����
int clock();

///////////////////////////////////
//  ����������
///////////////////////////////////


typedef void (HandlerType)(void);

//  ���������� ��-���������
extern HandlerType DefaultIntHandler;

//  ��������� ������� ����������
HandlerType*       //  ���������� ����������
SetInterrupt( int kind, HandlerType f );

inline HandlerType*   
SetInterruptPeriphery( int kind, HandlerType f )
    {   return SetInterrupt( kind + 4, f );    }


//  ��������� �������� ����������� ����������
HandlerType* GetInterrupt( int kind );

//  ��������� ����������� ���������� �� ���������
HandlerType* ClearInterrupt( int kind );

//  ����� ���� �������� �� ����������
HandlerType* FlushInterrupts( );


enum InterMaskPSWR
{
    I_MASK_OF = 0x00000100,      //  ������������
    I_MASK_EI = 0x00000080,      //  ������������ �������
    I_MASK_INM =0x00000040,      //  ������� ����������
    I_MASK_ST = 0x00000020       //  ��������� ����������
};

enum InterKind
{
    I_KIND_NMI =0,  //  ������������� ����������
    I_KIND_OF,      //  ������������
    I_KIND_EI,      //  ������������ �������
    I_KIND_ST       //  ��������� ����������
};


//  ��������� �������� ����������.
//      ��� ���������� ����
void EnableInterrupts_PSWR     ( InterMaskPSWR );
//      ��� ������ 32 ������������ ���������� �� ������
void EnableInterrupts_IMR_Low  ( int );
//      ��� ������������ ���������� � ������� ������ 32
void EnableInterrupts_IMR_High ( int );

//  ��������� �������� ����������.
void DisableInterrupts_PSWR     ( InterMaskPSWR );
void DisableInterrupts_IMR_Low  ( int );
void DisableInterrupts_IMR_High ( int );

//  ������� ����� ������������ ����������
int GetInterruptMask_IMR_Low  ( void );
int GetInterruptMask_IMR_High ( void );



///////////////////////////////////
//  ���������������
///////////////////////////////////

//  ��������� ��������� �������� ���������
unsigned int LibintGetCPUID();




//  ��������� ��������� �������� ���������
unsigned int LibintGetPSWR();

//  ������ � NMSCR
enum CPUIDMasks
{
    CPUID_INDEX   = 1   <<24,    //  ����� ����
    CPUID_FIXED   = 1   <<20,    //  ������� ������������ ������������� ����� 
    CPUID_FLOAT   = 1   <<21,    //  ������� ������������ ��������� ����� 
    CPUID_ARCH    = 0xf <<16,    //  ������ ����������� ( nmc4 - 4 )
    CPUID_PRTNUM  = 0xfff <<4,   //  ��� �� ��� (6407 - 0x0b7 )
    CPUID_REV     = 0xf          //  ������ ����
};

unsigned int LibintGetNMSCR();
void LibintSetNMSCR( unsigned int );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _NC_INT_H
