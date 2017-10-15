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
  Train<T, U>::Train(network::Config const &config)
    : m_network(config)
  {}

  template<typename T, typename U>
  network::NetworkWeights Train<T, U>::operator()(typename LearnSet<T, U> const &data, double percentageTrain)
  {
    // prepare data
    if (percentageTrain < 0 || percentageTrain > 1)
    {
      throw std::runtime_error("Bad percentage for train data");
    }
    
    // fill data
    std::default_random_engine re;
    std::uniform_real_distribution<double> gen(0.0, 1.0);
    LearnSet<T, U> trainData, evalData;
    for (size_t i{}; i < data.size(); ++i)
    {
      double v = gen(re);
      if (v <= percentageTrain)
      {
        trainData.push_back(data[i]);
      }
      else
      {
        evalData.push_back(data[i]);
      }
    }

    auto backupWeights = m_network.GetWeights();
    auto lastResult = 0.0;
    EvalSet<U> trainEvalSet;
    EvalSet<U> evalSet;
    for (size_t i{}; i <= constants::maxIter; ++i)
    {
      if (i == constants::maxIter)
      {
        std::cout << "Reached maxIter without satisfying solution\n";
        break;
      }

      for (auto &&d : trainData)
      {
        m_network.ForwardPass(d.input);
        m_network.BackwardPass(d.groundTruth);
      }

      trainEvalSet.clear();
      for (auto &&d : trainData)
      {
        m_network.ForwardPass(d.input);
        trainEvalSet.emplace_back(EvalData<U>{ m_network.GetOutput(), d.groundTruth });
      }
      double trainResult = m_eval(trainEvalSet);
      std::cout << "Result on train dataset: " << trainResult << "\n";

      evalSet.clear();
      for (auto &&d : evalData)
      {
        m_network.ForwardPass(d.input);
        evalSet.emplace_back(EvalData<U>{ m_network.GetOutput(), d.groundTruth });
      }
      double evalResult = m_eval(evalSet);
      std::cout << "Result on eval dataset: " << evalResult << "\n";
      
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
