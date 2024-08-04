#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class SimpleNeuralNetwork {
private:
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;
    double learning_rate;

    double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double sigmoid_derivative(double x) {
        return x * (1.0 - x);
    }

public:
    SimpleNeuralNetwork(int input_size, int hidden_size, int output_size, double lr = 0.1) : learning_rate(lr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        weights = {std::vector<double>(input_size * hidden_size),
                   std::vector<double>(hidden_size * output_size)};
        biases = {0.0, 0.0};

        for (auto& layer : weights) {
            for (auto& weight : layer) {
                weight = dis(gen);
            }
        }
    }

    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<double> hidden(weights[0].size() / input.size());
        for (size_t i = 0; i < hidden.size(); ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < input.size(); ++j) {
                sum += input[j] * weights[0][i * input.size() + j];
            }
            hidden[i] = sigmoid(sum + biases[0]);
        }

        std::vector<double> output(weights[1].size() / hidden.size());
        for (size_t i = 0; i < output.size(); ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < hidden.size(); ++j) {
                sum += hidden[j] * weights[1][i * hidden.size() + j];
            }
            output[i] = sigmoid(sum + biases[1]);
        }

        return output;
    }

    void train(const std::vector<double>& input, const std::vector<double>& target) {
        auto hidden = forward(input);
        auto output = forward(hidden);

        std::vector<double> output_error(output.size());
        for (size_t i = 0; i < output.size(); ++i) {
            output_error[i] = (target[i] - output[i]) * sigmoid_derivative(output[i]);
        }

        std::vector<double> hidden_error(hidden.size());
        for (size_t i = 0; i < hidden.size(); ++i) {
            double error = 0.0;
            for (size_t j = 0; j < output.size(); ++j) {
                error += output_error[j] * weights[1][j * hidden.size() + i];
            }
            hidden_error[i] = error * sigmoid_derivative(hidden[i]);
        }

        for (size_t i = 0; i < output.size(); ++i) {
            for (size_t j = 0; j < hidden.size(); ++j) {
                weights[1][i * hidden.size() + j] += learning_rate * output_error[i] * hidden[j];
            }
            biases[1] += learning_rate * output_error[i];
        }

        for (size_t i = 0; i < hidden.size(); ++i) {
            for (size_t j = 0; j < input.size(); ++j) {
                weights[0][i * input.size() + j] += learning_rate * hidden_error[i] * input[j];
            }
            biases[0] += learning_rate * hidden_error[i];
        }
    }
};

int main() {
    SimpleNeuralNetwork nn(2, 4, 1);
    std::vector<std::vector<double>> training_data = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (int epoch = 0; epoch < 10000; ++epoch) {
        for (const auto& data : training_data) {
            nn.train({data[0], data[1]}, {data[2]});
        }
    }

    for (const auto& data : training_data) {
        auto result = nn.forward({data[0], data[1]});
        std::cout << data[0] << " XOR " << data[1] << " = " << result[0] << std::endl;
    }

    return 0;
}
