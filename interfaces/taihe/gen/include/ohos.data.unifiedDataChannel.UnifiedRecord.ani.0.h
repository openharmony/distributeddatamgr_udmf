#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.proj.0.hpp"
::ohos::data::unifiedDataChannel::UnifiedRecord ohos_data_unifiedDataChannel_UnifiedRecord_fromANI(ani_env* env, ani_object ani_obj);
ani_object ohos_data_unifiedDataChannel_UnifiedRecord_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::UnifiedRecord cpp_obj);
