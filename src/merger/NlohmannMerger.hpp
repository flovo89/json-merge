#ifndef MERGE_JSON_NLOHMANN_MERGER_HPP_
#define MERGE_JSON_NLOHMANN_MERGER_HPP_

#include "IMerger.hpp"

namespace merge_json {

class NlohmannMerger : public IMerger {
 public:
  NlohmannMerger();
  virtual ~NlohmannMerger();

  void merge(const std::string& in1, const std::string& in2,
             std::string& merged) noexcept(false) override;
};

}  // namespace merge_json

#endif
