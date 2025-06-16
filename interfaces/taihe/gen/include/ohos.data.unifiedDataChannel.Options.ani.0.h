#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.Options.proj.0.hpp"
::ohos::data::unifiedDataChannel::Options ohos_data_unifiedDataChannel_Options_fromANI(ani_env* env, ani_object ani_obj);
ani_object ohos_data_unifiedDataChannel_Options_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::Options const& cpp_obj);
