#include <vector>
#include <string>
#include "rhythm_generator.h"
#include "mixer.h"
#include "beat.h"
#include "util.h"
#include "wav.h"

// testing, testing
#include "converter.h"


namespace {
	//const std::string DEFAULT_KICK = "samples/Kick_01.wav";
	//const std::string DEFAULT_SNARE = "samples/Snare_11.wav";
	//const std::string DEFAULT_HAT_CLOSED = "samples/Hat_Closed_05.wav";

	const std::string DEFAULT_KICK = "samples/bassdrum36.wav";
	const std::string DEFAULT_SNARE = "samples/snaredrum34.wav";
	const std::string DEFAULT_HAT_CLOSED = "samples/hihat1.wav";

	const int DEFAULT_MEASURE_TEMPOS = 16;
	const int DEFAULT_NUMBER_DRUMS = 3;

	const int DEFAULT_BEATS_PER_MEASURE = 4;
	const int DEFAULT_MEASURES = 2;
	const int DEFAULT_TEMPO = 120;

}


RhythmGenerator::RhythmGenerator() :
	mixer_(std::make_shared<Mixer>()), grid_(), manager_()
{
	reset_rhythmicity();
	reset_grid();
}


RhythmGenerator::~RhythmGenerator() {
	manager_.clear_wav_files();
	grid_.clear_grid();
	mixer_.reset();
}


void RhythmGenerator::reset_grid() {
	manager_.clear_wav_files();
	grid_.clear_grid();
	std::vector<std::string> keys = { DEFAULT_KICK, DEFAULT_SNARE, DEFAULT_HAT_CLOSED };	
	for (int i = 0; i < DEFAULT_NUMBER_DRUMS; ++i) {
		manager_.add_wav(keys[i]);
		grid_.add_measure(keys[i], DEFAULT_MEASURE_TEMPOS);
	}
	keys.clear();
	keys.shrink_to_fit();
}


void RhythmGenerator::reset_rhythmicity() {
	rhythmicity_ = { DEFAULT_BEATS_PER_MEASURE, DEFAULT_MEASURES, DEFAULT_TEMPO };
}


void RhythmGenerator::add_sample(const std::string& filepath, int columns) {
	manager_.add_wav(filepath);
}


void RhythmGenerator::change_magnitude(const Position& pos) {
	if (pos.r_ >= static_cast<int>(grid_.size()) ||
		pos.c_ >= static_cast<int>(grid_[0].size())){
		return;
	}
	grid_[pos.r_][pos.c_].change_magnitude();
}


void RhythmGenerator::update() {

	//std::cout << "Drum Pattern\n" << grid_ << std::endl;
	//manager_.write_wav(mixer_->mix(manager_, grid_, rhythmicity_), "output/mix_measure.wav");
	//std::cout << manager_[0] << std::endl;

	
	Converter converter;
	WAV* pre_convert = manager_.add_wav("samples/bassdrum36.wav");
	WAV* prototype = manager_.add_wav("samples/Snare_11.wav");
	WAV* post_convert = converter.convert(prototype, pre_convert);
	std::cout << 
		"\nPrototype\n" << prototype << 
		"\nPre-convert\n" << pre_convert << 
		"\nPost-convert\n" << post_convert << std::endl;
	manager_.write_wav(post_convert, "output/convert_channel.wav");
	
}

