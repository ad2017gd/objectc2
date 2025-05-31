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
        ($opt(PUBLIC SERIALIZABLE), double, X2)),
    $functions(
        ($opt(PUBLIC), double, area, $arg((double, scale)), $body({
             printf("    Called Rectangle.area with scale=%f\n", scale);
             double *procf = $ptr(this, double *, "ProtectedField");
             printf("    Trying to get protected field of Shape in Rectangle context. Expect %p==%p\n", procf, &this->super.ProtectedField);
             double *privf = $ptr(this, double *, "PrivateField");
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
/*
serializing field subRectangle
    objc_find: X size=8 off=16
    objc_find: Y size=8 off=24
    objc_find: Width size=8 off=32
    objc_find: Height size=8 off=40
    objc_find: PublicField size=8 off=48
    objc_find: ProtectedField size=8 off=56
    objc_find: PrivateField size=8 off=64
    objc_find: X2 size=8 off=80
    objc_find: CoolInt size=4 off=112
    objc_find: CoolInt2 size=4 off=116
    objc_find: subRectangle size=8 off=120

    serializing field subRectangle
    objc_find: X size=8 off=16
    objc_find: Y size=8 off=24
    objc_find: Width size=8 off=32
    objc_find: Height size=8 off=40
    objc_find: PublicField size=8 off=48
    objc_find: ProtectedField size=8 off=56
    objc_find: PrivateField size=8 off=64
    objc_find: X2 size=8 off=80
    objc_find: CoolInt size=4 off=112
    objc_find: CoolInt2 size=2 off=116
    objc_find: subRectangle size=8 off=120
    */

typedef struct {
    int a;
    char b;
    double f;
} mystruct;

$class(CoolRectangle $extends Rectangle,
    $fields(
        ($opt(PUBLIC SERIALIZABLE), int, CoolInt),
        ($opt(PUBLIC SERIALIZABLE), short, CoolInt2),
        ($opt(PUBLIC SERIALIZABLE), mystruct, SomeUnknownStruct),
        ($opt(PUBLIC SERIALIZABLE), string_t, str),
        ($opt(PUBLIC SERIALIZABLE), Rectangle, subRectangle),
        ($opt(PUBLIC SERIALIZABLE), _Bool, boolean)
    ),
    $functions(

    ),
    $constructor(
        this->subRectangle = Rectangle_new();
        this->CoolInt = 74;
        this->CoolInt2 = 6969;
        this->SomeUnknownStruct = (mystruct){1,2,3.5};
        this->str = "aa\"funny";
        this->boolean = TRUE;
    )
)





    void classwalk(struct ObjC_GeneralClassDescriptor cls)
{
    $o

    struct ObjC_GeneralClassDescriptor *cur = &cls;
    while (cur)
    {
        struct ObjC_GeneralClassDescriptor d = *cur;
        printf("\n\n----[%s]----\n", d.name);

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

            for (int i = 0; i < f.argument_count; i++)
            {

                struct ObjC_FuncArgument a = f.arguments[i];

                printf("        - ARGUMENT: %s\n", a.name);
                printf("        -   - Offset : %d bytes\n", a.offset);
                printf("        -   - Size : %d bytes\n", a.size);
                printf("        -   - Type : \"%s\"\n", a.type);
            }
        }
        cur = cur->super;
    }
}

/**
 * @TODO there is some stuf to do actually
 * i have to see if there s any way i can improve the current syntax because it is quite ugly
 *
 */

int main()
{$o


    printf("Running some tests...\n\nCreating instance of CoolRectangle that extends Rectangle, that extends Shape.\n");
    CoolRectangle cb = CoolRectangle_new();

    printf("Serializing the CoolRectangle instance.\n");
    char* buf = malloc(512);
    objc_tojson(cb, buf, 512);
    printf("Result: %s\n",buf);

    //objc_fromjson(buf);
    
    free(buf);
    return 0;


    printf("Class hierarchy : %s -> %s -> %s\n", cb->class->name, cb->super.class->name, cb->super.super.class->name);
    void (*ptr)(void *, double) = *($ptr(cb, void (**)(void *, double), "area"));
    printf("Trying to find public function \"area\" of CoolRectangle object. Expect %p == %p\n", ptr, Rectangle_area);

    double *procf = $ptr(cb, double *, "ProtectedField");
    printf("Trying to get protected field of Shape in outside context. Expect %p==0\n", procf, 0);
    double *privf = $ptr(cb, double *, "PrivateField");
    printf("Trying to get private field of Shape in outside context. Expect %p==0\n", privf, 0);

    Rectangle rect = (Rectangle)cb;
    printf("Calling Rectangle.area (from casting CoolRectangle* to Rectangle*) with scale=1\n");
    rect->area(rect, 1);

    printf("Trying to find class Rectangle by name. Expect %p==%p\n", objc_find_class("Rectangle"), &Rectangle_Class);

    

    printf("Calling classwalk on CoolRectangle class descriptor\n");

    classwalk(CoolRectangle_Class);
}