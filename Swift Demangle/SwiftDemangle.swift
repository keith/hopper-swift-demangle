import Demangler
import Foundation

@objc
final class SwiftDemangle: NSObject, HopperTool {
    var services: HPHopperServices
    var demangler = Demangler()

    init(hopperServices: HPHopperServices) {
        self.services = hopperServices
    }

    func pluginUUID() -> HopperUUID {
        return self.services.UUIDWithString("C8FAB152-90FC-4C70-9FA2-4828A2DF322F")
    }

    func pluginName() -> String {
        return "Swift Demangle"
    }

    func pluginAuthor() -> String {
        return "Keith Smiley"
    }

    func pluginVersion() -> String {
        return NSBundle.mainBundle().pluginVersion
    }

    func pluginCopyright() -> String {
        return "©2016 Keith Smiley"
    }

    func pluginDescription() -> String {
        return "Demangle Swift Selectors"
    }

    func pluginType() -> HopperPluginType {
        return .Plugin_Tool
    }

    func toolMenuDescription() -> [[String: AnyObject]] {
        return [
            [
                "Title": "Demangle Swift",
                "Submenu": [
                    [
                        "Title": "Demangle Entire File",
                        "Selector": "demangleAllProcedures",
                    ],
                    [
                        "Title": "Demangle Closest Name",
                        "Selector": "demangleClosestName",
                    ],
                ]
            ],
        ]
    }
}
