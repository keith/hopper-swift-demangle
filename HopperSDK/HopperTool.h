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
#import "HopperPlugin.h"

#define HPM_TITLE           @"Title"
#define HPM_SELECTOR        @"Selector"
#define HPM_SUBMENU         @"Submenu"

@protocol HopperTool <NSObject,HopperPlugin>

/// Returns an array of menu description to be added to Hopper.
/// A description contains at least a HPM_TITLE key, and a HPM_SELECTOR or a HPM_SUBMENU key.
/// The HPM_SELECTOR is a string which contains a selector name, which will be resolved by
/// Hopper at runtime, using the NSSelectorFromString system method.
- (nonnull NSArray<NSDictionary<NSString *, id> *> *)toolMenuDescription;

@end
