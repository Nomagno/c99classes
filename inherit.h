#if defined(__CLASS_INHERIT)
    #include __PARENT
#else
    #define __CLASS_INHERIT
    #include __PARENT
    #undef __CLASS_INHERIT
#endif
#undef __PARENT
