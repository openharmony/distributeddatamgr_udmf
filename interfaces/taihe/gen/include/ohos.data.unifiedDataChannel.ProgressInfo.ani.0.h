#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.ProgressInfo.proj.0.hpp"
::ohos::data::unifiedDataChannel::ProgressInfo ohos_data_unifiedDataChannel_ProgressInfo_fromANI(ani_env* env, ani_object ani_obj);
ani_object ohos_data_unifiedDataChannel_ProgressInfo_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::ProgressInfo const& cpp_obj);
