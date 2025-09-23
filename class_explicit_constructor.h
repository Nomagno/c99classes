// This is a two-pass extension part of the multi-pass class.h process that ONLY works
// for classes that don't depend on any other classes AND are not included by any other classes.
// It generates explicit constructors.
// Add #define __CLASS_INDEPENDENT
// right before the include of class.h in the template seen in classtemplate.h to enable generating an explicit constructor that takes one argument for each non-custom-init parameter.

// Fifth pass, start constructor with parametrized initialization with provided expressions for non-custom members. The constructor is named new_className_explicit
// Start function and parameter list
#define CLASS(__class)\
WEAK_LINKAGE __class *new_##__class##_explicit (
#define MEMBER(__type, __name, ...) __type __name,
#define MEMBERC(...)
#define MEMBER_CLEANUP(__type, __name, __init, ...) __type __name,
#define MEMBERC_CLEANUP(...)
#define METHOD(...)
#define METHOD_STATIC(...)
// Close parameter list, making it variadic is a HUGE hack but you gotta do what you gotta do
#define ENDCLASS(__class) ...)

#include __CLASS_FILE__

#undef CLASS
#undef MEMBER
#undef MEMBERC
#undef MEMBER_CLEANUP
#undef MEMBERC_CLEANUP
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS



// Sixth pass, finish constructor with parametrized initialization with provided expressions for non-custom init members. The constructor is named new_className_explicit
#define CLASS(__class) { \
    __class *self = malloc(sizeof(__class));
#define MEMBER(__type, __name, ...)\
    self->__name = __name;
#define MEMBERC(__type, __name, __type2, ...)\
    __VA_ARGS__;
#define MEMBER_CLEANUP(__type, __name, __init, ...)\
    self->__name = __init;
#define MEMBERC_CLEANUP(__type, __name, __type2, __init, ...)\
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
#undef MEMBER_CLEANUP
#undef MEMBERC_CLEANUP
#undef METHOD
#undef METHOD_STATIC
#undef ENDCLASS
