#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <merger/NlohmannMerger.hpp>
#include <nlohmann/json.hpp>

using namespace testing;
using namespace std;

namespace merge_json {
namespace gtests {

class TestNlohmannMerger : public Test {
 protected:
  TestNlohmannMerger() : Test() {}

  void SetUp() override { _merger.reset(new NlohmannMerger()); }

  void TearDown() override {}

  ~TestNlohmannMerger() override {}

  unique_ptr<IMerger> _merger;
};

//--------------------------------------------------------------------------------------------
TEST_F(TestNlohmannMerger, mergeEmpty) {
  string empty = "{}";
  string output;
  EXPECT_NO_THROW(_merger->merge(empty, empty, output));
  EXPECT_EQ(output, empty);
}

//--------------------------------------------------------------------------------------------
TEST_F(TestNlohmannMerger, mergeInvalid) {
  string empty = "{";
  string output;
  EXPECT_THROW(_merger->merge(empty, empty, output),
               nlohmann::detail::parse_error);
}

//--------------------------------------------------------------------------------------------
TEST_F(TestNlohmannMerger, mergeSimple) {
  string f1 = "{\"test1\":1234}";
  string f2 = "{\"test2\":4321}";
  string output;
  EXPECT_NO_THROW(_merger->merge(f1, f2, output));
  EXPECT_EQ(output, "{\"test1\":1234,\"test2\":4321}");
}

//--------------------------------------------------------------------------------------------
TEST_F(TestNlohmannMerger, mergeArrayDifferent) {
  string f1 = "{\"test1\":[{\"t1\":\"xyz\"}]}";
  string f2 = "{\"test2\":[{\"t2\":\"abc\"}]}";
  string output;
  EXPECT_NO_THROW(_merger->merge(f1, f2, output));
  EXPECT_EQ(output,
            "{\"test1\":[{\"t1\":\"xyz\"}],\"test2\":[{\"t2\":\"abc\"}]}");
}

//--------------------------------------------------------------------------------------------
TEST_F(TestNlohmannMerger, mergeArraySame) {
  string f1 = "{\"test1\":[{\"t1\":\"xyz\"}]}";
  string f2 = "{\"test1\":[{\"t2\":\"abc\"}]}";
  string output;
  EXPECT_NO_THROW(_merger->merge(f1, f2, output));
  EXPECT_EQ(output, "{\"test1\":[{\"t1\":\"xyz\"},{\"t2\":\"abc\"}]}");
}

}  // namespace gtests
}  // namespace merge_json
