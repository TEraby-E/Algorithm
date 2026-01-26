class Vector :
    def __init__ (self, data) :
        self.data = data
    def norm ( self ) :
        return sum(x * x for x in self.data) ** 0.5