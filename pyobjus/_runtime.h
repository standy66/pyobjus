#include <objc/runtime.h>
#include <objc/message.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

static void pyobjc_internal_init() {	

    static void *foundation = NULL;
    if ( foundation == NULL ) {
        foundation = dlopen(
        "/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation", RTLD_LAZY);
        if ( foundation == NULL ) {
            printf("Got dlopen error on Foundation\n");
	    printf(dlerror());
            return;
        }
    }
}

id allocAndInitAutoreleasePool() {
  Class NSAutoreleasePoolClass = (Class)objc_getClass("NSAutoreleasePool");
  id pool = class_createInstance(NSAutoreleasePoolClass, 0);
  return objc_msgSend(pool, sel_registerName("init"));
}

void drainAutoreleasePool(id pool) {
  (void)objc_msgSend(pool, sel_registerName("drain"));
}

