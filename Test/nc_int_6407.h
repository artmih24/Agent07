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
//  Таймеры
///////////////////////////////////

//  При запуске таймера устанавливается режим: при обнулении
// на вывод выдается импульс отрицательной полярности 
// длительностью один процессорный такт 

//  Получение счетчика таймера 1, с автозапуском в инит-коде
int clock();

///////////////////////////////////
//  Прерывания
///////////////////////////////////


typedef void (HandlerType)(void);

//  Обработчик по-умолчанию
extern HandlerType DefaultIntHandler;

//  Установка вектора прерывания
HandlerType*       //  предыдущий обработчик
SetInterrupt( int kind, HandlerType f );

inline HandlerType*   
SetInterruptPeriphery( int kind, HandlerType f )
    {   return SetInterrupt( kind + 4, f );    }


//  Получение текущего обработчика прерывания
HandlerType* GetInterrupt( int kind );

//  Установка обработчика прерывания по умолчанию
HandlerType* ClearInterrupt( int kind );

//  Сброс всех запросов на прерывание
HandlerType* FlushInterrupts( );


enum InterMaskPSWR
{
    I_MASK_OF = 0x00000100,      //  Переполнение
    I_MASK_EI = 0x00000080,      //  Неправильная команда
    I_MASK_INM =0x00000040,      //  Внешнее прерывание
    I_MASK_ST = 0x00000020       //  Пошаговое прерывание
};

enum InterKind
{
    I_KIND_NMI =0,  //  Немаскируемое прерывание
    I_KIND_OF,      //  Переполнение
    I_KIND_EI,      //  Неправильная команда
    I_KIND_ST       //  Пошаговое прерывание
};


//  Разрешить заданные прерывания.
//      для прерываний ядра
void EnableInterrupts_PSWR     ( InterMaskPSWR );
//      для первых 32 периферийных прерываний по списку
void EnableInterrupts_IMR_Low  ( int );
//      для периферийных прерываний с номером больше 32
void EnableInterrupts_IMR_High ( int );

//  Запретить заданные прерывания.
void DisableInterrupts_PSWR     ( InterMaskPSWR );
void DisableInterrupts_IMR_Low  ( int );
void DisableInterrupts_IMR_High ( int );

//  Вернуть маску переферийных прерываний
int GetInterruptMask_IMR_Low  ( void );
int GetInterruptMask_IMR_High ( void );



///////////////////////////////////
//  Вспомогательные
///////////////////////////////////

//  Получение состояния регистра переферии
unsigned int LibintGetCPUID();




//  Получение состояния регистра переферии
unsigned int LibintGetPSWR();

//  Работа с NMSCR
enum CPUIDMasks
{
    CPUID_INDEX   = 1   <<24,    //  Номер ядра
    CPUID_FIXED   = 1   <<20,    //  Наличие сопроцессора фиксированной точки 
    CPUID_FLOAT   = 1   <<21,    //  Наличие сопроцессора плавающей точки 
    CPUID_ARCH    = 0xf <<16,    //  Версия архитектуры ( nmc4 - 4 )
    CPUID_PRTNUM  = 0xfff <<4,   //  Что за чип (6407 - 0x0b7 )
    CPUID_REV     = 0xf          //  Версия чипа
};

unsigned int LibintGetNMSCR();
void LibintSetNMSCR( unsigned int );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _NC_INT_H
