#include "ohos.data.uniformTypeDescriptor.ani.hpp"
#include "ohos.data.uniformTypeDescriptor.user.hpp"
static ani_string ohos_data_uniformTypeDescriptor_getUniformDataTypeByFilenameExtension_ANIFunc([[maybe_unused]] ani_env *env, ani_string ani_arg_filenameExtension, ani_ref ani_arg_belongsTo) {
    ani_size cpp_arg_filenameExtension_len;
    env->String_GetUTF8Size(ani_arg_filenameExtension, &cpp_arg_filenameExtension_len);
    TString cpp_arg_filenameExtension_tstr;
    char* cpp_arg_filenameExtension_buf = tstr_initialize(&cpp_arg_filenameExtension_tstr, cpp_arg_filenameExtension_len + 1);
    env->String_GetUTF8(ani_arg_filenameExtension, cpp_arg_filenameExtension_buf, cpp_arg_filenameExtension_len + 1, &cpp_arg_filenameExtension_len);
    cpp_arg_filenameExtension_buf[cpp_arg_filenameExtension_len] = '\0';
    cpp_arg_filenameExtension_tstr.length = cpp_arg_filenameExtension_len;
    ::taihe::string cpp_arg_filenameExtension = ::taihe::string(cpp_arg_filenameExtension_tstr);
    ani_boolean cpp_arg_belongsTo_flag;
    ::taihe::string* cpp_arg_belongsTo_ptr = nullptr;
    env->Reference_IsUndefined(ani_arg_belongsTo, &cpp_arg_belongsTo_flag);
    if (!cpp_arg_belongsTo_flag) {
        ani_size cpp_arg_belongsTo_spec_len;
        env->String_GetUTF8Size(static_cast<ani_string>(ani_arg_belongsTo), &cpp_arg_belongsTo_spec_len);
        TString cpp_arg_belongsTo_spec_tstr;
        char* cpp_arg_belongsTo_spec_buf = tstr_initialize(&cpp_arg_belongsTo_spec_tstr, cpp_arg_belongsTo_spec_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(ani_arg_belongsTo), cpp_arg_belongsTo_spec_buf, cpp_arg_belongsTo_spec_len + 1, &cpp_arg_belongsTo_spec_len);
        cpp_arg_belongsTo_spec_buf[cpp_arg_belongsTo_spec_len] = '\0';
        cpp_arg_belongsTo_spec_tstr.length = cpp_arg_belongsTo_spec_len;
        ::taihe::string cpp_arg_belongsTo_spec = ::taihe::string(cpp_arg_belongsTo_spec_tstr);
        cpp_arg_belongsTo_ptr = new ::taihe::string(std::move(cpp_arg_belongsTo_spec));
    };
    ::taihe::optional<::taihe::string> cpp_arg_belongsTo(cpp_arg_belongsTo_ptr);
    ::taihe::string cpp_result = ::ohos::data::uniformTypeDescriptor::getUniformDataTypeByFilenameExtension(cpp_arg_filenameExtension, cpp_arg_belongsTo);
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
namespace ohos::data::uniformTypeDescriptor {
ani_status ANIRegister(ani_env *env) {
    if (::taihe::get_vm() == nullptr) {
        ani_vm *vm;
        if (ANI_OK != env->GetVM(&vm)) {
            return ANI_ERROR;
        }
        ::taihe::set_vm(vm);
    }
    {
        ani_namespace ani_env;
        if (ANI_OK != env->FindNamespace("L@ohos/data/uniformTypeDescriptor/uniformTypeDescriptor;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"getUniformDataTypeByFilenameExtension_inner", nullptr, reinterpret_cast<void*>(ohos_data_uniformTypeDescriptor_getUniformDataTypeByFilenameExtension_ANIFunc)},
        };
        if (ANI_OK != env->Namespace_BindNativeFunctions(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    return ANI_OK;
}
}
