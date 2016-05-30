@testable import Demangler
import XCTest

final class DemangleObjCSelectorTests: XCTestCase {
    private var demangler: Demangler!

    override func setUp() {
        super.setUp()

        demangler = Demangler()
    }

    func testExtractsString() {
        let (name, extracted) = demangler.extractMangledString(fromObjCSelector: "-[Foo bar]")

        XCTAssertEqual(name, "Foo")
        XCTAssertTrue(extracted)
    }

    func testDoesNotExtractNonObjCString() {
        let (name, extracted) = demangler.extractMangledString(fromObjCSelector: "_TCFoo")

        XCTAssertEqual(name, "_TCFoo")
        XCTAssertFalse(extracted)
    }

    func testIntegrateString() {
        let selector = demangler.integrateDemangledString(intoSelector: "-[Foo bar]", string: "Baz")

        XCTAssertEqual(selector, "-[Baz bar]")
    }

    func testIntegrateStringIntoClassSelector() {
        let selector = demangler.integrateDemangledString(intoSelector: "+[Foo.qux bar]", string: "Baz")

        XCTAssertEqual(selector, "+[Baz bar]")
    }
}
