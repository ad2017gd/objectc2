#pragma once
#include <stdlib.h>
#include "objectc_MP.h"


// Type definition will be used for valid string serialization
typedef char * string_t;

#ifdef UNICODE
typedef wchar_t * wstring_t;
#endif

/*
* Check offset for one struct's member
* Get a null pointer to the struct, access the member, get the pointer to the member and cast to size_t to get the offset
*/
#define ou_offset(type,member) ((size_t)&(((type*)0)->member))


// --------- INTERNAL -------------

// Pass (packed, arguments) to unpack, them
#define oi_unpack_generic(...) __VA_ARGS__

// Calls omp_narg. Really returns number of arguments but it is still useful
#define oi_isempty(...) omp_narg(__VA_ARGS__)

#define oi_doubleunderscore(...) __

// Print option. If option is empty, skip it. Used in oi_unpack_opts as for loop callback
#define oi_echo_opt(N,opt,...) omp_glue2(omp_if_zero(oi_isempty(opt), omp_empty, oi_doubleunderscore), opt)

// Unpack $opts() packed options.
#define oi_unpack_opts(...) { omp_for_2nd(oi_echo_opt,,__VA_ARGS__) }

// VOID TYPE CHECK MACROS
// Prepend oi__ to the type, expand it, remove first argument. If "void" type is supplied, it will expand to 1,1
// And the number of arguments will be 1, otherwise 0

#define oi__void 1,1

#define oi_is_void___(...) omp_narg(__VA_ARGS__)
#define oi_is_void__(...) oi_is_void___(omp_remove_first(__VA_ARGS__))
#define oi_is_void_(...) oi_is_void__(__VA_ARGS__)

// Returns 1 if type is void, 0 if not
#define oi_is_void(type) oi_is_void_(oi__ ## type)

// END VOID TYPE MACROS

// FIELDS

// FIELDS     PROTOTYPE
#define oi_expand_proto_field(opts, datatype, name, ...) datatype name;

#define oi_expand_prototype_fields_(tuple, ...) oi_expand_proto_field tuple
#define oi_expand_prototype_fields(N, tuple, ...) oi_expand_prototype_fields_(tuple)
#define oi_prototype_fields(...) omp_for(oi_expand_prototype_fields,, __VA_ARGS__)

// FIELDS     DESCRIPTOR
#define oi_create_field(class_name, field_options, field_datatype, field_name) { .name = omp_string(field_name), .type = omp_string(field_datatype), .options = (struct ObjC_FieldOptions) oi_unpack_opts field_options, .size = sizeof(field_datatype), .offset = ou_offset(class_name, field_name) },

#define oi_expand_field(datatype, name, options, ...) datatype, name, options

#define oi_expand_field_descriptor__(cl_name, ...) oi_create_field(cl_name, __VA_ARGS__)
#define oi_expand_field_descriptor_(tuple, cl_name) oi_expand_field_descriptor__(cl_name, oi_expand_field tuple)
#define oi_expand_field_descriptor(N, tuple, cl_name, ...) oi_expand_field_descriptor_(tuple, cl_name)
#define oi_field_descriptor(cl_name, ...) omp_for(oi_expand_field_descriptor, cl_name, __VA_ARGS__)

// FUNCTIONS

// FUNCTIONS     PROTOTYPE
#define oi_unpack_arg_(datatype, name) , datatype name
#define oi_unpack_arg(N,packed,...) oi_unpack_arg_ packed

#define oi_unpack_args_(...) omp_remove_first(__VA_ARGS__)
#define oi_unpack_args(...) oi_unpack_args_(omp_for_2nd(oi_unpack_arg,,__VA_ARGS__))

#define oi_unpack_args_comma_2nd(...) omp_if_2nd_zero(omp_narg(__VA_ARGS__), omp_empty, omp_comma)
#define oi_unpack_args_comma(...) omp_if_zero(omp_narg(__VA_ARGS__), omp_empty, omp_comma)

#define oi_expand_proto_function(opts, datatype, name, discard, packed_args, ...) datatype (* name) (oi_unpack_args packed_args);

#define oi_expand_prototype_functions_(tuple, ...) oi_expand_proto_function tuple
#define oi_expand_prototype_functions(N, tuple, ...) oi_expand_prototype_functions_(tuple)
#define oi_prototype_functions(...) omp_for(oi_expand_prototype_functions,, __VA_ARGS__)

// FUNCTIONS    ARGS

#define oi_expand_args(...) __VA_ARGS__

#define oi_sum_expand(tp,nm) +sizeof(tp)
#define oi_sum_offset(N, tuple, ...) oi_sum_expand tuple

#define oi_create_function_args____(cl_name, tp, nm, ...) $pack({.name = omp_string(nm), .type = omp_string(tp), .size = sizeof(tp), .offset = 0 omp_for_3rd(oi_sum_offset,0, __VA_ARGS__)})
#define oi_create_function_args___(cl_name,  ...) oi_create_function_args____(cl_name, __VA_ARGS__) omp_comma()
#define oi_create_function_args__(N, tuple, cl_name, ...) oi_create_function_args___(cl_name, oi_expand_args tuple, __VA_ARGS__)

#define oi_create_function_args_p(class_name, field_name, args) omp_for_2nd(oi_create_function_args__, class_name, args)
#define oi_create_function_args_(class_name, field_name, ...) oi_create_function_args_p(class_name,field_name, omp_reverse(__VA_ARGS__))
#define oi_create_function_args(class_name, field_name, ...) oi_create_function_args_(class_name,field_name, __VA_ARGS__)

#define oi_for_unpack__(V) oi_expand_args V omp_comma()
#define oi_for_unpack_(c, V, ...) omp_if_zero(c,omp_empty,oi_for_unpack__, V)
#define oi_for_unpack(N, V, ...) oi_for_unpack_(omp_narg(V),V)
#define oi_args_create_function(class_name, field_options, field_datatype, field_name, args, body, ...) struct ObjC_FuncArgument class_name ## _Func_ ## field_name ## _Arguments[] = {omp_for_3rd(oi_for_unpack, 0, omp_apply(omp_reverse,oi_create_function_args(class_name, field_name, oi_expand_args args)))};
#define oi_args_expand_function_descriptor__(cl_name, ...) oi_args_create_function(cl_name, __VA_ARGS__)
#define oi_args_expand_function_descriptor_(tuple, cl_name) oi_args_expand_function_descriptor__(cl_name, oi_expand_function tuple)
#define oi_args_expand_function_descriptor(N, tuple, cl_name, ...) oi_args_expand_function_descriptor_(tuple, cl_name)
#define oi_args_function_descriptor(cl_name, ...) omp_for(oi_args_expand_function_descriptor, cl_name, __VA_ARGS__)

// FUNCTIONS     DESCRIPTOR

#define oi_return_size(type) omp_if_zero(oi_is_void(type), omp_sizeof, omp_zero, type)

#define oi_expand_function(datatype, name, options, ...) datatype, name, options, __VA_ARGS__

#define oi_create_function(class_name, field_options, field_datatype, field_name, args, body, ...) { .name = omp_string(field_name), .return_type = omp_string(field_datatype), .options = (struct ObjC_FuncOptions) oi_unpack_opts field_options, .return_size = oi_return_size(field_datatype), .offset = ou_offset(class_name, field_name), .argument_count = omp_narg args, .arguments = (struct ObjC_FuncArgument *)& class_name ## _Func_ ## field_name ## _Arguments },

#define oi_expand_function_descriptor__(cl_name, ...) oi_create_function(cl_name, __VA_ARGS__)
#define oi_expand_function_descriptor_(tuple, cl_name) oi_expand_function_descriptor__(cl_name, oi_expand_function tuple)
#define oi_expand_function_descriptor(N, tuple, cl_name, ...) oi_expand_function_descriptor_(tuple, cl_name)
#define oi_function_descriptor(cl_name, ...) omp_for(oi_expand_function_descriptor, cl_name, __VA_ARGS__)

// FUNCTIONS     BODY

// Check if function options contain STATIC
#define oi_test_static(y,x,...) x ## __TEST

#define oi_if_static___(n, IFTRUE, IFFALSE, ...) omp_if_2nd_zero(n, IFFALSE, IFTRUE, __VA_ARGS__)
#define oi_if_static__(IFTRUE, IFFALSE, ARGS, ...) oi_if_static___(omp_narg(__VA_ARGS__), IFTRUE, IFFALSE, ARGS)
#define oi_if_static_(IFTRUE, IFFALSE, ARGS, ...) oi_if_static__(IFTRUE, IFFALSE, omp_pack_(ARGS), omp_for_2nd(oi_test_static, 0, __VA_ARGS__))
#define oi_if_static(opts, IFTRUE, IFFALSE, ...) oi_if_static_(IFTRUE, IFFALSE, omp_pack_(__VA_ARGS__), omp_pack_ opts)

#define oi_this_argument(class_name, packed_args) class_name * this oi_unpack_args_comma packed_args

#define oi_create_function_body(class_name, opts, return_type, func_name, packed_args, body, ...) \
return_type class_name ## _ ## func_name (oi_if_static(opts, omp_empty, oi_this_argument, class_name, packed_args) oi_unpack_args packed_args) {oi_unpack_generic body}

#define oi_expand_function_bodies__(cl_name, ...) oi_create_function_body(cl_name, __VA_ARGS__)
#define oi_expand_function_bodies_(tuple, cl_name) oi_expand_function_bodies__(cl_name, oi_expand_function tuple)
#define oi_expand_function_bodies(N, tuple, cl_name, ...) oi_expand_function_bodies_(tuple, cl_name)
#define oi_function_bodies(cl_name, ...) omp_for(oi_expand_function_bodies, cl_name, __VA_ARGS__)

// ---------

// ACCESS
#define ACCESS_PUBLIC 0
#define ACCESS_PROTECTED 1
#define ACCESS_PRIVATE 2


// Class and function information structures
// Populated automatically by the class creation macro

struct ObjC_FieldOptions {
    unsigned char serializable;
    unsigned char access;
};
struct ObjC_FuncOptions {
    unsigned char access;
};

struct ObjC_ClassField {
    char* name;
    char* type;
    size_t size;
    size_t offset;
    struct ObjC_FieldOptions options;
};

struct ObjC_FuncArgument {
    char* name;
    char* type;
    size_t size;
    size_t offset;
};

struct ObjC_ClassFunction {
    char* name;
    char* return_type;
    size_t return_size;
    size_t offset;
    struct ObjC_FuncOptions options;
    size_t argument_count;
    struct ObjC_FuncArgument* arguments;
};

struct ObjC_GeneralClassDescriptor {
    char* name;
    struct ObjC_ClassFieldsDescriptor* fields;
    struct ObjC_ClassFunctionsDescriptor* functions;
};
struct ObjC_ClassFieldsDescriptor {
    size_t size;
    struct ObjC_ClassField fields[];
};
struct ObjC_ClassFunctionsDescriptor {
    size_t size;
    struct ObjC_ClassFunction functions[];
};


// -------- START USER MACROS --------


#define TRUE 1
#define FALSE 0

#define __TEST
#define PUBLIC__TEST
#define PRIVATE__TEST
#define PROTECTED__TEST
#define SERIALIZABLE__TEST
#define STATIC__TEST 1

#define __PUBLIC .access = ACCESS_PUBLIC,
#define __PRIVATE .access = ACCESS_PRIVATE,
#define __PROTECTED .access = ACCESS_PROTECTED,
#define __SERIALIZABLE .serializable = TRUE,
#define __STATIC
#define PUBLIC PUBLIC,
#define PRIVATE PRIVATE,
#define PROTECTED PROTECTED,
#define SERIALIZABLE SERIALIZABLE,
#define STATIC STATIC,

// Class creation macro
// Creates and populates 
//  - a class struct (typedef'd)
//  - a class field descriptor (ObjC_ClassFieldsDescriptor) --> contains information about all the fields in the class
//  - a class function descriptor (ObjC_ClassFunctionsDescriptor) --> contains information about all the functions in the class
//  - a class descriptor (ObjC_GeneralClassDescriptor) --> contains the name and pointers to the two other descriptor structs above
// The class descriptors use the normal ObjectC naming convention, so ClassName_Fields, ClassName_Functions, ClassName_Class
// The class definition contains a pointer to the class descriptor, which is the "class" member


#define oi_class_common(cl_name, _FIELDS, _FUNCS) \
oi_args_function_descriptor(cl_name, _FUNCS) \
struct ObjC_ClassFieldsDescriptor cl_name ## _Fields = { \
    .size = omp_narg(_FIELDS), \
    .fields = {oi_field_descriptor(cl_name, _FIELDS)} \
}; \
struct ObjC_ClassFunctionsDescriptor cl_name ## _Functions = { \
    .size = omp_narg(_FUNCS), \
    .functions = {oi_function_descriptor(cl_name, _FUNCS)} \
}; \
struct ObjC_GeneralClassDescriptor cl_name ## _Class = { \
    .name = omp_string(cl_name), \
    .fields = & cl_name ## _Fields, \
    .functions = & cl_name ## _Functions \
}; \
oi_function_bodies(cl_name, _FUNCS)

#define $class(cl_name, _FIELDS, _FUNCS) \
typedef struct { \
    struct ObjC_GeneralClassDescriptor* class; \
    struct ObjC_Object* object; \
    oi_prototype_fields(_FIELDS) \
    oi_prototype_functions(_FUNCS) \
} cl_name; \
oi_class_common(cl_name, omp_pack__(_FIELDS), omp_pack__(_FUNCS))


#define $pack(...) omp_fold_((__VA_ARGS__))

#define $fields(...) omp_pack_(__VA_ARGS__)
#define $functions(...) omp_pack_(__VA_ARGS__)

#define oi_separate(N,V,sep) V sep
#define $opt(...) $pack(PROTECTED __VA_ARGS__)

#define $arg(...) $pack(__VA_ARGS__)
#define $body(...) $pack(__VA_ARGS__)