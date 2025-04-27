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
$class(Rectangle,
    $fields(
        (double, X, $opt(PUBLIC SERIALIZABLE)),
        (double, Y, $opt(PUBLIC SERIALIZABLE)),
        (double, Width, $opt(PUBLIC SERIALIZABLE)),
        (double, Height, $opt(PUBLIC SERIALIZABLE))
    ),
    $functions(
        (double, area, $arg(), $body(
            return this->Width*this->Height;
        ), $opt(PUBLIC)),

        (void, scale, $arg( (double, factor) ), $body(
            this->Width*=factor;
            this->Height*=factor;
        ), $opt(PUBLIC))
    )
);
```

</td>
<td>

```c
#include "objectc.h"

typedef struct {
    struct ObjC_GeneralClassDescriptor * class;
    double X;
    double Y;
    double Width;
    double Height;
    double (*area)();
    void (*scale)();
} Rectangle;
struct ObjC_FuncArgument Rectangle_Func_area_Arguments[] = {};
struct ObjC_FuncArgument Rectangle_Func_scale_Arguments[] = {
  {
    .name = "factor", .type = "double", .size = sizeof(double), .offset = 0
  },
};
struct ObjC_ClassFieldsDescriptor Rectangle_Fields = {
  .size = 4,
  .fields = {
    {
      .name = "X", .type = "double", .options = (struct ObjC_FieldOptions) {
        .access = 1, .access = 0, .serializable = 1,
      }, .size = sizeof(double), .offset = ((size_t) & (((Rectangle * ) 0) -> X))
    },
    {
      .name = "Y",
      .type = "double",
      .options = (struct ObjC_FieldOptions) {
        .access = 1, .access = 0, .serializable = 1,
      },
      .size = sizeof(double),
      .offset = ((size_t) & (((Rectangle * ) 0) -> Y))
    },
    {
      .name = "Width",
      .type = "double",
      .options = (struct ObjC_FieldOptions) {
        .access = 1, .access = 0, .serializable = 1,
      },
      .size = sizeof(double),
      .offset = ((size_t) & (((Rectangle * ) 0) -> Width))
    },
    {
      .name = "Height",
      .type = "double",
      .options = (struct ObjC_FieldOptions) {
        .access = 1, .access = 0, .serializable = 1,
      },
      .size = sizeof(double),
      .offset = ((size_t) & (((Rectangle * ) 0) -> Height))
    },
  }
};
struct ObjC_ClassFunctionsDescriptor Rectangle_Functions = {
  .size = 2,
  .functions = {
    {
      .name = "area", .return_type = "double", .options = (struct ObjC_FuncOptions) {
        .access = 1, .access = 0,
      }, .return_size = sizeof(double), .offset = ((size_t) & (((Rectangle * ) 0) -> area)), .argument_count = 0, .arguments = (struct ObjC_FuncArgument * ) & Rectangle_Func_area_Arguments
    },
    {
      .name = "scale",
      .return_type = "void",
      .options = (struct ObjC_FuncOptions) {
        .access = 1, .access = 0,
      },
      .return_size = 0,
      .offset = ((size_t) & (((Rectangle * ) 0) -> scale)),
      .argument_count = 1,
      .arguments = (struct ObjC_FuncArgument * ) & Rectangle_Func_scale_Arguments
    },
  }
};
struct ObjC_GeneralClassDescriptor Rectangle_Class = {
  .name = "Rectangle",
  .fields = & Rectangle_Fields,
  .functions = & Rectangle_Functions
};
double Rectangle_area(Rectangle * this) {
  return this -> Width * this -> Height;
}
void Rectangle_scale(Rectangle * this, double factor) {
  this -> Width *= factor;
  this -> Height *= factor;
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

function implementation is pretty straight-forward. arguments are unpacked and prepended by the instance `this` of the class type

objectc2 stores the function name and return type as strings. it also stores the offset in the struct, options, return size and information about arguments.

objectc2 stores function arguments' name and type as strings, but also offset and size. the offset is calculated by reversing the argument list and implementing another "for" that sums all the sizes of
next (normally previous, but list is reversed) arguments, effectively calculating the offset of said argument

usually, sizeof(void) returns 1, which is a problem for the return size of functions, but this is fixed using a macro trick (see `oi_is_void`)
