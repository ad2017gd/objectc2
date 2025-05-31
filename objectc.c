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
        BOOL,
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

            size_t fLen = strlen(field->name)+1;
            cur.name = malloc(fLen);
            memcpy(cur.name, field->name, fLen);


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
                memcpy(data, *str, len+1);

                cur.type = STRING;
                cur.memSize = len + 1;
            } else if (!strcmp("const bool", field->type) || !strcmp("bool", field->type) || !strcmp("const _Bool", field->type) || !strcmp("_Bool", field->type)) {
                _Bool *bl = (_Bool*)src;
                data = malloc(sizeof(_Bool));
                memcpy(data, bl, sizeof(_Bool));

                cur.type = BOOL;
                cur.memSize = sizeof(_Bool);
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

size_t _countChars(const char* in, char c) {
    size_t x = 0;
    do {
        if(*in == c) x++;
    } while(*(in++));
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
                size_t newLen = strlen(cur.value) + _countChars(cur.value, '"');
                char* fixStr = malloc(newLen+1);
                size_t cntSource = 0;
                size_t cntDest = 0;
                do {
                    char cch = ((char*)cur.value)[cntSource];
                    if(cch == '"') {
                        fixStr[cntDest++] = '\\';
                    }
                    fixStr[cntDest++] = cch;
                } while(((char*)cur.value)[++cntSource]);
                fixStr[newLen+1] = 0;

                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":\"%s\"", cur.name, fixStr);
                free(fixStr);
                break;
            }
            case BOOL: {
                cursor += sprintf_s(out+cursor, maxLen-cursor, "\"%s\":%s", cur.name, (*((_Bool*)cur.value)) ? "true" : "false");
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
                free(cur.name);
                break;
            }
        }
    }
}

int objc_tojson(void* obj, char *out, size_t maxLen)
{
    struct ObjC_State __objc__state = {.class = ((ObjC_BaseObject)obj)->class};

    Object object = {.children = malloc(16 * sizeof(KeyValuePair)), .size = 0, .allocatedSize = 16};
    _objc_tojson_populate(obj, &object);

    if(!_objc_tojson_write(obj, &object, out, maxLen, 0)) {
        memset(out, 0, maxLen);
        return 0;
    };

    _objc_tojson_depopulate(&object);
    free(object.children);

    return 1;
}
/*
IM TOO STUPID FOR THIS

int _indexOf(char* str, char of) {
    char* orig = str;
    while(*(str)) {
        if((of == 0 && *str != ' ') || (*str == of)) {
            if(str-orig > 0) {
                if(*(str-1) != '\\')
                    return str-orig;
            }
            else return str-orig;
        }
        str++;
    }
    return -1;
}

void _objc_fromjson_populate(char* in, Object* object, size_t scursor) {
    size_t cursor = scursor;
    size_t maxLen = strlen(in);
    char tmp[8192];

    size_t start = _indexOf(in, '{');
    if(start == -1) return;
    cursor+=start;
    printf("fromjson: found { at %d\n", cursor);
    while(TRUE) {
        size_t cur = cursor;
        KeyValuePair pair;
        

        size_t keyStart = cur + _indexOf(in+cur, '"');
        size_t keyEnd = keyStart + _indexOf(in+keyStart+1, '"') + 1;

        if(keyStart==-1 || keyEnd == -1) break;

        pair.name = malloc(keyEnd - keyStart);
        memcpy(pair.name, in+keyStart+1, keyEnd - keyStart - 1);
        pair.name[keyEnd - keyStart] = 0;

        size_t separator = keyEnd + _indexOf(in+keyEnd, ':');
        if(separator == -1) break;

        size_t valueStart = separator+1;

        size_t nextNonWhitespace = valueStart + _indexOf(in+valueStart, 0);

        size_t pairEnd = 0;

        char* litValue = 0;

        switch(in[nextNonWhitespace]) {
            case '\"': {
                // string value
                size_t stringEnd = valueStart + _indexOf(in+valueStart+1, '"')+1;

                litValue = malloc(stringEnd-valueStart);
                memcpy(litValue, in+valueStart+1, stringEnd - valueStart - 1);
                litValue[stringEnd - valueStart - 1] = 0;

                pairEnd = stringEnd + _indexOf(in+stringEnd, ',');
                if(pairEnd == stringEnd - 1) pairEnd = stringEnd + _indexOf(in+stringEnd, '}');
                break;
            }
            case '[': {
                // array value
                break;
            }
            case '{': {
                // object value
                break;
            }
            default: {
                // int/double/(bool?)
                pairEnd = valueStart + _indexOf(in+valueStart, ',');
                
                if(pairEnd == valueStart - 1) pairEnd = valueStart + _indexOf(in+valueStart, '}');

                litValue = malloc((pairEnd-1)-valueStart);
                memcpy(litValue, in+valueStart+1, (pairEnd-1) - valueStart - 1);
                litValue[(pairEnd-1) - valueStart - 1] = 0;
                break;
            }
        }
        

        

        printf("%s=%s\n", pair.name, litValue);

        if(in[pairEnd] == '}') break;
        cursor += pairEnd - cur;
    }
}

ObjC_BaseObject objc_fromjson(char* in) {$o
    Object object = {.children = malloc(16 * sizeof(KeyValuePair)), .size = 0, .allocatedSize = 16};
    _objc_fromjson_populate(in, &object, 0);
    return 0;
}*/