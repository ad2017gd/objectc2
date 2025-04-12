# objectc2
work in progress c object library heavily based on macro tricks

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
