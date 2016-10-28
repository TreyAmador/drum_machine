#ifndef DRUM_GRID_H_
#define DRUM_GRID_H_
#include <ostream>
#include <vector>
#include "drum_measure.h"
class WAVManager;


class DrumGrid {


public:
	DrumGrid();
	~DrumGrid();

	void add_measure(const std::string& key, int columns);
	DrumMeasure& operator[](int i);
	const std::string& key(int i) const;
	std::vector<std::string> keys();
	size_t size();
	void clear_grid();

	friend std::ostream& operator<<(std::ostream& stream, DrumGrid& grid);

private:
	std::vector<DrumMeasure> grid_;

};


#endif
