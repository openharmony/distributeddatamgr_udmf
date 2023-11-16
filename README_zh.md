# 统一数据管理框架

## 简介
从数据管理角度出发，随着OpenHarmony中数据跨应用、跨设备流转场景和需求的不断增加，流转过程中会存在数据协同通道繁杂、数据协同标准不一致、数据协同安全策略不一致、应用适配复杂度高、开发工作量增多等诸多痛点问题。统一数据管理框架（Unified Data Management Framework, UDMF）旨在定义数据跨应用、跨设备以及跨平台过程中的各项标准，提供统一的OpenHarmony数据语言和标准化的数据接入与读取通路。

## 架构介绍
UDMF提供统一的OpenHarmony数据语言和标准化的数据接入与读取通路。

**统一的OpenHarmony数据语言：** 构建OpenHarmony数据跨应用、跨设备交互的标准定义，降低应用/业务数据交互成本，促进数据生态建设。

**标准化的数据接入与读取通路：** 提供安全、标准化的数据通路，降低业务跨应用、跨设备数据交互的成本。

UDMF的整体架构如图1所示，业务层对外提供标准化的数据定义和数据接入与读取的业务接口。统一数据管理框架层提供标准化数据定义和数据接入与读取的具体实现，同时负责管理数据的生命周期、安全性、权限和存储。存储模块层负责数据的具体保存，可以使用分布式KVDB、分布式数据对象和分布式RDB进行数据存储。

**图1** UDMF架构图

![架构图](figures/udmf_architecture.png)

### 标准化数据定义

UDMF提供了标准化的数据定义，统一定义了以下几种不同的数据类型。

**基础数据类型：** File、Text等，能够进行跨应用、跨设备以及跨平台流转。File、Text数据类型可见图2和图3，它们具有继承关系和层次结构，衍生出多种具体子类。

**图2** UDMF File数据类型示意图

![架构图](figures/udmf_type_File.png)

**图3** UDMF Text数据类型示意图

![架构图](figures/udmf_type_Text.png)

**系统相关数据类型（System Defined Type, SDT）：** 与具体的平台/操作系统绑定，如Form（UI卡片信息）、AppItem（App描述信息）、PixelMap（缩略图格式）等，该类数据可以实现系统/平台内的跨应用、跨设备流转，如图4所示。

**图4** UDMF SDT数据类型示意图

![架构图](figures/udmf_type_SDT.png)

**应用自定义数据类型（App Defined Type, ADT）：** 单个应用自定义的数据，该类数据可以实现应用内的跨平台与跨设备流转，如图5所示为例，应用可自定义MyFile类型文件格式在应用生态内部使用。

**图5** UDMF ADT数据类型示意图

![架构图](figures/udmf_type_ADT.png)

### 标准化数据通路

UDMF定义了标准化的数据接入与读取通路，为各种业务场景（如跨应用跨设备数据拖拽）提供了跨应用、跨设备的数据接入与读取通路，通路中的数据URI定义为udmf://intension/bundleName/groupName/guid，其中各组成部分的含义分别为：  
**udmf:** 协议名，表示使用UDMF提供的数据通路。  
**intension:** 通道分类，对应不同的业务场景（如数据拖拽）。  
**bundleName:** 数据来源应用的包名称。  
**groupName:** 分组名称，支持批量数据分组管理。  
**guid:** 系统生成的数据id，全局唯一。

## 约束限制

- UDMF中每条数据记录大小不超过2MB。
- UDMF支持批量数据记录的分组管理，每个分组整体大小不超过4MB。

## 目录

UDMF代码仓的目录结构和对应目录的功能描述如下：

```undefined
foundation/distributeddatamgr/udmf  # udmf统一数据管理部件
├── frameworks                      # udmf的核心逻辑
│   ├── common                      # 公共工具
│   ├── innerkitsimpl               # nativie接口具体实现
│   │   ├── client                  # native客户端
│   │   ├── common                  # native接口公共工具类
│   │   ├── data                    # 数据结构定义
│   │   ├── service                 # 服务模块
│   │   └── test                    # 测试目录
│   ├── jskitsimpl                  # js接口具体实现
│   │   ├── common                  # js接口公共工具类
│   │   |── data                    # 统一数据公共接口实现
|   |   └── unittest                # js单元测试目录
├── interfaces                      # udmf对外接口声明
│   ├── innerkits                   # nativie接口声明
│   │   ├── client                  # client接口声明
│   │   ├── common                  # 公共工具类声明
│   │   └── data                    # 数据结构声明
│   └── jskits                      # napi接口声明
│       ├── common                  # napi工具类声明
│       ├── data                    # napi数据封装声明
│       └── module                  # 统一数据模块注册
├── BUILD.gn                        # 编译配置文件
├── bundle.json                     # 模块配置文件
├── LICENSE                         # License文件
├── OAT.xml                         # OAT扫描策略
├── README_zh.md                    # Readme中文介绍
└── udmf.gni                        # 编译配置头文件
```
## 相关仓

- [分布式数据管理子系统](https://gitee.com/openharmony/docs/blob/master/zh-cn/readme/%E5%88%86%E5%B8%83%E5%BC%8F%E6%95%B0%E6%8D%AE%E7%AE%A1%E7%90%86%E5%AD%90%E7%B3%BB%E7%BB%9F.md)

- [**distributeddatamgr\_kv_store**](https://gitee.com/openharmony/distributeddatamgr_kv_store/blob/master/README_zh.md)