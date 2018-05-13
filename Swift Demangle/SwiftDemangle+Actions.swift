import Demangler
import Foundation

private enum Action {
    case DemangleClosest
    case DemangleAll
}

extension SwiftDemangle {
    @objc
    func demangleClosestName() {
        self.performAction(action: .DemangleClosest)
    }

    @objc
    func demangleAllProcedures() {
        self.performAction(action: .DemangleAll)
    }

    private func performAction(action: Action) {
        let function: (HPDocument) -> Void
        switch action {
        case .DemangleClosest:
            function = self.demangleClosestName
        case .DemangleAll:
            function = self.demangleAllProcedures
        }

        if let document = self.services.currentDocument() {
            function(document)
        } else {
            self.services.logMessage("No document currently loaded")
        }
    }

    // MARK: - Actions

    private func demangleClosestName(withDocument document: HPDocument) {
        document.wait(withReason: "Demangling Closest Name") { document, file, _ in
            let address = file.nearestNamedAddress(beforeVirtualAddress: document.currentAddress())
            let mangledString = file.name(forVirtualAddress: address)
            let demangleResult = self.demangler.demangle(string: mangledString)
            self.handle(demangleResult: demangleResult, forAddress: address, mangledString: mangledString,
                        file: file, document: document)
        }
    }

    func handle(demangleResult result: DemangleResult, forAddress address: Address,
                               mangledString: String?, file: HPDisassembledFile, document: HPDocument)
    {
        switch result {
        case .Success(let demangledString):
            file.setName(demangledString, forVirtualAddress: address, reason: .NCReason_Script)
            document.logStringMessage("Demangled '\(mangledString ?? "")' -> '\(demangledString)'")
        case .Ignored(let ignoredString):
            document.logStringMessage("Ignoring '\(ignoredString)'")
        case .Failed(let failedString):
            document.logStringMessage("Failed to demangle '\(failedString ?? "")'")
        }
    }
}
