# knn
Implementation of the K-nn algorithm in c++

# Nonoptimal design choices made
- No copy constructor provided for Data class + automatic storage used for 1d vector containing data causing entire dataset to be copied.
