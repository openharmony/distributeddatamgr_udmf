/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from 'deccjsunit/index';
import intelligence from '@ohos.data.intelligence';
import deviceInfo from '@ohos.deviceInfo';
import relationalStore from '@ohos.data.relationalStore';
import featureAbility from '@ohos.ability.featureAbility';

const TAG = '[AipIntelligenceJSTest]';

let currentDeviceIsPc = false;
let context = featureAbility.getContext();
let rdbStore1 = undefined;
let rdbStore2 = undefined;

let storeConfigInvalid = {
  name: '',
  securityLevel: relationalStore.SecurityLevel.S1
};

let channelConfigInvalid = {
  channelType: 0,
  context:context,
  dbConfig:storeConfigInvalid
};

let storeConfigVector = {
  name: 'rdb_store_test.db',
  encrypt: false,
  securityLevel: relationalStore.SecurityLevel.S3,
  autoCleanDirtyData: false,
  isSearchable: false,
  vector: true,
  allowRebuild: false
};

let storeConfigInvIdx = {
  name: 'sqlite_store_test.db',
  encrypt: false,
  securityLevel: relationalStore.SecurityLevel.S3,
  autoCleanDirtyData: false,
  isSearchable: false,
  allowRebuild: false,
  tokenizer: 2
};

let channelConfigVector = {
  channelType: intelligence.ChannelType.VECTOR_DATABASE,
  context:context,
  dbConfig:storeConfigVector
};

let channelConfigInvIdx = {
  channelType: intelligence.ChannelType.INVERTED_INDEX_DATABASE,
  context:context,
  dbConfig:storeConfigInvIdx
};

describe('AipJSTest', function () {

  beforeAll(async function () {
    console.info(TAG + 'beforeAll');
    let deviceTypeInfo = deviceInfo.deviceType;
    currentDeviceIsPc = deviceTypeInfo === '2in1' ? true : false;
    console.info(TAG + 'the value of the deviceType is : ' + deviceInfo.deviceType);
    relationalStore.deleteRdbStore(context, 'rdb_store_test.db', (err) => {
      if (err) {
        console.error(`Delete RdbStore failed, code is ${err.code},message is ${err.message}`);
        return;
      }
      console.info(TAG + 'Delete RdbStore successfully.');
    });
    rdbStore1 = await relationalStore.getRdbStore(context, storeConfigVector);
    if (rdbStore1 !== undefined) {
      let createSql = 'CREATE TABLE IF NOT EXISTS vector_table(fileid TEXT PRIMARY KEY, filename_text TEXT, filename FLOATVECTOR(128), keywords_text TEXT, keywords FLOATVECTOR(128), chapter FLOATVECTOR(128), abstract FLOATVECTOR(128));';
      await rdbStore1.execute(createSql, 0, undefined);
      await insertVectorDB();
    };
    rdbStore2 = await relationalStore.getRdbStore(context, storeConfigInvIdx);
    if (rdbStore2 !== undefined) {
      let createSql = 'CREATE VIRTUAL TABLE IF NOT EXISTS invidx_table USING fts5(fileid, filename, keywords, chapter, abstract, content, tokenize = "customtokenizer");';
      await rdbStore2.executeSql(createSql);
      await insertInvIdxDB();
    };
  });
  beforeEach(async function () {
    console.info(TAG + 'beforeEach');
  });
  afterEach(async function () {
    console.info(TAG + 'afterEach');
  });
  afterAll(async function () {
    console.info(TAG + 'afterAll');
  });

  async function insertVectorDB() {
    let insertSQL;
    for (let i = 0; i < 5; i++) {
      let array = new Array(128);
      for (let j = 0; j < array.length; j++) {
        let randomNumber = Math.random();
        array[j] = randomNumber;
      }
      let data = array.toString();
      insertSQL = "INSERT INTO vector_table VALUES('" + i + "', '大模型系统概述', '[" + data + "]', '生成式AI, 人工智能, 大模型', '[" + data + "]', '[" + data + "]', '[" + data + "]');";
      console.info(TAG + 'insertVectorDB insertSQL::' + insertSQL);
      await rdbStore1.execute(insertSQL, 0, undefined);
    }
    let arraySpecial = new Array(128).fill(0.1);
    let dataSpecial = arraySpecial.toString();
    let insertSQLSpecial = "INSERT INTO vector_table VALUES('5', '大模型系统概述', '[" + dataSpecial + "]', '生成式AI, 人工智能, 大模型', '[" + dataSpecial + "]', '[" + dataSpecial + "]', '[" + dataSpecial + "]');";
    console.info(TAG + 'insertVectorDB insertSQL::' + insertSQLSpecial);
    await rdbStore1.execute(insertSQLSpecial, 0, undefined);
  }

  async function insertInvIdxDB() {
    let insertSQL = 'INSERT INTO invidx_table VALUES("1", "大模型系统概述", "生成式AI, 人工智能, 大模型", "人工智能导论", "这是一篇关于大模型的综述文章", "这是一篇关于大模型的综述文章");';
    console.info(TAG + 'insertInvIdxDB insertSQL::' + insertSQL);
    await rdbStore2.executeSql(insertSQL);
    insertSQL = 'INSERT INTO invidx_table VALUES("2", "数据库在大模型时代下的发展", "数据库, 内核, 向量", "数据库导论", "这是一篇关于数据库和大模型交叉的综述文章", "这是一篇关于数据库和大模型交叉的综述文章");';
    console.info(TAG + 'insertInvIdxDB insertSQL::' + insertSQL);
    await rdbStore2.executeSql(insertSQL);
    insertSQL = 'INSERT INTO invidx_table VALUES("3", "社会发展报告", "旅游, 民生, 交通", "社会发展", "这是一篇关于社会发展的综述文章", "这是一篇关于社会发展的综述文章");';
    console.info(TAG + 'insertInvIdxDB insertSQL::' + insertSQL);
    await rdbStore2.executeSql(insertSQL);
    insertSQL = 'INSERT INTO invidx_table VALUES("4", "纯血鸿蒙", "鸿蒙, 生态, 遥遥领先", "鸿蒙系统", "这是一篇关于鸿蒙系统的综述文章", "这是一篇关于鸿蒙系统的综述文章");';
    console.info(TAG + 'insertInvIdxDB insertSQL::' + insertSQL);
    await rdbStore2.executeSql(insertSQL);
    insertSQL = 'INSERT INTO invidx_table VALUES("5", "原生AI", "鸿蒙, 生态, 大模型", "原生AI系统", "这是一篇关于原生AI系统的综述文章", "这是一篇关于原生AI系统的综述文章");';
    console.info(TAG + 'insertInvIdxDB insertSQL::' + insertSQL);
    await rdbStore2.executeSql(insertSQL);
    console.info(TAG + 'insertInvIdxDB end');
  }

  async function sleep(time) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve();
        }, time);
    }).then(() => {
        console.info(`sleep ${time} over...`);
    });
  }

  console.log('******************************Aip API Test Begin******************************');

  /**
   * @tc.name Aip_001
   * @tc.desc Test getRetriever. rdbStoreName is empty.
   * @tc.type: FUNC
   */
  it('Aip_001', 0, async function (done) {
    console.info(TAG, 'Aip_001 start');
    let retrievalConfig = {
      channelConfigs: [channelConfigInvalid]
    };
    if (currentDeviceIsPc) {
      try {
        await intelligence.getRetriever(retrievalConfig)
        .then((data) => {
            expect(data != null).assertEqual(true);
            done();
          });
      } catch (err) {
        console.info(TAG, 'Aip_001 catch::' + err.code);
        expect(err.code).assertEqual(401);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_002
   * @tc.desc Test getRetriever. channelConfigs is empty.
   * @tc.type: FUNC
   */
  it('Aip_002', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: []
    };
    if (currentDeviceIsPc) {
      try {
        await intelligence.getRetriever(retrievalConfig);
      } catch (err) {
        console.info(TAG, 'Aip_002 catch::' + err.code);
        expect(err.code).assertEqual(401);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
  });

  /**
   * @tc.name Aip_003
   * @tc.desc Test retrieveRdb. The value of deepSize is too large.
   * @tc.type: FUNC
   */
  it('Aip_003', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallCondition = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename_text'],
          filters: [],
          deepSize: 1000000
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '软件设计与建模';
              data.retrieveRdb(query, retrievalCondition)
              .then((rdbdata) => {
                let length = rdbdata.records.length;
                console.info(TAG, 'Aip_003 get result::' + length);
                let ret = length >= 0;
                expect(ret).assertEqual(true);
                done();
              });
            } catch (err) {
              console.info(TAG, 'catch::' + err.code);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_004
   * @tc.desc Test retrieveRdb.fromClause is empty.
   * @tc.type: FUNC
   */
  it('Aip_004', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallCondition = {
          vectorQuery: vectorQuery,
          fromClause: '',
          primaryKey: ['fileid'],
          responseColumns: ['filename_text'],
          deepSize: 500
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '软件设计与建模';
              data.retrieveRdb(query, retrievalCondition);
            } catch (err) {
              console.info(TAG, 'Aip_004 catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_004 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch11::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_005
   * @tc.desc Test retrieveRdb. primaryKey is empty.
   * @tc.type: FUNC
   */
  it('Aip_005', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallCondition = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: [],
          responseColumns: ['filename_text'],
          deepSize: 500
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '软件设计与建模';
              data.retrieveRdb(query, retrievalCondition);
            } catch (err) {
              console.info(TAG, 'catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_005 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch11::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_006
   * @tc.desc Test retrieveRdb. responseColumns is empty.
   * @tc.type: FUNC
   */
  it('Aip_006', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallCondition = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: ['fileid'],
          responseColumns: [],
          deepSize: 500
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '软件设计与建模';
              data.retrieveRdb(query, retrievalCondition);
            } catch (err) {
              console.info(TAG, 'Aip_006 catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_007
   * @tc.desc Test retrieveRdb. column is invalid.
   * @tc.type: FUNC
   */
  it('Aip_007', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'invalidField',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallCondition = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename_text'],
          deepSize: 500
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '软件设计与建模';
              data.retrieveRdb(query, retrievalCondition)
              .catch((err) => {
                console.info(TAG, 'Aip_007 catch::' + err.code);
                expect(err.code).assertEqual(31300100);
                done();
              });
            } catch (err) {
              console.info(TAG, 'Aip_007 catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_008
   * @tc.desc Test retrieveRdb. One-way vector normal recall.
   * @tc.type: FUNC
   */
  it('Aip_008', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let floatArray = new Float32Array(128).fill(0.1);
        const str = floatArray.toString();
        console.log(TAG, str);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallCondition = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename_text'],
          deepSize: 500
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '软件设计与建模';
              data.retrieveRdb(query, retrievalCondition)
              .then((rdbdata) => {
                let length = rdbdata.records.length;
                console.info(TAG, 'Aip_008 get result length::' + length);
                expect(length > 0).assertEqual(true);
                done();
              });
            } catch (err) {
              console.info(TAG, 'Aip_008 catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_008 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'Aip_008 catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_009
   * @tc.desc Test retrieveRdb. One-way invertedindex normal recall.
   * @tc.type: FUNC
   */
  it('Aip_009', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigInvIdx]
    };
    if (currentDeviceIsPc) {
      try {
        let fieldWeight = {
          'filename': 4.0
        };
        let fieldSlops = {
          'filename': 5
        };
        let bm25Strategy = {
          bm25Weight: 1.5,
          columnWeight: fieldWeight
        };
        let exactStrategy = {
          exactMatchingWeight: 1.2,
          columnWeight: fieldWeight
        };
        let outOfOrderStrategy = {
          proximityWeight: 1.2,
          columnWeight: fieldWeight,
          columnSlops: fieldSlops
        };
        let invertedIndexStrategies = [bm25Strategy, exactStrategy, outOfOrderStrategy];
        let recallCondition = {
          ftsTableName: 'invidx_table',
          fromClause: 'invidx_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename', 'keywords'],
          deepSize: 500,
          invertedIndexStrategies: invertedIndexStrategies
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            console.info(TAG, 'Aip_009 get result::' + data);
            try {
              let query = '数据库';
              data.retrieveRdb(query, retrievalCondition)
              .then((rdbdata) => {
                let length = rdbdata.records.length;
                console.info(TAG, 'Aip_009 get result::' + length);
                expect(length).assertEqual(1);
                done();
              });
            } catch (err) {
              console.info(TAG, 'Aip_009 catch::' + err.code);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_009 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'Aip_009 catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_010
   * @tc.desc Test retrieveRdb. ftsTableName is empty.
   * @tc.type: FUNC
   */
  it('Aip_010', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigInvIdx]
    };
    if (currentDeviceIsPc) {
      try {
        let fieldWeight = {
          'filename': 4.0
        };
        let fieldSlops = {
          'filename': 5
        };
        let bm25Strategy = {
          bm25Weight: 1.5,
          columnWeight: fieldWeight
        };
        let exactStrategy = {
          exactMatchingWeight: 1.2,
          columnWeight: fieldWeight
        };
        let outOfOrderStrategy = {
          proximityWeight: 1.2,
          columnWeight: fieldWeight,
          columnSlops: fieldSlops
        };
        let invertedIndexStrategies = [bm25Strategy, exactStrategy, outOfOrderStrategy];
        let recallCondition = {
          ftsTableName: '',
          fromClause: 'invidx_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename', 'keywords'],
          deepSize: 500,
          invertedIndexStrategies: invertedIndexStrategies
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '数据库';
              data.retrieveRdb(query, retrievalCondition);
            } catch (err) {
              console.info(TAG, 'Aip_010 catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_010 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'Aip_010 catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_011
   * @tc.desc Test retrieveRdb. invertedindex match field is invalid.
   * @tc.type: FUNC
   */
  it('Aip_011', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigInvIdx]
    };
    if (currentDeviceIsPc) {
      try {
        let fieldWeight = {
          'invalid': 4.0
        };
        let fieldSlops = {
          'filename': 5
        };
        let bm25Strategy = {
          bm25Weight: 1.5,
          columnWeight: fieldWeight
        };
        let exactStrategy = {
          exactMatchingWeight: 1.2,
          columnWeight: fieldWeight
        };
        let outOfOrderStrategy = {
          proximityWeight: 1.2,
          columnWeight: fieldWeight,
          columnSlops: fieldSlops
        };
        let invertedIndexStrategies = [bm25Strategy, exactStrategy, outOfOrderStrategy];
        let recallCondition = {
          ftsTableName: 'invidx_table',
          fromClause: 'invidx_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename', 'keywords'],
          deepSize: 500,
          invertedIndexStrategies: invertedIndexStrategies
        };
        let retrievalCondition = {
          recallConditions : [recallCondition]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '数据库';
              data.retrieveRdb(query, retrievalCondition)
              .catch((err) => {
                console.info(TAG, 'Aip_011 catch::' + err.code);
                expect(err.code).assertEqual(31301010);
                done();
              });
            } catch (err) {
              console.info(TAG, 'Aip_011 catch::' + err.code);
              expect(err.code).assertEqual(401);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_011 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'Aip_011 catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });


  /**
   * @tc.name Aip_012
   * @tc.desc Test retrieveRdb. Two-way normal recall.
   * @tc.type: FUNC
   */
  it('Aip_012', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigInvIdx, channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let fieldWeight = {
          'filename': 4.0
        };
  
        let fieldSlops = {
          'filename': 5
        };
        let bm25Strategy = {
          bm25Weight: 1.5,
          columnWeight: fieldWeight
        };
        let exactStrategy = {
          exactMatchingWeight: 1.2,
          columnWeight: fieldWeight
        };
        let outOfOrderStrategy = {
          proximityWeight: 1.2,
          columnWeight: fieldWeight,
          columnSlops: fieldSlops
        };
        let invertedIndexStrategies = [bm25Strategy, exactStrategy, outOfOrderStrategy];
        let recallConditionInvIdx = {
          ftsTableName: 'invidx_table',
          fromClause: 'invidx_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename', 'keywords'],
          deepSize: 500,
          invertedIndexStrategies: invertedIndexStrategies
        };
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallConditionVector = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename_text'],
          deepSize: 500
        };
        let retrievalCondition = {
          recallConditions : [recallConditionInvIdx, recallConditionVector]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '数据库';
              data.retrieveRdb(query, retrievalCondition)
              .then((rdbdata) => {
                let length = rdbdata.records.length;
                console.info(TAG, 'Aip_012 get result::' + length);
                expect(length >= 2).assertEqual(true);
                done();
              });
            } catch (err) {
              console.info(TAG, 'Aip_012 catch::' + err.code);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_012 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'Aip_012 catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });

  /**
   * @tc.name Aip_013
   * @tc.desc Test retrieveRdb. Two-way normal recall and configing rerankMethod.
   * @tc.type: FUNC
   */
  it('Aip_013', 0, async function (done) {
    console.info(TAG, 'start');
    let retrievalConfig = {
      channelConfigs: [channelConfigInvIdx, channelConfigVector]
    };
    if (currentDeviceIsPc) {
      try {
        let fieldWeight = {
          'filename': 4.0,
          'keywords':4.0
        };
        let fieldSlops = {
          'filename': 5,
          'keywords':5
        };
        let bm25Strategy = {
          bm25Weight: 1.5,
          columnWeight: fieldWeight
        };
        let exactStrategy = {
          exactMatchingWeight: 1.2,
          columnWeight: fieldWeight
        };
        let outOfOrderStrategy = {
          proximityWeight: 1.2,
          columnWeight: fieldWeight,
          columnSlops: fieldSlops
        };
        let invertedIndexStrategies = [bm25Strategy, exactStrategy, outOfOrderStrategy];
        let recallConditionInvIdx = {
          ftsTableName: 'invidx_table',
          fromClause: 'invidx_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename', 'keywords'],
          deepSize: 500,
          invertedIndexStrategies: invertedIndexStrategies
        };
        let floatArray = new Float32Array(128).fill(0.1);
        let vectorQuery = {
          column: 'filename',
          value: floatArray,
          similarityThreshold: 0.1
        };
        let recallConditionVector = {
          vectorQuery: vectorQuery,
          fromClause: 'vector_table',
          primaryKey: ['fileid'],
          responseColumns: ['filename_text'],
          recallName: 'vectorRecall',
          deepSize: 500
        };
        let vectorWeights = {
          'vectorRecall': 1
        };
        let numberInspector = {
          'vector_query':'filename_text'
        };
        let vectorRerankParameter = {
          vectorWeights:vectorWeights,
          thresholds: [0.55, 0.45, 0.35],
          numberInspector: numberInspector
        };
        let parameters = {
          0: vectorRerankParameter
        };
        let rerankMethod = {
          rerankType: 1,
          parameters: parameters,
          isSoftmaxNormalized: true,
        };
        let retrievalCondition = {
          rerankMethod: rerankMethod,
          recallConditions : [recallConditionInvIdx, recallConditionVector]
        };
        await intelligence.getRetriever(retrievalConfig)
          .then((data) => {
            try {
              let query = '数据库';
              data.retrieveRdb(query, retrievalCondition)
              .then((rdbdata) => {
                let length = rdbdata.records.length;
                console.info(TAG, 'Aip_013 get result::' + length);
                expect(length >= 2).assertEqual(true);
                done();
              });
            } catch (err) {
              console.info(TAG, 'Aip_013 catch::' + err.code);
              done();
            }
          });
      } catch (err) {
        console.info(TAG, 'Aip_013 catch::' + err.code);
        done();
      }
    } else {
      await intelligence.getRetriever(retrievalConfig)
        .catch((err) => {
          console.info(TAG, 'Aip_013 catch::' + err.code);
          expect(err.code).assertEqual(801);
          done();
        });
    }
    console.info(TAG, 'end');
  });
});