@testable import Demangler
import XCTest

final class StringExtensionTests: XCTestCase {
    func testSplit() {
        let string = "hi there"
        let components = string.split()
        XCTAssertEqual(components, ["hi", "there"])
    }

    func testStrip() {
        let string = "hi there\n"
        XCTAssertEqual(string.strip(), "hi there")
    }
}
