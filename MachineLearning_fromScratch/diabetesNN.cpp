#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>

class DiabetesNeuralNetwork {
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
    DiabetesNeuralNetwork(const std::vector<int>& layer_sizes, double lr = 0.01) : learning_rate(lr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        for (size_t i = 1; i < layer_sizes.size(); ++i) {
            weights.push_back(std::vector<double>(layer_sizes[i-1] * layer_sizes[i]));
            biases.push_back(0.0);
            for (auto& weight : weights.back()) {
                weight = dis(gen);
            }
        }
    }

    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<std::vector<double>> activations = {input};
        for (size_t i = 0; i < weights.size(); ++i) {
            std::vector<double> layer_output(weights[i].size() / activations.back().size());
            for (size_t j = 0; j < layer_output.size(); ++j) {
                double sum = 0.0;
                for (size_t k = 0; k < activations.back().size(); ++k) {
                    sum += activations.back()[k] * weights[i][j * activations.back().size() + k];
                }
                layer_output[j] = sigmoid(sum + biases[i]);
            }
            activations.push_back(layer_output);
        }
        return activations.back();
    }

    void train(const std::vector<double>& input, const std::vector<double>& target) {
        std::vector<std::vector<double>> activations = {input};
        std::vector<std::vector<double>> zs;

        // Forward pass
        for (size_t i = 0; i < weights.size(); ++i) {
            std::vector<double> z(weights[i].size() / activations.back().size());
            std::vector<double> activation(z.size());
            for (size_t j = 0; j < z.size(); ++j) {
                double sum = 0.0;
                for (size_t k = 0; k < activations.back().size(); ++k) {
                    sum += activations.back()[k] * weights[i][j * activations.back().size() + k];
                }
                z[j] = sum + biases[i];
                activation[j] = sigmoid(z[j]);
            }
            zs.push_back(z);
            activations.push_back(activation);
        }

        // Backward pass
        std::vector<std::vector<double>> deltas;
        for (size_t i = 0; i < target.size(); ++i) {
            deltas.push_back({(activations.back()[i] - target[i]) * sigmoid_derivative(activations.back()[i])});
        }

        for (int i = weights.size() - 2; i >= 0; --i) {
            std::vector<double> delta(weights[i].size() / weights[i+1].size());
            for (size_t j = 0; j < delta.size(); ++j) {
                double error = 0.0;
                for (size_t k = 0; k < deltas.back().size(); ++k) {
                    error += deltas.back()[k] * weights[i+1][k * delta.size() + j];
                }
                delta[j] = error * sigmoid_derivative(activations[i+1][j]);
            }
            deltas.push_back(delta);
        }
        std::reverse(deltas.begin(), deltas.end());

        // Update weights and biases
        for (size_t i = 0; i < weights.size(); ++i) {
            for (size_t j = 0; j < deltas[i].size(); ++j) {
                for (size_t k = 0; k < activations[i].size(); ++k) {
                    weights[i][j * activations[i].size() + k] -= learning_rate * deltas[i][j] * activations[i][k];
                }
                biases[i] -= learning_rate * deltas[i][j];
            }
        }
    }
};

std::vector<std::vector<double>> load_csv(const std::string& filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        data.push_back(row);
    }

    return data;
}

int main() {
    auto data = load_csv("diabetes.csv");
    DiabetesNeuralNetwork nn({8, 16, 8, 1});

    // Normalize data
    std::vector<double> min_values(8, std::numeric_limits<double>::max());
    std::vector<double> max_values(8, std::numeric_limits<double>::lowest());

    for (const auto& row : data) {
        for (size_t i = 0; i < 8; ++i) {
            min_values[i] = std::min(min_values[i], row[i]);
            max_values[i] = std::max(max_values[i], row[i]);
        }
    }

    for (auto& row : data) {
        for (size_t i = 0; i < 8; ++i) {
            row[i] = (row[i] - min_values[i]) / (max_values[i] - min_values[i]);
        }
    }

    // Train the network
    for (int epoch = 0; epoch < 1000; ++epoch) {
        for (const auto& row : data) {
            std::vector<double> input(row.begin(), row.begin() + 8);
            std::vector<double> target = {row[8]};
            nn.train(input, target);
        }
    }

    // Test the network
    int correct = 0;
    for (const auto& row : data) {
        std::vector<double> input(row.begin(), row.begin() + 8);
        auto output = nn.forward(input);
        int predicted = output[0] > 0.5 ? 1 : 0;
        int actual = row[8];
        if (predicted == actual) {
            correct++;
        }
    }

    double accuracy = static_cast<double>(correct) / data.size();
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;

    return 0;
}
