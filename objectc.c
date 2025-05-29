#include "objectc.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

size_t objc_registered_classes_count = 0;

struct ObjC_GeneralClassDescriptor *objc_find_class(const char *name)
{
    for (int i = 0; i < objc_registered_classes_count; i++)
    {
        if (!strcmp(name, objc_registered_classes[i]->name))
        {
            return objc_registered_classes[i];
        }
    }
    return 0;
}

void *objc_find_access(struct ObjC_State *state, ObjC_BaseObject obj, struct ObjC_GeneralClassDescriptor *cur, size_t offset, unsigned char access)
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
/*
void *objc_find(struct ObjC_State *state, ObjC_BaseObject obj, const char *name)
{
    size_t offset = 0;
    do
    {
        
        struct ObjC_GeneralClassDescriptor *cur = 0;

        cur = ((ObjC_BaseObject)(((void *)obj) + offset))->class;
        if (offset == 0)
            offset += sizeof(struct ObjC_Object *);
        offset += sizeof(struct ObjC_GeneralClassDescriptor *);

        for (size_t j = 0; j < cur->fields->size; j++)
        {
            offset = cur->fields->fields[j].offset;
            printf("    objc_find: %s size=%d off=%d/%d\n", cur->fields->fields[j].name, cur->fields->fields[j].size, cur->fields->fields[j].offset, offset);
            if (!strcmp(cur->fields->fields[j].name, name))
            {
                return objc_find_access(state, obj, cur, offset, cur->fields->fields[j].options.access);
            }
        }
        for (size_t j = 0; j < cur->functions->size; j++)
        {
            offset = cur->fields->fields[j].offset;
            if (!strcmp(cur->functions->functions[j].name, name))
            {
                return objc_find_access(state, obj, cur, offset, cur->functions->functions[j].options.access);
            }
        }
        
    } while (offset < obj->object->total_size);
    return 0;
}*/
void *objc_find(struct ObjC_State *state, ObjC_BaseObject obj, const char *name)
{
    struct ObjC_GeneralClassDescriptor *cur = obj->object->topClass;
    while(cur) {
        struct ObjC_GeneralClassDescriptor *super = cur->super;
        for (size_t j = 0; j < cur->fields->size; j++)
        {
            size_t offset = cur->fields->fields[j].offset;
            if (!strcmp(cur->fields->fields[j].name, name))
            {
                return objc_find_access(state, obj, cur, offset, cur->fields->fields[j].options.access);
            }
        }
        for (size_t j = 0; j < cur->functions->size; j++)
        {
            size_t offset = cur->fields->fields[j].offset;
            if (!strcmp(cur->functions->functions[j].name, name))
            {
                return objc_find_access(state, obj, cur, offset, cur->functions->functions[j].options.access);
            }
        }
        cur = cur->super;
    }
    return 0;
}
typedef struct
{
    char *name;
    void *value;
    size_t memSize;
    enum
    {
        INT,
        DOUBLE,
        STRING,
        OBJECT,
        MEMCPY
    } type;
} KeyValuePair;
typedef struct
{
    KeyValuePair *children;
    size_t size;
    size_t allocatedSize;
} Object;

void _objc_tojson_populate(ObjC_BaseObject obj, Object *object)
{

    struct ObjC_GeneralClassDescriptor *class = obj->object->topClass;

    struct ObjC_State __objc__state = {.class = obj->class};

    KeyValuePair className = {"__objc_iden__", class->name, strlen(class->name) + 1, STRING};
    object->children[object->size++] = className;

    while (class)
    {
        for (int i = 0; i < class->fields->size; i++)
        {
            struct ObjC_ClassField *field = &class->fields->fields[i];

            if (!field->options.serializable)
                continue;
            if (field->options.access != ACCESS_PUBLIC)
                continue;

            KeyValuePair cur;
            void *data;
            cur.name = field->name;


            void *src = objc_find(&__objc__state, obj, field->name);
            if (!src)
                continue;

            if (object->size == object->allocatedSize)
            {
                object->children = realloc(object->children, (object->allocatedSize + 32) * sizeof(KeyValuePair));
                object->allocatedSize += 32;
            }

            if (objc_find_class(field->type))
            {
                Object *subObj = malloc(sizeof(Object));
                subObj->children = malloc(16 * sizeof(KeyValuePair));
                subObj->size = 0;
                subObj->allocatedSize = 16;


                _objc_tojson_populate(*((ObjC_BaseObject *)(src)), subObj);
                

                cur.type = OBJECT;
                data = subObj;
                cur.memSize = 0;
            }
            else if (!strcmp("const char*", field->type) || !strcmp("const char *", field->type) || !strcmp("char*", field->type) || !strcmp("char *", field->type) || !strcmp("string_t", field->type) || !strcmp("const string_t", field->type))
            {
                char **str = (char **)src;
                size_t len = strlen(*str);
                data = malloc(len);
                memcpy(data, *str, len);

                cur.type = STRING;
                cur.memSize = len + 1;
            }
            else
            {
                data = malloc(field->size);
                memcpy(data, src, field->size);


                if (!strcmp("double", field->type) || !strcmp("float", field->type) || !strcmp("const float", field->type) || !strcmp("const double", field->type) || !strcmp("long double", field->type)){
                    cur.type = DOUBLE;
                }else if (field->size == 1 || field->size == 2 || field->size == 4 || field->size == 8)
                    cur.type = INT;
                else
                    cur.type = MEMCPY;

                cur.memSize = field->size;
                
            }

            cur.value = data;

            object->children[object->size++] = cur;
        }
        class = class->super;
    }
    
    object->children = realloc(object->children, object->size * sizeof(KeyValuePair));
}

size_t _objc_tojson_write(ObjC_BaseObject obj, Object* object, char *out, size_t maxLen, size_t scursor) {
    struct ObjC_State __objc__state = {.class = obj->class};
    size_t cursor = scursor;
    out[cursor++] = '{';
    for(int i = 0; i < object->size; i++) {
        KeyValuePair cur = object->children[i];
        
        switch(cur.type) {
            case INT: {
                long long x = 0;
                memcpy(&x, cur.value, cur.memSize);
                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":%d", cur.name, x);
                
                break;
            }
            case DOUBLE: {
                double x = 0;
                memcpy(&x, cur.value, cur.memSize);
                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":%f", cur.name, x);
                break;
            }
            case OBJECT: {
                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":", cur.name);
                cursor = _objc_tojson_write(obj, (Object*)cur.value, out, maxLen, cursor);
                break;
            }
            case STRING: {
                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":\"%s\"", cur.name, cur.value);
                break;
            }
            case MEMCPY: {
                
                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":[", cur.name, cur.value);
                for(int j = 0; j < cur.memSize; j++) {
                    cursor += sprintf_s(out+cursor, maxLen-cursor, "%d", ((char*)cur.value)[j]);

                    if(cursor == maxLen) return 0;

                    if(j != cur.memSize-1) out[cursor++] = ',';
                }

                if(cursor == maxLen) return 0;

                out[cursor++] = ']';
                break;
            }
        }
        if(cursor == maxLen) return 0;
        if(i != object->size-1) out[cursor++] = ',';
    }
    if(cursor == maxLen) return 0;
    out[cursor++] = '}';
    if(scursor == 0) {
        if(cursor == maxLen) return 0;
        out[cursor++] = 0;
    }
    return cursor;
}

void _objc_tojson_depopulate(Object* object) {
    for(int i = 1; i < object->size; i++) {
        KeyValuePair cur = object->children[i];
        switch(cur.type) {
            case OBJECT: {
                _objc_tojson_depopulate(cur.value);
                free(((Object*)cur.value)->children);
                break;
            }
            default: {
                free(cur.value);
                break;
            }
        }
    }
}

void objc_tojson(ObjC_BaseObject obj, char *out, size_t maxLen)
{
    struct ObjC_State __objc__state = {.class = obj->class};

    Object object = {.children = malloc(16 * sizeof(KeyValuePair)), .size = 0, .allocatedSize = 16};
    _objc_tojson_populate(obj, &object);

    if(!_objc_tojson_write(obj, &object, out, maxLen, 0)) {
        memset(out, 0, maxLen);
    };

    _objc_tojson_depopulate(&object);
    free(object.children);
}