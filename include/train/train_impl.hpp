#ifndef TRAIN_IMPL_HPP_
#define TRAIN_IMPL_HPP_

#include <iostream>
#include <random>

namespace
{
  namespace constants
  {
    // will be read by config later on
    size_t const maxIter = 10U;
    double const precision = 0.9;
  }
}

namespace train
{
  template<typename T, typename U>
  Train<T, U>::Train(size_t hiddenLayerSize)
    : m_network(hiddenLayerSize)
    , m_adapt(m_network)
  {}

  template<typename T, typename U>
  network::NetworkWeights Train<T, U>::operator()(LearnData<T, U> const &data, double percentageTrain)
  {
    // prepare data
    if (percentageTrain < 0 || percentageTrain > 1)
    {
      throw std::runtime_error("Bad percentage for train data");
    }

    if (data.input.size() != data.groundTruth.size())
    {
      throw std::runtime_error("Bad input size for train data");
    }

    // fill data
    std::default_random_engine re;
    std::uniform_real_distribution<double> gen(0.0, 1.0);
    LearnData<T, U> learnData, evalData;
    for (size_t i{}; i < data.input.size(); ++i)
    {
      double v = gen(re);
      if (v > percentageTrain)
      {
        learnData.input.push_back(data.input[i]);
        learnData.groundTruth.push_back(data.groundTruth[i]);
      }
      else
      {
        evalData.input.push_back(data.input[i]);
        evalData.groundTruth.push_back(data.groundTruth[i]);
      }
    }

    auto backupWeights = m_network.GetWeights();
    auto lastOutput = m_network.GetOutput();
    auto lastResult = 0.0;
    EvalData<U> performanceData;
    for (size_t i{}; i <= constants::maxIter; ++i)
    {
      if (i == constants::maxIter)
      {
        std::cout << "Reached maxIter without satisfying solution\n";
        break;
      }

      m_adapt(learnData);

      lastOutput = m_network.GetOutput();
      performanceData = EvalData<U>{ lastOutput, learnData.groundTruth };
      double learnResult = m_eval(performanceData);

      std::cout << "Result on learn dataset: " << learnResult << "\n";

      m_network.ForwardPass(evalData.input);
      lastOutput = m_network.GetOutput();
      performanceData = EvalData<U>{ lastOutput, evalData.groundTruth };
      double evalResult = m_eval(performanceData);
      
      if (evalResult >= constants::precision)
      {
        std::cout << "Found best solution\n";
        break;
      }
      else if (evalResult < lastResult)
      {
        std::cout << "Result was getting worse - reset last weights and break\n";
        m_network.SetWeights(backupWeights);
        break;
      }

      backupWeights = m_network.GetWeights();
      lastResult = evalResult;
    }
  }
}

#endif
