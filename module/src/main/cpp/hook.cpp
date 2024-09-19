#include <cstring>
#include <android/log.h>
#include <dlfcn.h>

#include "zygisk_next_api.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "wvmkiller", __VA_ARGS__)

static char* (*old_getenv)(const char *name) = nullptr;
static const char* my_getenv(const char *name) {
    // https://github.com/LineageOS/android_hardware_oplus/commit/4c37ab7678f3efea2d9ab5f54c57871eb5c19e00
    if (strcmp(name, "FORCE_LEVEL3_OEMCRYPTO") == 0) {
        LOGI("set FORCE_LEVEL3_OEMCRYPTO env success");
        return "yes";
    }
    return old_getenv(name);
}

// this function will be called after all of the main executable's needed libraries are loaded
// and before the entry of the main executable called
void onModuleLoaded(void* self_handle, const struct ZygiskNextAPI* api) {
    // inline hook drm service's getenv function
    auto fun = dlsym(RTLD_NEXT, "getenv");
    if (api->inlineHook(fun, (void *) my_getenv, (void**) &old_getenv) == ZN_SUCCESS) {
        LOGI("inline hook success %p", old_getenv);
    } else {
        LOGI("inline hook failed");
    }
}

// declaration of the zygisk next module
__attribute__((visibility("default"), unused))
struct ZygiskNextModule zn_module = {
        .target_api_version = ZYGISK_NEXT_API_VERSION_1,
        .onModuleLoaded = onModuleLoaded
};
