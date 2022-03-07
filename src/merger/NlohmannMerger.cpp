#include "NlohmannMerger.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
namespace merge_json {

using json = nlohmann::json;

//--------------------------------------------------------------------------------------------
NlohmannMerger::NlohmannMerger() {}

//--------------------------------------------------------------------------------------------
NlohmannMerger::~NlohmannMerger() {}

//--------------------------------------------------------------------------------------------
void NlohmannMerger::merge(const std::string& in1, const std::string& in2,
                           std::string& merged) noexcept(false) {
  json o1 = json::parse(in1);
  json o2 = json::parse(in2);

  o1.update(o2);

  merged = o1.dump();
}

}  // namespace merge_json
