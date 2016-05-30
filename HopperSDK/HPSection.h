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

@protocol HPSegment;

@protocol HPSection

@property (nonatomic, copy) NSString *sectionName;

@property (nonatomic, assign) uint64_t fileOffset;
@property (nonatomic, assign) uint64_t fileLength;

@property (nonatomic) BOOL pureCodeSection;
@property (nonatomic) BOOL pureDataSection;
@property (nonatomic) BOOL containsCode;
@property (nonatomic) BOOL pureCStringSection;

- (Address)startAddress;
- (size_t)length;

- (Address)endAddress;

- (BOOL)hasDataOnDisk;

- (NSObject<HPSegment> *)segment;
- (NSObject<HPSection> *)previousSection;
- (NSObject<HPSection> *)nextSection;

- (BOOL)sectionContainsAddress:(Address)address;

@end
