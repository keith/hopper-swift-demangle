import Foundation

extension String {
    func split() -> [String] {
        return self.characters.split(" ").map(String.init)
    }

    func strip() -> String {
        return self.stringByTrimmingCharactersInSet(NSCharacterSet.whitespaceAndNewlineCharacterSet())
    }
}

