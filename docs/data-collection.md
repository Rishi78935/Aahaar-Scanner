# Data Collection Workflow

1. Connect the AS7341 to the ESP32-S3.
2. Upload `firmware/data_collector.ino`.
3. Confirm the sensor reports `AS7341 DETECTED`.
4. Install Python dependencies: `pip install -r requirements.txt`
5. Set the correct serial `PORT` in `tools/datacollector.py`.
6. Run the logger.
7. Enter the fruit and ripeness labels.
8. Start the capture.
9. Keep the sample position and illumination geometry fixed.
10. Stop the capture after the required measurement period.

## Validation note

The logger can produce many sensor rows from one physical fruit. Those rows are useful for studying sensor stability, but they should not be treated as independent fruit samples when evaluating a classifier.

For meaningful validation, collect multiple physical samples and keep samples from the same physical fruit in only one of train, validation, or test groups.
