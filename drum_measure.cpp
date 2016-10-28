#include "drum_measure.h"
#include "beat.h"
#include "util.h"


DrumMeasure::DrumMeasure(const std::string& key, int col) :
	wav_key_(key)
{
	reset(col);
}


DrumMeasure::~DrumMeasure() {
	clear();
}


void DrumMeasure::reset(int cols) {
	clear();
	for (int c = 0; c < cols; ++c)
		verse_.push_back(std::make_shared<Beat>());
}


void DrumMeasure::resize(int columns) {
	clear();
	for (int c = 0; c < columns; ++c)
		verse_.push_back(std::make_shared<Beat>());
}


const std::string& DrumMeasure::key() const {
	return wav_key_;
}


Beat& DrumMeasure::operator[](int i) {
	return *verse_[i];
}


void DrumMeasure::clear() {
	for (auto iter = verse_.begin(); iter != verse_.end(); ++iter) {
		iter->reset();
	}
	verse_.clear();
	verse_.shrink_to_fit();
}


size_t DrumMeasure::size() {
	return verse_.size();
}

