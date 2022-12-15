#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <vector>

// Declare the VAE class
class VAE {

public:
  // Constructor for the VAE
  VAE(int input_dim, int latent_dim, int hidden_dim) {
    this->input_dim = input_dim;
    this->latent_dim = latent_dim;
    this->hidden_dim = hidden_dim;

    // Initialize the weights and biases of the encoder and decoder networks
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    // Initialize the weights of the encoder network
    this->W_encoder = std::vector<std::vector<double>>(input_dim, std::vector<double>(hidden_dim));
    for (int i = 0; i < input_dim; i++) {
      for (int j = 0; j < hidden_dim; j++) {
        this->W_encoder[i][j] = distribution(generator);
      }
    }
    this->b_encoder = std::vector<double>(hidden_dim);
    for (int i = 0; i < hidden_dim; i++) {
      this->b_encoder[i] = distribution(generator);
    }

    // Initialize the weights of the decoder network
    this->W_decoder = std::vector<std::vector<double>>(hidden_dim, std::vector<double>(input_dim));
    for (int i = 0; i < hidden_dim; i++) {
      for (int j = 0; j < input_dim; j++) {
        this->W_decoder[i][j] = distribution(generator);
      }
    }
    this->b_decoder = std::vector<double>(input_dim);
    for (int i = 0; i < input_dim; i++) {
      this->b_decoder[i] = distribution(generator);
    }
  }

  // Encoder function
  std::vector<double> encode(std::vector<double> input) {
    // Perform a feedforward calculation on the input to obtain the hidden layer representation
    std::vector<double> hidden_layer(this->hidden_dim);
    for (int i = 0; i < this->hidden_dim; i++) {
      hidden_layer[i] = this->b_encoder[i];
      for (int j = 0; j < this->input_dim; j++) {
        hidden_layer[i] += this->W_encoder[j][i] * input[j];
      }
      hidden_layer[i] = std::max(0.0, hidden_layer[i]); // Apply ReLU activation
    }

    // Sample the latent representation using the reparameterization trick
    std::vector<double> latent_mean(

// Sample the latent representation using the reparameterization trick
std::vector<double> latent_mean(this->latent_dim);
std::vector<double> latent_std(this->latent_dim);
for (int i = 0; i < this->latent_dim; i++) {
  latent_mean[i] = 0.0;
  for (int j = 0; j < this->hidden_dim; j++) {
    latent_mean[i] += this->W_encoder[j][i] * hidden_layer[j];
  }
  latent_mean[i] = sigmoid(latent_mean[i]); // Apply sigmoid activation

  latent_std[i] = 0.0;
  for (int j = 0; j < this->hidden_dim; j++) {
    latent_std[i] += this->W_encoder[j][i] * hidden_layer[j];
  }
  latent_std[i] = sigmoid(latent_std[i]); // Apply sigmoid activation
}

      // Decoder function
std::vector<double> decode(std::vector<double> latent) {
  // Perform a feedforward calculation on the latent representation to obtain the reconstructed input
  std::vector<double> reconstructed_input(this->input_dim);
  for (int i = 0; i < this->input_dim; i++) {
    reconstructed_input[i] = this->b_decoder[i];
    for (int j = 0; j < this->hidden_dim; j++) {
      reconstructed_input[i] += this->W_decoder[j][i] * latent[j];
    }
    reconstructed_input[i] = sigmoid(reconstructed_input[i]); // Apply sigmoid activation
  }

  return reconstructed_input;
}
