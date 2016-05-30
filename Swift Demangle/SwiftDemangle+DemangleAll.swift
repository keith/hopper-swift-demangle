import Foundation

extension SwiftDemangle {
    func demangleAllProcedures(withDocument document: HPDocument) {
        if self.showAnalysisAlertAndCancel(forDocument: document) {
            return
        }

        document.wait(withReason: "Demangling All Procedures") { document, file, shouldCancel in
            self.demangleAllProcedures(withDocument: document, file: file, shouldCancel: shouldCancel)
        }
    }

    private func demangleAllProcedures(withDocument document: HPDocument,
                                                    file: HPDisassembledFile,
                                                    shouldCancel: UnsafeMutablePointer<Bool>)
    {
        let segments = file.segments()
        var procedureCount: Int?

        dispatch_async(dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0)) {
            let totalProcedureCount = segments.reduce(0) { accumulator, segment in
                return accumulator + segment.procedures().count
            }

            procedureCount = totalProcedureCount
            document.logStringMessage("Found \(totalProcedureCount) procedures")
        }

        var processedCount = 0
        for segment in segments {
            for procedure in segment.procedures() {
                if shouldCancel.memory {
                    let countString = procedureCount.map(String.init) ?? "Unknown"
                    return document.logErrorStringMessage(
                        "Cancelling after demangling \(processedCount) of \(countString) procedures")
                }

                if let procedureCount = procedureCount {
                    let progressString = "Demangling \(processedCount + 1) of \(procedureCount)"
                    let percentDone = Float(processedCount) / Float(procedureCount)
                    document.updateWaitingValue(percentDone, desc: progressString)
                } else {
                    document.updateWaitingValue(1, desc: "Demangling \(processedCount + 1)")
                }

                let procedureAddress = procedure.entryPoint()
                let mangledString: String? = segment.nameForVirtualAddress(procedureAddress)
                let demangleResult = self.demangler.demangle(string: mangledString)
                self.handle(demangleResult: demangleResult, forAddress: procedureAddress,
                            mangledString: mangledString, file: file, document: document)

                processedCount += 1
            }
        }
    }


    /**
     Show an alert indicating analysis is still in progress and not all procedures will be demangled.
     (Since those that are not yet loaded cannot be demangled)
     
     - returns: true if the user decides that we should cancel
     */
    private func showAnalysisAlertAndCancel(forDocument document: HPDocument) -> Bool {
        if document.disassembledFile()?.analysisInProgress() == true {
            let response = document.displayAlertWithMessageText("File is still being analyzed",
                defaultButton: "Cancel", alternateButton: "Continue", otherButton: nil,
                informativeText: "Would you like to demangle what has already been loaded?")

            // Cancel Button Pressed
            return response == 1
        }

        return false
    }
}
