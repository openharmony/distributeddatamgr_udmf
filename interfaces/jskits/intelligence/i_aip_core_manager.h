/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef I_AIP_CORE_MANAGER_H
#define I_AIP_CORE_MANAGER_H

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

namespace OHOS {
namespace DataIntelligence {
struct ModelConfigData {
    int32_t versionValue;
    bool isNPUAvailableValue;
    std::string cachePathValue;
};

using Blob = std::vector<uint8_t>;
using Bigint = std::vector<uint64_t>;
using FloatVector = std::vector<float>;
using FieldType = std::variant<int64_t, int32_t, double, std::string, bool, Blob, Bigint, FloatVector>;
struct ChannelConfigStruct {
    int32_t channelType;
    std::string channelUri;
};

enum TsChannelType {
    VECTOR_DATABASE = 0,
    INVERTED_INDEX_DATABASE,
};

enum StrategyType {
    BM25 = 0,
    EXACT_MATCH,
    OUT_OF_ORDER_MATCH
};

struct RetrievalConfigStruct {
    std::vector<ChannelConfigStruct> channelConfigs;
};

struct InvertedIndexStrategyStruct {
    std::map<std::string, float> fieldWeight;
    virtual StrategyType GetStrategy() = 0;
    virtual ~InvertedIndexStrategyStruct() = default;
};

struct Bm25StrategyStruct : public InvertedIndexStrategyStruct {
    float bm25Weight;
    StrategyType GetStrategy() override
    {
        return StrategyType::BM25;
    }
    ~Bm25StrategyStruct() override = default;
};

struct ExactMatchingStrategyStruct : public InvertedIndexStrategyStruct {
    float exactMatchingWeight;
    StrategyType GetStrategy() override
    {
        return StrategyType::EXACT_MATCH;
    }
    ~ExactMatchingStrategyStruct() override = default;
};

struct OutOfOrderStrategyStruct : public InvertedIndexStrategyStruct {
    float outOfOrderWeight;
    std::map<std::string, int> fieldSlops;
    StrategyType GetStrategy() override
    {
        return StrategyType::OUT_OF_ORDER_MATCH;
    }
    ~OutOfOrderStrategyStruct() override = default;
};

enum TsOperator {
    OP_EQ = 0,
    OP_NE,
    OP_LT,
    OP_LE,
    OP_GE,
    OP_GT,
    OP_IN,
    OP_NOT_IN,
    OP_BETWEEN,
    OP_LIKE,
    OP_NOT_LIKE,
    BUTT
};

struct FilterInfoStruct {
    std::string field;
    std::vector<std::string> fields;
    TsOperator op;
    std::string value;
    std::pair<std::string, std::string> range;
};

struct RecallConditionStruct {
    std::string fromClause;
    std::vector<std::string> primaryKey;
    std::vector<std::string> responseColumns;
    std::vector<FilterInfoStruct> filters;
    std::string recallName;
    int32_t deepSize;
    virtual TsChannelType GetChannelType() = 0;
    virtual ~RecallConditionStruct() = default;
};

struct InvertedIndexRecallConditionStruct: public RecallConditionStruct {
    std::string ftsTableName;
    std::vector<std::shared_ptr<InvertedIndexStrategyStruct>> invertedIndexStrategies;
    TsChannelType GetChannelType() override
    {
        return TsChannelType::INVERTED_INDEX_DATABASE;
    }
    ~InvertedIndexRecallConditionStruct() override = default;
};

struct VectorQueryStruct {
    std::string vectorColumn;
    std::vector<float> vectorValue;
    double similarityThreshold = 1;
};

struct VectorRecallConditionStruct : public RecallConditionStruct {
    VectorQueryStruct vectorQuery;
    TsChannelType GetChannelType() override
    {
        return TsChannelType::VECTOR_DATABASE;
    }
};

struct ChannelRerankParamsStruct {
    std::map<std::string, double> recallWeights;
    virtual TsChannelType GetChannelType() = 0;
    virtual ~ChannelRerankParamsStruct() = default;
};

struct InvertedIndexRerankParamsStruct : public ChannelRerankParamsStruct {
    TsChannelType GetChannelType() override
    {
        return TsChannelType::INVERTED_INDEX_DATABASE;
    }
    ~InvertedIndexRerankParamsStruct() override = default;
};

struct VectorChannelRerankParamsStruct : public ChannelRerankParamsStruct {
    std::vector<double> rankLevelThresholds;
    std::map<std::string, std::string> numberFilterCheckFields;
    TsChannelType GetChannelType() override
    {
        return TsChannelType::VECTOR_DATABASE;
    }
    ~VectorChannelRerankParamsStruct() override = default;
};

enum TsRerankType {
    RRF = 0,
    FUSION_SCORE
};

struct RerankParamsStruct {
    int32_t rankType{TsRerankType::RRF};
    std::map<int32_t, std::shared_ptr<ChannelRerankParamsStruct>> channelParams;
    bool useScoreSoftmax{false};
};

struct RetrievalConditionStruct {
    std::string query;
    std::vector<std::shared_ptr<RecallConditionStruct>> recallConditions;
    RerankParamsStruct rerankParameter;
    int topN = 500;
};

struct RecallScoreStruct {
    double recallScore;
    bool isOriginal;
};

struct ItemInfoStruct {
    std::string primaryKey;
    double score;
    std::map<std::string, FieldType> fields;
    std::map<int32_t, std::map<std::string, RecallScoreStruct>> recallScores;
    std::map<std::string, double> features;
    int32_t similarityLevel;
};

struct RetrievalResponseStruct {
    std::vector<ItemInfoStruct> retrievalResults;
};

class IAipCoreManager {
public:
    IAipCoreManager() = default;
    virtual ~IAipCoreManager() = default;

    virtual int32_t InitRetriever(const RetrievalConfigStruct& retrievalConfig) = 0;
    virtual int32_t Retrieve(const RetrievalConditionStruct &condition, RetrievalResponseStruct &retrievalResponse) = 0;
    virtual int32_t InitTextModel(const ModelConfigData &config) = 0;
    virtual int32_t InitImageModel(const ModelConfigData &config) = 0;
    virtual int32_t LoadTextModel() = 0;
    virtual int32_t ReleaseTextModel() = 0;
    virtual int32_t GetTextEmbedding(std::string file, std::vector<float> &results) = 0;
    virtual int32_t GetTextEmbedding(const std::vector<std::string> &files,
        std::vector<std::vector<float>> &results) = 0;
    virtual int32_t LoadImageModel() = 0;
    virtual int32_t ReleaseImageModel() = 0;
    virtual int32_t GetImageEmbedding(std::string uri, std::vector<float> &results) = 0;
    virtual int32_t SplitText(std::string text, int32_t size, float overlap, std::vector<std::string> &results) = 0;
};

struct AipCoreManagerHandle {
    void *handle;
    IAipCoreManager *(*create)();
    void (*destroy)(const IAipCoreManager *);
    IAipCoreManager *pAipManager;
    AipCoreManagerHandle() : handle(nullptr), create(nullptr), destroy(nullptr), pAipManager(nullptr) {}
    ~AipCoreManagerHandle() {}
    void Clear()
    {
        handle = nullptr;
        create = nullptr;
        destroy = nullptr;
        pAipManager = nullptr;
    }
};
} // namespace DataIntelligence
} // namespace OHOS

#endif // I_AIP_CORE_MANAGER_H