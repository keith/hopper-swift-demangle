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

@protocol HPFormattedInstructionInfo

/// Indicates that the operand contains a reference to a local variable on stack.
/// This is an information used by Hopper to let one renames stack variables from the interface
/// when the cursor is on an operand that references a variable, instead of renaming the address.
- (void)setFormatOfOperandIndex:(NSUInteger)operand toStackVariableWithDisplacement:(int)displacement;

@end
