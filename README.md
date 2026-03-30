# Weather Forecast Model with Merkle Tree (C++)

## Overview

This project is a **simple weather forecasting simulation written in C++**.
It predicts the **next day's temperature** based on past temperature data and determines the **weather condition** using basic rules.

Additionally, the project uses a **Merkle Tree** to generate a hash that verifies the **integrity of the forecast data**, similar to how blockchain systems ensure data consistency.

---

## Features

* Predict next day **minimum and maximum temperature**
* Calculate **average temperature**
* Determine **weather condition** (Rainy, Hot & Sunny, Cold, Pleasant)
* Generate **Merkle Root Hash** for forecast data integrity
* Clean **object-oriented C++ implementation**

---

## Project Structure

| Class              | Description                                                  |
| ------------------ | ------------------------------------------------------------ |
| `WeatherData`      | Stores minimum and maximum temperature                       |
| `TemperatureModel` | Predicts the next day's temperature based on historical data |
| `WeatherAnalyzer`  | Determines the weather condition                             |
| `SimpleHash`       | Generates hashes using C++ STL hash                          |
| `MerkleTree`       | Creates a Merkle Tree and calculates the Merkle Root         |
| `main()`           | Runs the forecast simulation                                 |

---

## How the Prediction Works

The model calculates the **average change in temperature** from the first day to the last day and applies it to predict the next day's values.

Example:

Past Data

```
Day 1 → 22-30  
Day 2 → 23-31  
Day 3 → 24-32  
Day 4 → 25-33
```

Predicted Next Day

```
26-34
```

---

## Weather Condition Logic

| Condition   | Rule                     |
| ----------- | ------------------------ |
| Rainy       | Temperature range ≤ 5    |
| Hot & Sunny | Average temperature ≥ 30 |
| Cold        | Average temperature < 18 |
| Pleasant    | Otherwise                |

---

## Merkle Tree Usage

The predicted forecast is stored as a record:

```
TemperatureRange-Condition
```

Example:

```
26-34-Hot & Sunny
```

This record is hashed and used to generate a **Merkle Root**, ensuring **forecast data integrity**.

---

## How to Compile and Run

### Compile

```bash
g++ weather_forecast.cpp -o weather
```

### Run

```bash
./weather
```

---

## Example Output

```
Next Day Forecast
Min Temp: 26
Max Temp: 34
Weather: Hot & Sunny
Merkle Root (Forecast Integrity): 734582934823
```

---

## Technologies Used

* **C++**
* **Object Oriented Programming**
* **Standard Template Library (STL)**
* **Hashing**
* **Merkle Tree Concept**

---

## Possible Improvements

* Use **real weather datasets**
* Implement **machine learning prediction**
* Add **multiple forecast records**
* Visualize results
* Implement **SHA-256 instead of STL hash**

---

## Author

Veepin

---

⭐ If you like this project, consider giving it a **star on GitHub**!
