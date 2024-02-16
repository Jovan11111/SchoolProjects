# Convolutional Neural Network for Image Classification

This repository contains a Convolutional Neural Network (CNN) implemented using TensorFlow and Keras for image classification tasks. The CNN is trained to classify images into multiple classes: photography, sketch, drawing, and scheme. It uses a dataset organized into training, validation, and test sets.
Project done for faculty course "Neural Networks". 

## Requirements

- Python 3.x
- TensorFlow 2.x
- Keras
- NumPy
- PIL (Python Imaging Library)

## Installation

1. Clone this repository to your local machine:

    ```bash
    git clone <repository_url>
    ```

2. Install the required dependencies using pip:

    ```bash
    pip install -r requirements.txt
    ```

## Usage

1. Prepare your dataset: Organize your image dataset into the following directory structure:

    ```
    ├── dataset
    │   ├── train
    │   │   ├── photography
    │   │   ├── sketch
    │   │   ├── drawing
    │   │   ├── scheme
    │   ├── val
    │   │   ├── photography
    │   │   ├── sketch
    │   │   ├── drawing
    │   │   ├── scheme
    │   ├── test
    │   │   ├── photography
    │   │   ├── sketch
    │   │   ├── drawing
    │   │   ├── scheme
    ```

    Ensure that images are properly labeled and placed in the corresponding class directories.

2. Update the paths in the code: Modify the paths in the code to point to the correct locations of your dataset.

3. Run the code: Execute the Python script to train the CNN and evaluate its performance.

    ```bash
    python ModelNeuralneMreze.py
    ```

## Model Architecture

The CNN model architecture used in this code consists of the following layers:

1. Data Augmentation: Randomly flip, rotate, and zoom images for increased variation during training.
2. Convolutional Layers: Multiple convolutional layers with ReLU activation followed by max-pooling layers to extract features from input images.
3. Flatten Layer: Flatten the output of convolutional layers to feed into fully connected layers.
4. Fully Connected Layers: Dense layers with ReLU activation and dropout to perform classification.
5. Output Layer: Dense layer with softmax activation for multi-class classification.

## Training

- The model is trained using the `fit()` function, with early stopping and model checkpointing callbacks to prevent overfitting and save the best model during training.
- Class weights are utilized to handle class imbalance in the dataset.
- Training and validation accuracy and loss are monitored during training.

## Evaluation

- The trained model is evaluated on the test dataset to assess its performance.
- Test accuracy is reported as the evaluation metric.
