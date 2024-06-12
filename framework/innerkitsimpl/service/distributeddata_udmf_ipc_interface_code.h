/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DISTRIBUTEDDATA_UDMF_IPC_INTERFACE_CODE_H
#define DISTRIBUTEDDATA_UDMF_IPC_INTERFACE_CODE_H

/* SAID:1301 FeatureSystem:udmf_service */
namespace OHOS::UDMF {
enum class UdmfServiceInterfaceCode : uint32_t {
    CODE_HEAD = 0,
    SET_DATA = CODE_HEAD,
    GET_DATA,
    GET_BATCH_DATA,
    UPDATE_DATA,
    DELETE_DATA,
    GET_SUMMARY,
    ADD_PRIVILEGE,
    SYNC,
    IS_REMOTE_DATA,
    SET_APP_SHARE_OPTION,
    GET_APP_SHARE_OPTION,
    REMOVE_APP_SHARE_OPTION,
    CODE_BUTT
};
} // namespace OHOS::UDMF
#endif // DISTRIBUTEDDATA_UDMF_IPC_INTERFACE_CODE_H