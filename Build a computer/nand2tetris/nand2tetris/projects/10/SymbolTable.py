# created by mike meng @ 2020.12.23

class SymbolTable:
    def __init__(self):
        # reset yambol table
        self.table = {}
        self.cnt = {}
        self.startSubroutine()

    def startSubroutine(self):
        self.table.clear()
        self.cnt["static"] = 0
        self.cnt["field"] = 0
        self.cnt["argument"] = 0
        self.cnt["var"] = 0
        
    def define(self,name,varType,varKind):
        assert (name not in self.table), "duplicate variable name!\n\r"
        self.table[name] = (varType,varKind,self.cnt[varKind])
        self.cnt[varKind] += 1
        return 0
    
    def varCount(self,kind):
        return self.cnt[kind]
    
    def kindOf(self,name):
        assert (name in self.table), "invalid variable name!\n\r"
        return self.table[name][1]

    def typeOf(self,name):
        assert (name in self.table), "invalid variable name!\n\r"
        return self.table[name][0]
    
    def indexOf(self,name):
        if name in self.table:
            return self.table[name][2]
        else:
            return -1
    
    def debugAll(self):
        print("name   type  kind  idx")
        for k in self.table:
            print(k)
