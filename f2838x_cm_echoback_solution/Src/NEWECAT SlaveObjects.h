/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup NEWECATSlave NEWECAT Slave
* @{
*/

/**
\file NEWECAT SlaveObjects
\author ET9300Utilities.ApplicationHandler (Version 1.6.2.0) | EthercatSSC@beckhoff.com

\brief NEWECAT Slave specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : Vars_0x7000 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | Vars_0x7000 process data mapping
* @{
* \brief Object 0x1600 (Vars_0x7000 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
* SubIndex 2 - Reference to 0x7000.2<br>
* SubIndex 3 - Reference to 0x7000.3<br>
* SubIndex 4 - Reference to 0x7000.4<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex4 - Reference to 0x7000.4 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "Vars_0x7000 process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000\377";
#endif //#ifdef _OBJD_

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7000.4 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 Vars_0x7000ProcessDataMapping0x1600
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
={4,0x70000120,0x70000220,0x70000320,0x70000420}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : Vars_0x6000 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | Vars_0x6000 process data mapping
* @{
* \brief Object 0x1A00 (Vars_0x6000 process data mapping) definition
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
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex4 - Reference to 0x6000.4 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "Vars_0x6000 process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000\377";
#endif //#ifdef _OBJD_

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6000.4 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 Vars_0x6000ProcessDataMapping0x1A00
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
={4,0x60000120,0x60000220,0x60000320,0x60000420}
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

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
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

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : Vars_0x6000
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | Vars_0x6000
* @{
* \brief Object 0x6000 (Vars_0x6000) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Switch1<br>
* SubIndex 2 - Switch2<br>
* SubIndex 3 - Switch3<br>
* SubIndex 4 - Switch4<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - Switch1 */
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - Switch2 */
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - Switch3 */
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex4 - Switch4 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "Vars_0x6000\000"
"Switch1\000"
"Switch2\000"
"Switch3\000"
"Switch4\000\377";
#endif //#ifdef _OBJD_

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
REAL64 Switch1; /* Subindex1 - Switch1 */
REAL64 Switch2; /* Subindex2 - Switch2 */
REAL64 Switch3; /* Subindex3 - Switch3 */
REAL64 Switch4; /* Subindex4 - Switch4 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 Vars_0x6000
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
={4,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : Vars_0x7000
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | Vars_0x7000
* @{
* \brief Object 0x7000 (Vars_0x7000) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - LED1<br>
* SubIndex 2 - LED2<br>
* SubIndex 3 - LED3<br>
* SubIndex 4 - LED4<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - LED1 */
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - LED2 */
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - LED3 */
{ DEFTYPE_REAL64 , 0x20 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }}; /* Subindex4 - LED4 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "Vars_0x7000\000"
"LED1\000"
"LED2\000"
"LED3\000"
"LED4\000\377";
#endif //#ifdef _OBJD_

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
REAL64 LED1; /* Subindex1 - LED1 */
REAL64 LED2; /* Subindex2 - LED2 */
REAL64 LED3; /* Subindex3 - LED3 */
REAL64 LED4; /* Subindex4 - LED4 */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 Vars_0x7000
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
={4,0,0,0,0}
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

#ifndef _NEWECAT_SLAVE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _NEWECAT_SLAVE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_NEWECAT_SLAVE_) && (_NEWECAT_SLAVE_ == 1)
={2,0x0010,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &Vars_0x7000ProcessDataMapping0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &Vars_0x6000ProcessDataMapping0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &Vars_0x6000 , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &Vars_0x7000 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_

#undef PROTO

/** @}*/
#define _NEWECAT_SLAVE_OBJECTS_H_
