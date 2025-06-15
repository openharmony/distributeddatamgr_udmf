#include "ohos.data.uniformTypeDescriptor.proj.hpp"
#include "ohos.data.uniformTypeDescriptor.impl.hpp"
#include "taihe/runtime.hpp"
#include "stdexcept"


namespace {
// To be implemented.

::taihe::string getUniformDataTypeByFilenameExtension(::taihe::string_view filenameExtension, ::taihe::optional_view<::taihe::string> belongsTo) {
    TH_THROW(std::runtime_error, "getUniformDataTypeByFilenameExtension not implemented");
}
}  // namespace

// Since these macros are auto-generate, lint will cause false positive.
// NOLINTBEGIN
TH_EXPORT_CPP_API_getUniformDataTypeByFilenameExtension(getUniformDataTypeByFilenameExtension);
// NOLINTEND
