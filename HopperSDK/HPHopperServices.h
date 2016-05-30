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

@protocol HPDocument;
@protocol HPDetectedFileType;
@protocol HPLoaderOptionComponents;

@protocol HPHopperServices <NSObject>

// Global
- (NSInteger)hopperMajorVersion;
- (NSInteger)hopperMinorVersion;
- (NSInteger)hopperRevision;
- (nonnull NSString *)hopperVersionString;

- (nullable NSObject<HPDocument> *)currentDocument;
- (void)logMessage:(nonnull NSString *)message;

// Build an UUID object from a string like XXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
- (nonnull HopperUUID *)UUIDWithString:(nonnull NSString *)uuidString;

// New detected type
- (nullable NSObject<HPDetectedFileType> *)detectedType;

// Information about attributes used in the ASM view
- (nullable NSDictionary *)ASMOperatorAttributes;
- (nullable NSDictionary *)ASMNumberAttributes;
- (nullable NSDictionary *)ASMLanguageAttributes;
- (nullable NSDictionary *)ASMSubLanguageAttributes;
- (nullable NSDictionary *)ASMCommentAttributes;

- (void)colorizeASMString:(nonnull NSMutableAttributedString *)string
        operatorPredicate:(nonnull BOOL(^)(unichar c))operatorPredicate
    languageWordPredicate:(nonnull BOOL(^)(NSString * __nonnull s))languageWordPredicate
 subLanguageWordPredicate:(nonnull BOOL(^)(NSString * __nonnull s))subLanguageWordPredicate;

// Options for loaders
- (nullable NSObject<HPLoaderOptionComponents> *)addressComponentWithLabel:(nonnull NSString *)label;
- (nullable NSObject<HPLoaderOptionComponents> *)checkboxComponentWithLabel:(nonnull NSString *)label;
- (nullable NSObject<HPLoaderOptionComponents> *)cpuComponentWithLabel:(nonnull NSString *)label;
- (nullable NSObject<HPLoaderOptionComponents> *)addressComponentWithLabel:(nonnull NSString *)label andValue:(Address)value;
- (nullable NSObject<HPLoaderOptionComponents> *)checkboxComponentWithLabel:(nonnull NSString *)label checked:(BOOL)checked;
- (nullable NSObject<HPLoaderOptionComponents> *)stringListComponentWithLabel:(nonnull NSString *)label andList:(nonnull NSArray *)strings;
- (nullable NSObject<HPLoaderOptionComponents> *)comboBoxComponentWithLabel:(nonnull NSString *)label andList:(nonnull NSArray *)strings;

@end
