import Foundation

private typealias SwiftDemangleFunction = @convention(c) (UnsafePointer<CChar>,
    UnsafeMutablePointer<CChar>, size_t) -> size_t

private let kDemangleLibraryPath = ("/Applications/Xcode.app/Contents/Developer/Toolchains" +
    "/XcodeDefault.xctoolchain/usr/lib/libswiftDemangle.dylib")
private let kBufferSize = 1024

final class LibraryDemangler: InternalDemangler {
    private var handle: UnsafeMutablePointer<Void> = {
        return dlopen(kDemangleLibraryPath, RTLD_NOW)
    }()

    private lazy var internalDemangleFunction: SwiftDemangleFunction = {
        let address = dlsym(self.handle, "swift_demangle_getDemangledName")
        return unsafeBitCast(address, SwiftDemangleFunction.self)
    }()

    func demangle(string string: String) -> String? {
        let formattedString = self.removingExcessLeadingUnderscores(fromString: string)
        let outputString = UnsafeMutablePointer<CChar>.alloc(kBufferSize)
        let resultSize = self.internalDemangleFunction(formattedString, outputString, kBufferSize)
        if resultSize > kBufferSize {
            NSLog("Attempted to demangle string with length \(resultSize) but buffer size \(kBufferSize)")
        }

        return String(CString: outputString, encoding: NSUTF8StringEncoding)
    }

    private func removingExcessLeadingUnderscores(fromString string: String) -> String {
        if string.hasPrefix("__T") {
            return String(string.characters.dropFirst())
        }

        return string
    }

    deinit {
        dlclose(self.handle)
    }
}
