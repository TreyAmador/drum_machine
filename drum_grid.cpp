#include <iomanip>
#include <memory>
#include "drum_grid.h"
#include "wav_manager.h"
#include "beat.h"


DrumGrid::DrumGrid() {}


DrumGrid::~DrumGrid() {
	clear_grid();
}


void DrumGrid::add_measure(const std::string& key, int columns) {
	grid_.push_back(DrumMeasure(key, columns));
}


DrumMeasure& DrumGrid::operator[](int i) {
	return grid_[i];
}


const std::string& DrumGrid::key(int i) const {
	return grid_[i].key();
}


std::vector<std::string> DrumGrid::keys() {
	std::vector<std::string> keys;
	for (auto iter = grid_.begin(); iter != grid_.end(); ++iter) {
		keys.push_back(iter->key());
	}
	return keys;
}


void DrumGrid::clear_grid() {
	grid_.clear();
	grid_.shrink_to_fit();
}


size_t DrumGrid::size() {
	return grid_.size();
}


std::ostream& operator<<(std::ostream& stream, DrumGrid& grid) {
	
	auto iter = grid.grid_.begin();
	size_t largest = iter->key().size();
	++iter;
	while (iter != grid.grid_.end()) {
		size_t current = iter->key().size();
		if (largest < current)
			largest = iter->key().size();
		++iter;
	}

	for (size_t r = 0; r < grid.size(); ++r) {
		stream << std::left << std::setw(largest) << grid[r].key() << "  ";
		for (size_t c = 0; c < grid[r].size(); ++c)
			stream << grid[r][c].magnitude() << "  ";
		stream << "\n";
	}
	return stream;
}

