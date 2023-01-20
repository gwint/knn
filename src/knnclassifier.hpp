#ifndef KNN_CLASSIFIER_H
#define KNN_CLASSIFIER_H

#include "dataparser.hpp"

/// Class representing a K-nearest neighbors classifier.  Currently,
/// only data containing integer datapoints is allowed.
class KnnClassifier {
	KnnClassifier(int, const Data&);

	int classify();

	double _getDistance();
}

#endif
