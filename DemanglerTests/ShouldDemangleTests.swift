@testable import Demangler
import XCTest

final class ShouldDemangleTests: XCTestCase {
    private var demangler: Demangler!

    override func setUp() {
        super.setUp()

        demangler = Demangler()
    }

    func testShouldNotDemangleSub() {
        let shouldDemangle = demangler.shouldDemangle(string: "sub_123")

        XCTAssertFalse(shouldDemangle)
    }

    func testShouldNotDemangleImp() {
        let shouldDemangle = demangler.shouldDemangle(string: "imp__abc")

        XCTAssertFalse(shouldDemangle)
    }

    func testShouldDemangleMangledString() {
        let shouldDemangle = demangler.shouldDemangle(string: "__TFV3foo3BarCfT_S0_")

        XCTAssertTrue(shouldDemangle)
    }

    func testShouldDemangleClassFunction() {
        let shouldDemangle = demangler.shouldDemangle(string: "+[_TtC3foo3Baz objective]")

        XCTAssertTrue(shouldDemangle)
    }

    func testShouldDemangleNormalString() {
        let shouldDemangle = demangler.shouldDemangle(string: "_TtC3foo3Baz")

        XCTAssertTrue(shouldDemangle)
    }
}
