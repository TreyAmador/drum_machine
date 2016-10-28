#ifndef MIXER_H_
#define MIXER_H_
#include <vector>
#include <memory>
struct RhythmAttributes;
class WAVManager;
class Compressor;
class DrumGrid;
struct WAV;


class Mixer {

public:
	Mixer();
	~Mixer();

	WAV* mix(WAVManager& manager, DrumGrid& grid, RhythmAttributes& rhythmicity);
	WAV* mix(WAVManager& manager, std::vector<WAV*> channels);
	
	void determine_scaling(int* buffer, int size, float& max_factor, float& min_factor);
	void scale_data(char* data, int* buffer, int size, float& pos_factor, float& neg_factor);

	int* create_buffer(int size);


private:
	std::shared_ptr<Compressor> compressor_;


};


#endif
