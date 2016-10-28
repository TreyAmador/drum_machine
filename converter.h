#ifndef CONVERTER_H_
#define CONVERTER_H_
struct WAV;


class Converter {


public:
	Converter();
	~Converter();

	WAV* convert(WAV* prototype, WAV* uncoverted);
	void copy_tag(char* dest, char* source);
	void copy_data(WAV* dest, WAV* source);

	void alter_num_channels(WAV* wav, short channels);
	//void alter_sample_rate(int* dest, int* source, WAV* wav);
	//void alter_byte_rate(int* dest, int* source, WAV* wav);
	//void alter_block_align(short* dest, short* source, WAV* wav);
	//void alter_bits_per_sample(short* dest, short* source, WAV* wav);

	WAV* test_irreconcilables(WAV* converted, WAV* prototye);

	char* create_buffer(int bytes);
	void clean_up(WAV* wav, short channels, short prev_channels);


private:



};


#endif
