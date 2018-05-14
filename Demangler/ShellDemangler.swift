import Foundation

final class ShellDemangler: InternalDemangler {
    private lazy var executablePath: String = {
        return self.output(forShellCommand: "/usr/bin/xcrun --find swift-demangle")!
    }()

    func demangle(string: String) -> String? {
        return self.output(forShellCommand: self.demangleCommand(forString: string))
    }

    private func demangleCommand(forString string: String) -> String {
        return "\(self.executablePath) -compact \(string)"
    }

    private func output(forShellCommand command: String) -> String? {
        assert(command.split().count >= 2)

        let task = Process()
        let pipe = Pipe()
        let components = command.split()

        task.launchPath = components.first
        task.arguments = Array(components.dropFirst())
        task.standardOutput = pipe

        task.launch()
        task.waitUntilExit()

        let data = pipe.fileHandleForReading.readDataToEndOfFile()
        return String(data: data, encoding: .utf8)?.strip()
    }
}
