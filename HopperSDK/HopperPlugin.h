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
#import "CommonTypes.h"

@interface HopperUUID: NSObject
@end

@protocol HPHopperServices;

@protocol HopperPlugin <NSObject>

- (nonnull instancetype)initWithHopperServices:(nonnull NSObject<HPHopperServices> *)services;

- (nonnull HopperUUID *)pluginUUID;
- (HopperPluginType)pluginType;

- (nonnull NSString *)pluginName;
- (nonnull NSString *)pluginDescription;
- (nonnull NSString *)pluginAuthor;
- (nonnull NSString *)pluginCopyright;
- (nonnull NSString *)pluginVersion;

@end
