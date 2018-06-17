/* ----------------------------------------------------------------------
** Static Audio Weaver command packets
** Source file = D:\132\First.awb
** Created on 04-Dec-2017 20:40:31
** ------------------------------------------------------------------- */


#define AWB_SOURCE_FILE "First" // Name of the .awb file from which this file is generated

unsigned int InitCommands[] = {
0x0002005d,		/* PFID_DestroyAll CoreID=0 */
0x0002000c,		/* PFID_Destroy CoreID=0 */
0x0002010c,		/* PFID_Destroy CoreID=1 */
0x00060006,		/* PFID_ClassWire_Constructor CoreID=0 */
0x473b8000,		/*   0x473b8000 [Pin pointer] */
0x40008002,		/*   TBD */
0x00000020,		/*   TBD */
0x00000000,		/*   TBD */
0x00060006,		/* PFID_ClassWire_Constructor CoreID=0 */
0x473b8000,		/*   0x473b8000 [Pin pointer] */
0x40008002,		/*   TBD */
0x00000020,		/*   TBD */
0x00000000,		/*   TBD */
0x00060006,		/* PFID_ClassWire_Constructor CoreID=0 */
0x473b8000,		/*   0x473b8000 [Pin pointer] */
0x40008002,		/*   TBD */
0x00000020,		/*   TBD */
0x00000000,		/*   TBD */
0x00060006,		/* PFID_ClassWire_Constructor CoreID=0 */
0x473b8000,		/*   0x473b8000 [Pin pointer] */
0x40008001,		/*   TBD */
0x00000020,		/*   TBD */
0x00000000,		/*   TBD */
0x00060006,		/* PFID_ClassWire_Constructor CoreID=0 */
0x473b8000,		/*   0x473b8000 [Pin pointer] */
0x40008002,		/*   TBD */
0x00000020,		/*   TBD */
0x00000000,		/*   TBD */
0x00040007,		/* PFID_BindIOToWire CoreID=0 */
0x00000001,		/*   0x00000001 [Wire pointer] */
0x00000001,		/*   0x00000001 [I/O pin pointer] */
0x00040007,		/* PFID_BindIOToWire CoreID=0 */
0x00000002,		/*   0x00000002 [Wire pointer] */
0x00000002,		/*   0x00000002 [I/O pin pointer] */
0x0009000f,		/* PFID_ClassModule_Constructor CoreID=0 */
0xbeef0866,		/*          102 [classID = TypeConversion] */
0x00000101,		/*   0x00000101 [nIO.  numIn=1. numOut=1. numScratch=0] */
0x00000002,		/*            2 [argCount] */
0x00000001,		/*   0x00000001 [wire 0] */
0x00000003,		/*   0x00000003 [wire 1] */
0x00000001,		/*   0x00000001 [arg 0] : inputType = 1 */
0x00000000,		/*   0x00000000 [arg 1] : outputType = 0 */
0x000c000f,		/* PFID_ClassModule_Constructor CoreID=0 */
0xbeef086b,		/*          107 [classID = Meter] */
0x00010001,		/*   0x00010001 [nIO.  numIn=1. numOut=0. numScratch=1] */
0x00000005,		/*            5 [argCount] */
0x00000003,		/*   0x00000003 [wire 0] */
0x00000004,		/*   0x00000004 [wire 1] */
0x00000012,		/*   0x00000012 [arg 0] : meterType = 18 */
0x42820000,		/*   0x42820000 [arg 1] : attackTime = 65.0 */
0x42820000,		/*   0x42820000 [arg 2] : releaseTime = 65.0 */
0x3cbf5376,		/*   0x3cbf5376 [arg 3] : attackCoeff = 0.023355227 */
0x3cbf5376,		/*   0x3cbf5376 [arg 4] : releaseCoeff = 0.023355227 */
0x000d000f,		/* PFID_ClassModule_Constructor CoreID=0 */
0xbeef0813,		/*           19 [classID = ScalerV2] */
0x00000101,		/*   0x00000101 [nIO.  numIn=1. numOut=1. numScratch=0] */
0x00000006,		/*            6 [argCount] */
0x00000003,		/*   0x00000003 [wire 0] */
0x00000005,		/*   0x00000005 [wire 1] */
0x00000000,		/*   0x00000000 [arg 0] : gain = 0.0 */
0x41200000,		/*   0x41200000 [arg 1] : smoothingTime = 10.0 */
0x00000001,		/*   0x00000001 [arg 2] : isDB = 1 */
0x3f800000,		/*   0x3f800000 [arg 3] : targetGain = 1.0 */
0x3f800000,		/*   0x3f800000 [arg 4] : currentGain = 1.0 */
0x3b086426,		/*   0x3b086426 [arg 5] : smoothingCoeff = 0.00208116462 */
0x0007000f,		/* PFID_ClassModule_Constructor CoreID=0 */
0xbeef086d,		/*          109 [classID = Sink] */
0x00000001,		/*   0x00000001 [nIO.  numIn=1. numOut=0. numScratch=0] */
0x00000001,		/*            1 [argCount] */
0x00000005,		/*   0x00000005 [wire 0] */
0x00000000,		/*   0x00000000 [arg 0] : enable = 0 */
0x00080065,		/* PFID_SetValuesSetCall_float CoreID=0 */
0x0000980a,		/*            2 [numValues] */
0x00000000,		/*   TBD */
0x00000400,		/*   TBD */
0x00000002,		/*   TBD */
0xc0a00000,		/*   TBD */
0x40a00000,		/*   TBD */
0x0009000f,		/* PFID_ClassModule_Constructor CoreID=0 */
0xbeef0866,		/*          102 [classID = TypeConversion] */
0x00000101,		/*   0x00000101 [nIO.  numIn=1. numOut=1. numScratch=0] */
0x00000002,		/*            2 [argCount] */
0x00000005,		/*   0x00000005 [wire 0] */
0x00000002,		/*   0x00000002 [wire 1] */
0x00000000,		/*   0x00000000 [arg 0] : inputType = 0 */
0x00000001,		/*   0x00000001 [arg 1] : outputType = 1 */
0x00040010,		/* PFID_ClassLayout_Constructor CoreID=0 */
0x00000005,		/*            5 [numModules] */
0x00000001,		/*            1 [divider] */
0x0009002f,		/* PFID_AddModuleToLayout CoreID=0 */
0x0000000b,		/*   0x0000000b [Layout address] */
0x00000000,		/*            0 [startIndex] */
0x00000006,		/*   0x00000006 [Module pointer 0] */
0x00000007,		/*   0x00000007 [Module pointer 1] */
0x00000008,		/*   0x00000008 [Module pointer 2] */
0x00000009,		/*   0x00000009 [Module pointer 3] */
0x0000000a,		/*   0x0000000a [Module pointer 4] */
};
unsigned InitCommands_Len = sizeof(InitCommands)/sizeof(*InitCommands); // Length should be 97
