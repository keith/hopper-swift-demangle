//
// Hopper Disassembler SDK
//
// (c)2014 - Cryptic Apps SARL. All Rights Reserved.
// http://www.hopperapp.com
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//

#ifndef _HOPPER_DISASM_STRUCT_H_
#define _HOPPER_DISASM_STRUCT_H_

#include <stdint.h>
#include "CommonTypes.h"

#define DISASM_INSTRUCTION_MAX_LENGTH 2048
#define DISASM_OPERAND_MNEMONIC_MAX_LENGTH 1024

#define DISASM_UNKNOWN_OPCODE -1

#define DISASM_MAX_OPERANDS                             6
#define DISASM_MAX_REG_INDEX                            32
#define DISASM_MAX_REG_CLASSES                          16

#define DISASM_OPERAND_REGISTER_INDEX_MASK              0x00000000FFFFFFFFllu
#define DISASM_OPERAND_TYPE_MASK                        0xFFFF000000000000llu
#define DISASM_OPERAND_REG_CLASS_MASK                   0x0000FFFF00000000llu
#define DISASM_OPERAND_TYPE_AND_REG_CLASS_MASK          0xFFFFFFFF00000000llu

// Type
#define DISASM_OPERAND_NO_OPERAND                       0x8000000000000000llu
#define DISASM_OPERAND_CONSTANT_TYPE                    0x4000000000000000llu
#define DISASM_OPERAND_MEMORY_TYPE                      0x2000000000000000llu
#define DISASM_OPERAND_REGISTER_TYPE                    0x1000000000000000llu
#define DISASM_OPERAND_ABSOLUTE                         0x0800000000000000llu
#define DISASM_OPERAND_RELATIVE                         0x0400000000000000llu
#define DISASM_OPERAND_OTHER                            0x0200000000000000llu

#define DISASM_EXTRACT_REGISTER_CLASS(TYPE)             ((RegClass)(((TYPE) & DISASM_OPERAND_REG_CLASS_MASK) >> DISASM_MAX_REG_INDEX))

#define DISASM_BUILD_REGISTER_CLS_MASK(CLS)             (0x100000000llu << (CLS))
#define DISASM_BUILD_REGISTER_INDEX_MASK(INDEX)         (1llu << (INDEX))
#define DISASM_BUILD_REGISTER_MASK(CLS,INDEX)           (DISASM_BUILD_REGISTER_CLS_MASK(CLS) | DISASM_BUILD_REGISTER_INDEX_MASK(INDEX))

#define DISASM_OPERAND_GENERAL_REG_INDEX                2

// Register class (x86)
#define DISASM_OPERAND_X86_FPU_REG_INDEX                3
#define DISASM_OPERAND_X86_MMX_REG_INDEX                4
#define DISASM_OPERAND_X86_SSE_REG_INDEX                5
#define DISASM_OPERAND_X86_AVX_REG_INDEX                6
#define DISASM_OPERAND_X86_CR_REG_INDEX                 7
#define DISASM_OPERAND_X86_DR_REG_INDEX                 8
#define DISASM_OPERAND_X86_SPECIAL_REG_INDEX            9
#define DISASM_OPERAND_X86_MEMORY_MANAGEMENT_REG_INDEX  10
#define DISASM_OPERAND_X86_SEGMENT_REG_INDEX            11

#define DISASM_OPERAND_GENERAL_REG                      DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_GENERAL_REG_INDEX)
#define DISASM_OPERAND_X86_FPU_REG                      DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_FPU_REG_INDEX)
#define DISASM_OPERAND_X86_MMX_REG                      DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_MMX_REG_INDEX)
#define DISASM_OPERAND_X86_SSE_REG                      DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_SSE_REG_INDEX)
#define DISASM_OPERAND_X86_AVX_REG                      DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_AVX_REG_INDEX)
#define DISASM_OPERAND_X86_CR_REG                       DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_CR_REG_INDEX)
#define DISASM_OPERAND_X86_DR_REG                       DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_DR_REG_INDEX)
#define DISASM_OPERAND_X86_SPECIAL_REG                  DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_SPECIAL_REG_INDEX)
#define DISASM_OPERAND_X86_MEMORY_MANAGEMENT_REG        DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_MEMORY_MANAGEMENT_REG_INDEX)
#define DISASM_OPERAND_X86_SEGMENT_REG                  DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_X86_SEGMENT_REG_INDEX)

// Register class (ARM)
#define DISASM_OPERAND_ARM_VFP_SINGLE_REG_INDEX         3
#define DISASM_OPERAND_ARM_VFP_DOUBLE_REG_INDEX         4
#define DISASM_OPERAND_ARM_VFP_QUAD_REG_INDEX           5
#define DISASM_OPERAND_ARM_MEDIA_REG_INDEX              6

#define DISASM_OPERAND_ARM_VFP_SINGLE_REG               DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_ARM_VFP_SINGLE_REG_INDEX)
#define DISASM_OPERAND_ARM_VFP_DOUBLE_REG               DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_ARM_VFP_DOUBLE_REG_INDEX)
#define DISASM_OPERAND_ARM_VFP_QUAD_REG                 DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_ARM_VFP_QUAD_REG_INDEX)
#define DISASM_OPERAND_ARM_MEDIA_REG                    DISASM_BUILD_REGISTER_CLS_MASK(DISASM_OPERAND_ARM_MEDIA_REG_INDEX)

#define DISASM_REG0  DISASM_BUILD_REGISTER_INDEX_MASK(0)
#define DISASM_REG1  DISASM_BUILD_REGISTER_INDEX_MASK(1)
#define DISASM_REG2  DISASM_BUILD_REGISTER_INDEX_MASK(2)
#define DISASM_REG3  DISASM_BUILD_REGISTER_INDEX_MASK(3)
#define DISASM_REG4  DISASM_BUILD_REGISTER_INDEX_MASK(4)
#define DISASM_REG5  DISASM_BUILD_REGISTER_INDEX_MASK(5)
#define DISASM_REG6  DISASM_BUILD_REGISTER_INDEX_MASK(6)
#define DISASM_REG7  DISASM_BUILD_REGISTER_INDEX_MASK(7)
#define DISASM_REG8  DISASM_BUILD_REGISTER_INDEX_MASK(8)
#define DISASM_REG9  DISASM_BUILD_REGISTER_INDEX_MASK(9)
#define DISASM_REG10 DISASM_BUILD_REGISTER_INDEX_MASK(10)
#define DISASM_REG11 DISASM_BUILD_REGISTER_INDEX_MASK(11)
#define DISASM_REG12 DISASM_BUILD_REGISTER_INDEX_MASK(12)
#define DISASM_REG13 DISASM_BUILD_REGISTER_INDEX_MASK(13)
#define DISASM_REG14 DISASM_BUILD_REGISTER_INDEX_MASK(14)
#define DISASM_REG15 DISASM_BUILD_REGISTER_INDEX_MASK(15)
#define DISASM_REG16 DISASM_BUILD_REGISTER_INDEX_MASK(16)
#define DISASM_REG17 DISASM_BUILD_REGISTER_INDEX_MASK(17)
#define DISASM_REG18 DISASM_BUILD_REGISTER_INDEX_MASK(18)
#define DISASM_REG19 DISASM_BUILD_REGISTER_INDEX_MASK(19)
#define DISASM_REG20 DISASM_BUILD_REGISTER_INDEX_MASK(20)
#define DISASM_REG21 DISASM_BUILD_REGISTER_INDEX_MASK(21)
#define DISASM_REG22 DISASM_BUILD_REGISTER_INDEX_MASK(22)
#define DISASM_REG23 DISASM_BUILD_REGISTER_INDEX_MASK(23)
#define DISASM_REG24 DISASM_BUILD_REGISTER_INDEX_MASK(24)
#define DISASM_REG25 DISASM_BUILD_REGISTER_INDEX_MASK(25)
#define DISASM_REG26 DISASM_BUILD_REGISTER_INDEX_MASK(26)
#define DISASM_REG27 DISASM_BUILD_REGISTER_INDEX_MASK(27)
#define DISASM_REG28 DISASM_BUILD_REGISTER_INDEX_MASK(28)
#define DISASM_REG29 DISASM_BUILD_REGISTER_INDEX_MASK(29)
#define DISASM_REG30 DISASM_BUILD_REGISTER_INDEX_MASK(30)
#define DISASM_REG31 DISASM_BUILD_REGISTER_INDEX_MASK(31)

typedef uint64_t DisasmOperandType;

typedef enum {
    DISASM_LOWPOSITION,
    DISASM_HIGHPOSITION
} DisasmPosition;

typedef enum {
    DISASM_EFLAGS_TESTED    = 0x01,   // the flag is tested
    DISASM_EFLAGS_MODIFIED  = 0x02,   // the flag is modified
    DISASM_EFLAGS_RESET     = 0x04,   // the flag is reset
    DISASM_EFLAGS_SET       = 0x08,   // the flag is set
    DISASM_EFLAGS_UNDEFINED = 0x10,   // undefined behavior
    DISASM_EFLAGS_PRIOR     = 0x20    // restore prior state
} DisasmEflagsState;

typedef enum {
    DISASM_BRANCH_JNO = -1,
    DISASM_BRANCH_JNC = -2,
    DISASM_BRANCH_JNB = DISASM_BRANCH_JNC,
    DISASM_BRANCH_JNE = -3,
    DISASM_BRANCH_JNA = -4,
    DISASM_BRANCH_JNS = -5,
    DISASM_BRANCH_JNP = -6,
    DISASM_BRANCH_JNL = -7,
    DISASM_BRANCH_JNG = -8,

    DISASM_BRANCH_NONE = 0,

    DISASM_BRANCH_JO = 1,
    DISASM_BRANCH_JC = 2,
    DISASM_BRANCH_JB = DISASM_BRANCH_JC,
    DISASM_BRANCH_JE = 3,
    DISASM_BRANCH_JA = 4,
    DISASM_BRANCH_JS = 5,
    DISASM_BRANCH_JP = 6,
    DISASM_BRANCH_JL = 7,
    DISASM_BRANCH_JG = 8,
    DISASM_BRANCH_JLE = DISASM_BRANCH_JNG,
    DISASM_BRANCH_JGE = DISASM_BRANCH_JNL,

    DISASM_BRANCH_JECXZ = 10,

    DISASM_BRANCH_JMP = 11,
    DISASM_BRANCH_CALL = 12,
    DISASM_BRANCH_RET = 13,

    DISASM_BRANCH_JCXZ = 14,
    DISASM_BRANCH_JRCXZ = 15
} DisasmBranchType;

typedef enum {
    DISASM_INST_COND_AL,
    DISASM_INST_COND_EQ,
    DISASM_INST_COND_NE,
    DISASM_INST_COND_CS,
    DISASM_INST_COND_CC,
    DISASM_INST_COND_MI,
    DISASM_INST_COND_PL,
    DISASM_INST_COND_VS,
    DISASM_INST_COND_VC,
    DISASM_INST_COND_HI,
    DISASM_INST_COND_LS,
    DISASM_INST_COND_GE,
    DISASM_INST_COND_LT,
    DISASM_INST_COND_GT,
    DISASM_INST_COND_LE,

    DISASM_INST_COND_NEVER
} DisasmCondition;

typedef enum {
    DISASM_SHIFT_NONE,
    DISASM_SHIFT_LSL,
    DISASM_SHIFT_LSR,
    DISASM_SHIFT_ASR,
    DISASM_SHIFT_ROR,
    DISASM_SHIFT_RRX
} DisasmShiftMode;

typedef enum {
    DISASM_ACCESS_NONE  =  0x0,
    DISASM_ACCESS_READ  =  0x1,
    DISASM_ACCESS_WRITE =  0x2
} DisasmAccessMode;

enum {
    DISASM_REG_INDEX_RAX, DISASM_REG_INDEX_RCX, DISASM_REG_INDEX_RDX, DISASM_REG_INDEX_RBX,
    DISASM_REG_INDEX_RSP, DISASM_REG_INDEX_RBP, DISASM_REG_INDEX_RSI, DISASM_REG_INDEX_RDI,
    DISASM_REG_INDEX_R8,  DISASM_REG_INDEX_R9,  DISASM_REG_INDEX_R10, DISASM_REG_INDEX_R11,
    DISASM_REG_INDEX_R12, DISASM_REG_INDEX_R13, DISASM_REG_INDEX_R14, DISASM_REG_INDEX_R15,
    DISASM_REG_INDEX_RIP
};

typedef enum {
    DISASM_ES_Reg = 1,
    DISASM_DS_Reg = 2,
    DISASM_FS_Reg = 3,
    DISASM_GS_Reg = 4,
    DISASM_CS_Reg = 5,
    DISASM_SS_Reg = 6
} DisasmSegmentReg;

typedef struct {
    uint8_t lockPrefix;
    uint8_t operandSize;
    uint8_t addressSize;
    uint8_t repnePrefix;
    uint8_t repPrefix;
} DisasmPrefix;

typedef struct {
    uint8_t OF_flag;
    uint8_t SF_flag;
    uint8_t ZF_flag;
    uint8_t AF_flag;
    uint8_t PF_flag;
    uint8_t CF_flag;
    uint8_t TF_flag;
    uint8_t IF_flag;
    uint8_t DF_flag;
    uint8_t NT_flag;
    uint8_t RF_flag;
} DisasmEFLAGS;

/// Define a memory access in the form [BASE_REGISTERS + (INDEX_REGISTERS) * SCALE + DISPLACEMENT]
typedef struct {
    uint32_t    baseRegister;                       /// Base registers mask
    uint32_t    indexRegister;                      /// Index registers mask
    int32_t     scale;                              /// Scale (1, 2, 4, 8)
    int64_t     displacement;                       /// Displacement
} DisasmMemoryAccess;

typedef struct  {
    char                mnemonic[20];               /// Instruction mnemonic, with its optional condition.

    char                unconditionalMnemonic[16];  /// Mnemonic string without the conditional part.
    DisasmCondition     condition;                  /// Condition to be met to execute instruction.

    uintptr_t           userData;                   /// A field that you can use internally to keep information on the instruction. Hopper don't need it.

    uint8_t             length;                     /// Length in bytes of the instruction encoding.

    DisasmBranchType    branchType;                 /// Information on the type of branch this instruction can perform.
    DisasmEFLAGS        eflags;                     /// Information on the CPU state register after this instruction is executed.
    Address             addressValue;               /// A value computed from one of the operands, known to point to an address.

    /// The value of the PC register at this address.
    /// For instance, on the Intel processor, it will be the address of the instruction + the length of the instruction.
    /// For the ARM processor, it will be the address of the instruction + 4 or 8, depending on various things.
    /// Anyway, it must reflects the exact value of the PC register if read from the instruction.
    Address             pcRegisterValue;

    uint8_t             ARMSBit;                    // ARM specific. Set to 1 if 'S' flag.
    uint8_t             ARMWriteBack;               // ARM specific: Set to 1 if writeback flag (!).
    uint8_t             ARMSpecial;                 // ARM specific: Set to 1 if special flag (^).
    uint8_t             ARMThumb;                   // ARM specifig: Set to 1 if thumb instruction.
} DisasmInstruction;

typedef struct {
    char               mnemonic[DISASM_OPERAND_MNEMONIC_MAX_LENGTH];
    DisasmOperandType  type;                /// Mask of DISASM_OPERAND_* values.
    uint32_t           size;                /// Argument size in bits. In the case of a memory access, this is the size of the read or written value.
    DisasmAccessMode   accessMode;          /// Whether the operand is accessed for reading or writing. DISASM_ACCESS_READ / DISASM_ACCESS_WRITE

    DisasmPosition     position;            /// DISASM_HIGHPOSITION / DISASM_LOWPOSITION: high position if for 8bits registers AH, BH, CH, DH

    DisasmSegmentReg   segmentReg;          /// X86 specific: the segment register used for the memory access.
    DisasmMemoryAccess memory;              /// Description of the memory indirection.
    int8_t             memoryDecoration;    /// Used for decoration on memory operands, like "dword ptr"… This is a plugin specific value, Hopper don't need it.

    /// Shifting used when the type is DISASM_OPERAND_REGISTER_TYPE
    DisasmShiftMode    shiftMode;           /// Shifting mode
    int32_t            shiftAmount;         /// Shifting amount (if not shifted by a register)
    int32_t            shiftByReg;          /// Shifting register

    int64_t            immediateValue;      /// The immediate value for this operand, if known.
} DisasmOperand;

typedef struct {
    /// Address where you can read the bytes to be decoded. Set by Hopper.
    const uint8_t *   bytes;

    /// Virtual address in the disassembled file space. Set by Hopper.
    Address           virtualAddr;

    /// Syntax to be used when building the various mnemonics.
    uint8_t           syntaxIndex;

    /// Formatted instruction string, directly displayed in Hopper.
    char              completeInstructionString[DISASM_INSTRUCTION_MAX_LENGTH];

    /// You can set the CPU, CPUSubType to any value during the initialization of the structure.
    /// These values are only used by plugins for their own purpose. Hopper don't need them.
    int32_t           CPU;
    int32_t           CPUSubType;

    /// Fields to be set by the plugin.
    DisasmPrefix      prefix;
    DisasmInstruction instruction;

    /// Mask of registers implicitly read or written.
    uint32_t          implicitlyReadRegisters[DISASM_MAX_REG_CLASSES];
    uint32_t          implicitlyWrittenRegisters[DISASM_MAX_REG_CLASSES];

    /// Instruction operands description
    DisasmOperand     operand[DISASM_MAX_OPERANDS];
} DisasmStruct;

#endif
