# Movie Recommendation System

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Components and Functions](#components-and-functions)
  - [Loading the Ratings Matrix](#loading-the-ratings-matrix)
  - [Calculating Similarity](#calculating-similarity)
  - [Predicting Ratings](#predicting-ratings)
  - [Generating Recommendations](#generating-recommendations)
  - [Calculating RMSE](#calculating-rmse)
- [Output Format](#output-format)
---

## Introduction

The **Movie Recommendation System** is a C++ application that predicts user ratings for movies they haven't rated and recommends the top-rated movies based on collaborative filtering. The project uses cosine similarity to calculate user similarities and generate personalized movie recommendations.

---

## Features

- Load ratings data from a CSV file.
- Predict ratings for unrated movies for a specific user.
- Generate a ranked list of top N recommended movies.
- Display recommendations and predictions in a clear, tabular format.
- Evaluate the system's accuracy using RMSE (Root Mean Square Error).

---

## Prerequisites

- A C++ compiler (e.g., GCC, Clang).
- A ratings dataset in CSV format.
- Basic understanding of collaborative filtering and cosine similarity.

---

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/sreyangshu05/Movie_Recommendation_System.git
   cd Movie_Recommendation_System
2. Ensure your ratings CSV file (e.g., Ratings.csv) is in the project directory.


## Components and Functions:

### Loading the Ratings Matrix: 
- Function: loadRatingsMatrix
- Reads the ratings dataset from a CSV file.
- Converts the data into a 2D vector of doubles.
- Handles file opening errors gracefully.

### Calculating Similarity:
- Function: calculateSimilarity
- Computes cosine similarity between two users based on their ratings.
- Ignores movies that are unrated by either user.
- Returns a similarity score between 0 and 1.

### Predicting Ratings:
- Function: predictRating
- Predicts a user's rating for a specific movie using weighted averages.
- Weights are based on cosine similarity scores.

### Generating Recommendations:
- Function: recommendMovies
- Predicts ratings for all unrated movies for a user.
- Sorts the predicted ratings in descending order.
- Returns the top N recommendations.

### Calculating RMSE:
- Function: calculateRMSE
- Compares original ratings with predicted ratings.
- Computes the Root Mean Square Error (RMSE) to evaluate the model's accuracy.

## Output Format:
- Predicted Ratings: Displays all unrated movies for the selected user and their predicted ratings.
- Top N Recommendations: Outputs a ranked list of the top N movies for the user.
- Model Accuracy: Displays the Root Mean Square Error (RMSE) to evaluate prediction accuracy.
