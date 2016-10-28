#include <memory>
#include "beat.h"


Beat::Beat() :
	magnitude_(0)
{}


Beat::~Beat() {}


void Beat::change_magnitude() {
	magnitude_ == 0 ? magnitude_ = 2 : --magnitude_;
}


void Beat::play() {
	// play da beat!
}


const int Beat::magnitude() const {
	return magnitude_;
}

