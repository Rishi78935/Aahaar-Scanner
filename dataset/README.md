# Dataset

The original project archive contains labeled AS7341 measurements collected during prototype testing.

The dataset format is:

timestamp, fruit, ripeness, F1, F2, F3, F4, F5, F6, F7, F8, NIR, CLEAR

The measurements are experimental and should not be interpreted as scientifically validated evidence of organic certification or food composition.

For reproducible ML work, keep training, validation, and test samples separated by physical sample rather than by individual sensor rows. This reduces leakage from repeated measurements of the same fruit.
