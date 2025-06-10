#pragma once
#include "ani.h"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.0.hpp"
::ohos::data::unifiedDataChannel::AllRecords ohos_data_unifiedDataChannel_AllRecords_fromANI(ani_env* env, ani_ref ani_obj);
ani_ref ohos_data_unifiedDataChannel_AllRecords_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::AllRecords const& cpp_obj);
