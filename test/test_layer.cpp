/*
 * @Author: zzh
 * @Date: 2023-03-04 	
 * @LastEditTime: 2023-03-13 10:06:23
 * @Description: 
 * @FilePath: /scnni/test/test_layer.cpp
 */
#include "scnni/graph.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;

TEST(layer_test, relu_only_1batch_test) {
  std::cout << "In graph_test load params" << std::endl;
  std::unique_ptr<scnni::Graph> g = std::make_unique<scnni::Graph>();
  g->LoadModel("/code/scnni/python_scripts/relu_only_net/relu_only_net.pnnx.param",
              "/code/scnni/python_scripts/relu_only_net/relu_only_net.pnnx.bin");
  EXPECT_EQ(g->blobs_.size(), 2);
  EXPECT_EQ(g->operators_.size(), 3);
  scnni::Excecutor exe = scnni::Excecutor(std::move(g));

  scnni::Tensor<float> input_tensor(3, 2, 2);
  Eigen::Tensor<float, 3> input_data(2, 2, 3);
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 2; j ++) {
      for (int k = 0; k < 2; k ++) {
        input_data(j, k, i) = ((j + k) % 2) != 0 ? 12.324 : -12121.123;
      }
    }
  }
  // for (int i = 0; i < 3; i ++) {
  //   for (int j = 0; j < 2; j ++) {
  //     for (int k = 0; k < 2; k ++) {
  //       cout << input_data(j, k, i) << " ";
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  input_tensor.SetData(input_data);
  std::vector<scnni::Tensor<float>> input_batch;
  input_batch.push_back(input_tensor);

  exe.Input("0", input_batch);
  exe.Forward();
  std::vector<scnni::Tensor<float>> output_batch = exe.Output(); 

  Eigen::Tensor<float, 3> output_data(2, 2, 3);
  output_data = output_batch[0].GetData();
  EXPECT_EQ(output_batch.size(), 1);
  EXPECT_EQ(output_data.size(), 12);
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 2; j ++) {
      for (int k = 0; k < 2; k ++) {
        EXPECT_EQ(output_data(j, k, i), input_data(j, k, i) > 0 ? input_data(j, k, i) : 0);
      }
    }
  }
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 2; j ++) {
  //     for (int k = 0; k < 2; k ++) {
  //       cout << output_data(j, k, i) << " ";
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  // }
  // cout << endl;
}

TEST(layer_test, relu_flatten_1batch_test) {
  std::cout << "In graph_test load params" << std::endl;
  std::unique_ptr<scnni::Graph> g = std::make_unique<scnni::Graph>();
  g->LoadModel("/code/scnni/python_scripts/relu_flatten_net/relu_flatten_net.pnnx.param",
              "/code/scnni/python_scripts/relu_flatten_net/relu_flatten_net.pnnx.bin");
  EXPECT_EQ(g->blobs_.size(), 3);
  EXPECT_EQ(g->operators_.size(), 4);
  scnni::Excecutor exe = scnni::Excecutor(std::move(g));

  scnni::Tensor<float> input_tensor(3, 2, 2);
  Eigen::Tensor<float, 3> input_data(2, 2, 3);
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 2; j ++) {
      for (int k = 0; k < 2; k ++) {
        input_data(j, k, i) = ((j + k + i) % 2) != 0 ? i + 1 : -i - 1;
      }
    }
  }
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 2; j ++) {
      for (int k = 0; k < 2; k ++) {
        cout << input_data(j, k, i) << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  cout << endl;

  input_tensor.SetData(input_data);
  std::vector<scnni::Tensor<float>> input_batch;
  input_batch.push_back(input_tensor);

  exe.Input("0", input_batch);
  exe.Forward();
  std::vector<scnni::Tensor<float>> output_batch = exe.Output(); 

  Eigen::Tensor<float, 3> output_data(12, 1, 1);
  output_data = output_batch[0].GetData();
  
  EXPECT_EQ(output_batch[0].Shapes()[0], 1);
  EXPECT_EQ(output_batch[0].Shapes()[1], 1);
  EXPECT_EQ(output_batch[0].Shapes()[2], 12);
  EXPECT_EQ(output_batch.size(), 1);
  EXPECT_EQ(output_data.size(), 12);
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 2; j ++) {
      for (int k = 0; k < 2; k ++) {
        EXPECT_EQ(output_data(k+j*2+i*4), input_data(j, k, i) > 0 ? input_data(j, k, i) : 0);
      }
    }
  }
  for (int i = 0; i < 12; i++) {
    cout << output_data(i) << " ";
  }
  cout << endl;
}