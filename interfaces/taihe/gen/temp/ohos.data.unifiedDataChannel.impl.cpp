#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "taihe/runtime.hpp"
#include "stdexcept"


namespace {
// To be implemented.

class UnifiedDataInnerImpl {
    public:
    UnifiedDataInnerImpl() {
        // Don't forget to implement the constructor.
    }

    void AddRecord(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) {
        TH_THROW(std::runtime_error, "AddRecord not implemented");
    }

    ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> GetRecords() {
        TH_THROW(std::runtime_error, "GetRecords not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class UnifiedRecordInnerImpl {
    public:
    UnifiedRecordInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class FileInnerImpl {
    public:
    FileInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::string GetUri() {
        TH_THROW(std::runtime_error, "GetUri not implemented");
    }

    void SetUri(::taihe::string_view uri) {
        TH_THROW(std::runtime_error, "SetUri not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class FolderInnerImpl {
    public:
    FolderInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::string GetUri() {
        TH_THROW(std::runtime_error, "GetUri not implemented");
    }

    void SetUri(::taihe::string_view uri) {
        TH_THROW(std::runtime_error, "SetUri not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    ::taihe::string GetFolderUri() {
        TH_THROW(std::runtime_error, "GetFolderUri not implemented");
    }

    void SetFolderUri(::taihe::string_view folderUri) {
        TH_THROW(std::runtime_error, "SetFolderUri not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class AudioInnerImpl {
    public:
    AudioInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::string GetUri() {
        TH_THROW(std::runtime_error, "GetUri not implemented");
    }

    void SetUri(::taihe::string_view uri) {
        TH_THROW(std::runtime_error, "SetUri not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    ::taihe::string GetAudioUri() {
        TH_THROW(std::runtime_error, "GetAudioUri not implemented");
    }

    void SetAudioUri(::taihe::string_view audioUri) {
        TH_THROW(std::runtime_error, "SetAudioUri not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class VideoInnerImpl {
    public:
    VideoInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::string GetUri() {
        TH_THROW(std::runtime_error, "GetUri not implemented");
    }

    void SetUri(::taihe::string_view uri) {
        TH_THROW(std::runtime_error, "SetUri not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    ::taihe::string GetVideoUri() {
        TH_THROW(std::runtime_error, "GetVideoUri not implemented");
    }

    void SetVideoUri(::taihe::string_view videoUri) {
        TH_THROW(std::runtime_error, "SetVideoUri not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class ImageInnerImpl {
    public:
    ImageInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::string GetUri() {
        TH_THROW(std::runtime_error, "GetUri not implemented");
    }

    void SetUri(::taihe::string_view uri) {
        TH_THROW(std::runtime_error, "SetUri not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    ::taihe::string GetImageUri() {
        TH_THROW(std::runtime_error, "GetImageUri not implemented");
    }

    void SetImageUri(::taihe::string_view imageUri) {
        TH_THROW(std::runtime_error, "SetImageUri not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class TextInnerImpl {
    public:
    TextInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class HTMLInnerImpl {
    public:
    HTMLInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    void SetHtmlContent(::taihe::string_view htmlContent) {
        TH_THROW(std::runtime_error, "SetHtmlContent not implemented");
    }

    ::taihe::string GetHtmlContent() {
        TH_THROW(std::runtime_error, "GetHtmlContent not implemented");
    }

    void SetPlainContent(::taihe::string_view plainContent) {
        TH_THROW(std::runtime_error, "SetPlainContent not implemented");
    }

    ::taihe::string GetPlainContent() {
        TH_THROW(std::runtime_error, "GetPlainContent not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class HyperlinkInnerImpl {
    public:
    HyperlinkInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    void SetUrl(::taihe::string_view url) {
        TH_THROW(std::runtime_error, "SetUrl not implemented");
    }

    ::taihe::string GetUrl() {
        TH_THROW(std::runtime_error, "GetUrl not implemented");
    }

    void SetDescription(::taihe::string_view description) {
        TH_THROW(std::runtime_error, "SetDescription not implemented");
    }

    ::taihe::string GetDescription() {
        TH_THROW(std::runtime_error, "GetDescription not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class PlainTextInnerImpl {
    public:
    PlainTextInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    void SetTextContent(::taihe::string_view textContent) {
        TH_THROW(std::runtime_error, "SetTextContent not implemented");
    }

    ::taihe::string GetTextContent() {
        TH_THROW(std::runtime_error, "GetTextContent not implemented");
    }

    void SetAbstract1(::taihe::string_view abstract1) {
        TH_THROW(std::runtime_error, "SetAbstract1 not implemented");
    }

    ::taihe::string GetAbstract1() {
        TH_THROW(std::runtime_error, "GetAbstract1 not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class SystemDefinedRecordInnerImpl {
    public:
    SystemDefinedRecordInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class SystemDefinedFormInnerImpl {
    public:
    SystemDefinedFormInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    double GetFormId() {
        TH_THROW(std::runtime_error, "GetFormId not implemented");
    }

    void SetFormId(double formId) {
        TH_THROW(std::runtime_error, "SetFormId not implemented");
    }

    ::taihe::string GetFormName() {
        TH_THROW(std::runtime_error, "GetFormName not implemented");
    }

    void SetFormName(::taihe::string_view formName) {
        TH_THROW(std::runtime_error, "SetFormName not implemented");
    }

    ::taihe::string GetBundleName() {
        TH_THROW(std::runtime_error, "GetBundleName not implemented");
    }

    void SetBundleName(::taihe::string_view bundleName) {
        TH_THROW(std::runtime_error, "SetBundleName not implemented");
    }

    ::taihe::string GetAbilityName() {
        TH_THROW(std::runtime_error, "GetAbilityName not implemented");
    }

    void SetAbilityName(::taihe::string_view abilityName) {
        TH_THROW(std::runtime_error, "SetAbilityName not implemented");
    }

    ::taihe::string GetModule() {
        TH_THROW(std::runtime_error, "GetModule not implemented");
    }

    void SetModule(::taihe::string_view module) {
        TH_THROW(std::runtime_error, "SetModule not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class SystemDefinedAppItemInnerImpl {
    public:
    SystemDefinedAppItemInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    ::taihe::string GetAppId() {
        TH_THROW(std::runtime_error, "GetAppId not implemented");
    }

    void SetAppId(::taihe::string_view appId) {
        TH_THROW(std::runtime_error, "SetAppId not implemented");
    }

    ::taihe::string GetAppName() {
        TH_THROW(std::runtime_error, "GetAppName not implemented");
    }

    void SetAppName(::taihe::string_view appName) {
        TH_THROW(std::runtime_error, "SetAppName not implemented");
    }

    ::taihe::string GetAppIconId() {
        TH_THROW(std::runtime_error, "GetAppIconId not implemented");
    }

    void SetAppIconId(::taihe::string_view appIconId) {
        TH_THROW(std::runtime_error, "SetAppIconId not implemented");
    }

    ::taihe::string GetAppLabelId() {
        TH_THROW(std::runtime_error, "GetAppLabelId not implemented");
    }

    void SetAppLabelId(::taihe::string_view appLabelId) {
        TH_THROW(std::runtime_error, "SetAppLabelId not implemented");
    }

    ::taihe::string GetBundleName() {
        TH_THROW(std::runtime_error, "GetBundleName not implemented");
    }

    void SetBundleName(::taihe::string_view bundleName) {
        TH_THROW(std::runtime_error, "SetBundleName not implemented");
    }

    ::taihe::string GetAbilityName() {
        TH_THROW(std::runtime_error, "GetAbilityName not implemented");
    }

    void SetAbilityName(::taihe::string_view abilityName) {
        TH_THROW(std::runtime_error, "SetAbilityName not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

class SystemDefinedPixelMapInnerImpl {
    public:
    SystemDefinedPixelMapInnerImpl() {
        // Don't forget to implement the constructor.
    }

    ::taihe::string GetType() {
        TH_THROW(std::runtime_error, "GetType not implemented");
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue() {
        TH_THROW(std::runtime_error, "GetValue not implemented");
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() {
        TH_THROW(std::runtime_error, "GetDetails not implemented");
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) {
        TH_THROW(std::runtime_error, "SetDetails not implemented");
    }

    ::taihe::optional<::taihe::array<uint8_t>> GetRawData() {
        TH_THROW(std::runtime_error, "GetRawData not implemented");
    }

    void SetRawData(::taihe::array_view<uint8_t> rawData) {
        TH_THROW(std::runtime_error, "SetRawData not implemented");
    }

    int64_t GetInner() {
        TH_THROW(std::runtime_error, "GetInner not implemented");
    }
};

::ohos::data::unifiedDataChannel::Summary CreateSummary() {
    TH_THROW(std::runtime_error, "CreateSummary not implemented");
}

::ohos::data::unifiedDataChannel::UnifiedDataInner CreateUnifiedData() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<UnifiedDataInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedDataInner>();
}

::ohos::data::unifiedDataChannel::UnifiedDataInner CreateUnifiedDataWithParams(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<UnifiedDataInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedDataInner>();
}

::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecord() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<UnifiedRecordInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedRecordInner>();
}

::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecordWithParams(::taihe::string_view type, ::ohos::data::unifiedDataChannel::ValueType const& value) {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<UnifiedRecordInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedRecordInner>();
}

::ohos::data::unifiedDataChannel::FileInner CreateUnifiedFile() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<FileInnerImpl, ::ohos::data::unifiedDataChannel::FileInner>();
}

::ohos::data::unifiedDataChannel::FolderInner CreateUnifiedFolder() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<FolderInnerImpl, ::ohos::data::unifiedDataChannel::FolderInner>();
}

::ohos::data::unifiedDataChannel::AudioInner CreateUnifiedAudio() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<AudioInnerImpl, ::ohos::data::unifiedDataChannel::AudioInner>();
}

::ohos::data::unifiedDataChannel::VideoInner CreateUnifiedVideo() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<VideoInnerImpl, ::ohos::data::unifiedDataChannel::VideoInner>();
}

::ohos::data::unifiedDataChannel::ImageInner CreateUnifiedImage() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<ImageInnerImpl, ::ohos::data::unifiedDataChannel::ImageInner>();
}

::ohos::data::unifiedDataChannel::TextInner CreateText() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<TextInnerImpl, ::ohos::data::unifiedDataChannel::TextInner>();
}

::ohos::data::unifiedDataChannel::HTMLInner CreateHtml() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<HTMLInnerImpl, ::ohos::data::unifiedDataChannel::HTMLInner>();
}

::ohos::data::unifiedDataChannel::HyperlinkInner CreateHyperlink() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<HyperlinkInnerImpl, ::ohos::data::unifiedDataChannel::HyperlinkInner>();
}

::ohos::data::unifiedDataChannel::PlainTextInner CreatePlainText() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<PlainTextInnerImpl, ::ohos::data::unifiedDataChannel::PlainTextInner>();
}

::ohos::data::unifiedDataChannel::SystemDefinedRecordInner CreateSystemDefinedRecord() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedRecordInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner>();
}

::ohos::data::unifiedDataChannel::SystemDefinedFormInner CreateSystemDefinedForm() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedFormInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedFormInner>();
}

::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner CreateSystemDefinedAppItem() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedAppItemInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner>();
}

::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner CreateSystemDefinedPixelMap() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedPixelMapInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner>();
}

::taihe::string InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options, ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner data) {
    TH_THROW(std::runtime_error, "InsertDataSync not implemented");
}

::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner> QueryDataSync(::ohos::data::unifiedDataChannel::Options const& options) {
    TH_THROW(std::runtime_error, "QueryDataSync not implemented");
}
}  // namespace

// Since these macros are auto-generate, lint will cause false positive.
// NOLINTBEGIN
TH_EXPORT_CPP_API_CreateSummary(CreateSummary);
TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);
TH_EXPORT_CPP_API_CreateUnifiedRecord(CreateUnifiedRecord);
TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CreateUnifiedRecordWithParams);
TH_EXPORT_CPP_API_CreateUnifiedFile(CreateUnifiedFile);
TH_EXPORT_CPP_API_CreateUnifiedFolder(CreateUnifiedFolder);
TH_EXPORT_CPP_API_CreateUnifiedAudio(CreateUnifiedAudio);
TH_EXPORT_CPP_API_CreateUnifiedVideo(CreateUnifiedVideo);
TH_EXPORT_CPP_API_CreateUnifiedImage(CreateUnifiedImage);
TH_EXPORT_CPP_API_CreateText(CreateText);
TH_EXPORT_CPP_API_CreateHtml(CreateHtml);
TH_EXPORT_CPP_API_CreateHyperlink(CreateHyperlink);
TH_EXPORT_CPP_API_CreatePlainText(CreatePlainText);
TH_EXPORT_CPP_API_CreateSystemDefinedRecord(CreateSystemDefinedRecord);
TH_EXPORT_CPP_API_CreateSystemDefinedForm(CreateSystemDefinedForm);
TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(CreateSystemDefinedAppItem);
TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(CreateSystemDefinedPixelMap);
TH_EXPORT_CPP_API_InsertDataSync(InsertDataSync);
TH_EXPORT_CPP_API_QueryDataSync(QueryDataSync);
// NOLINTEND
