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

@class HopperUUID;

@protocol HPLoaderOptionComponents <NSObject>

@property (assign) Address addressValue;

@property (assign) BOOL isChecked;

@property (strong) HopperUUID *cpuUUID;
@property (strong) NSString *cpuFamily;
@property (strong) NSString *cpuSubFamily;

@property (strong) NSArray *stringList;
@property (assign) NSUInteger selectedStringIndex;

@end
