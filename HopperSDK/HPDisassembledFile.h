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

#import "CommonTypes.h"

@class HopperUUID;
@protocol CPUDefinition;
@protocol HPSegment;
@protocol HPSection;
@protocol HPProcedure;
@protocol HPTag;
@protocol CPUContext;

typedef void (^FileLoadingCallbackInfo)(NSString *desc, float progress);

@protocol HPDisassembledFile

@property (copy) HopperUUID *fileUUID;

@property (copy) NSString *cpuFamily;
@property (copy) NSString *cpuSubFamily;
@property (strong) NSObject<CPUDefinition> *cpuDefinition;

// Methods essentially used by Loader plugin
- (NSUInteger)addressSpaceWidthInBits;
- (void)setAddressSpaceWidthInBits:(NSUInteger)bits;

- (BOOL)is32Bits;
- (BOOL)is64Bits;

- (BOOL)analysisInProgress;

- (Address)fileBaseAddress;

- (void)addEntryPoint:(Address)address;
- (void)addPotentialProcedure:(Address)address;
- (Address)firstEntryPoint;
- (NSArray *)entryPoints;

// Get access to segments and sections
- (NSArray<NSObject<HPSegment> *> *)segments;
- (NSUInteger)segmentCount;

- (NSObject<HPSegment> *)segmentForVirtualAddress:(Address)virtualAddress;
- (NSObject<HPSection> *)sectionForVirtualAddress:(Address)virtualAddress;

- (NSObject<HPSegment> *)segmentNamed:(NSString *)name;
- (NSObject<HPSection> *)sectionNamed:(NSString *)name;

- (NSObject<HPSegment> *)addSegmentAt:(Address)address size:(size_t)length;
- (NSObject<HPSegment> *)addSegmentAt:(Address)address toExcludedAddress:(Address)endAddress;

- (NSObject<HPSegment> *)firstSegment;
- (NSObject<HPSegment> *)lastSegment;
- (NSObject<HPSection> *)firstSection;
- (NSObject<HPSection> *)lastSection;

- (NSObject<HPSegment> *)previousSegment:(NSObject<HPSegment> *)segment;
- (NSObject<HPSegment> *)nextSegment:(NSObject<HPSegment> *)segment;

// CPUContext factory
- (NSObject<CPUContext> *)buildCPUContext;

// Access to the labels
/// An array of NSString objects, containing all labels.
- (NSArray *)allNames;
/// An array of NSNumber objects, representing the address of memory locations that was named.
- (NSArray *)allNamedAddresses;
- (NSString *)nameForVirtualAddress:(Address)virtualAddress;
- (NSString *)nearestNameBeforeVirtualAddress:(Address)virtualAddress;

- (Address)nearestNamedAddressBeforeVirtualAddress:(Address)virtualAddress;
- (void)setName:(NSString *)name forVirtualAddress:(Address)virtualAddress reason:(NameCreationReason)reason;
- (Address)findVirtualAddressNamed:(NSString *)name;

// Comments
- (void)removeCommentAtVirtualAddress:(Address)virtualAddress;
- (void)removeInlineCommentAtVirtualAddress:(Address)virtualAddress;
- (NSString *)commentAtVirtualAddress:(Address)virtualAddress;
- (NSString *)inlineCommentAtVirtualAddress:(Address)virtualAddress;
- (void)setComment:(NSString *)comment atVirtualAddress:(Address)virtualAddress reason:(CommentCreationReason)reason;
- (void)setInlineComment:(NSString *)comment atVirtualAddress:(Address)virtualAddress reason:(CommentCreationReason)reason;

// Types
- (BOOL)typeCanBeModifiedAtAddress:(Address)va;
- (ByteType)typeForVirtualAddress:(Address)virtualAddress;
- (void)setType:(ByteType)type atVirtualAddress:(Address)virtualAddress forLength:(size_t)length;
- (BOOL)hasCodeAt:(Address)virtualAddress;
- (uint8_t)cpuModeAtVirtualAddress:(Address)virtualAddress;

- (void)newRuntimeMethodNameDefinedAt:(Address)virtualAddress;

// Searching
- (Address)findNextAddress:(Address)address ofTypeOrMetaType:(ByteType)typeOrMetaType wrapping:(BOOL)wrapping;

// Instruction Operand Format
- (ArgFormat)formatForArgument:(int)argIndex atVirtualAddress:(Address)virtualAddress;
- (void)setFormat:(ArgFormat)format forArgument:(int)argIndex atVirtualAddress:(Address)virtualAddress;

// Procedures
- (BOOL)hasProcedureAt:(Address)address;
- (NSObject<HPProcedure> *)procedureAt:(Address)address;
- (void)removeProcedure:(NSObject<HPProcedure> *)procedure;
- (void)removeProcedureAt:(Address)address;

// Colors
- (BOOL)hasColorAt:(Address)address;
- (Color)colorAt:(Address)address;
- (void)setColor:(Color)color at:(Address)address;
- (void)setColor:(Color)color atRange:(AddressRange)range;
- (void)clearColorAt:(Address)address;
- (void)clearColorAtRange:(AddressRange)range;

// Tags
- (NSObject<HPTag> *)tagWithName:(NSString *)tagName;
- (NSObject<HPTag> *)buildTag:(NSString *)tagName;
- (void)deleteTag:(NSObject<HPTag> *)tag;
- (void)deleteTagName:(NSString *)tagName;

- (void)addTag:(NSObject<HPTag> *)tag at:(Address)address;
- (void)removeTag:(NSObject<HPTag> *)tag at:(Address)address;
- (NSArray *)tagsAt:(Address)virtualAddress;
- (BOOL)hasTag:(NSObject<HPTag> *)tag at:(Address)virtualAddress;

// Problem list
- (void)addProblemAt:(Address)address withString:(NSString *)message;

// Assembler
- (NSData *)assembleInstruction:(NSString *)instr atAddress:(Address)address withCPUMode:(uint8_t)cpuMode usingSyntaxVariant:(NSUInteger)syntax isRawData:(BOOL *)isRawData error:(NSError **)error;
- (NSData *)nopDataForRegion:(AddressRange)range;

// Reading file
// Warning: don't use these methods in a Loader plugin, because no CPU plugin
// is attached to the file at this stage!
// Note: writing operations are defined in the HPDocument protocol.
- (int8_t)readInt8AtVirtualAddress:(Address)virtualAddress;
- (int16_t)readInt16AtVirtualAddress:(Address)virtualAddress;
- (int32_t)readInt32AtVirtualAddress:(Address)virtualAddress;
- (int64_t)readInt64AtVirtualAddress:(Address)virtualAddress;
- (uint8_t)readUInt8AtVirtualAddress:(Address)virtualAddress;
- (uint16_t)readUInt16AtVirtualAddress:(Address)virtualAddress;
- (uint32_t)readUInt32AtVirtualAddress:(Address)virtualAddress;
- (uint64_t)readUInt64AtVirtualAddress:(Address)virtualAddress;

- (Address)readAddressAtVirtualAddress:(Address)virtualAddress;

- (int64_t)readSignedLEB128AtVirtualAddress:(Address)virtualAddress length:(size_t *)numberLength;
- (uint64_t)readUnsignedLEB128AtVirtualAddress:(Address)virtualAddress length:(size_t *)numberLength;

- (NSString *)readCStringAt:(Address)address;

// Misc
- (Address)parseAddressString:(NSString *)addressString;

// Undo/Redo Stack Management
- (BOOL)undoRedoLoggingEnabled;

- (void)beginUndoRedoTransactionWithName:(NSString *)name;
- (void)endUndoRedoTransaction;
- (void)discardUndoRedoTransaction;

@end
