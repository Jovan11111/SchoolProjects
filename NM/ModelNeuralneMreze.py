import tensorflow as tf
from tensorflow.keras.layers import Input, Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from tensorflow.keras.models import Sequential
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.callbacks import ModelCheckpoint, EarlyStopping
from PIL import ImageFile


# This setting allows truncated images to be loaded without raising errors
ImageFile.LOAD_TRUNCATED_IMAGES = True

# Checking for GPU availability
print(tf.config.list_physical_devices('GPU'))

# Setting up data generators for training, validation, and testing
train_datagen = ImageDataGenerator(rescale=1. / 255)
test_val_datagen = ImageDataGenerator(rescale=1. / 255)

# Loading training data from directory
train_generator = train_datagen.flow_from_directory(
    'path_to_archive\\archive\\image_type\\train',
    target_size=(64, 64),  # Resizing images to 64x64
    batch_size=32,
    class_mode='categorical',  # Using categorical mode for multiclass classification
    shuffle=True,
    seed=123
)

# Loading validation data from directory
validation_generator = test_val_datagen.flow_from_directory(
    'path_to_archive\\archive\\image_type\\val',
    target_size=(64, 64),
    batch_size=32,
    class_mode='categorical',
    shuffle=True,
    seed=123
)

# Loading test data from directory
test_generator = test_val_datagen.flow_from_directory(
    'path_to_archive\\archive\\image_type\\test',
    target_size=(64, 64),
    batch_size=32,
    class_mode='categorical',
    shuffle=False  # Keeping the order of data to evaluate predictions correctly
)

# Data augmentation for training images
data_augmentation = Sequential(
    [
        layers.RandomFlip("horizontal", input_shape=(64, 64, 3)),  # Randomly flip images horizontally
        layers.RandomRotation(0.25),  # Randomly rotate images by a maximum of 25 degrees
        layers.RandomZoom(0.1),  # Randomly zoom into images by a maximum of 10%
    ]
)

# Setting class weights for imbalanced classes
sb = 8000  # Adjusting based on the size of each class
class_weights = {0: sb / 7999,
                 1: sb / 1124,
                 2: sb / 7422,
                 3: sb / 8000,
                 4: sb / 7993}

# Defining the CNN model
model = Sequential([
    data_augmentation,
    Conv2D(32, (3, 3), activation='relu'),  # 32 filters with 3x3 kernel size and ReLU activation
    MaxPooling2D(pool_size=(2, 2)),  # Max pooling with 2x2 pool size
    Conv2D(64, (3, 3), activation='relu'),
    MaxPooling2D(pool_size=(2, 2)),
    Conv2D(64, (3, 3), activation='relu'),
    MaxPooling2D(pool_size=(2, 2)),
    Conv2D(64, (3, 3), activation='relu'),
    MaxPooling2D(pool_size=(2, 2)),
    Flatten(),  # Flatten the output for dense layers
    Dense(128, activation='relu'),  # Fully connected layer with 128 units and ReLU activation
    Dropout(0.5),  # Dropout layer to prevent overfitting
    Dense(5, activation='softmax')  # Output layer with 5 units for multiclass classification
])

# Compiling the model
model.compile(optimizer='adam',
              loss='categorical_crossentropy',  # Using categorical crossentropy loss for multiclass classification
              metrics=['accuracy'])

# Setting up callbacks for early stopping and model checkpointing
my_callbacks = [
    EarlyStopping(patience=3, monitor='accuracy'),  # Early stopping to prevent overfitting
    ModelCheckpoint('my_model_training.keras', save_best_only=True, monitor='accuracy')  # Saving the best model
]

# Training the model
history = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // train_generator.batch_size,
    validation_data=validation_generator,
    validation_steps=validation_generator.samples // validation_generator.batch_size,
    epochs=30,
    callbacks=my_callbacks,
    class_weight=class_weights  # Using class weights to handle class imbalance
)

# Evaluating the model on test data
test_loss, test_acc = model.evaluate(test_generator, steps=test_generator.samples // test_generator.batch_size)

# Printing test accuracy
print(test_acc)

# Saving the trained model
model.save('my_model.keras')

# Getting predictions on test data
predictions = model.predict(test_generator, steps=test_generator.samples // test_generator.batch_size)
