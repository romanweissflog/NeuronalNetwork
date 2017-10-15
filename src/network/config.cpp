#include "network/config.h"

#include "picojson.h"

#include <fstream>
#include <string>

namespace
{
  std::string GetString(picojson::value &jsonVal)
  {
    if (!jsonVal.is<std::string>())
    {
      throw std::runtime_error("picojson value is no string");
    }
    return jsonVal.get<std::string>();
  }

  double GetDouble(picojson::value &jsonVal)
  {
    if (!jsonVal.is<double>())
    {
      throw std::runtime_error("picojson value is no double");
    }
    return jsonVal.get<double>();
  }

  double GetBool(picojson::value &jsonVal)
  {
    if (!jsonVal.is<bool>())
    {
      throw std::runtime_error("picojson value is no bool");
    }
    return jsonVal.get<bool>();
  }

  picojson::array GetArray(picojson::value &jsonVal)
  {
    if (!jsonVal.is<picojson::array>())
    {
      throw std::runtime_error("picojson value is no array");
    }
    return jsonVal.get<picojson::array>();
  }

  picojson::object GetObject(picojson::value &jsonVal)
  {
    if (!jsonVal.is<picojson::object>())
    {
      throw std::runtime_error("picojson value is no object");
    }
    return jsonVal.get<picojson::object>();
  }

  network::NetworkType GetType(picojson::object &jsonObj)
  {
    if (jsonObj.count("type") == 0)
    {
      throw std::runtime_error("Config doesn't contain type entry");
    }
    auto const stringType = GetString(jsonObj["type"]);
    if (stringType == "number")
    {
      return network::NetworkType::TypeNumber;
    }
    else if (stringType == "image")
    {
      return network::NetworkType::TypeImage;
    }
    else if (stringType == "pointCloud")
    {
      return network::NetworkType::TypePointCloud;
    }
    else
    {
      throw std::runtime_error("Unsupported network type");
    }
  }

  network::TransferFunctionType GetTransferFunction(picojson::object &jsonObj)
  {
    if (jsonObj.count("transfer_function") == 0)
    {
      return network::TransferFunctionType::TypeSum;
    }

    auto const stringType = GetString(jsonObj["transfer_function"]);
    if (stringType == "sum")
    {
      return network::TransferFunctionType::TypeSum;
    }
    else
    {
      throw std::runtime_error("Unsupported transfer function type");
    }
  }

  network::ActivationFunctionType GetActivationFunction(picojson::object &jsonObj)
  {
    if (jsonObj.count("activation_function") == 0)
    {
      return network::ActivationFunctionType::TypeNone;
    }

    auto const stringType = GetString(jsonObj["activation_function"]);
    if (stringType == "identity")
    {
      return network::ActivationFunctionType::TypeIdentity;
    }
    else if (stringType == "sigmoid")
    {
      return network::ActivationFunctionType::TypeSigmoid;
    }
    else if (stringType == "relu")
    {
      return network::ActivationFunctionType::TypeReLu;
    }
    else
    {
      throw std::runtime_error("Unsupported activation function type");
    }
  }

  network::LayerConfig GetLayer(picojson::object &jsonObj)
  {
    network::LayerConfig layer;
    if (jsonObj.count("number_neurons") == 0)
    {
      throw std::runtime_error("Layer doesn't container number_neurons");
    }
    layer.nrNeurons = static_cast<size_t>(GetDouble(jsonObj["number_neurons"]));

    layer.neuronConfig.transferFunction = GetTransferFunction(jsonObj);
    layer.neuronConfig.activationFunction = GetActivationFunction(jsonObj);
    if (jsonObj.count("bias") != 0)
    {
      layer.withBias = GetBool(jsonObj["bias"]);
    }

    return layer;
  }

  network::LayerConfig GetInputLayer(picojson::object &jsonObj)
  {
    if (jsonObj.count("inputLayer") == 0)
    {
      throw std::runtime_error("Config doen't contain input layer");
    }
    auto layerObj = GetObject(jsonObj["inputLayer"]);
    network::LayerConfig layer = GetLayer(layerObj);
    layer.type = network::NeuronType::TypeInput;
    return layer;
  }

  network::LayerConfig GetHiddenLayer(picojson::object &jsonObj, size_t idx)
  {
    auto arrEntry = GetArray(jsonObj["hiddenLayer"])[idx];
    auto obj = GetObject(arrEntry);
    network::LayerConfig layer = GetLayer(obj);
    layer.type = network::NeuronType::TypeHidden;
    return layer;
  }

  network::LayerConfig GetOutputLayer(picojson::object &jsonObj)
  {
    if (jsonObj.count("outputLayer") == 0)
    {
      throw std::runtime_error("Config doen't contain output layer");
    }
    auto layerObj = GetObject(jsonObj["outputLayer"]);
    network::LayerConfig layer = GetLayer(layerObj);
    layer.type = network::NeuronType::TypeOutput;
    return layer;
  }

  size_t GetHiddenLayerSize(picojson::object &jsonObj)
  {
    if (jsonObj.count("hiddenLayer") == 0)
    {
      throw std::runtime_error("Config doesn't contain hiddenLayer entry");
    }
    auto arr = GetArray(jsonObj["hiddenLayer"]);
    return arr.size();
  }
}

namespace network
{
  Config GetConfig(std::string const &path)
  {
    Config config;
    std::ifstream f(path);

    picojson::value root;
    picojson::parse(root, f);
    auto rootObj = root.get<picojson::object>();

    config.networkType = GetType(rootObj);
    
    if (rootObj.count("step") == 0)
    {
      throw std::runtime_error("Config doesn't contain step value");
    }
    config.step = GetDouble(rootObj["step"]);

    config.layers.push_back(GetInputLayer(rootObj));
    for (size_t i{}; i < GetHiddenLayerSize(rootObj); ++i)
    {
      config.layers.push_back(GetHiddenLayer(rootObj, i));
    }
    config.layers.push_back(GetOutputLayer(rootObj));

    return config;
  }
}