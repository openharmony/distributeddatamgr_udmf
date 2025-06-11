#pragma once
#include "ohos.data.uniformTypeDescriptor.proj.hpp"
#include "taihe/common.hpp"
#include "ohos.data.uniformTypeDescriptor.abi.h"
#include "taihe/string.hpp"
#include "taihe/optional.hpp"
namespace ohos::data::uniformTypeDescriptor {
inline ::taihe::string getUniformDataTypeByFilenameExtension(::taihe::string_view filenameExtension, ::taihe::optional_view<::taihe::string> belongsTo) {
    return ::taihe::from_abi<::taihe::string>(ohos_data_uniformTypeDescriptor_getUniformDataTypeByFilenameExtension_f(::taihe::into_abi<::taihe::string_view>(filenameExtension), ::taihe::into_abi<::taihe::optional_view<::taihe::string>>(belongsTo)));
}
}
