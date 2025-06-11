#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.UnifiedData.proj.0.hpp"
::ohos::data::unifiedDataChannel::UnifiedData ohos_data_unifiedDataChannel_UnifiedData_fromANI(ani_env* env, ani_object ani_obj);
ani_object ohos_data_unifiedDataChannel_UnifiedData_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::UnifiedData cpp_obj);
