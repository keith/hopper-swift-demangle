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

@protocol HPProcedure;
@protocol HPTag;

@protocol HPBasicBlock

- (Address)from;
- (Address)to;

- (NSObject<HPProcedure> *)procedure;
- (NSUInteger)index;

- (BOOL)hasSuccessors;
- (BOOL)hasPredecessors;

- (NSArray *)predecessors; /// Array of NSObject<HPBasicBlocks> *
- (NSArray *)successors;   /// Array of NSObject<HPBasicBlocks> *

// Tags
- (void)addTag:(NSObject<HPTag> *)tag;
- (void)removeTag:(NSObject<HPTag> *)tag;
- (BOOL)hasTag:(NSObject<HPTag> *)tag;

@end
