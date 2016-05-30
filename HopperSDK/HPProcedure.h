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

@protocol HPTag;
@protocol HPBasicBlock;
@protocol HPSegment;
@protocol CPUContext;

@protocol HPProcedure

- (BOOL)bpBasedFrame;
- (int32_t)savedRegistersSize;
- (int32_t)framePointerOffset;
- (int32_t)purgedBytes;
- (int32_t)localsSize;

- (NSUInteger)basicBlockCount;
- (NSObject<HPBasicBlock> *)firstBasicBlock;
- (NSObject<HPBasicBlock> *)basicBlockStartingAt:(Address)address;
- (NSObject<HPBasicBlock> *)basicBlockContainingInstructionAt:(Address)address;
- (NSObject<HPBasicBlock> *)basicBlockAtIndex:(NSUInteger)index;

- (NSObject<HPSegment> *)segment;

- (Address)entryPoint;
- (NSArray *)allExitBlocks; // Array of BasicBlock

// Stack
- (int16_t)stackPointerOffsetAt:(Address)address;

// Variables
- (NSString *)variableNameForDisplacement:(int64_t)disp;
- (void)setVariableName:(NSString *)name forDisplacement:(int64_t)disp;
- (NSString *)resolvedVariableNameForDisplacement:(int64_t)disp usingCPUContext:(NSObject<CPUContext> *)cpuContext;

// Tags
- (void)addTag:(NSObject<HPTag> *)tag;
- (void)removeTag:(NSObject<HPTag> *)tag;
- (BOOL)hasTag:(NSObject<HPTag> *)tag;

@end
