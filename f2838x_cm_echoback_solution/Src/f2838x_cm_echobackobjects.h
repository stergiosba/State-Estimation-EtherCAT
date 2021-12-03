//###########################################################################
//
// FILE:   f2838x_cm_echobackobjects.h
//
// TITLE:  F2838x CM Echoback Object Dictionary
//
//###########################################################################
// $TI Release: F2838x EtherCAT Software v2.01.00.00 $
// $Release Date: August 31 2020 $
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Defines
//
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
#define PROTO
#else
#define PROTO extern
#endif

//*****************************************************************************
//                   Object 0x1600 : LEDS Process Data Mapping
//*****************************************************************************
//
//! \addtogroup 0x1600 0x1600 | LEDS process data mapping
//! @{
//! \brief Object 0x1600 (LEDS process data mapping) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - Reference to 0x7000.1<br>
//! SubIndex 2 - Reference to 0x7000.2<br>
//! SubIndex 3 - Reference to 0x7000.3<br>
//! SubIndex 4 - Reference to 0x7000.4<br>
//! SubIndex 5 - Reference to 0x7000.5<br>
//! SubIndex 6 - Reference to 0x7000.6<br>
//! SubIndex 7 - Reference to 0x7000.7<br>
//! SubIndex 8 - Reference to 0x7000.8<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x1600[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex1
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex2
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex3
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex4
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex5
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex6
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex7
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ}}; // SubIndex8

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x1600[] = "LEDS process data mapping\000"
                                      "SubIndex 001\000"
                                      "SubIndex 002\000"
                                      "SubIndex 003\000"
                                      "SubIndex 004\000"
                                      "SubIndex 005\000"
                                      "SubIndex 006\000"
                                      "SubIndex 007\000"
                                      "SubIndex 008\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 SI1; // Subindex1 - Reference to 0x7000.1
    UINT32 SI2; // Subindex2 - Reference to 0x7000.2
    UINT32 SI3; // Subindex3 - Reference to 0x7000.3
    UINT32 SI4; // Subindex4 - Reference to 0x7000.4
    UINT32 SI5; // Subindex5 - Reference to 0x7000.5
    UINT32 SI6; // Subindex6 - Reference to 0x7000.6
    UINT32 SI7; // Subindex7 - Reference to 0x7000.7
    UINT32 SI8; // Subindex8 - Reference to 0x7000.8
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ1600 LEDSProcessDataMapping0x1600
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={8U, 0x70000101UL, 0x70000201UL, 0x70000301UL, 0x70000401UL, 0x70000501UL,
  0x70000601UL, 0x70000701UL, 0x70000801UL}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x1601 : Output Mapping 1
//*****************************************************************************
//
//! \addtogroup 0x1601 0x1601 | Output mapping 1
//! @{
//! \brief Object 0x1601 (Output mapping 1) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - Reference to 0x7010.1<br>
//! SubIndex 2 - Reference to 0x7012.1<br>
//! SubIndex 3 - Reference to 0x7014.1<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x1601[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex1
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex2
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ}}; // SubIndex3

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x1601[] = "Output mapping 1\000"
                                      "SubIndex 001\000"
                                      "SubIndex 002\000"
                                      "SubIndex 003\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 SI1; // Subindex1 - Reference to 0x7010.1
    UINT32 SI2; // Subindex2 - Reference to 0x7012.1
    UINT32 SI3; // Subindex3 - Reference to 0x7014.1
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ1601 OutputMapping10x1601
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={3U, 0x70100120UL, 0x70120110UL, 0x70140120UL}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x1A00 : Switches Process Data Mapping
//*****************************************************************************
//
//! \addtogroup 0x1A00 0x1A00 | switches process data mapping
//! @{
//! \brief Object 0x1A00 (switches process data mapping) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - Reference to 0x6000.1<br>
//! SubIndex 2 - Reference to 0x6000.2<br>
//! SubIndex 3 - Reference to 0x6000.3<br>
//! SubIndex 4 - Reference to 0x6000.4<br>
//! SubIndex 5 - Reference to 0x6000.5<br>
//! SubIndex 6 - Reference to 0x6000.6<br>
//! SubIndex 7 - Reference to 0x6000.7<br>
//! SubIndex 8 - Reference to 0x6000.8<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x1A00[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex1
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex2
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex3
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex4
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex5
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex6
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex7
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ}}; // SubIndex8

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x1A00[] = "switches process data mapping\000"
                                      "SubIndex 001\000"
                                      "SubIndex 002\000"
                                      "SubIndex 003\000"
                                      "SubIndex 004\000"
                                      "SubIndex 005\000"
                                      "SubIndex 006\000"
                                      "SubIndex 007\000"
                                      "SubIndex 008\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 SI1; // Subindex1 - Reference to 0x6000.1
    UINT32 SI2; // Subindex2 - Reference to 0x6000.2
    UINT32 SI3; // Subindex3 - Reference to 0x6000.3
    UINT32 SI4; // Subindex4 - Reference to 0x6000.4
    UINT32 SI5; // Subindex5 - Reference to 0x6000.5
    UINT32 SI6; // Subindex6 - Reference to 0x6000.6
    UINT32 SI7; // Subindex7 - Reference to 0x6000.7
    UINT32 SI8; // Subindex8 - Reference to 0x6000.8
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ1A00 SwitchesProcessDataMapping0x1A00
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={8U, 0x60000101UL, 0x60000201UL, 0x60000301UL, 0x60000401UL, 0x60000501UL,
  0x60000601UL, 0x60000701UL, 0x60000801UL}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x1A01 : Input mapping 1
//*****************************************************************************
//
//! \addtogroup 0x1A01 0x1A01 | Input mapping 1
//! @{
//! \brief Object 0x1A01 (Input mapping 1) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - Reference to 0x6010.1<br>
//! SubIndex 2 - Reference to 0x6012.1<br>
//! SubIndex 3 - Reference to 0x6014.1<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x1A01[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex1
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ},  // SubIndex2
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ}}; // SubIndex3

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x1A01[] = "Input mapping 1\000"
                                      "SubIndex 001\000"
                                      "SubIndex 002\000"
                                      "SubIndex 003\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 SI1; // Subindex1 - Reference to 0x6010.1
    UINT32 SI2; // Subindex2 - Reference to 0x6012.1
    UINT32 SI3; // Subindex3 - Reference to 0x6014.1
} OBJ_STRUCT_PACKED_END
TOBJ1A01;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ1A01 InputMapping10x1A01
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={3U, 0x60100120UL, 0x60120110UL, 0x60140120UL}
#endif
;
//
// @}
//

//*****************************************************************************
//                   Object 0x1C12 : SyncManager 2 Assignment
//*****************************************************************************
//
//! \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
//! @{
//! \brief Object 0x1C12 (SyncManager 2 assignment) definition
//
#ifdef _OBJD_
//
//! \brief Entry descriptions<br>
//!
//! Subindex 0<br>
//! Subindex 1 - n (the same entry description is used)<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x1C12[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED16, 0x10U, ACCESS_READ}};

//
//! \brief Object name definition<br>
//! For Subindex 1 to n the syntax 'Subindex XXX' is used
//
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0; //!< \brief Subindex 0
    UINT16 aEntries[2];  //!< \brief Subindex 1 - 2
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ1C12 sRxPDOassign
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={2U, {0x1600U, 0x1601U}}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x1C13 : SyncManager 3 Assignment
//*****************************************************************************
//
//! \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
//! @{
//! \brief Object 0x1C13 (SyncManager 3 assignment) definition
//
#ifdef _OBJD_
//
//! \brief Entry descriptions<br>
//!
//! Subindex 0<br>
//! Subindex 1 - n (the same entry description is used)<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x1C13[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED16, 0x10U, ACCESS_READ}};

//
//! \brief Object name definition<br>
//! For Subindex 1 to n the syntax 'Subindex XXX' is used
//
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0; //!< \brief Subindex 0
    UINT16 aEntries[2];  //!< \brief Subindex 1 - 2
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ1C13 sTxPDOassign
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={2U, {0x1A00U, 0x1A01U}}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x6000 : Switches
//*****************************************************************************
//
//! \addtogroup 0x6000 0x6000 | switches
//! @{
//! \brief Object 0x6000 (switches) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - Switch1<br>
//! SubIndex 2 - Switch2<br>
//! SubIndex 3 - Switch3<br>
//! SubIndex 4 - Switch4<br>
//! SubIndex 5 - Switch5<br>
//! SubIndex 6 - Switch6<br>
//! SubIndex 7 - Switch7<br>
//! SubIndex 8 - Switch8<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x6000[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex1
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex2
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex3
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex4
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex5
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex6
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS},  // SubIndex7
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READ |
                        OBJACCESS_TXPDOMAPPING |
                        OBJACCESS_SETTINGS}}; // SubIndex8

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x6000[] = "switches\000"
                                      "Switch1\000"
                                      "Switch2\000"
                                      "Switch3\000"
                                      "Switch4\000"
                                      "Switch5\000"
                                      "Switch6\000"
                                      "Switch7\000"
                                      "Switch8\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    BOOLEAN(Switch1); // Subindex1 - Switch1
    BOOLEAN(Switch2); // Subindex2 - Switch2
    BOOLEAN(Switch3); // Subindex3 - Switch3
    BOOLEAN(Switch4); // Subindex4 - Switch4
    BOOLEAN(Switch5); // Subindex5 - Switch5
    BOOLEAN(Switch6); // Subindex6 - Switch6
    BOOLEAN(Switch7); // Subindex7 - Switch7
    BOOLEAN(Switch8); // Subindex8 - Switch8
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ6000 Switches0x6000
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={8U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}
#endif
;
//
// @}
//

//*****************************************************************************
//                   Object 0x6010 : DataToMaster
//*****************************************************************************
//
//! \addtogroup 0x6010 0x6010 | DataToMaster
//! @{
//! \brief Object 0x6010 (DataToMaster) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - DataToMaster<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x6010[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ |
                            OBJACCESS_TXPDOMAPPING |
                            OBJACCESS_SETTINGS }}; // Subindex1

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x6010[] = "DataToMaster\000"
                                      "DataToMaster\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 DataToMaster; // Subindex1 - DataToMaster
} OBJ_STRUCT_PACKED_END
TOBJ6010;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ6010 DataToMaster0x6010
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={1U, 0x00000000UL}
#endif
;
//
//! @}
//


//*****************************************************************************
//                   Object 0x6012 : TargetModeResponse
//*****************************************************************************
//
//! \addtogroup 0x6012 0x6012 | TargetModeResponse
//! @{
//! \brief Object 0x6012 (TargetModeResponse) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - ModeResponse<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x6012[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED16, 0x10U, ACCESS_READ |
                            OBJACCESS_TXPDOMAPPING |
                            OBJACCESS_SETTINGS }}; // Subindex1

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x6012[] = "TargetModeResponse\000"
                                      "ModeResponse\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT16 ModeResponse; // Subindex1 - ModeResponse
} OBJ_STRUCT_PACKED_END
TOBJ6012;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ6012 TargetModeResponse0x6012
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={1U, 0x0000U}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x6014 : TargetSpeedPosFeedback
//*****************************************************************************
//
//! \addtogroup 0x6014 0x6014 | TargetSpeedPosFeedback
//! @{
//! \brief Object 0x6014 (TargetSpeedPosFeedback) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - SpeedPosFbk<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x6014[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READ |
                            OBJACCESS_TXPDOMAPPING |
                            OBJACCESS_SETTINGS }}; // Subindex1

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x6014[] = "TargetSpeedPosFeedback\000"
                                      "SpeedPosFbk\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 SpeedPosFbk; // Subindex1 - SpeedPosFbk
} OBJ_STRUCT_PACKED_END
TOBJ6014;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ6014 TargetSpeedPosFeedback0x6014
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={1U, 0x00000000UL}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x7000 : LEDS
//*****************************************************************************
//
//! \addtogroup 0x7000 0x7000 | LEDS
//! @{
//! \brief Object 0x7000 (LEDS) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - LED1<br>
//! SubIndex 2 - LED2<br>
//! SubIndex 3 - LED3<br>
//! SubIndex 4 - LED4<br>
//! SubIndex 5 - LED5<br>
//! SubIndex 6 - LED6<br>
//! SubIndex 7 - LED7<br>
//! SubIndex 8 - LED8<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x7000[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex1
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex2
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex3
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex4
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex5
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex6
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS },  // SubIndex7
{DEFTYPE_BOOLEAN, 0x1U, ACCESS_READWRITE |
                        OBJACCESS_RXPDOMAPPING |
                        OBJACCESS_SETTINGS }}; // SubIndex8

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x7000[] = "LEDS\000"
                                      "LED1\000"
                                      "LED2\000"
                                      "LED3\000"
                                      "LED4\000"
                                      "LED5\000"
                                      "LED6\000"
                                      "LED7\000"
                                      "LED8\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    BOOLEAN(LED1); // Subindex1 - LED1
    BOOLEAN(LED2); // Subindex2 - LED2
    BOOLEAN(LED3); // Subindex3 - LED3
    BOOLEAN(LED4); // Subindex4 - LED4
    BOOLEAN(LED5); // Subindex5 - LED5
    BOOLEAN(LED6); // Subindex6 - LED6
    BOOLEAN(LED7); // Subindex7 - LED7
    BOOLEAN(LED8); // Subindex8 - LED8
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ7000 LEDS0x7000
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={8U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x7010 : DatafromMaster
//*****************************************************************************
//
//! \addtogroup 0x7010 0x7010 | DatafromMaster
//! @{
//! \brief Object 0x7010 (DatafromMaster) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - DatafromMaster<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x7010[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READWRITE |
                            OBJACCESS_RXPDOMAPPING |
                            OBJACCESS_SETTINGS }}; // Subindex1

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x7010[] = "DatafromMaster\000"
                                      "DatafromMaster\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 DatafromMaster; // Subindex1 - DatafromMaster
} OBJ_STRUCT_PACKED_END
TOBJ7010;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ7010 DatafromMaster0x7010
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={1U, 0x00000000UL}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x7012 : TargetMode
//*****************************************************************************
//
//! \addtogroup 0x7012 0x7012 | TargetMode
//! @{
//! \brief Object 0x7012 (TargetMode) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - Mode<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x7012[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED16, 0x10U, ACCESS_READWRITE |
                            OBJACCESS_RXPDOMAPPING |
                            OBJACCESS_SETTINGS }}; // Subindex1

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x7012[] = "TargetMode\000"
                                      "Mode\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT16 Mode; // Subindex1 - Mode
} OBJ_STRUCT_PACKED_END
TOBJ7012;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ7012 TargetMode0x7012
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={1U, 0x0000U}
#endif
;
//
//! @}
//

//*****************************************************************************
//                   Object 0x7014 : TargetSpeedPosReq
//*****************************************************************************
//
//! \addtogroup 0x7014 0x7014 | TargetSpeedPosReq
//! @{
//! \brief Object 0x7014 (TargetSpeedPosReq) definition
//
#ifdef _OBJD_
//
//! \brief Object entry descriptions<br>
//! <br>
//! SubIndex 0<br>
//! SubIndex 1 - SpeedPosReq<br>
//
OBJCONST TSDOINFOENTRYDESC
OBJMEM asEntryDesc0x7014[] = {
{DEFTYPE_UNSIGNED8, 0x8U, ACCESS_READ},
{DEFTYPE_UNSIGNED32, 0x20U, ACCESS_READWRITE |
                            OBJACCESS_RXPDOMAPPING |
                            OBJACCESS_SETTINGS }}; // Subindex1

//
//! \brief Object/Entry names
//
OBJCONST UCHAR OBJMEM aName0x7014[] = "TargetSpeedPosReq\000"
                                      "SpeedPosReq\000\377";
#endif // _OBJD_

#ifndef F2838X_CM_ECHOBACK_OBJECTS_H
//
//! \brief Object structure
//
typedef struct OBJ_STRUCT_PACKED_START
{
    UINT16 u16SubIndex0;
    UINT32 SpeedPosReq; // Subindex1 - SpeedPosReq
} OBJ_STRUCT_PACKED_END
TOBJ7014;
#endif // F2838X_CM_ECHOBACK_OBJECTS_H

//
//! \brief Object variable
//
PROTO TOBJ7014 TargetSpeedPosReq0x7014
#if defined(_F2838X_ECHOBACK_) && (_F2838X_ECHOBACK_ == 1)
={1U, 0x00000000UL}
#endif
;
//
//! @}
//

//
// Application Object Dictionary
//
#ifdef _OBJD_
TOBJECT OBJMEM ApplicationObjDic[] = {
//
// Object 0x1600
//
{NULL, NULL,  0x1600U, {DEFTYPE_PDOMAPPING, 8 | (OBJCODE_REC << 8)},
 asEntryDesc0x1600, aName0x1600, &LEDSProcessDataMapping0x1600, NULL,
 NULL, 0x0000U},
//
// Object 0x1601
//
{NULL, NULL,  0x1601U, {DEFTYPE_PDOMAPPING, 3 | (OBJCODE_REC << 8)},
 asEntryDesc0x1601, aName0x1601, &OutputMapping10x1601, NULL, NULL, 0x0000U},
//
// Object 0x1A00
//
{NULL, NULL,  0x1A00U, {DEFTYPE_PDOMAPPING, 8 | (OBJCODE_REC << 8)},
 asEntryDesc0x1A00, aName0x1A00, &SwitchesProcessDataMapping0x1A00, NULL,
 NULL, 0x0000U},
//
// Object 0x1A01
//
{NULL, NULL,  0x1A01U, {DEFTYPE_PDOMAPPING, 3 | (OBJCODE_REC << 8)},
 asEntryDesc0x1A01, aName0x1A01, &InputMapping10x1A01, NULL, NULL, 0x0000U},
//
// Object 0x1C12
//
{NULL, NULL,  0x1C12U, {DEFTYPE_UNSIGNED16, 2 | (OBJCODE_ARR << 8)},
 asEntryDesc0x1C12, aName0x1C12, &sRxPDOassign, NULL, NULL, 0x0000U},
//
// Object 0x1C13
//
{NULL, NULL,  0x1C13U, {DEFTYPE_UNSIGNED16, 2 | (OBJCODE_ARR << 8)},
 asEntryDesc0x1C13, aName0x1C13, &sTxPDOassign, NULL, NULL, 0x0000U},
//
// Object 0x6000
//
{NULL, NULL,  0x6000U, {DEFTYPE_RECORD, 8 | (OBJCODE_REC << 8)},
 asEntryDesc0x6000, aName0x6000, &Switches0x6000, NULL, NULL, 0x0000U},
//
// Object 0x6010
//
{NULL, NULL,  0x6010U, {DEFTYPE_RECORD, 1 | (OBJCODE_REC << 8)},
 asEntryDesc0x6010, aName0x6010, &DataToMaster0x6010, NULL, NULL, 0x0000U},
//
// Object 0x6012
//
{NULL, NULL,  0x6012U, {DEFTYPE_RECORD, 1 | (OBJCODE_REC << 8)},
 asEntryDesc0x6012, aName0x6012, &TargetModeResponse0x6012, NULL,
 NULL, 0x0000U},
//
// Object 0x6014
//
{NULL, NULL,  0x6014U, {DEFTYPE_RECORD, 1 | (OBJCODE_REC << 8)},
 asEntryDesc0x6014, aName0x6014, &TargetSpeedPosFeedback0x6014, NULL,
 NULL, 0x0000U},
//
// Object 0x7000
//
{NULL, NULL,  0x7000U, {DEFTYPE_RECORD, 8 | (OBJCODE_REC << 8)},
 asEntryDesc0x7000, aName0x7000, &LEDS0x7000, NULL, NULL, 0x0000U},
//
// Object 0x7010
//
{NULL, NULL,  0x7010U, {DEFTYPE_RECORD, 1 | (OBJCODE_REC << 8)},
 asEntryDesc0x7010, aName0x7010, &DatafromMaster0x7010, NULL, NULL, 0x0000U},
//
// Object 0x7012
//
{NULL, NULL,  0x7012U, {DEFTYPE_RECORD, 1 | (OBJCODE_REC << 8)},
 asEntryDesc0x7012, aName0x7012, &TargetMode0x7012, NULL, NULL, 0x0000U},
//
// Object 0x7014
//
{NULL, NULL,  0x7014U, {DEFTYPE_RECORD, 1 | (OBJCODE_REC << 8)},
 asEntryDesc0x7014, aName0x7014, &TargetSpeedPosReq0x7014, NULL, NULL, 0x0000U},

{NULL, NULL, 0xFFFFU, {0U, 0U}, NULL, NULL, NULL, NULL}};
#endif // _OBJD_
#undef PROTO

//
//! @}
//
#define F2838X_CM_ECHOBACK_OBJECTS_H

//
// End of File
//
