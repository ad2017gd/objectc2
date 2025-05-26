#include "objectc.h"
#include <stdarg.h>
#include <string.h>

void *objc_find_access(struct ObjC_State *state, ObjC_BaseObject *obj, struct ObjC_GeneralClassDescriptor *cur, size_t offset, unsigned char access)
{
    if (access == ACCESS_PRIVATE)
    {
        if (cur == state->class)
            return ((void *)obj + offset);
        else
            return 0;
    }
    if (access == ACCESS_PROTECTED)
    {
        struct ObjC_GeneralClassDescriptor *curDesc = obj->object->topClass;

        int deep = 48; // failsafe?
        while (deep--)
        {
            if (curDesc == state->class)
                return ((void *)obj + offset);

            if (curDesc->super)
                curDesc = curDesc->super;
            else
                return 0;
        }
        return 0;
    }

    return ((void *)obj + offset);
}

void *objc_find(struct ObjC_State *state, ObjC_BaseObject *obj, char *name)
{
    size_t offset = 0;
    do
    {
        struct ObjC_GeneralClassDescriptor *cur = 0;

        cur = ((ObjC_BaseObject *)(((void *)obj) + offset))->class;
        if (offset == 0)
            offset += sizeof(struct ObjC_Object *);
        offset += sizeof(struct ObjC_GeneralClassDescriptor *);

        for (size_t j = 0; j < cur->fields->size; j++)
        {
            if (!strcmp(cur->fields->fields[j].name, name))
            {
                return objc_find_access(state, obj, cur, offset, cur->fields->fields[j].options.access);
            }
            offset += cur->fields->fields[j].size;
        }
        for (size_t j = 0; j < cur->functions->size; j++)
        {
            if (!strcmp(cur->functions->functions[j].name, name))
            {
                return objc_find_access(state, obj, cur, offset, cur->functions->functions[j].options.access);
            }
            offset += sizeof(void *);
        }
    } while (offset < obj->object->total_size);
    return 0;
}