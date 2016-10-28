#ifndef RHYTHM_GENERATOR_H_
#define RHYTHM_GENERATOR_H_
#include <memory>
#include "wav_manager.h"
#include "drum_grid.h"
struct Position;
class Mixer;


struct RhythmAttributes {
	int beats_per_measure_;
	int total_measures_;
	int tempo_;
};


class RhythmGenerator {

public:
	RhythmGenerator();
	~RhythmGenerator();

	void add_sample(const std::string& filepath, int columns);
	void change_magnitude(const Position& pos);
	void reset_rhythmicity();
	void reset_grid();
	void update();


private:
	RhythmAttributes rhythmicity_;
	std::shared_ptr<Mixer> mixer_;
	WAVManager manager_;
	DrumGrid grid_;


};


#endif
