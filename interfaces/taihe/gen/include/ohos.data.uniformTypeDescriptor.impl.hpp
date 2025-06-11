#pragma once
#include "taihe/common.hpp"
#include "ohos.data.uniformTypeDescriptor.abi.h"
#include "taihe/string.hpp"
#include "taihe/optional.hpp"
#define TH_EXPORT_CPP_API_getUniformDataTypeByFilenameExtension(CPP_FUNC_IMPL) \
    struct TString ohos_data_uniformTypeDescriptor_getUniformDataTypeByFilenameExtension_f(struct TString filenameExtension, struct TOptional belongsTo) { \
        return ::taihe::into_abi<::taihe::string>(CPP_FUNC_IMPL(::taihe::from_abi<::taihe::string_view>(filenameExtension), ::taihe::from_abi<::taihe::optional_view<::taihe::string>>(belongsTo))); \
    }
