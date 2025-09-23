test: example/* class.h endclass.h class_explicit_constructor.h
	cc -o test example/use.c example/light.c example/rotary.c example/box.c
