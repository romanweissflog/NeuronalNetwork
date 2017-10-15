#ifndef EVAL_HPP_
#define EVAL_HPP_

#include <vector>

namespace train
{
  template<typename T>
  struct EvalData
  {
    std::vector<T> hypothesis;
    std::vector<T> groundTruth;
  };

  template<typename T>
  struct Eval
  {
    double operator()(EvalData<T> const &data)
    {
      if (data.hypothesis.size() != data.groundTruth.size())
      {
        throw std::runtime_error("Bad input sizes for eval data");
      }
      if (data.hypothesis.size() == 0)
      {
        throw std::runtime_error("Empty input data for eval data");
      }

      size_t correctCount{};
      size_t totalCount = data.hypothesis.size();
      for (size_t i{}; i < totalCount; ++i)
      {
        auto &&h = data.hypothesis[i];
        auto &&gt = data.groundTruth[i];
        if (h == gt)
        {
          correctCount++;
        }
      }

      return static_cast<double>(correctCount) / static_cast<double>(totalCount);
    }
  };
}


#endif
