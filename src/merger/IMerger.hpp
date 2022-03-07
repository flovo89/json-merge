#ifndef MERGE_JSON_I_MERGER_HPP_
#define MERGE_JSON_I_MERGER_HPP_

#include <string>

namespace merge_json {

class IMerger {
 public:
  IMerger();
  virtual ~IMerger();

  virtual void merge(const std::string& in1, const std::string& in2,
                     std::string& merged) noexcept(false) = 0;
};

}  // namespace merge_json

#endif
