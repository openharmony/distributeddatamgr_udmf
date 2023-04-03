# UDMF 统一数据管理框架

## 简介
**统一数据管理框架（Unified Data Management Framework，UDMF）代码仓。**

## 目录
```
foundation/distributeddatamgr/udmf  # udmf统一数据管理部件
├── frameworks                      # udmf的核心逻辑
│   ├── common                      # 公共工具
│   ├── core                        # 核心逻辑
│   ├── dbadapter                   # 对接db
│   ├── innerkitsimpl               # nativie接口具体实现
│   │   ├── client                  # native客户端
│   │   ├── common                  # native接口公共工具类
│   │   └── data                    # 数据结构定义
│   ├── jskitsimpl                  # public接口具体实现
│   │   ├── common                  # public接口公共工具类
│   │   ├── data                    # 统一数据公共接口实现
│   │   └── module                  # 统一数据模块注册
│   ├── manager                     # 数据管理核心类
│   │   ├── container               # 数据容器
│   │   ├── store                   # 存储策略
│   │   └── preprocess              # 预处理
│   ├── service                     # 预处理模块
│   ├── task                        # 任务调度
│   ├── tlv                         # tlv工具
├── interfaces                      # udmf对外接口声明
│   ├── innerkits                   # nativie接口声明
│   │   ├── client                  # client接口声明
│   │   ├── common                  # 公共工具类声明
│   │   ├── data                    # 数据结构声明
│   │   └── test                    # 测试目录（XTS，待补充）
│   └── jskits                      # napi接口声明
│       ├── common                  # napi工具类声明
│       ├── data                    # napi数据封装声明
│       └── test                    # 测试目录（TDD，待补充）
├── service                         # udmf服务框架代码
│   ├── include                     # 服务端声明
│   └── src                         # 服务端具体实现
├── test                            # 测试目录（Fuzz，待补充）
├── BUILD.gn                        # 编译配置文件
├── bundle.json                     # 模块配置文件
└── udmf.gni                        # 编译配置头文件
```

## 使用说明
1. 数据定义
2. 接口定义
3. 使用指导

## 相关仓
