#ifndef __CLASS_H
#define __CLASS_H

#define EMPTY

// VALUE_IFNOT_TEST(X) only pastes T of no vara
#define VALUE_IFNOT_TEST(...) __VA_ARGS__
#define VALUE_IFNOT_TEST1(...)
#define VALUE_IFNOT(COND, ...) VALUE_IFNOT_TEST ## COND ( __VA_ARGS__ )
#define __VA_ALT__(__x, ...) VALUE_IFNOT(__VA_OPT__(1), __x) __VA_ARGS__
#define PAREN(...) __VA_ARGS__
#define BLOCK(...) {__VA_ARGS__}

/*
IF_VALUE(_x_)(_y_)(_z_)
If _x_ is not empty, produces _y_, else produces _z_. Do not use or redefine beginning with _IF_VALUE_.
*/

#define _IF_VALUE__SECOND(_a, _b, ...)		_b
#define _IF_VALUE__SECOND_2(_a, _b, ...)	_IF_VALUE__SECOND(_a, _b, __VA_ARGS__)
#define _IF_VALUE__CHECK__IF_VALUE__IS_EMPTY()	~, _IF_VALUE__IS_EMPTY
#define _IF_VALUE__CHECK(_first, ...)		_IF_VALUE__SECOND_2(_IF_VALUE__CHECK_ ## _first (), _IF_VALUE__NOT_EMPTY, ~)
#define _IF_VALUE__CHECK_2(_first, ...)		_IF_VALUE__CHECK(_first, __VA_ARGS__)
#define _IF_VALUE__IS_EMPTY(...)		_IF_VALUE__IS_EMPTY_1
#define _IF_VALUE__IS_EMPTY_1(...)		__VA_ARGS__
#define _IF_VALUE__NOT_EMPTY(...)		__VA_ARGS__ _IF_VALUE__NOT_EMPTY_1
#define _IF_VALUE__NOT_EMPTY_1(...)		/* nothing */
#define IF_VALUE(_maybe_empty)	_IF_VALUE__CHECK_2(_IF_VALUE__CHECK _maybe_empty (_IF_VALUE__IS_EMPTY, ~), ~)

// removes one layer of parentheses from X, only if it exists
#define DEPAREN(X) ESC(ISH X)
#define ISH(...) ISH __VA_ARGS__
#define ESC(...) ESC_(__VA_ARGS__)
#define ESC_(...) VAN ## __VA_ARGS__
#define VANISH


// The inheritance branch has improved ergonomics and inheritance, at the cost of:
// - It requires __VA_OPT__, which is only available in C23 rather than C99
// - rather than the master branch approach,
//      CLASS(MyClass) 
//          ...
//      ENDCLASS(MyClass)
//  the following variation must ALWAYS be used to make inheritance play nice:
//      #ifndef __CLASS_INHERIT
//      CLASS(MyClass) 
//      #endif
//          ...
//      #ifndef __CLASS_INHERIT
//      ENDCLASS(MyClass) 
//      #endif
//   I'm open to any suggestions to eliminate the need for this.

// The CLASS macro framework allows to the define a class
// It provides implicit constructors and methods with dynamic dispatch, but no inheritance/polymorphism.

// Each class header file must follow the classtemplate.h template to behave nicely and transparently.

// See the files in the example/ folder for a full example, specially rotary.h, box.h and light.h for the syntax.

// Just for easier debugging, replace with #include <stdlib.h> for portability
void *malloc(long unsigned);
void free(void *);

#ifndef __CLASS_FILE__
#error "The __CLASS_FILE__ macro is not defined. Check the README for help."
#endif

// First pass, make class type
#define STARTUP(...)
#define CLEANUP(...)
#define CLASS(__class)\
typedef struct __class {
// The type must fully precede the name.
// __init is an init expression, use PAREN() if it contains commas
// What goes after __init is the cleanup statement, if needed. Use PAREN() if it contains a comma, or BLOCK() if it's a whole block of code.
// __type 2 is a second type parameter to be able to express arrays, function pointers and such.
#define MEMBER(__type, __name, __type2, __init, ... /*cleanup*/) \
    __type __name __type2;

// Declares a method, it will create a function pointer member called [__name], which will be assigned the value of the default implementation in the constructor.
// The default implementation will be declared and named method_className_methodName, and must be implemented in the .c file.
// __in is the input type, and what goes after __name is the output list (with implicit self).
// If it just takes self, don't put any arguments after __name.
// Else, put the type list: METHOD(MyClass, int, someMethodThatTakesTwoFloatsAndReturnsAnInt, float, float)
#define METHOD(__class, __in, __name, __args, ... /*implementation*/) \
    __in (*__name)(struct __class * IF_VALUE(__args)(,)() DEPAREN(__args));
// Same as METHOD, but without the implicit self.
// You can put either parameter list after __name, or leave it empty
//     (which is the same as putting a void at the end).
#define METHOD_STATIC(__class, __in, __name, __args, ... /*implementation*/) \
    __in (*__name)(__VA_ALT__(void, DEPAREN(__args)));
#define ENDCLASS(__class)\
} __class;

#include __CLASS_FILE__

#undef CLASS
#undef STARTUP
#undef CLEANUP
#undef MEMBER
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS


// Second pass, declare default method implementations
#define STARTUP(...)
#define CLEANUP(...)
#define CLASS(...)
#define MEMBER(...)
#define METHOD(__class, __in, __name, __args, ... /*implementation*/)\
    static inline  __in method_##__class##_##__name(__class *self IF_VALUE(__args)(,)() DEPAREN(__args)) IF_VALUE(__CLASS_INHERIT)(__VA_ARGS__)();
#define METHOD_STATIC(__class, __in, __name, __args, ... /*implementation*/)\
    static inline __in method_##__class##_##__name(__VA_ALT__(void, DEPAREN(__args))) IF_VALUE(__CLASS_INHERIT)(__VA_ARGS__)();
#define ENDCLASS(...)

#include __CLASS_FILE__

#undef CLASS
#undef STARTUP
#undef CLEANUP
#undef MEMBER
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS

// Third pass, declare and define constructor with automatic initialization with provided expressions/code blocks. The constructor is named new_className
#define STARTUP(...) __VA_ARGS__
#define CLEANUP(...)
#define CLASS(__class)\
static inline __class *new_##__class (void) { \
    __class *self = malloc(sizeof(__class));
#define MEMBER(__type, __name, __type2, __init, ...) \
    self->__name __init;
#define METHOD(__class, __in, __name, __args, ...)\
    self->__name = &method_##__class##_##__name;
#define METHOD_STATIC(__class, __in, __name, __args, ...)\
    self->__name = &method_##__class##_##__name;
#define ENDCLASS(__class)\
     return self;\
}

#include __CLASS_FILE__

#undef CLASS
#undef STARTUP
#undef CLEANUP
#undef MEMBER
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS



// Fourth pass, declare and define destructor with automatic cleanup with provided code blocks. The destructor is named delete_className
#define STARTUP(...)
#define CLEANUP(...) __VA_ARGS__
#define CLASS(__class)\
static inline void delete_##__class (__class *self) {
#define MEMBER(__type, __name, __type2, __init, ...) \
    __VA_ARGS__;
#define METHOD(...)
#define METHOD_STATIC(...)
#define ENDCLASS(__class)\
    free(self);\
    return;\
}

#include __CLASS_FILE__

#undef CLASS
#undef STARTUP
#undef CLEANUP
#undef MEMBER
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS


#define CLASS(...)
#define MEMBER(...)
#define METHOD(...)
#define METHOD_STATIC(...)
#define ENDCLASS(...)

#undef __CLASS_H

#endif
