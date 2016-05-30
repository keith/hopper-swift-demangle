extension HPDocument {
    func wait(withReason reason: String, forWork work: (document: HPDocument, file: HPDisassembledFile,
        shouldCancel: UnsafeMutablePointer<Bool>) -> Void)
    {
        if self.isWaiting() {
            return self.logErrorStringMessage("Already waiting on something")
        }

        guard let file = self.disassembledFile() else {
            return self.logErrorStringMessage("Document doesn't have a disassembled file yet")
        }

        var shouldCancel = false
        self.beginToWait(reason)

//
// For some reason passing a cancelBlock crashes 100%. But not if you do it via cycript :/
// Hopefully I can figure this out since it can take a long time to demangle large executables
//
//        self.beginToWait(reason, cancelBlock: { [weak self] in
//            shouldCancel = true
//            self?.logErrorStringMessage("Attempting to cancel")
//        })
//

        dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0)) {
            work(document: self, file: file, shouldCancel: &shouldCancel)

            dispatch_async(dispatch_get_main_queue()) {
                self.updateStaticNames()
                self.endWaiting()
            }
        }
    }
}
