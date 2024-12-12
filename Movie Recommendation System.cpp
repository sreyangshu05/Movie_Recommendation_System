#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to load ratings matrix from a CSV file
vector<vector<double>> loadRatingsMatrix(const string &filename) {
    vector<vector<double>> matrix;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            row.push_back(stod(value)); // Convert string to double
        }

        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

// Function to calculate cosine similarity between two users
double calculateSimilarity(const vector<double> &user1, const vector<double> &user2) {
    double dotProduct = 0.0, magnitude1 = 0.0, magnitude2 = 0.0;

    for (size_t i = 0; i < user1.size(); i++) {
        if (user1[i] != 0 && user2[i] != 0) { // Ignore missing ratings
            dotProduct += user1[i] * user2[i];
            magnitude1 += pow(user1[i], 2);
            magnitude2 += pow(user2[i], 2);
        }
    }

    if (magnitude1 == 0 || magnitude2 == 0) return 0.0;

    return dotProduct / (sqrt(magnitude1) * sqrt(magnitude2));
}

// Function to predict a user's rating for a specific movie
double predictRating(const vector<vector<double>> &matrix, int userIndex, int movieIndex) {
    double numerator = 0.0, denominator = 0.0;

    for (size_t i = 0; i < matrix.size(); i++) {
        if (i != userIndex && matrix[i][movieIndex] != 0) {
            double similarity = calculateSimilarity(matrix[userIndex], matrix[i]);
            numerator += similarity * matrix[i][movieIndex];
            denominator += fabs(similarity);
        }
    }

    return (denominator == 0) ? 0 : numerator / denominator;
}

// Function to recommend top N movies for a user
vector<pair<int, double>> recommendMovies(const vector<vector<double>> &matrix, int userIndex, int topN) {
    vector<pair<int, double>> recommendations;

    for (size_t i = 0; i < matrix[userIndex].size(); i++) {
        if (matrix[userIndex][i] == 0) { // Only predict for unrated movies
            double predictedRating = predictRating(matrix, userIndex, i);
            recommendations.push_back({i, predictedRating});
        }
    }

    // Sort recommendations by predicted rating in descending order
    sort(recommendations.begin(), recommendations.end(), [](const pair<int, double> &a, const pair<int, double> &b) {
        return a.second > b.second;
    });

    if (recommendations.size() > topN) {
        recommendations.resize(topN); // Limit to top N recommendations
    }

    return recommendations;
}

// Function to calculate RMSE
double calculateRMSE(const vector<vector<double>> &originalMatrix, const vector<vector<double>> &predictedMatrix) {
    double error = 0.0;
    int count = 0;

    for (size_t i = 0; i < originalMatrix.size(); i++) {
        for (size_t j = 0; j < originalMatrix[i].size(); j++) {
            if (originalMatrix[i][j] != 0) {
                error += pow(originalMatrix[i][j] - predictedMatrix[i][j], 2);
                count++;
            }
        }
    }

    return sqrt(error / count);
}

// Function to print predicted ratings for all unrated movies for a specific user
void printPredictedRatings(const vector<vector<double>> &matrix, int userIndex) {
    cout << "\nPredicted ratings for unrated movies for User " << userIndex << ":\n";
    cout << setw(10) << "Movie ID" << setw(20) << "Predicted Rating" << endl;

    for (size_t i = 0; i < matrix[userIndex].size(); i++) {
        if (matrix[userIndex][i] == 0) {
            double predictedRating = predictRating(matrix, userIndex, i);
            cout << setw(10) << i << setw(20) << fixed << setprecision(2) << predictedRating << endl;
        }
    }
}

// Main function
int main() {
    string filename = "Ratings.csv"; // File containing the ratings matrix
    vector<vector<double>> ratingsMatrix = loadRatingsMatrix(filename);

    // User input for choosing the target user
    int userIndex, topN;
    cout << "Enter the user index (0 to " << ratingsMatrix.size() - 1 << "): ";
    cin >> userIndex;

    while (userIndex < 0 || userIndex >= ratingsMatrix.size()) {
        cout << "Invalid user index. Please try again: ";
        cin >> userIndex;
    }

    cout << "Enter the number of top recommendations to display: ";
    cin >> topN;

    // Predict ratings for all users (for performance evaluation)
    vector<vector<double>> predictedMatrix = ratingsMatrix;
    for (size_t i = 0; i < ratingsMatrix.size(); i++) {
        for (size_t j = 0; j < ratingsMatrix[i].size(); j++) {
            if (ratingsMatrix[i][j] == 0) {
                predictedMatrix[i][j] = predictRating(ratingsMatrix, i, j);
            }
        }
    }

    // Display predicted ratings for unrated movies for the target user
    printPredictedRatings(ratingsMatrix, userIndex);

    // Generate and display top N recommendations for the chosen user
    vector<pair<int, double>> recommendations = recommendMovies(ratingsMatrix, userIndex, topN);
    cout << "\nTop " << topN << " recommendations for User " << userIndex << ":\n";
    cout << setw(10) << "Movie ID" << setw(20) << "Predicted Rating" << endl;

    for (const auto &rec : recommendations) {
        cout << setw(10) << rec.first << setw(20) << fixed << setprecision(2) << rec.second << endl;
    }

    // Evaluate and display performance using RMSE
    double rmse = calculateRMSE(ratingsMatrix, predictedMatrix);
    cout << "\nRoot Mean Square Error (RMSE): " << fixed << setprecision(4) << rmse << endl;

    return 0;
}
