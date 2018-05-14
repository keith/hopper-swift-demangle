import Foundation

public enum DemangleResult {
    case Success(String)
    case Ignored(String)
    case Failed(String?)
}

public final class Demangler {
    private let ExtractFromObjCRegex = try! NSRegularExpression(pattern: "^[-+]\\[([^\\]]+)\\s+[^\\]]+\\]$",
                                                                options: [.anchorsMatchLines])

    private var internalDemangler: InternalDemangler = LibraryDemangler()

    public init() {}

    /**
     Demangle a mangled swift string

     - parameter name: A mangled swift string

     - returns: The demangled name
     */
    public func demangle(string mangledName: String?) -> DemangleResult {
        guard let string = mangledName else {
            return .Failed(mangledName)
        }

        if !self.shouldDemangle(string: string) {
            return .Ignored(string)
        }

        let (extracted, wasExtracted) = self.extractMangledString(fromObjCSelector: string)
        if let demangled = self.internalDemangler.demangle(string: extracted) {
            if wasExtracted {
                return .Success(self.integrateDemangledString(intoSelector: string, string: demangled))
            } else {
                return .Success(demangled)
            }
        } else {
            return .Failed(string)
        }
    }

    /**
     Integrate a demangled name back into the original ObjC selector it was pulled from.
     Example: -[_MangledName_ foo] -> -[Demangled foo]

     - parameter selector: The original ObjC style selector
     - parameter name:     The demangled name

     - returns: The demangled name integrated into the ObjC selector
     */
    func integrateDemangledString(intoSelector selector: String, string: String) -> String {
        let range = NSRange(location: 0, length: selector.utf16.count)
        let matches = self.ExtractFromObjCRegex.matches(in: selector, options: [], range: range)
        assert(matches.count <= 1)
        assert(matches.first?.numberOfRanges == 2)

        let match = matches.first!
        let matchRange = match.range(at: 1)
        let selectorString = selector as NSString
        let start = selectorString.substring(with: NSRange(location: 0, length: matchRange.location))
        let position = matchRange.location + matchRange.length
        let end = selectorString.substring(with: NSRange(location: position,
            length: selectorString.length - position))
        return "\(start)\(string)\(end)"
    }

    func extractMangledString(fromObjCSelector selector: String) -> (String, Bool) {
        let range = NSRange(location: 0, length: selector.utf16.count)
        let matches = self.ExtractFromObjCRegex.matches(in: selector, options: [], range: range)
        assert(matches.count <= 1)

        if let match = matches.first, match.numberOfRanges == 2 {
            let range = match.range(at: 1)
            return ((selector as NSString).substring(with: range), true)
        }

        return (selector, false)
    }

    /**
     Does a simple check to see if the string should be demangled. This only exists to reduce the number of
     times we have to shell out to the demangle tool.

     - SEEALSO: https://github.com/apple/swift/blob/82509cbd7451e72fb99d22556ad259ceb335cb1f/lib/SwiftDemangle/SwiftDemangle.cpp#L22

     - parameter string: The possibly mangled string

     - returns: true if a demangle should be attempted
     */
    func shouldDemangle(string: String) -> Bool {
        if string.hasPrefix("__T") {
            return true
        }

        if string.hasPrefix("_T") {
            return true
        }

        if string.hasPrefix("-[_T") {
            return true
        }

        if string.hasPrefix("+[_T") {
            return true
        }

        return false
    }
}
