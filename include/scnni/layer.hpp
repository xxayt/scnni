/*
 * @Author: zzh
 * @Date: 2023-03-04
 * @LastEditTime: 2023-03-06 12:05:02
 * @Description: 
 * @FilePath: /SCNNI/include/scnni/layer.hpp
 */

#ifndef SCNNI_LAYER_HPP_
#define SCNNI_LAYER_HPP_ 
#include "tensor.hpp"
#include <memory>
#include <string>
#include <vector>

namespace scnni {
class Blob;
class Layer {
  public:
    explicit Layer(std::string layer_name): layer_name_(std::move(layer_name)) {};
    virtual ~Layer() = default;

    /**
     * @description: Layer的前向计算
     * @param input_blobs,  output_blobs
     * @return {*}
     */
    virtual auto Forward(const std::vector<std::shared_ptr<Tensor<float>>>& input_blobs, std::shared_ptr<std::vector<std::shared_ptr<Tensor<float>>>> output_blobs) const -> int; 
    virtual auto Forward(const std::shared_ptr<Tensor<float>>& input_blobs, std::shared_ptr<Tensor<float>> output_blobs) const ->int;

    auto LayerName() const -> const std::string & { return this->layer_name_; }

    std::vector<std::shared_ptr<Blob>> inputs_; // 输入blob
    std::vector<std::shared_ptr<Blob>> outputs_; // 输出blob

  protected:
    std::string layer_name_;
    std::string layer_type_;
};

} // namespace scnni
#endif