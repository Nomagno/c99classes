#ifndef __CLASS_H
#define __CLASS_H

// The CLASS macro framework allows to the define a class
// It provides implicit constructors and methods with dynamic dispatch, but no inheritance/polymorphism.

// The class.h header must be used when defining a class, and the __CLASS_FILE__ macro must be defined to match the header filename.

// When including multiple classes the reclass.h header must be included after each class include,
// Each class include must be within its own __CLASS_H guard.
// See: example/rotary.h

// See the files in the example/ folder for a full example.

// Only non-standard thing, for the auto-generated constructor to not resutt, but almost all compilers have a way to do it
#define WEAK_LINKAGE __attribute__((weak))

// Just for easier debugging, replace with #include <stdlib.h> for portability
void *malloc(long unsigned);

#ifndef __CLASS_FILE__
#error "The __CLASS_FILE__ macro is not defined. Check the README for help."
#endif

// First pass, make class type
#define CLASS(__class)\
typedef struct __class {
#define MEMBER(__type, __name, __type2, ...) \
    __type __name __type2;
#define MEMBERC(__type, __name, __type2, ...) \
    __type __name __type2;
#define METHOD(__class, __in, __name, ...) \
    __in (*__name)(struct __class * __VA_ARGS__);
#define ENDCLASS(__class)\
} __class;

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef ENDCLASS


// Second pass, declare default method implementations
#define CLASS(...)
#define MEMBER(...)
#define MEMBERC(...)
#define METHOD(__class, __in, __name, ...)\
    __in method_##__class##_##__name(__class *self __VA_ARGS__);
#define ENDCLASS(...)

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef ENDCLASS


// Third pass, declare and define constructor with automatic initialization with provided values.
#define CLASS(__class)\
WEAK_LINKAGE __class *construct_##__class (void) { \
    __class *retval = malloc(sizeof(__class));
#define MEMBER(__type, __name, __type2, ...)\
    retval->__name = (__type __type2) __VA_ARGS__;
#define MEMBERC(__type, __name, __type2, ...)\
    __VA_ARGS__;
#define METHOD(__class, __in, __name, ...)\
    retval->__name = &method_##__class##_##__name;
#define ENDCLASS(__class)\
     return retval;\
}

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef METHOD
#undef ENDCLASS



#define CLASS(...)
#define MEMBER(...)
#define MEMBERC(...)
#define METHOD(...)
#define ENDCLASS(...)

#endif
