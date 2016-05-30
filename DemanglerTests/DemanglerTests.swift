@testable import Demangler
import XCTest

extension DemangleResult: Equatable {}

public func == (lhs: DemangleResult, rhs: DemangleResult) -> Bool {
    switch (lhs, rhs) {
    case (.Success(let string), .Success(let string2)):
        return string == string2
    case (.Ignored(let string), .Ignored(let string2)):
        return string == string2
    case (.Failed(let string), .Failed(let string2)):
        return string == string2
    default:
        return false
    }
}

final class DemanglerTests: XCTestCase {
    private var demangler: Demangler!

    override func setUp() {
        super.setUp()

        demangler = Demangler()
    }

    func testDemangleSanity() {
        let demangledResult = demangler.demangle(string: "__TFV3foo3BarCfT_S0_")
        let expectedName = "foo.Bar.init () -> foo.Bar"

        XCTAssertEqual(demangledResult, DemangleResult.Success(expectedName))
    }

    func testReturningNonDemangledName() {
        let demangled = demangler.demangle(string: "sub_123")

        XCTAssertEqual(demangled, DemangleResult.Ignored("sub_123"))
    }

    func testDemanglingExtractedName() {
        let demangledString = demangler.demangle(string: "-[_TtC3foo3Baz objective]")
        let expectedString = "-[foo.Baz objective]"

        XCTAssertEqual(demangledString, DemangleResult.Success(expectedString))
    }
}
