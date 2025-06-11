#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "taihe/runtime.hpp"
#include "stdexcept"


namespace {
// To be implemented.

class UnifiedDataImpl {
    public:
    UnifiedDataImpl() {
        // Don't forget to implement the constructor.
    }

    void AddRecord1(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) {
        TH_THROW(std::runtime_error, "AddRecord1 not implemented");
    }

    ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> GetRecords1() {
        TH_THROW(std::runtime_error, "GetRecords1 not implemented");
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

class FolderImpl {
    public:
    FolderImpl() {
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

class AudioImpl {
    public:
    AudioImpl() {
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

class VideoImpl {
    public:
    VideoImpl() {
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

class ImageImpl {
    public:
    ImageImpl() {
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

class TextImpl {
    public:
    TextImpl() {
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

class HTMLImpl {
    public:
    HTMLImpl() {
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

class HyperlinkImpl {
    public:
    HyperlinkImpl() {
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

class PlainTextImpl {
    public:
    PlainTextImpl() {
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

class SystemDefinedRecordImpl {
    public:
    SystemDefinedRecordImpl() {
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

class SystemDefinedFormImpl {
    public:
    SystemDefinedFormImpl() {
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

class SystemDefinedAppItemImpl {
    public:
    SystemDefinedAppItemImpl() {
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

class SystemDefinedPixelMapImpl {
    public:
    SystemDefinedPixelMapImpl() {
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

::ohos::data::unifiedDataChannel::UnifiedData CreateUnifiedData() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedData>();
}

::ohos::data::unifiedDataChannel::UnifiedData CreateUnifiedDataWithParams(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedData>();
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

::ohos::data::unifiedDataChannel::Folder CreateFolder() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<FolderImpl, ::ohos::data::unifiedDataChannel::Folder>();
}

::ohos::data::unifiedDataChannel::Audio CreateAudio() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<AudioImpl, ::ohos::data::unifiedDataChannel::Audio>();
}

::ohos::data::unifiedDataChannel::Video CreateVideo() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<VideoImpl, ::ohos::data::unifiedDataChannel::Video>();
}

::ohos::data::unifiedDataChannel::Image CreateImage() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<ImageImpl, ::ohos::data::unifiedDataChannel::Image>();
}

::ohos::data::unifiedDataChannel::Text CreateText() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<TextImpl, ::ohos::data::unifiedDataChannel::Text>();
}

::ohos::data::unifiedDataChannel::HTML CreateHtml() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<HTMLImpl, ::ohos::data::unifiedDataChannel::HTML>();
}

::ohos::data::unifiedDataChannel::Hyperlink CreateHyperlink() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<HyperlinkImpl, ::ohos::data::unifiedDataChannel::Hyperlink>();
}

::ohos::data::unifiedDataChannel::PlainText CreatePlainText() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<PlainTextImpl, ::ohos::data::unifiedDataChannel::PlainText>();
}

::ohos::data::unifiedDataChannel::SystemDefinedRecord CreateSystemDefinedRecord() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedRecordImpl, ::ohos::data::unifiedDataChannel::SystemDefinedRecord>();
}

::ohos::data::unifiedDataChannel::SystemDefinedForm CreateSystemDefinedForm() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedFormImpl, ::ohos::data::unifiedDataChannel::SystemDefinedForm>();
}

::ohos::data::unifiedDataChannel::SystemDefinedAppItem CreateSystemDefinedAppItem() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedAppItemImpl, ::ohos::data::unifiedDataChannel::SystemDefinedAppItem>();
}

::ohos::data::unifiedDataChannel::SystemDefinedPixelMap CreateSystemDefinedPixelMap() {
    // The parameters in the make_holder function should be of the same type
    // as the parameters in the constructor of the actual implementation class.
    return taihe::make_holder<SystemDefinedPixelMapImpl, ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap>();
}

void InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options, ::ohos::data::unifiedDataChannel::weak::UnifiedData data) {
    TH_THROW(std::runtime_error, "InsertDataSync not implemented");
}

::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData> QueryDataSync(::ohos::data::unifiedDataChannel::Options const& options) {
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
TH_EXPORT_CPP_API_CreateFolder(CreateFolder);
TH_EXPORT_CPP_API_CreateAudio(CreateAudio);
TH_EXPORT_CPP_API_CreateVideo(CreateVideo);
TH_EXPORT_CPP_API_CreateImage(CreateImage);
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
