# UDMF - Agent 指令

UDMF 为 OpenHarmony 提供跨应用、跨设备、跨运行时的统一数据定义与数据访问通路。本文档是 Agent 行为护栏，不是项目 README。

## 核心原则

- 用户只要求调研、检视或对比时，禁止直接实现；必须等用户明确要求改代码。`[S1]`
- 优先选择最小改动，并保持 InnerKit、NAPI、NDK、CJ、Taihe 的 API 兼容。`[E4,C1]`
- 引用构建或测试命令前，必须从 `BUILD.gn` 核对真实目标名。`[E5]`
- `AGENTS.md` 只记录 Agent 无法从代码推导出的约束；长解释应沉淀到 `docs/`。`[C2]`

## 仓库指引

| 项目 | 内容 |
|---|---|
| 主要语言 | C++、C、ArkTS/ETS、JavaScript 绑定代码、JSON、GN |
| 构建系统 | OpenHarmony `./build.sh` 驱动 GN |
| 包管理器 | 本组件无独立包管理器；依赖来自 OpenHarmony bundle 组件 |
| 组件信息 | `@ohos/udmf`，版本 `4.0`，子系统 `distributeddatamgr` |
| 对外接口层 | InnerKit、NAPI、NDK、CJ FFI、Taihe/ANI |

关键依赖：

| 依赖 | 用途 |
|---|---|
| `ipc` / `samgr` | UDMF 服务发现与跨进程调用 |
| `access_token` / `bundle_framework` | 调用方身份、权限与包信息校验 |
| `kv_store` / `dfs_service` | 分布式数据存储与文件服务集成 |
| `napi` / `runtime_core` / `ets_frontend` | JS/ArkTS API 暴露与运行时集成 |
| `image_framework` | PixelMap 与图片类系统定义记录 |
| `hilog` / `hisysevent` / `hitrace` / `api_metrics` | 日志、事件、跟踪与 API 指标 |
| `cJSON` / `json` / `libxml2` | UTD 配置、JSON 与 XML 解析 |
| `libuv` | NAPI 异步任务调度 |

构建与测试命令：

| 命令 | 用途 | 备注 |
|---|---|---|
| `./build.sh --product-name <product> --build-target udmf_packages` | 构建 UDMF 包 | 根 `BUILD.gn` 目标 |
| `./build.sh --product-name <product> --build-target unittest` | 构建全部单元测试 | 聚合 common、InnerKit、JSKit、NDK 测试 |
| `./build.sh --product-name <product> --build-target fuzztest` | 构建全部 fuzz 测试 | 聚合 common、InnerKit、NDK fuzz 测试 |
| `./build.sh --product-name <product> --build-target <gn_target>` | 构建单个目标 | 先确认最近的 `BUILD.gn` 中存在该目标 |

NEVER 在 Agent 会话中运行宽泛的 OpenHarmony 产品级全量构建，除非用户明确要求承担该成本。

单元测试约定：

| 项目 | 规则 |
|---|---|
| 测试框架 | Google Test，使用 `HWTEST_F` 与 `testing::ext` |
| 文件命名 | 测试文件以 `_test.cpp` 结尾 |
| 存放目录 | `framework/*/test/unittest/`，JS stage 测试位于 `framework/jskitsimpl/test/` |
| Mock 目录 | 使用本地 `mock/` 目录，按被 mock 组件命名，如 `message_parcel_mock.*` |
| 单目标测试 | 构建最近的 GN 测试目标，再在 OpenHarmony 输出目录运行生成的二进制 |
| TDD | RED：先写或调整测试并 MUST 看到失败；GREEN：最小实现；IMPROVE：不改行为地重构 |

## CI 要求

本组件目录下没有独立 `.github/`、`.gitcode/` 或 `.gitee/` CI workflow。OpenHarmony 集成构建以 `bundle.json`、根 `BUILD.gn` 与各级 `BUILD.gn` 为准。

| 门禁 | 本地等价命令 |
|---|---|
| 包构建 | `./build.sh --product-name <product> --build-target udmf_packages` |
| 单元测试 | `./build.sh --product-name <product> --build-target unittest` |
| Fuzz 测试 | `./build.sh --product-name <product> --build-target fuzztest` |
| 文档空白检查 | `git diff --check -- <paths>` |

提交代码前，先跑受影响的最小目标，再跑上表中相关聚合目标。

## 环境变量

本组件没有 UDMF 专属环境变量。

| 名称 | 必需 | 用途 | 示例值 | 来源 |
|---|---|---|---|---|
| `<product>` | 是 | 传给 `./build.sh --product-name` 的产品占位符 | `rk3568` | OpenHarmony 工作区或产品选择 |

NEVER 在本文档中写入密钥、Token、真实服务端点或生产专用变量。`[C4]`

## 探索总结

### 数据对象改动影响面

- 问题：修改 `UnifiedData` 或 `UnifiedRecord` 时要检查哪些层？
- 结论：必须同时检查 InnerKit 头/实现、NAPI 转换、NDK wrapper、CJ、Taihe、TLV 与单元测试。
- 关键路径：`interfaces/innerkits/data/`、`framework/innerkitsimpl/data/`、`framework/jskitsimpl/data/`、`framework/ndkimpl/data/`、`interfaces/cj/`、`interfaces/taihe/`。
- 失效条件：任一对外 API 层被删除、重命名或拆分。

### UTD 类型改动影响面

- 问题：UTD 类型定义从哪里流到公共查询 API？
- 结论：内置类型从 `conf/uniform_data_types.json` 出发，经过 UTD 解析、图检查、`TypeDescriptor` 与公开查询 API。
- 关键路径：`conf/uniform_data_types.json`、`framework/common/utd_*`、`interfaces/innerkits/data/type_descriptor.h`、`framework/innerkitsimpl/client/utd_client.cpp`。
- 失效条件：UTD 配置存储或解析器重构。

## 踩坑记录

| 现象 | 根因 | 反模式 | 正确写法 | 引入时机 |
|---|---|---|---|---|
| 构建目标名被编造 | Agent 凭记忆而不是读 `BUILD.gn` | NEVER 在核对前引用构建目标 | 读取最近的 `BUILD.gn` 后使用真实目标名 | 任何构建/测试命令变更 |
| 某一接口层能编译，其他接口层破坏 | UDMF 有多套公开绑定 | NEVER 只改一层核心数据形状 | 同时追踪 InnerKit、NAPI、NDK、CJ、Taihe | 数据模型或公开 API 变更 |
| TLV 读写大小不一致 | 只改了序列化单向逻辑 | NEVER 只改 TLV 写逻辑 | 同一补丁内修改写、读、size 计算和测试 | TLV 字段或 tag 变更 |

## 编码约定

- 不可变性：除非方法名或既有契约明确表示会修改，否则不要跨 API 边界修改调用方对象。`[C2]`
- 规模：新增函数控制在 80 行内；仅当抽取函数有稳定职责和可测试边界时才拆分。`[C2,E4]`
- 错误处理：公共 API 返回既有 `Status` 或 C 错误码；不要向非异常路径引入异常。`[C2]`
- 日志：需要打日志的 `.cpp` 定义 `LOG_TAG`；禁止打印原始 URI、bundle 敏感信息、设备、账号、Token、文件路径。`[C4]`
- 命名：沿用 PascalCase 方法/类、尾下划线成员变量、全大写下划线常量。`[C2]`
- 导出：公共 C++ 符号使用 `API_EXPORT`；C、NAPI、CJ、Taihe 导出必须跟随本目录既有模式。`[C2]`
- 配置：UTD typeId、MIME 类型和文件扩展名应复用配置或既有常量，禁止散落重复字符串。`[E5]`

## 反模式

语法级：

- NEVER 只在一个绑定层新增公开 API，而等价概念已存在于其他绑定层。
- NEVER 新增源文件但不更新最近的 `BUILD.gn`。
- NEVER 对外部裸指针使用 `std::shared_ptr<T>(rawPtr)`；应使用既有所有权辅助函数或工厂模式。
- NEVER 在 NAPI/ANI/FFI 转换路径留下空错误分支或空 `catch`。
- NEVER 硬编码产品名、输出目录、用户路径、凭据或私有端点。

认知级：

- NEVER 在没有新鲜命令输出时声称构建或测试通过。`[E1]`
- NEVER 在用户只要求分析或 review 时直接实现。`[S1]`
- NEVER 编造类名、GN 目标、API 签名或配置路径。`[E5]`
- NEVER 对有风险的请求静默同意；必须说明风险并选择更安全路径。`[S4,C4]`
- NEVER 在为行为变更补测试时跳过 RED 步骤。`[E1]`

合理化对照表：

| Agent 借口 | 现实 |
|---|---|
| "这只是很小的 API 改动。" | UDMF 有五类公开绑定层，小的核心改动也可能破坏其中一层。 |
| "目标名很明显。" | 根 `BUILD.gn` 才是真实来源。 |
| "文档不需要验证。" | Markdown 也必须跑 `git diff --check` 并核对命令和路径事实。 |
| "我可以先更新 AGENTS.md。" | 本文件记录代码事实，不记录愿望清单。 |

## 内部模块依赖

| 模块 | 能力 | 依赖 | 被谁依赖 |
|---|---|---|---|
| `conf` | 内置 UTD 声明 | JSON 配置安装规则 | UTD 解析器和类型查询 |
| `framework/common` | TLV、UTD 图、工具、日志辅助能力 | OpenHarmony 公共库 | InnerKit、JSKit、NDK、测试 |
| `interfaces/innerkits` | C++ 公共声明 | common 头文件和可见性规则 | InnerKit 实现、NAPI、NDK、CJ、Taihe |
| `framework/innerkitsimpl` | 核心客户端、服务、数据实现 | common、IPC、权限、存储、动态 wrapper | 公开客户端和绑定层 |
| `framework/jskitsimpl` | NAPI 实现 | InnerKit API、NAPI runtime、异步队列 | JS 模块 |
| `framework/ndkimpl` | C API 实现 | InnerKit 转换和 C ABI wrapper | NDK 使用方 |
| `interfaces/cj` | CJ FFI 绑定 | InnerKit 和转换工具 | CJ 使用方 |
| `interfaces/taihe` | Taihe/ANI 绑定 | InnerKit、ANI/Taihe runtime helper | Taihe 使用方 |
| `adapter` | 平台适配 | 平台服务 | 核心实现 |

当前未记录有意设计的循环依赖。若发现循环依赖，先创建 issue 并在此记录，再继续扩大依赖。

## 外部依赖

| 组件 | 用途 | 版本范围 | 关键路径 | 降级策略 |
|---|---|---|---|---|
| OpenHarmony IPC/SAMGR | 服务调用与发现 | 平台提供 | 是 | 无降级 |
| AccessToken/Bundle Manager | 权限与调用方元数据 | 平台提供 | 是 | 返回既有权限或状态错误 |
| KV Store/DFS/App File Service | 数据与文件后端服务 | 平台提供 | 是 | 返回存储或文件错误 |
| NAPI/ETS Runtime | JS/ArkTS 绑定 | 平台提供 | JS API 关键路径 | Native API 保持可用 |
| Image Framework | PixelMap 和图片记录 | 平台提供 | 部分关键 | 非图片记录不受影响 |
| HiLog/HiSysEvent/HiTrace/API Metrics | 可观测性 | 平台提供 | 否 | 功能继续运行但诊断能力下降 |
| cJSON/json/libxml2 | 配置和结构化数据解析 | 平台提供 | 相关解析关键路径 | 返回解析或配置错误 |
| MCP Server | 本仓不要求 | N/A | 否 | N/A |

## 文档索引

新增核心文档时应放入 `docs/`。当前高频仓库文档如下：

| 路径 | 标题 | 加载场景 | 稳定性 |
|---|---|---|---|
| `README_zh.md` | UDMF 概览与架构 | 需要产品背景或目录概览 | 稳定 |
| `bundle.json` | 组件元数据和构建/测试注册 | 检查依赖、导出 kits 或聚合目标 | 中等 |
| `BUILD.gn` | 根 GN 目标 | 命名包、单测或 fuzz 构建目标 | 稳定 |
| `conf/uniform_data_types.json` | 内置 UTD 声明 | 修改类型描述、MIME 映射或扩展名 | 中等 |
| `.gitee/PULL_REQUEST_TEMPLATE.zh-CN.md` | PR 检查清单 | 创建或更新 GitCode PR 正文 | 稳定 |

新增、删除或重命名文档时，必须在同一 PR 中更新本索引。
