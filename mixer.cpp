#include "mixer.h"
#include "rhythm_generator.h"
#include "wav_manager.h"
#include "compressor.h"
#include "drum_grid.h"
#include "beat.h"
#include "wav.h"


Mixer::Mixer() :
	compressor_(std::make_shared<Compressor>())
{}


Mixer::~Mixer() {
	compressor_.reset();
}


WAV* Mixer::mix(WAVManager& manager, DrumGrid& grid, RhythmAttributes& rhythmicity) {

	WAV* mixed_wav = manager.create_sized_given_format(manager[0], manager.create_buffer_size(manager[0], rhythmicity));
	int bytes = *mixed_wav->header_->data_length_;
	int interval = bytes / grid[0].size();
	int* buffer = create_buffer(bytes);

	for (size_t r = 0; r < grid.size(); ++r) {
		WAV* wav = manager[grid.key(r)];
		int size = *wav->header_->data_length_;
		for (size_t c = 0; c < grid[r].size(); ++c) {
			if (grid[r][c].magnitude() > 0) {
				int init_byte = c*interval;
				for (int w = 0, i = init_byte; w < size && i < bytes; ++w, ++i) {
					buffer[i] += wav->body_->data_[w];
				}
			}
		}
	}

	// very rough scaling...
	// use compression next!
	for (int i = 0; i < bytes; ++i) {
		mixed_wav->body_->data_[i] = (char)(buffer[i] / 2);
	}

	delete[] buffer;
	return mixed_wav;
}



WAV* Mixer::mix(WAVManager& manager, std::vector<WAV*> channels) {

	WAV* mixed_wav = manager.create_sized_given_format(channels[0], manager.largest_data_size(channels));
	int data_length = *mixed_wav->header_->data_length_;
	int* buffer = new int[data_length];
	for (int i = 0; i < data_length; ++i)
		buffer[i] = 0;

	for (size_t c = 0; c < channels.size(); ++c) {
		int size_c = *channels[c]->header_->data_length_;
		for (int i = 0; i < size_c; ++i)
			buffer[i] += channels[c]->body_->data_[i];
	}

	float max_factor = 1.0f, min_factor = -1.0f;
	determine_scaling(buffer, data_length, max_factor, min_factor);
	scale_data(mixed_wav->body_->data_, buffer, data_length, max_factor, min_factor);

	delete[] buffer;
	return mixed_wav;
}


// these are bad scaling algorithms
void Mixer::determine_scaling(int* buffer, int size, float& max_factor, float& min_factor) {
	int max = 1, min = -1;
	for (int i = 0; i < size; ++i) {
		if (buffer[i] > max) {
			max = buffer[i];
		}
		else if (buffer[i] < min) {
			min = buffer[i];
		}
	}
	max_factor = 127.0f / max;
	min_factor = 128.0f / min;
}


// these are bad scaling algorithms
void Mixer::scale_data(char* data, int* buffer, int size, float& pos_scale, float& neg_scale) {
	for (int i = 0; i < size; ++i) {
		if (buffer[i] > 0)
			data[i] = (char)(buffer[i] * pos_scale);
		else if (buffer[i] < 0)
			data[i] = (char)(buffer[i] * neg_scale);
	}
}


int* Mixer::create_buffer(int size) {
	int* buffer = new int[size];
	for (int i = 0; i < size; ++i)
		buffer[i] = 0;
	return buffer;
}

