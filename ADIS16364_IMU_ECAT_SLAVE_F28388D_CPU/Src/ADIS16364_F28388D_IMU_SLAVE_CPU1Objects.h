/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup ADIS16364_F28388D_IMU_SLAVE_CPU1 ADIS16364_F28388D_IMU_SLAVE_CPU1
* @{
*/

/**
\file ADIS16364_F28388D_IMU_SLAVE_CPU1Objects
\author ET9300Utilities.ApplicationHandler (Version 1.6.2.0) | EthercatSSC@beckhoff.com

\brief ADIS16364_F28388D_IMU_SLAVE_CPU1 specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : SUS_CONTROL process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | SUS_CONTROL process data mapping
* @{
* \brief Object 0x1600 (SUS_CONTROL process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x7000.1 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "SUS_CONTROL process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 SUS_CONTROLProcessDataMapping0x1600
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={1,0x70000110}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : SUS_SENSE process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | SUS_SENSE process data mapping
* @{
* \brief Object 0x1A00 (SUS_SENSE process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.1<br>
* SubIndex 2 - Reference to 0x6000.2<br>
* SubIndex 3 - Reference to 0x6000.3<br>
* SubIndex 4 - Reference to 0x6000.4<br>
* SubIndex 5 - Reference to 0x6000.5<br>
* SubIndex 6 - Reference to 0x6000.6<br>
* SubIndex 7 - Reference to 0x6000.7<br>
* SubIndex 8 - Reference to 0x6000.8<br>
* SubIndex 9 - Reference to 0x6000.9<br>
* SubIndex 10 - Reference to 0x6000.16<br>
* SubIndex 11 - Reference to 0x6000.17<br>
* SubIndex 12 - Reference to 0x6000.18<br>
* SubIndex 13 - Reference to 0x6000.19<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6000.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6000.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x6000.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x6000.7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x6000.8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex9 - Reference to 0x6000.9 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex10 - Reference to 0x6000.16 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex11 - Reference to 0x6000.17 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex12 - Reference to 0x6000.18 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex13 - Reference to 0x6000.19 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "SUS_SENSE process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6000.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x6000.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x6000.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x6000.7 */
UINT32 SI8; /* Subindex8 - Reference to 0x6000.8 */
UINT32 SI9; /* Subindex9 - Reference to 0x6000.9 */
UINT32 SI10; /* Subindex10 - Reference to 0x6000.16 */
UINT32 SI11; /* Subindex11 - Reference to 0x6000.17 */
UINT32 SI12; /* Subindex12 - Reference to 0x6000.18 */
UINT32 SI13; /* Subindex13 - Reference to 0x6000.19 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 SUS_SENSEProcessDataMapping0x1A00
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={13,0x60000120,0x60000220,0x60000320,0x60000420,0x60000520,0x60000620,0x60000720,0x60000820,0x60000920,0x60001020,0x60001120,0x60001220,0x60001320}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={1,{0x1600}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : SUS_SENSE
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | SUS_SENSE
* @{
* \brief Object 0x6000 (SUS_SENSE) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - XGyro_sense<br>
* SubIndex 2 - YGyro_sense<br>
* SubIndex 3 - ZGyro_sense<br>
* SubIndex 4 - XAcc_sense<br>
* SubIndex 5 - YAcc_sense<br>
* SubIndex 6 - ZAcc_sense<br>
* SubIndex 7 - Temp_sense<br>
* SubIndex 8 - XAngle_calc<br>
* SubIndex 9 - YAngle_calc<br>
* SubIndex 10 does not exists<br>
* SubIndex 11 does not exists<br>
* SubIndex 12 does not exists<br>
* SubIndex 13 does not exists<br>
* SubIndex 14 does not exists<br>
* SubIndex 15 does not exists<br>
* SubIndex 16 - ZAngle_calc<br>
* SubIndex 17 - XLinVel_calc<br>
* SubIndex 18 - YLinVel_calc<br>
* SubIndex 19 - ZLinVel_calc<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - XGyro_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - YGyro_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - ZGyro_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - XAcc_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - YAcc_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - ZAcc_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - Temp_sense */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex8 - XAngle_calc */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex9 - YAngle_calc */
{ DEFTYPE_NULL , 0x00 , 0x0000 }, /* Subindex10 does not exists */
{ DEFTYPE_NULL , 0x00 , 0x0000 }, /* Subindex11 does not exists */
{ DEFTYPE_NULL , 0x00 , 0x0000 }, /* Subindex12 does not exists */
{ DEFTYPE_NULL , 0x00 , 0x0000 }, /* Subindex13 does not exists */
{ DEFTYPE_NULL , 0x00 , 0x0000 }, /* Subindex14 does not exists */
{ DEFTYPE_NULL , 0x00 , 0x0000 }, /* Subindex15 does not exists */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex16 - ZAngle_calc */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex17 - XLinVel_calc */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex18 - YLinVel_calc */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex19 - ZLinVel_calc */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "SUS_SENSE\000"
"XGyro_sense\000"
"YGyro_sense\000"
"ZGyro_sense\000"
"XAcc_sense\000"
"YAcc_sense\000"
"ZAcc_sense\000"
"Temp_sense\000"
"XAngle_calc\000"
"YAngle_calc\000"
"\000"
"\000"
"\000"
"\000"
"\000"
"\000"
"ZAngle_calc\000"
"XLinVel_calc\000"
"YLinVel_calc\000"
"ZLinVel_calc\000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
REAL32 XGyro_sense; /* Subindex1 - XGyro_sense */
REAL32 YGyro_sense; /* Subindex2 - YGyro_sense */
REAL32 ZGyro_sense; /* Subindex3 - ZGyro_sense */
REAL32 XAcc_sense; /* Subindex4 - XAcc_sense */
REAL32 YAcc_sense; /* Subindex5 - YAcc_sense */
REAL32 ZAcc_sense; /* Subindex6 - ZAcc_sense */
REAL32 Temp_sense; /* Subindex7 - Temp_sense */
REAL32 XAngle_calc; /* Subindex8 - XAngle_calc */
REAL32 YAngle_calc; /* Subindex9 - YAngle_calc */
REAL32 ZAngle_calc; /* Subindex16 - ZAngle_calc */
REAL32 XLinVel_calc; /* Subindex17 - XLinVel_calc */
REAL32 YLinVel_calc; /* Subindex18 - YLinVel_calc */
REAL32 ZLinVel_calc; /* Subindex19 - ZLinVel_calc */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 SUS_SENSE0x6000
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={19,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : SUS_CONTROL
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | SUS_CONTROL
* @{
* \brief Object 0x7000 (SUS_CONTROL) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - IMU_flags<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }}; /* Subindex1 - IMU_flags */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "SUS_CONTROL\000"
"IMU_flags\000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IMU_flags; /* Subindex1 - IMU_flags */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 SUS_CONTROL0x7000
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={1,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0xF000 : Modular Device Profile
******************************************************************************/
/**
* \addtogroup 0xF000 0xF000 | Modular Device Profile
* @{
* \brief Object 0xF000 (Modular Device Profile) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Index distance <br>
* SubIndex 2 - Maximum number of modules <br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - Index distance  */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex2 - Maximum number of modules  */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000"
"Index distance \000"
"Maximum number of modules \000\377";
#endif //#ifdef _OBJD_

#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_ADIS16364__F28388_D__IMU__SLAVE__CPU1_) && (_ADIS16364__F28388_D__IMU__SLAVE__CPU1_ == 1)
={2,0x0010,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &SUS_CONTROLProcessDataMapping0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 13 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &SUS_SENSEProcessDataMapping0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 19 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &SUS_SENSE0x6000 , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &SUS_CONTROL0x7000 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_

#undef PROTO

/** @}*/
#define _ADIS16364__F28388_D__IMU__SLAVE__CPU1_OBJECTS_H_
