#ifndef __CLASS_H
#define __CLASS_H

#define VALUE_IFNOT_TEST(...) __VA_ARGS__
#define VALUE_IFNOT_TEST1(...)
#define VALUE_IFNOT(COND, ...) VALUE_IFNOT_TEST ## COND ( __VA_ARGS__ )
#define __VA_ALT__(__x, ...) VALUE_IFNOT(__VA_OPT__(1), __x) __VA_ARGS__
#define PAREN(...) __VA_ARGS__
#define BLOCK(...) {__VA_ARGS__}

// The CLASS macro framework allows to the define a class
// It provides implicit constructors and methods with dynamic dispatch, but no inheritance/polymorphism.

// Each class header file must follow the classtemplate.h template to behave nicely and transparently.

// See the files in the example/ folder for a full example, specially rotary.h, box.h and light.h for the syntax.

// Only non-standard thing, for the auto-generated constructor to not resutt, but almost all compilers have a way to do it
#define WEAK_LINKAGE __attribute__((weak))

// Just for easier debugging, replace with #include <stdlib.h> for portability
void *malloc(long unsigned);
void free(void *);

#ifndef __CLASS_FILE__
#error "The __CLASS_FILE__ macro is not defined. Check the README for help."
#endif

// First pass, make class type
#define CLASS(__class)\
typedef struct __class {
// The type must fully precede the name.
// __init is an init expression, use PAREN() if it contains commas
// What goes after __init is the cleanup statement, if needed. Use PAREN() if it contains a comma, or BLOCK() if it's a whole block of code.
// Hence, MEMBER can't be used for arrays and function pointers, use MemberC for that
#define MEMBER(__type, __name, __init, ...) \
    __type __name;

// MEMBERC(OMPOUND) is like MEMBER, but you have a second type parameter to be able to express arrays, function pointers and such.
#define MEMBERC(__type, __name, __type2, __init, ...) \
    __type __name __type2;

// Declares a method, it will create a function pointer member called [__name], which will be assigned the value of the default implementation in the constructor.
// The default implementation will be declared and named method_className_methodName, and must be implemented in the .c file.
// __in is the input type, and what goes after __name is the output list (with implicit self).
// If it just takes self, don't put any arguments after __name.
// Else, put the type list: METHOD(MyClass, int, someMethodThatTakesTwoFloatsAndReturnsAnInt, float, float)
#define METHOD(__class, __in, __name, ...) \
    __in (*__name)(struct __class * __VA_OPT__(,) __VA_ARGS__);
// Same as METHOD, but without the implicit self.
// You can put either parameter list after __name, or leave it empty
//     (which is the same as putting a void at the end).
#define METHOD_STATIC(__class, __in, __name, ...) \
    __in (*__name)(__VA_ALT__(void, __VA_ARGS__));
#define ENDCLASS(__class)\
} __class;

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS


// Second pass, declare default method implementations
#define CLASS(...)
#define MEMBER(...)
#define MEMBERC(...)
#define METHOD(__class, __in, __name, ...)\
    __in method_##__class##_##__name(__class *self __VA_OPT__(,) __VA_ARGS__);
#define METHOD_STATIC(__class, __in, __name, ...)\
    __in method_##__class##_##__name(__VA_ALT__(void, __VA_ARGS__));
#define ENDCLASS(...)

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS


// Third pass, declare and define constructor with automatic initialization with provided expressions/code blocks. The constructor is named new_className
#define CLASS(__class)\
WEAK_LINKAGE __class *new_##__class (void) { \
    __class *self = malloc(sizeof(__class));
#define MEMBER(__type, __name, __init, ...) \
    self->__name = (__type) __init;
#define MEMBERC(__type, __name, __type2, __init, ...) \
    __init;
#define METHOD(__class, __in, __name, ...)\
    self->__name = &method_##__class##_##__name;
#define METHOD_STATIC(__class, __in, __name, ...)\
    self->__name = &method_##__class##_##__name;
#define ENDCLASS(__class)\
     return self;\
}

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS



// Fourth pass, declare and define destructor with automatic cleanup with provided code blocks. The destructor is named delete_className
#define CLASS(__class)\
WEAK_LINKAGE void delete_##__class (__class *self) {
#define MEMBER(__type, __name, __init, ...) \
    __VA_ARGS__;
#define MEMBERC(__type, __name, __type2, __init, ...) \
    __VA_ARGS__;
#define METHOD(...)
#define METHOD_STATIC(...)
#define ENDCLASS(__class)\
    free(self);\
    return;\
}

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS



// This is a two-pass extension part of the multi-pass class.h process.
// It generates explicit constructors.
// Add #define __CLASS_EXPLICIT_CONSTRUCTOR
//   right before the include of class.h in the template seen in classtemplate.h
//   to enable generating an explicit constructor that takes one argument for each non-custom-init parameter.
//   you can also force a class to be included with an explicit constructor by defining it right before including
#ifdef __CLASS_EXPLICIT_CONSTRUCTOR
#include "class_explicit_constructor.h"
#undef __CLASS_EXPLICIT_CONSTRUCTOR
#endif

#define CLASS(...)
#define MEMBER(...)
#define MEMBERC(...)
#define METHOD(...)
#define METHOD_STATIC(...)
#define ENDCLASS(...)

#undef __CLASS_H

#endif
