#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.Summary.proj.0.hpp"
::ohos::data::unifiedDataChannel::Summary ohos_data_unifiedDataChannel_Summary_fromANI(ani_env* env, ani_object ani_obj);
ani_object ohos_data_unifiedDataChannel_Summary_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::Summary const& cpp_obj);
