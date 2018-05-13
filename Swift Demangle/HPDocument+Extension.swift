extension HPDocument {
    func wait(withReason reason: String,
              forWork work: @escaping (HPDocument, HPDisassembledFile, UnsafeMutablePointer<Bool>) -> Void)
    {
        if self.isWaiting() {
            return self.logErrorStringMessage("Already waiting on something")
        }

        guard let file = self.disassembledFile() else {
            return self.logErrorStringMessage("Document doesn't have a disassembled file yet")
        }

        var shouldCancel = false
        self.begin(toWait: reason)

//
// For some reason passing a cancelBlock crashes 100%. But not if you do it via cycript :/
// Hopefully I can figure this out since it can take a long time to demangle large executables
//
//        self.beginToWait(reason, cancelBlock: { [weak self] in
//            shouldCancel = true
//            self?.logErrorStringMessage("Attempting to cancel")
//        })
//

        DispatchQueue.global(qos: .userInitiated).async {
            work(self, file, &shouldCancel)

            DispatchQueue.main.async {
                self.updateStaticNames()
                self.endWaiting()
            }
        }
    }
}
