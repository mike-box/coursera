#ifndef VM_TRANSLATOR
#define VM_TRANSLATOR

/*macro define*/
#define ADDR_SP 0
#define ADDR_LCL 1
#define ADDR_ARG 2
#define ADDR_THIS 3
#define ADDR_THAT 4

typedef enum DEBUG_LEVEL{
    LEVEL_INFO = 1,
    LEVEL_WARNING = 2,
    LEVEL_ERROR = 3,
    LEVEL_DEGBUG = 4
}DEBUG_LEVEL;

typedef enum COMMAND_TYPE{
    C_ARITHMETIC = 0,
    C_PUSH = 1, 
    C_POP = 2,
    C_LABEL = 3,
    C_GOTO = 4, 
    C_IF = 5,
    C_FUNCTION = 6,
    C_RETURN = 7,
    C_CALL = 8
}COMMAND_TYPE;

typedef enum COMMAND_ARITHMETIC_TYPE{
    C_ARITHMETIC_ADD = 0,
    C_ARITHMETIC_SUB = 1,
    C_ARITHMETIC_NEG = 2,
    C_ARITHMETIC_EQ = 3,
    C_ARITHMETIC_GT = 4,
    C_ARITHMETIC_LT = 5,
    C_ARITHMETIC_AND = 6,
    C_ARITHMETIC_OR = 7,
    C_ARITHMETIC_NOT = 8
}COMMAND_ARITHMETIC_TYPE;

typedef enum SEG_TYPE{
    SEG_ARGUMENT = 0,
    SEG_LOCAL = 1,
    SEG_STATIC = 2,
    SEG_CONSTANT = 3,
    SEG_THIS = 4,
    SEG_THAT = 5,
    SEG_POINTER = 6,
    SEG_TMP = 7
}SEG_TYPE;

#endif