import Foundation

extension NSBundle {
    var pluginVersion: String {
        return self.infoDictionary?["CFBundleShortVersionString"] as? String ?? "Unknown"
    }
}
