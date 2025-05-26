#include "objectc.h"
#include <stdio.h>


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
        ($opt(PUBLIC SERIALIZABLE), double, X2)
    ),
    $functions(
        ($opt(PUBLIC), double, area, $arg((double,scale)), $body({
            double* procf = $ptr(this, double*, PrivateField);
            printf("Called Rectangle.area with %p, %f\n", procf, scale);
            return this->super.Width * this->super.Height + 1;
        })),

        ($opt(PUBLIC), void, scale, $arg( (double, factor), (double, factor2), (char, x), (int, factor3) ), $body({
            this->super.Width*=factor;
            this->super.Height*=factor;
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
    $fields(),
    $functions()
)

void classwalk(struct ObjC_GeneralClassDescriptor d)
{$o
    
    CoolRectangle* cb = CoolRectangle_new();
    //printf("%s -> %s -> %s\n", cb->class->name, cb->super.class->name, cb->super.super.class->name);
    void (*ptr)(void*,double) = *($ptr(cb, void (**)(void*,double), area));
    //printf("expect %p == %p\n", ptr, Rectangle_area);
    Rectangle* rect = (Rectangle*)cb;
    rect->area(rect, 1);
    
    

    return;
    //ptr(args.this, args.scale);
    

    printf("----[%s]----\n", d.name);
    for (int i = 0; i < d.fields->size; i++)
    {
        struct ObjC_ClassField f = d.fields->fields[i];
        printf("    - FIELD: %s\n", f.name);
        printf("    -   - Size : %d bytes\n", f.size);
        printf("    -   - Offset : %d bytes\n", f.offset);
        printf("    -   - Typeof : \"%s\"\n", f.type);
        printf("    -   - Options: serializable(%d) access(%d)\n", f.options.serializable, f.options.access);
    }
    for (int i = 0; i < d.functions->size; i++)
    {
        struct ObjC_ClassFunction f = d.functions->functions[i];
        printf("    - FUNCTION: %s\n", f.name);
        printf("    -   - Return size : %d bytes\n", f.return_size);
        printf("    -   - Offset : %d bytes\n", f.offset);
        printf("    -   - Return type : \"%s\"\n", f.return_type);
        printf("    -   - Options: access(%d)\n", f.options.access);
        printf("    -   - Argument count : %d\n", f.argument_count);

        for(int i = 0; i < f.argument_count; i++) {

            struct ObjC_FuncArgument a = f.arguments[i];
            
            printf("        - ARGUMENT: %s\n", a.name);
            printf("        -   - Offset : %d bytes\n", a.offset);
            printf("        -   - Size : %d bytes\n", a.size);
            printf("        -   - Type : \"%s\"\n", a.type);
        }
        
    }
}

/**
 * @TODO there is some stuf to do actually
 * i have to see if there s any way i can improve the current syntax because it is quite ugly
 * 
 */

int main()
{
    classwalk(Rectangle_Class);
}