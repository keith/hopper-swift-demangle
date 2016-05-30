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
#import "HPDisassembledFile.h"
#import "HPDetectedFileType.h"
#import "HopperPlugin.h"
#import "CommonTypes.h"

@class DetectedFileType;

@protocol FileLoader <NSObject,HopperPlugin>

- (BOOL)canLoadDebugFiles;

/// Returns an array of DetectedFileType objects.
- (NSArray *)detectedTypesForData:(NSData *)data;

/// Load a file.
/// The plugin should create HPSegment and HPSection objects.
/// It should also fill information about the CPU by setting the CPU family, the CPU subfamily and optionally the CPU plugin UUID.
/// The CPU plugin UUID should be set ONLY if you want a specific CPU plugin to be used. If you don't set it, it will be later set by Hopper.
/// During long operations, you should call the provided "callback" block to give a feedback to the user on the loading process.
- (FileLoaderLoadingStatus)loadData:(NSData *)data usingDetectedFileType:(DetectedFileType *)fileType options:(FileLoaderOptions)options forFile:(NSObject<HPDisassembledFile> *)file usingCallback:(FileLoadingCallbackInfo)callback;
- (FileLoaderLoadingStatus)loadDebugData:(NSData *)data forFile:(NSObject<HPDisassembledFile> *)file usingCallback:(FileLoadingCallbackInfo)callback;

/// Hopper changed the base address of the file, and needs help to fix it up.
/// The address of every segment was shifted of "slide" bytes.
- (void)fixupRebasedFile:(NSObject<HPDisassembledFile> *)file withSlide:(int64_t)slide originalFileData:(NSData *)fileData;

/// Extract a file
/// In the case of a "composite loader", extract the NSData object of the selected file.
- (NSData *)extractFromData:(NSData *)data
      usingDetectedFileType:(NSObject<HPDetectedFileType> *)fileType
         returnAdjustOffset:(uint64_t *)adjustOffset;

@end
