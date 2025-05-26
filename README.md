# objectc2
work in progress c object library heavily based on macro tricks. currently has no real functionality

# short description
currently can expand simple definition into pretty complete structs containing info about the class such as fields, field options, functions and its arguments etc
![image](https://github.com/user-attachments/assets/9e8d2bf2-4ae0-48be-82da-7877c9c19b1a)

<details>
<summary>See comparison</summary>


<table width=100%>
<tr>
<th>Original</th>
<th>Expanded</th>
</tr>
<tr>
<td valign=top>
  
```c
#include "objectc.h"

$class(Shape,
    $fields(
        ($opt(PUBLIC SERIALIZABLE), double, X),
        ($opt(PUBLIC SERIALIZABLE), double, Y),
        ($opt(PUBLIC SERIALIZABLE), double, Width),
        ($opt(PUBLIC SERIALIZABLE), double, Height),
        ($opt(PUBLIC SERIALIZABLE), double, PublicField),
        ($opt(PROTECTED SERIALIZABLE), double, ProtectedField),
        ($opt(PRIVATE SERIALIZABLE), double, PrivateField)
     ),
    $functions()
);

$class(Rectangle $extends Shape,
    $fields(
        ($opt(PUBLIC SERIALIZABLE), double, X2)),
    $functions(
        ($opt(PUBLIC), double, area, $arg((double, scale)), $body({
             printf("    Called Rectangle.area with scale=%f\n", scale);
             double *procf = $ptr(this, double *, ProtectedField);
             printf("    Trying to get protected field of Shape in Rectangle context. Expect %p==%p\n", procf, &this->super.ProtectedField);
             double *privf = $ptr(this, double *, PrivateField);
             printf("    Trying to get private field of Shape in Rectangle context. Expect %p==0\n", privf);
             return this->super.Width * this->super.Height + 1;
        })),

        ($opt(PUBLIC), void, scale, $arg((double, factor), (double, factor2)), $body({
             this->super.Width *= factor;
             this->super.Height *= factor;
        }))
    ),
    $constructor(
        this->super.Width = 0;
        this->super.Height = 0;
        this->super.X = 0;
        this->super.Y = 0;
     )
);

$class(CoolRectangle $extends Rectangle,
    $fields(
        ($opt(), char*, coolrectname)
    ),
    $functions(
        
    )
)
```

</td>
<td>

```c
#include "objectc.h"

typedef struct Shape {
    struct ObjC_GeneralClassDescriptor * class;
    struct ObjC_Object * object;
    double X;
    double Y;
    double Width;
    double Height;
    double PublicField;
    double ProtectedField;
    double PrivateField;
}
Shape;
struct ObjC_ClassFieldsDescriptor Shape_Fields = {
    .size = 7,
    .fields = {
        {
            .name = "X", .type = "double", .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 0, .serializable = 1,
            }, .size = sizeof(double), .offset = ((size_t) & (((Shape * ) 0) -> X))
        },
        {
            .name = "Y",
            .type = "double",
            .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 0, .serializable = 1,
            },
            .size = sizeof(double),
            .offset = ((size_t) & (((Shape * ) 0) -> Y))
        },
        {
            .name = "Width",
            .type = "double",
            .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 0, .serializable = 1,
            },
            .size = sizeof(double),
            .offset = ((size_t) & (((Shape * ) 0) -> Width))
        },
        {
            .name = "Height",
            .type = "double",
            .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 0, .serializable = 1,
            },
            .size = sizeof(double),
            .offset = ((size_t) & (((Shape * ) 0) -> Height))
        },
        {
            .name = "PublicField",
            .type = "double",
            .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 0, .serializable = 1,
            },
            .size = sizeof(double),
            .offset = ((size_t) & (((Shape * ) 0) -> PublicField))
        },
        {
            .name = "ProtectedField",
            .type = "double",
            .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 1, .serializable = 1,
            },
            .size = sizeof(double),
            .offset = ((size_t) & (((Shape * ) 0) -> ProtectedField))
        },
        {
            .name = "PrivateField",
            .type = "double",
            .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 2, .serializable = 1,
            },
            .size = sizeof(double),
            .offset = ((size_t) & (((Shape * ) 0) -> PrivateField))
        },
    }
};
struct ObjC_ClassFunctionsDescriptor Shape_Functions = {
    .size = 0,
    .functions = {}
};
struct ObjC_GeneralClassDescriptor Shape_Class = {
    .name = "Shape",
    .total_size = sizeof(Shape),
    .super = 0,
    .fields = & Shape_Fields,
    .functions = & Shape_Functions
};
Shape * Shape_new() {
    struct ObjC_State __objc__state = {
        .class = & Shape_Class
    };
    Shape * this = (Shape * ) malloc(sizeof(Shape));
    this -> class = & Shape_Class;
    ((ObjC_BaseObject * ) this) -> object = (struct ObjC_Object * ) malloc(sizeof(struct ObjC_Object));
    ((ObjC_BaseObject * ) this) -> object -> total_size = sizeof(Shape);
    return this;
};

typedef struct Rectangle {
    Shape super;
    struct ObjC_GeneralClassDescriptor * class;
    double X2;
    double( * area)(struct Rectangle * this, double scale);
    void( * scale)(struct Rectangle * this, double factor, double factor2);
}
Rectangle;
struct ObjC_FuncArgument Rectangle_Func_area_Arguments[] = {
    {
        .name = "this", .type = "struct Rectangle *", .size = sizeof(struct Rectangle * ), .offset = 0
    },
    {
        .name = "scale",
        .type = "double",
        .size = sizeof(double),
        .offset = 0 + sizeof(struct Rectangle * )
    },
};
struct ObjC_FuncArgument Rectangle_Func_scale_Arguments[] = {
    {
        .name = "this", .type = "struct Rectangle *", .size = sizeof(struct Rectangle * ), .offset = 0
    },
    {
        .name = "factor",
        .type = "double",
        .size = sizeof(double),
        .offset = 0 + sizeof(struct Rectangle * )
    },
    {
        .name = "factor2",
        .type = "double",
        .size = sizeof(double),
        .offset = 0 + sizeof(double) + sizeof(struct Rectangle * )
    },
};
struct ObjC_ClassFieldsDescriptor Rectangle_Fields = {
    .size = 1,
    .fields = {
        {
            .name = "X2", .type = "double", .options = (struct ObjC_FieldOptions) {
                .access = 1, .access = 0, .serializable = 1,
            }, .size = sizeof(double), .offset = ((size_t) & (((Rectangle * ) 0) -> X2))
        },
    }
};
struct ObjC_ClassFunctionsDescriptor Rectangle_Functions = {
    .size = 2,
    .functions = {
        {
            .name = "area", .return_type = "double", .options = (struct ObjC_FuncOptions) {
                .access = 1, .access = 0,
            }, .return_size = sizeof(double), .offset = ((size_t) & (((Rectangle * ) 0) -> area)), .argument_count = 2, .arguments = (struct ObjC_FuncArgument * ) & Rectangle_Func_area_Arguments
        },
        {
            .name = "scale",
            .return_type = "void",
            .options = (struct ObjC_FuncOptions) {
                .access = 1, .access = 0,
            },
            .return_size = 0,
            .offset = ((size_t) & (((Rectangle * ) 0) -> scale)),
            .argument_count = 3,
            .arguments = (struct ObjC_FuncArgument * ) & Rectangle_Func_scale_Arguments
        },
    }
};
struct ObjC_GeneralClassDescriptor Rectangle_Class = {
    .name = "Rectangle",
    .total_size = sizeof(Rectangle),
    .super = & Shape_Class,
    .fields = & Rectangle_Fields,
    .functions = & Rectangle_Functions
};
double Rectangle_area(struct Rectangle * this, double scale) {
    struct ObjC_State __objc__state = {
        .class = & Rectangle_Class
    };
    do {
        printf("    Called Rectangle.area with scale=%f\n", scale);
        double * procf = ((double * ) objc_find( & __objc__state, (ObjC_BaseObject * ) this, "ProtectedField"));
        printf("    Trying to get protected field of Shape in Rectangle context. Expect %p==%p\n", procf, & this -> super.ProtectedField);
        double * privf = ((double * ) objc_find( & __objc__state, (ObjC_BaseObject * ) this, "PrivateField"));
        printf("    Trying to get private field of Shape in Rectangle context. Expect %p==0\n", privf);
        return this -> super.Width * this -> super.Height + 1;
    } while (0);
}
void Rectangle_scale(struct Rectangle * this, double factor, double factor2) {
    struct ObjC_State __objc__state = {
        .class = & Rectangle_Class
    };
    do {
        this -> super.Width *= factor;
        this -> super.Height *= factor;
    } while (0);
}
Rectangle * Rectangle_new() {
    struct ObjC_State __objc__state = {
        .class = & Rectangle_Class
    };
    Rectangle * this = (Rectangle * ) malloc(sizeof(Rectangle));
    this -> class = & Rectangle_Class;
    ((ObjC_BaseObject * ) this) -> object = (struct ObjC_Object * ) malloc(sizeof(struct ObjC_Object));
    ((ObjC_BaseObject * ) this) -> object -> total_size = sizeof(Rectangle);
    Shape * sp = Shape_new();
    memcpy( & this -> super, sp, sizeof(Shape));
    free(sp);
    ((ObjC_BaseObject * ) this) -> object -> total_size = sizeof(Rectangle);
    ((ObjC_BaseObject * ) this) -> object -> topClass = & Rectangle_Class;
    this -> super.Width = 0;
    this -> super.Height = 0;
    this -> super.X = 0;
    this -> super.Y = 0;
    this -> area = Rectangle_area;
    this -> scale = Rectangle_scale;
    return this;
};

typedef struct CoolRectangle {
    Rectangle super;
    struct ObjC_GeneralClassDescriptor * class;
    char * coolrectname;
}
CoolRectangle;
struct ObjC_ClassFieldsDescriptor CoolRectangle_Fields = {
    .size = 1,
    .fields = {
        {
            .name = "coolrectname", .type = "char*", .options = (struct ObjC_FieldOptions) {
                .access = 1,
            }, .size = sizeof(char * ), .offset = ((size_t) & (((CoolRectangle * ) 0) -> coolrectname))
        },
    }
};
struct ObjC_ClassFunctionsDescriptor CoolRectangle_Functions = {
    .size = 0,
    .functions = {}
};
struct ObjC_GeneralClassDescriptor CoolRectangle_Class = {
    .name = "CoolRectangle",
    .total_size = sizeof(CoolRectangle),
    .super = & Rectangle_Class,
    .fields = & CoolRectangle_Fields,
    .functions = & CoolRectangle_Functions
};
CoolRectangle * CoolRectangle_new() {
    struct ObjC_State __objc__state = {
        .class = & CoolRectangle_Class
    };
    CoolRectangle * this = (CoolRectangle * ) malloc(sizeof(CoolRectangle));
    this -> class = & CoolRectangle_Class;
    ((ObjC_BaseObject * ) this) -> object = (struct ObjC_Object * ) malloc(sizeof(struct ObjC_Object));
    ((ObjC_BaseObject * ) this) -> object -> total_size = sizeof(CoolRectangle);
    Rectangle * sp = Rectangle_new();
    memcpy( & this -> super, sp, sizeof(Rectangle));
    free(sp);
    ((ObjC_BaseObject * ) this) -> object -> total_size = sizeof(CoolRectangle);
    ((ObjC_BaseObject * ) this) -> object -> topClass = & CoolRectangle_Class;
    return this;
}
```

</td>
</tr>
</table>


</details>

# "classwalk" output for Rectangle class

```
----[Rectangle]----

    - FIELD: X
    -   - Size : 8 bytes
    -   - Offset : 8 bytes
    -   - Typeof : "double"
    -   - Options: serializable(1) access(0)
    - FIELD: Y
    -   - Size : 8 bytes
    -   - Offset : 16 bytes
    -   - Typeof : "double"
    -   - Options: serializable(1) access(0)
    - FIELD: Width
    -   - Size : 8 bytes
    -   - Offset : 24 bytes
    -   - Typeof : "double"
    -   - Options: serializable(1) access(0)
    - FIELD: Height
    -   - Size : 8 bytes
    -   - Offset : 32 bytes
    -   - Typeof : "double"
    -   - Options: serializable(1) access(0)
    - FUNCTION: area
    -   - Return size : 8 bytes
    -   - Offset : 40 bytes
    -   - Return type : "double"
    -   - Options: access(0)
    -   - Argument count : 0
    - FUNCTION: scale
    -   - Return size : 0 bytes
    -   - Offset : 48 bytes
    -   - Return type : "void"
    -   - Options: access(0)
    -   - Argument count : 1
        - ARGUMENT: factor
        -   - Offset : 0 bytes
        -   - Size : 8 bytes
        -   - Type : "double"
```

# a more in-depth overview
fields and functions are separated using `$fields(...)` and `$functions(...)` function-like macros, which are identical, only serving the purpose of grouping multiple entries into 1 single macro argument that is then expanded.

each entry is then also packed using parantheses and will be expanded after iteration using a macro implementation of "for"

## fields
objectc2 stores the name and type of fields as strings.

furthermore, it stores the size, offset (see `ou_offset`) and other field options in the resulting struct

## functions
functions have to be both implemented but also have their information stored.

function implementation is pretty straight-forward. arguments are unpacked and prepended by the instance `this` of the class type, unless the function is marked as static.

objectc2 stores the function name and return type as strings. it also stores the offset in the struct, options, return size and information about arguments.

objectc2 stores function arguments' name and type as strings, but also offset and size. the offset is calculated by reversing the argument list and implementing another "for" that sums all the sizes of
next (normally previous, but list is reversed) arguments, effectively calculating the offset of said argument

usually, sizeof(void) returns 1, which is a problem for the return size of functions, but this is fixed using a macro trick (see `oi_is_void`)
