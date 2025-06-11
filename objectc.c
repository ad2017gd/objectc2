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


typedef enum
{
        INT,
        DOUBLE,
        STRING,
        OBJECT,
        BOOL,
        MEMCPY
} KVType;
typedef struct
{
    char *name;
    void *value;
    size_t memSize;
    KVType type;
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
            } // TODO: remove excess whitespaces / actually parse the type
            else if (!strcmp("const char*", field->type) || !strcmp("const char *", field->type) || !strcmp("char*", field->type) || !strcmp("char *", field->type) || !strcmp("string_t", field->type) || !strcmp("const string_t", field->type))
            {
                
                char **str = (char **)src;
                size_t len = strlen(*str);
                data = malloc(len+1);
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
    return x;
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
                fixStr[newLen] = 0;
                

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

size_t _objc_fromjson_populate(char* in, Object* object, size_t scursor) {
    enum {
        NONE,
        WAITKEY,
        KEY,
        KVSEP,
        WAITVALUE,
        VALUE,
        ESEP
    } state = NONE;

    KVType valueType = DOUBLE;

    size_t cursor = scursor;
    size_t maxLen = strlen(in);

    char tmp[8192];
    size_t tIdx = 0;


    while(cursor < maxLen) {
        //printf("    state %d char %c\n", state, in[cursor]);
        if(in[cursor] == '{' && state == NONE) {
            state = WAITKEY;
        }

        if(state == KEY) {
            if(in[cursor] == '"' && in[cursor-1] != '\\') {
                // create object entry, add key

                tmp[tIdx++] = 0;
                if(object->size >= object->allocatedSize) {
                    object->children = realloc(object->children, (object->allocatedSize + 32)*sizeof(KeyValuePair));
                    object->allocatedSize+=32;
                }
                object->children[object->size].name = malloc(tIdx);
                memcpy(object->children[object->size].name, tmp, tIdx);


                state = KVSEP;
                tIdx=0;
            } else {
                tmp[tIdx++] = in[cursor];
            }
        }
        if(state == VALUE) {
            _Bool end = FALSE;
            Object *subObj = 0;

            if(valueType == STRING) {
                if(in[cursor] == '"' && in[cursor-1] != '\\') end = TRUE;
            }
            if(valueType == MEMCPY) {
                if(in[cursor] == ']') end = TRUE;
            }
            if(valueType == OBJECT) {
                subObj = malloc(sizeof(Object));
                subObj->children = malloc(16 * sizeof(KeyValuePair));
                subObj->size = 0;
                subObj->allocatedSize = 16;

                size_t subEnd = _objc_fromjson_populate(in, subObj, cursor);

                cursor = subEnd+1;
                end = TRUE;
            }
            if(valueType == INT || valueType == DOUBLE || valueType == BOOL) {
                if(in[cursor] == ',' || in[cursor] == '}') end = TRUE;
            }

            if(end) {
                // parse value & add to obj

                tmp[tIdx++] = 0;

                
                object->children[object->size].type = valueType;
                if(valueType == OBJECT) {
                    object->children[object->size].value = subObj;
                    object->children[object->size].memSize = 0;
                }
                if(valueType == STRING) {
                    

                    object->children[object->size].value = malloc(tIdx);
                    size_t cnt = 0;
                    size_t vcnt = 0;
                    while(tmp[cnt]) {
                        if(tmp[cnt] == '\\' && tmp[cnt-1] != '\\') {
                            cnt++;
                            continue;
                        }
                        ((char*)object->children[object->size].value)[vcnt++] = tmp[cnt++]; 
                    }
                    ((char*)object->children[object->size].value)[vcnt++] = 0;

                    object->children[object->size].memSize = tIdx;
                }
                if(valueType == BOOL) {
                    object->children[object->size].value = malloc(sizeof(_Bool));
                    *((_Bool*)(object->children[object->size].value)) = memcmp(tmp, "true", sizeof("true")-1) == 0;
                    object->children[object->size].memSize = sizeof(_Bool);
                }
                if(valueType == MEMCPY) {
                    size_t memsize = 0;
                    // check empty array?
                    _Bool hasValue = FALSE;
                    for(int i = 0; i < strlen(tmp); i++) {
                        int asnum = tmp[i] - '0';
                        if(tmp[i] == ',') memsize++;
                        if(asnum >= 0 && asnum <= 9) hasValue = TRUE;
                    }
                    if(hasValue) memsize++;

                    char* mem = malloc(memsize);
                    size_t midx = 0;

                    char curval[4];
                    int vidx = 0;
                    for(int i = 0; i < strlen(tmp)+1; i++) {
                        int asnum = tmp[i] - '0';
                        if(tmp[i] == ',' || tmp[i] == 0) {
                            if(vidx == 0) curval[vidx++] = '0';
                            curval[vidx] = 0;
                            mem[midx++] = atoi(curval);
                            vidx = 0;
                        } else
                        if(asnum >= 0 && asnum <= 9) curval[vidx++] = tmp[i];
                    }

                    object->children[object->size].value = mem;

                    object->children[object->size].memSize = memsize;
                }
                if(valueType == INT) {
                    long long* p = malloc(sizeof(long long));
                    *p = atoll(tmp);

                    object->children[object->size].value = p;
                    object->children[object->size].memSize = sizeof(long long);
                }
                if(valueType == DOUBLE) {
                    double* p = malloc(sizeof(double));
                    *p = atof(tmp);

                    object->children[object->size].value = p;
                    object->children[object->size].memSize = sizeof(double);
                }

                object->size++;
                state = ESEP;
                tIdx=0;
            } else {
                if(valueType == INT && in[cursor] == '.') valueType = DOUBLE;
                tmp[tIdx++] = in[cursor];
            }
        }


        if(state == WAITVALUE && in[cursor] != ' ') {
            if(in[cursor] == '"') valueType = STRING;
            else if(in[cursor] == '{') {valueType = OBJECT;cursor--;}
            else if(memcmp(in+cursor, "true", sizeof("true")-1) == 0 || memcmp(in+cursor, "false", sizeof("false")-1) == 0) {valueType = BOOL; cursor--;}
            else if(in[cursor] == '[') valueType = MEMCPY;
            else {valueType = INT;cursor--;} // assume? convert to DOUBLE if floating point
            
            state = VALUE;
        }
        if(state == KVSEP && in[cursor] == ':') {
            state = WAITVALUE;
        }
        if(state == ESEP && in[cursor] == ',') {
            state = WAITKEY;
        }
        if(state == WAITKEY && in[cursor] == '"') {
            state = KEY;
        }
        if((state == WAITKEY || state == ESEP || state == WAITVALUE || state == KVSEP) && in[cursor] == '}') {
            break;
        }
        
        cursor++;
    }
    return cursor;
}

struct ObjC_ClassField *_objc_find_desc(ObjC_BaseObject obj, const char *name)
{
    struct ObjC_GeneralClassDescriptor *cur = obj->object->topClass;
    while(cur) {
        struct ObjC_GeneralClassDescriptor *super = cur->super;
        for (size_t j = 0; j < cur->fields->size; j++)
        {
            size_t offset = cur->fields->fields[j].offset;
            if (!strcmp(cur->fields->fields[j].name, name))
            {
                return &cur->fields->fields[j];
            }
        }
        cur = cur->super;
    }
    return 0;
}

typedef struct { 
    CObjC_BaseObject super;
    struct ObjC_GeneralClassDescriptor* class; 
} CObjC_ExtObject;
typedef CObjC_ExtObject* ObjC_ExtObject;

ObjC_BaseObject _objc_fromjson_create(Object* object, _Bool super) {
    struct ObjC_GeneralClassDescriptor* cd = objc_find_class(object->children[0].value);
    ObjC_BaseObject this = cd->constructor();

    struct ObjC_State _st = {.class = 0};
    for(size_t i = 1; i < object->size; i++) {
        KeyValuePair* cur = &object->children[i];

        void* _target = objc_find(&_st, this, cur->name);
        struct ObjC_ClassField* field = _objc_find_desc(this, cur->name);
        if(_target == 0 || field == 0) continue;

        if(!field->options.serializable && field->options.access != ACCESS_PUBLIC) continue;

        switch(cur->type) {
            
            case STRING:{
                // TODO: fix memleak for string literal in future
                    // like
                    /*
                        class{
                            string a = "some const string"
                        }
                        
                        if i serialize and deserialize string lit. become allocated and -> memleak
                        lol

                        maybe check section of string?
                    */
                char* s = malloc(cur->memSize);
                memcpy(s, cur->value, cur->memSize);
                *((char**)_target) = s;
                break;
            }
            case OBJECT:{
                void* ptr = _objc_fromjson_create(cur->value, TRUE);
                *((void**)(_target)) = ptr;
                break;
            }

            
            default:{
                
                memcpy(_target, cur->value, field->size);
                break;
            }
        }
    }
    return this;
}

void _objc_fromjson_depopulate(Object* object) {
    for(int i = 0; i < object->size; i++) {
        KeyValuePair cur = object->children[i];
        switch(cur.type) {
            case OBJECT: {
                _objc_fromjson_depopulate(cur.value);
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

ObjC_BaseObject objc_fromjson(char* in) {$o
    Object object = {.children = malloc(16 * sizeof(KeyValuePair)), .size = 0, .allocatedSize = 16};
    _objc_fromjson_populate(in, &object, 0);
    
    if(object.size == 0) return 0;

    ObjC_BaseObject res = _objc_fromjson_create(&object, FALSE);

    _objc_fromjson_depopulate(&object);

    return res;
}