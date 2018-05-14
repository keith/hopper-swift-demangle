import Foundation

extension Bundle {
    var pluginVersion: String {
        return self.infoDictionary?["CFBundleShortVersionString"] as? String ?? "Unknown"
    }
}
