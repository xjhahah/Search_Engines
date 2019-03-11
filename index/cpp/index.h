#pragma once
#include <unordered_map>
#include <base/base.h>
#include <cppjieba/Jieba.hpp>
#include "../../common/util.hpp"
#include "index.pb.h"

namespace doc_index {

typedef doc_index_proto::DocInfo DocInfo;
typedef doc_index_proto::KwdInfo KwdInfo;
typedef doc_index_proto::Weight Weight;
typedef std::vector<DocInfo> ForwardIndex;
typedef std::vector<Weight> InvertedList;
typedef std::unordered_map<std::string,
                           InvertedList> InvertedIndex;

struct WordCnt {
  int32_t title_cnt;
  int32_t content_cnt;
  // 该词在正文中第一次出现的位置
  int32_t first_pos;    // 为了后面方便生成描述信息

  WordCnt() : title_cnt(0), content_cnt(0), first_pos(-1) {}
};

typedef std::unordered_map<std::string, WordCnt> WordCntMap;

// 包含了实现索引的数据结构以及索引需要提供的 API 接口
class Index {
public:
  // 凡是需要使用索引对象, 就必须通过 Instance 这个接口来
  // 访问索引, 而不允许使用 Index 创建其他的对象.
  // 这个叫做懒汉模式的实现
  static Index* Instance() {
    if (inst_ == NULL) {
      inst_ = new Index();
    }
    return inst_;
  }

  Index();

  // 1. 制作: 读取 raw_input 文件, 分析生成内存中的索引结构
  bool Build(const std::string& input_path);
  // 2. 保存: 基于 protobuf 把内存中的索引结构写到文件中
  bool Save(const std::string& output_path);
  // 3. 加载: 把文件中的索引结构加载到内存中
  bool Load(const std::string& index_path);
  // 4. 反解: 内存中的索引结构按照可读性比较好的格式打印到文件中
  bool Dump(const std::string& forward_dump_path, 
            const std::string& inverted_dump_path);
  // 5. 查正排: 给定文档id, 获取到文档详细内容(取vector的下标)
  const DocInfo* GetDocInfo(uint64_t doc_id) const;
  // 6. 查倒排: 给定关键词, 获取到倒排拉链(查hash)
  const InvertedList* GetInvertedList(const std::string& key) const;
  // 此处新增一个 API, 作为分词时使用(过滤掉暂停词)
  void CutWordWithoutStopWord(const std::string& query,std::vector<std::string>* words);
  // 把比较函数作为 public, 供后面 server 模块也去使用
  static bool CmpWeight(const Weight& w1, const Weight& w2);
private:
  ForwardIndex forward_index_;
  InvertedIndex inverted_index_;
  cppjieba::Jieba jieba_;
  common::DictUtil stop_word_dict_;
  static Index* inst_;

  // 以下函数为辅助构造索引的函数
  const DocInfo* BuildForward(const std::string& line);
  void BuildInverted(const DocInfo& doc_info);
  void SortInverted();
  void SplitTitle(const std::string& title, DocInfo* doc_info);
  void SplitContent(const std::string& content,
                    DocInfo* doc_info);
  int32_t CalcWeight(const WordCnt& word_cnt);
  bool ConvertToProto(std::string* proto_data);
  bool ConvertFromProto(const std::string& proto_data);
};

}  // end doc_index
