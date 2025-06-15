#include "taihe/runtime.hpp"
#include "ohos.data.unifiedDataChannel.ani.hpp"
#include "ohos.data.uniformTypeDescriptor.ani.hpp"
ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result) {
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }
    if (ANI_OK != ohos::data::unifiedDataChannel::ANIRegister(env)) {
        std::cerr << "Error from ohos::data::unifiedDataChannel::ANIRegister" << std::endl;
        return ANI_ERROR;
    }
    if (ANI_OK != ohos::data::uniformTypeDescriptor::ANIRegister(env)) {
        std::cerr << "Error from ohos::data::uniformTypeDescriptor::ANIRegister" << std::endl;
        return ANI_ERROR;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
