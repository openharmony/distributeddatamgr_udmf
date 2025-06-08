#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.Audio.proj.0.hpp"
::ohos::data::unifiedDataChannel::Audio ohos_data_unifiedDataChannel_Audio_fromANI(ani_env* env, ani_object ani_obj);
ani_object ohos_data_unifiedDataChannel_Audio_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::Audio cpp_obj);
