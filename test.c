#include "objectc.h"


$class(MyClass,
    $fields(
        (int, test, $opt(PUBLIC SERIALIZABLE)),
        (string_t, stringy_test, $opt(PUBLIC SERIALIZABLE))),
    $functions(
        (string_t, stringy_test2, $arg((int, test), (double, f)), $body(
            // this is function code
            int a = 1; 
            string_t string = "aaaaaabbb"; 
            int test223[] = {1, 2, 3, 4, sizeof(void)}; 
            return string;
        ), $opt(PUBLIC)),
        (void, lol, $arg(), $body(

        ),$opt(STATIC))
        )
    );

void classwalk(struct ObjC_GeneralClassDescriptor d)
{

    printf("----[%s]----\n\n", d.name);
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
    classwalk(MyClass_Class);
}