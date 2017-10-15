#ifndef EVAL_HPP_
#define EVAL_HPP_

#include "learn_data.hpp"
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
  using EvalSet = std::vector<EvalData<T>>;

  template<typename T>
  struct Eval
  {
    double operator()(EvalSet<T> const &data)
    {
      if (data.size() == 0)
      {
        throw std::runtime_error("Empty eval data");
      }
      
      double result{};
      for (auto &&d : data)
      {
        if (d.hypothesis.size() == 0)
        {
          throw std::runtime_error("Empty input data for eval data");
        }
        if (d.hypothesis.size() != d.groundTruth.size())
        {
          throw std::runtime_error("Bad input size for eval data");
        }

        size_t correctCount{};
        size_t totalCount = d.hypothesis.size();
        for (size_t i{}; i < totalCount; ++i)
        {
          auto &&h = d.hypothesis[i];
          auto &&gt = d.groundTruth[i];
          if (h == gt)
          {
            correctCount++;
          }
        }

        result += static_cast<double>(correctCount) / static_cast<double>(totalCount);
      }
      result /= static_cast<double>(data.size());
      return result;
    }
  };
}


#endif
