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

#import <Foundation/Foundation.h>
#include "DisasmStruct.h"

@protocol HPSegment;
@protocol HPProcedure;
@protocol HPBasicBlock;
@protocol HPFormattedInstructionInfo;
@protocol HPDisassembledFile;
@protocol CPUDefinition;

@class Decompiler;
@class ASTNode;

@protocol CPUContext

- (NSObject<CPUDefinition> *)cpuDefinition;

- (void)initDisasmStructure:(DisasmStruct*)disasm withSyntaxIndex:(NSUInteger)syntaxIndex;

////////////////////////////////////////////////////////////////////////////////
//
// Analysis
//
////////////////////////////////////////////////////////////////////////////////

/// Adjust address to the lowest possible address acceptable by the CPU. Example: M68000 instruction must be word aligned, so this method would clear bit 0.
- (Address)adjustCodeAddress:(Address)address;

/// Returns a guessed CPU mode for a given address. Example, ARM processors knows that an instruction is in Thumb mode if bit 0 is 1.
- (uint8_t)cpuModeFromAddress:(Address)address;

/// Returns YES if we know that a given address forces the CPU to use a specific mode. Thumb mode of comment above.
- (BOOL)addressForcesACPUMode:(Address)address;

/// An heuristic to estimate the CPU mode at a given address, not based on the value of the
/// address itself (this is the purpose of the "cpuModeFromAddress:" method), but rather
/// by trying to disassemble a few instruction and see which mode seems to be the best guess.
- (uint8_t)estimateCPUModeAtVirtualAddress:(Address)address;

- (Address)nextAddressToTryIfInstructionFailedToDecodeAt:(Address)address forCPUMode:(uint8_t)mode;

/// Return 0 if the instruction at this address doesn't represent a NOP instruction (or any padding instruction), or the insturction length if any.
- (int)isNopAt:(Address)address;

/// Returns YES if a procedure prolog has been detected at this address.
- (BOOL)hasProcedurePrologAt:(Address)address;

/// Notify the plugin that an analysisbegan from an entry point.
/// This could be either a simple disassembling, or a procedure creation.
/// In the latter case, another method will be called to notify the plugin (see below).
- (void)analysisBeginsAt:(Address)entryPoint;
/// Notify the plugin that analysis has ended.
- (void)analysisEnded;

/// A Procedure object is about to be created.
- (void)procedureAnalysisBeginsForProcedure:(NSObject<HPProcedure> *)procedure atEntryPoint:(Address)entryPoint;
/// The prolog of the created procedure is being analyzed.
/// Warning: this method is not called at the begining of the procedure creation, but once all basic blocks
/// have been created.
- (void)procedureAnalysisOfPrologForProcedure:(NSObject<HPProcedure> *)procedure atEntryPoint:(Address)entryPoint;
- (void)procedureAnalysisOfEpilogForProcedure:(NSObject<HPProcedure> *)procedure atEntryPoint:(Address)entryPoint;
- (void)procedureAnalysisEndedForProcedure:(NSObject<HPProcedure> *)procedure atEntryPoint:(Address)entryPoint;

/// A new basic bloc is created
- (void)procedureAnalysisContinuesOnBasicBlock:(NSObject<HPBasicBlock> *)basicBlock;

/// This method may be called when the internal state of the disassembler should be reseted.
/// For instance, the ARM plugin maintains a state during the disassembly process to
/// track the state of IT blocks. When this method is called, this state is reseted.
- (void)resetDisassembler;

/// Disassemble a single instruction, filling the DisasmStruct structure.
/// Only a few fields are set by Hopper (mainly, the syntaxIndex, the "bytes" field and the virtualAddress of the instruction).
/// The CPU should fill as much information as possible.
- (int)disassembleSingleInstruction:(DisasmStruct *)disasm usingProcessorMode:(NSUInteger)mode;

/// Returns whether or not an instruction may halt the processor (like the HLT Intel instruction).
- (BOOL)instructionHaltsExecutionFlow:(DisasmStruct *)disasm;

/// These methods are called to let you update your internal plugin state during the analysis.
- (void)performProcedureAnalysis:(NSObject<HPProcedure> *)procedure basicBlock:(NSObject<HPBasicBlock> *)basicBlock disasm:(DisasmStruct *)disasm;
- (void)updateProcedureAnalysis:(DisasmStruct *)disasm;

/// Return YES if the provided DisasmStruct represents an instruction that cand directly reference a memory address.
/// Ususally, this methods returns YES. This is used by the ARM plugin to avoid false references on "MOVW" instruction
/// for instance.
- (BOOL)instructionCanBeUsedToExtractDirectMemoryReferences:(DisasmStruct *)disasmStruct;

/// Return YES if the instruction may be used to build a switch/case statement.
/// For instance, for the Intel processor, it returns YES for the "JMP reg" and the "JMP [xxx+reg*4]" instructions,
/// and for the Am processor, it returns YES for the "TBB" and "TBH" instructions.
- (BOOL)instructionMayBeASwitchStatement:(DisasmStruct *)disasmStruct;

/// If a branch instruction is found, Hopper calls this method to compute additional destinations of the instruction.
/// The "*next" value is already set to the address which follows the instruction if the jump does not occurs.
/// The "branches" array is filled by NSNumber objects. The values are the addresses where the instruction can jump. Only the
/// jumps that occur in the same procedure are put here (for instance, CALL instruction targets are not put in this array).
/// The "calledAddresses" array is filled by NSNumber objects of addresses that are the target of a "CALL like" instruction, ie
/// all the jumps which go outside of the procedure.
/// The "callSiteAddresses" contains NSNumber of the addresses of the "CALL" instructions.
/// The purpose of this method is to compute additional destinations.
/// Most of the time, Hopper already found the destinations, so there is no need to do more.
/// This is used by the Intel CPU plugin to compute the destinations of switch/case constructions when it found a "JMP register" instruction.
- (void)performBranchesAnalysis:(DisasmStruct *)disasm
           computingNextAddress:(Address *)next
                    andBranches:(NSMutableArray *)branches
                   forProcedure:(NSObject<HPProcedure> *)procedure
                     basicBlock:(NSObject<HPBasicBlock> *)basicBlock
                      ofSegment:(NSObject<HPSegment> *)segment
                calledAddresses:(NSMutableArray *)calledAddresses
                      callsites:(NSMutableArray *)callSitesAddresses;

/// If you need a specific analysis, this method will be called once the previous branch analysis is performed.
/// For instance, this is used by the ARM CPU plugin to set the type of the destination of an LDR instruction to
/// an int of the correct size.
- (void)performInstructionSpecificAnalysis:(DisasmStruct *)disasm forProcedure:(NSObject<HPProcedure> *)procedure inSegment:(NSObject<HPSegment> *)segment;

/// Returns the destination address if the function starting at the given address is a thunk (ie: a direct jump to another method)
/// Returns BAD_ADDRESS is the instruction is not a thunk.
- (Address)getThunkDestinationForInstructionAt:(Address)address;

////////////////////////////////////////////////////////////////////////////////
//
// Printing instruction
//
////////////////////////////////////////////////////////////////////////////////

/// Build the complete instruction string in the DisasmStruct structure.
/// This is the string to be displayed in Hopper.
- (void)buildInstructionString:(DisasmStruct *)disasm forSegment:(NSObject<HPSegment> *)segment populatingInfo:(NSObject<HPFormattedInstructionInfo> *)formattedInstructionInfo;

////////////////////////////////////////////////////////////////////////////////
//
// Decompiler
//
////////////////////////////////////////////////////////////////////////////////

- (BOOL)canDecompileProcedure:(NSObject<HPProcedure> *)procedure;

/// Return the address of the first instruction of the procedure, after its prolog.
- (Address)skipHeader:(NSObject<HPBasicBlock> *)basicBlock ofProcedure:(NSObject<HPProcedure> *)procedure;

/// Return the address of the last instruction of the procedure, before its epilog.
- (Address)skipFooter:(NSObject<HPBasicBlock> *)basicBlock ofProcedure:(NSObject<HPProcedure> *)procedure;

/// Decompile an assembly instruction.
/// Note: ASTNode is not publicly exposed yet. You cannot write a decompiler at the moment.
- (ASTNode *)decompileInstructionAtAddress:(Address)a
                                    disasm:(DisasmStruct)d
                                 addNode_p:(BOOL *)addNode_p
                           usingDecompiler:(Decompiler *)decompiler;

////////////////////////////////////////////////////////////////////////////////
//
// Assembler
//
////////////////////////////////////////////////////////////////////////////////

- (NSData *)assembleRawInstruction:(NSString *)instr atAddress:(Address)addr forFile:(NSObject<HPDisassembledFile> *)file withCPUMode:(uint8_t)cpuMode usingSyntaxVariant:(NSUInteger)syntax error:(NSError **)error;

@end
