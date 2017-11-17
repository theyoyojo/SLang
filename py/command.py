import sys
from inspect import signature

class CommandData:
    
    def __init__(self,prompt,options,manual):
        self.options = options 
        self.prompt = prompt
        self.help = manual
        self.vars = []

    def execute(self,option,*params):
        sys.stdout.write(">>")
        self.options[option](*params)

    def var(self, option):
        if option == "new":
            None

    def output(self,*args):
        print(*args)


    def getParams(self,option):
       return signature(self.options[option]).parameters

    def createPrompt(self):
        commands = ""
        userWantsToExit = False
        while (not userWantsToExit):
            sys.stdout.write(self.prompt)
            raw_in = input()
            commands = separateCommands(raw_in)

            if commands == []:
               None 

            #mathmatical parsing
            elif canMath(commands[0]):
                parseMath(commands)

            elif (commands[0] in self.options):
                option = commands[0]

                                #regular ol' parsing
                if(self.isValidCommand(commands)):
                    if(len(commands) > 1):

                        if functionHasTypes(self.getParams(option)):
                            types = getTypes(self.getParams(option))
                            commands = fixTypes(commands, types)

                        params = tuple(commands[1:len(commands)])
                        self.execute(commands[0],*params)

                    else:
                        self.execute(option)
                else:
                    print("[GENERAL] Invalid use of command.")

            
            elif(commands[0] == "help"):
                print(data.help)
            elif(commands[0] == "exit" or commands[0] == "quit"):
                userWantsToExit = True
                print("Goodbye.")
            else:
                print("Unrecognized command.")

    def isValidCommand(self,commands):
        params = self.getParams(commands[0])

        if(len(params) == len(commands)-1):
            if (functionHasTypes(params)):
                types = getTypes(params)
                if checkTypes(types, commands[1:len(commands)]) == False:
                    return False
                else:
                    return True
            else:
                return True

        else:
            print("[USAGE] Invalid number of parameters.")
            return False

def couldBe(string,typ):
    try:
        typ(string)
    except ValueError:
        return False
    
    return True

def nextIndexExists(lst, i):
    try:
        lst[i+1]
    except IndexError:
        return False
    return True

class Expression:

    OP_BINARY = 0
    OP_UNARY_LEFT = -1
    OP_UNARY_RIGHT = 1

    operations = {  "^":OP_BINARY,
                    "!":OP_UNARY_LEFT,
                    "*":OP_BINARY,
                    "/":OP_BINARY,
                    "+":OP_BINARY,
                    "-":OP_BINARY
                 }

    opOrder = [ ["^"],
                ["!"],
                ["*","/"],
                ["+","-"]]

    def __init__(self, items):
       self.items = items 
       self.raw_items = items
       self.errors = []
       self.valid = True
       self.validate()
       self.insertImplications()
    
    def insertImplications(self):
        new = []
        for ni in range(len(self.items)):
            i = self.items[ni]
            if i == "(" and self.items[ni-1] not in Expression.operations and not self.items[ni-1] == ")": 
                if not self.items[ni-1] == "(":
                    new.append("*")
                new.append(i)
            elif i == ")":
                if self.items[ni-1] == "(":
                    new.append(1)
                new.append(i) 
                if nextIndexExists(self.items,ni) and self.items[ni+1] not in Expression.operations:
                    if not self.items[ni+1] == ")":
                        new.append("*") 
            else:
                new.append(i)
        self.items = new

    def validateOperand(self, op, direction):
        if type(op) ==  int or type(op) == float:
            return True
        elif (direction == 1 and op == "(") or (direction == -1 and op == ")"):
            return True
        elif op.isalpha(): #TODO check validity of variable input, also add assignment,storage,retrieval mechanism
            return False
        else:
            return False

    def canBeOperand(self, op):
        if type(op) ==  int or type(op) == float:
            return True
        elif op == "(" or op == ")":
            return True
        elif op.isalpha(): #TODO check validity of variable input, also add assignment,storage,retrieval mechanism
            return False
        else:
            return False


    def validateParen(self):
        parenLevel = 0
        for i in self.items:
            if i == "(":
                parenLevel += 1
            elif i == ")":
                if parenLevel == 0:
                    self.errors.append("[MATH] Found ')' without partner")
                    self.valid = False
                parenLevel -= 1
        if parenLevel > 0:
            self.errors.append("[MATH] Found '(' without partner")
            self.valid = False 
    
    def validateLeftOperand(self, i, ni):
        if not self.validateOperand(self.items[ni-1],-1):
            self.valid = False 
            self.errors.append("[MATH] invalid left operand '" + str(self.items[ni-1]) + "' for operator " + i + ".") 

    def validateRightOperand(self, i,ni):
        if nextIndexExists(self.items, ni):
            if not self.validateOperand(self.items[ni+1],1):
                self.errors.append("[MATH] invalid right operand '" + str(self.items[ni+1]) + "' for operator " + i + ".")
                self.valid = False
        else:
            self.errors.append("[MATH] no right operand exists for operator " + i + ".")
            self.valid = False

    def validateOperator(self,ni):
        i = self.items[ni]
        if i in self.operations:
            if self.operations[i] == Expression.OP_BINARY:
                self.validateLeftOperand(i,ni)
                self.validateRightOperand(i,ni)
            elif self.operations[i] == Expression.OP_UNARY_LEFT:
                self.validateLeftOperand(i,ni)
            elif self.operations[i] == Expression.OP_UNARY_RIGHT:
                self.validateRightOperand(i,ni)
            else:
                print("[MATH] CRITICAL ERROR IN VALIDATE OPERATOR: operator type does not exist, please debug")
        


    def validateOperations(self):
        for ni in range(len(self.items)):
            self.validateOperator(ni)

    def validateValues(self):
        for ni in range(len(self.items)):
            i = self.items[ni]

            #print(i not in Expression.operations ,self.canBeOperand(i))
            if i not in Expression.operations and not self.canBeOperand(i):
                self.valid = False
                self.errors.append("[MATH] Invalid item '" + str(i) + "' is neither valid operator nor valid operand.")

    def validate(self):
        self.validateParen()
        self.validateOperations()
        self.validateValues()
    
    def factorial(self, value):
        if value == 1:
            return 1
        else:
            return value * self.factorial(value-1)


    def replaceWithValue(self, inList , iStart, iEnd, inValue):
        del inList[iStart:iEnd+1]
        inList.insert(iStart,inValue)
        return inList
        
    def evaluate(self,exp):
        didOp = False
        counter = 0
        while(len(exp) > 1):
            for op in Expression.opOrder:
                for ni in range(len(exp)):
                    new = []
                    for item in exp:
                        new.append(item)
                    i = exp[ni]
                    #print(op)
                    if i in op:
                        if i == "^":
                            self.replaceWithValue(new,ni-1,ni+1,exp[ni-1]**exp[ni+1])
                        elif i  == "!":
                            self.replaceWithValue(new,ni-1,ni+1,self.factorial(int(exp[ni-1])))
                        elif i == "*":
                            self.replaceWithValue(new,ni-1,ni+1,exp[ni-1]*exp[ni+1])
                        elif i == "/":
                            self.replaceWithValue(new,ni-1,ni+1,exp[ni-1]/exp[ni+1])
                        elif i == "+":
                            self.replaceWithValue(new,ni-1,ni+1,exp[ni-1]+exp[ni+1])
                        elif i == "-":
                            self.replaceWithValue(new,ni-1,ni+1,exp[ni-1]-exp[ni+1])
        
                        #systemic operations for continuous integration to the solution cloud                
                        exp = []
                        for i in new:
                           exp.append(i) 
                        didOp = True
                        break
                if didOp:
                    didOp = False
                    #print("eval count#",counter,exp)
                    counter += 1
                    break
        #print(exp)
        return exp


    def hasParen(self,exp):
        for i in exp:
            if i == "(" or i == ")":
                return True 

        return False

    def evaluateParen(self,exp):
        if len(exp) == 1:
            return exp

        while self.hasParen(exp):
            paren = self.getFirstParen(exp)
            """
            print(paren[0],paren[1])
            print(paren[0]+1,paren[1]-1,exp[paren[0]+1:paren[1]])
            print(exp)
            """
            self.replaceWithValue(exp,paren[0],paren[1],self.evaluateParen(exp[paren[0]+1:paren[1]])[0])
            #print("AFTER CALL",exp)
            print(self.evaluate(exp))
        return self.evaluate(exp)

    def simplify(self):
        if not self.valid:
            self.errors.append("[MATH] Cannot simplify invalid expression.")
            return None
        else:
            """
            while self.hasParen(self.items):
                paren = self.getFirstParen(self.items)
                self.items = self.evaluateParen(self.items[paren[0]+1:paren[1]])
            self.items = self.evaluate(self.items)
            """
            self.items = self.evaluateParen(self.items)
            return True
            
    def getFirstParen(self, items):
        part = []
        parenLevel = 0
        iStart = 0
        iEnd = 0
        for ni in range(len(items)):
            i = items[ni]
            if i == "(":
                parenLevel +=1
                if parenLevel > 1:
                    part.append(i)
                else:
                    iStart = ni
            elif i == ")":
                parenLevel -= 1
                if parenLevel > 0:
                    part.append(i)
                else:
                    iEnd = ni
            elif parenLevel > 0:
                part.append(i)

        return iStart,iEnd
                

def parseMath(commands):
    operations = []
    for i in range(len(commands)):
        sym = commands[i]
        if couldBe(sym,int):
            operations.append(int(sym))
        elif couldBe(sym,float):
            operations.append(float(sym))
        #elif sym.isalpha(): #TODO parse variables
        #    operations.append(1) 
        else:
            operations.append(sym)
        
    exp = Expression(operations)
    print(exp.items)
    result = exp.simplify()

    if result == None:
        for e in exp.errors:
            print(e)
        print("[MATH] Invalid syntax.")
    else:
        print(">>",exp.items[0])
    

def canMath(option):
    try:
        int(option)
    except ValueError:
        try:
            float(option)
        except ValueError:
            return False

    return True

def separateCommands(commands):
    listCommands = []
    currentCommand = ""
    inQuotes= False
    inSymbolic = False 
    inNum = False
    inDecimal = False
    inAlpha = False
    inSpace = False
    for c in commands:
        if inQuotes:
            if c == "\"":
                inQuotes= False
                listCommands.append(currentCommand)
                currentCommand = ""
            else:
                currentCommand += c
        elif c.isalpha():
            if inSymbolic or inNum:
                listCommands.append(currentCommand)
                currentCommand = ""
                inNum = False
                inSymbolic = False
            inAlpha = True
            inCommand = True
            inSpace = False
            currentCommand += c
        elif c.isdigit():
            inNum = True
            if inDecimal == True:
                inDecimal = False 
            elif inSymbolic or inAlpha:
                listCommands.append(currentCommand)
                currentCommand = ""
                inAlpha = False
                inSymbolic = False
            inSpace = False
            inCommand = True
            currentCommand += c
        elif c.isspace():
            inAlpha = False
            inSymbolic = False
            inNum= False
            if inSpace == False:
                listCommands.append(currentCommand)
            currentCommand = ""
            inSpace = True
        elif c == "\"":
            inQuotes= True
        else:
            if inNum and c == "." and not inDecimal:
               inDecimal = True
            else:
                if len(currentCommand) > 0:
                    listCommands.append(currentCommand)
                    currentCommand = ""
                inSymbolic = True
            inSpace = False
            currentCommand += c

    if len(currentCommand) > 0:
        listCommands.append(currentCommand)
            
    print(listCommands)
    return listCommands


def functionHasTypes(params):
    if len(str(params).split(":")) == 1:
        return False
    return True

def checkTypes(types, commands):
    i = 0;
    hasError = False
    for t in types:
        try:
            if t == "int":
                int(commands[i])
            elif t == "float":
                float(commands[i])
        except ValueError:
            print("[TYPE] Incorrect use of types.")
            print("[TYPE] param " + str(i+1) + " should be of type " + t + ".")
            hasError = True
        i += 1
    if hasError:
        return False
    else:
        return True

def getTypes(params):
    types = []
    
    for param in params:
        types.append(str(params[param]).split(":")[-1:][0])
    return types

def fixTypes(commands, types):

    fixed = []
    fixed.append(commands[0])

    print(commands, types)
    for i in range(1,len(commands)):
        if types[i-1] == "int":
            print(i)
            fixed.append(int(commands[i]))
            print(fixed)
        elif types[i-1] == "float":
            fixed.append(float(commands[i]))
        else:
            fixed.append(str(commands[i]))
        
    return fixed 
            

def show(string):
    data.output(string)

def length(string):
    data.output(len(string))

def add(a:int ,b:int):
    data.output(str(a) + " + " + str(b) + " = " + str(a+b))

def execute(arg):
    print("executing " + arg + ".") 

def nameage(name:str, age:int):
    print("your name is " + name + " and you will be " + str(age+20) + " in 20 years if you aren't dead.") 


options = {"show":show,"length":length, "add":add, "nameage":nameage, "execute":execute}

prompt = "Enter a command >>"

manual = "show <str>, length <str>, add <int> <int>, name_age <str> <int>, execute <str> "
        
data = CommandData(prompt,options,manual)

#separateCommands("execute(3a+4b) \" and now + for something \"")

data.createPrompt()
