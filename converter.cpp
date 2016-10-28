#include "converter.h"
#include "wav.h"


namespace {
	const int BITS_PER_BYTE = 8;
	const int TAG_SIZE = 4;
}


Converter::Converter() {}


Converter::~Converter() {}


WAV* Converter::convert(WAV* prototype, WAV* unconverted) {

	WAV* converted = new WAV;

	copy_tag(converted->header_->riff_tag_, prototype->header_->riff_tag_);
	copy_tag(converted->header_->wav_tag_, prototype->header_->wav_tag_);
	copy_tag(converted->header_->fmt_tag_, prototype->header_->fmt_tag_);
	copy_tag(converted->header_->data_tag_, prototype->header_->data_tag_);
	copy_data(converted, unconverted);

	*converted->header_->fmt_length_ = *unconverted->header_->fmt_length_;
	*converted->header_->audio_format_ = *unconverted->header_->audio_format_;
	*converted->header_->num_channels_ = *unconverted->header_->num_channels_;
	*converted->header_->sample_rate_ = *unconverted->header_->sample_rate_;
	*converted->header_->byte_rate_ = *unconverted->header_->byte_rate_;
	*converted->header_->block_align_ = *unconverted->header_->block_align_;
	*converted->header_->bits_per_sample_ = *unconverted->header_->bits_per_sample_;

	alter_num_channels(converted, *prototype->header_->num_channels_);

	return test_irreconcilables(converted, prototype);
}


void Converter::copy_tag(char* dest, char* source) {
	for (int i = 0; i < TAG_SIZE; ++i)
		dest[i] = source[i];
}


void Converter::copy_data(WAV* dest, WAV* source) {
	*dest->header_->riff_length_ = *source->header_->riff_length_;
	*dest->header_->data_length_ = *source->header_->data_length_;
	int size = *dest->header_->data_length_;
	dest->body_->data_ = new char[size + 1];
	dest->body_->data_[size] = '\0';
	for (int i = 0; i < size; ++i)
		dest->body_->data_[i] = source->body_->data_[i];
}


void Converter::alter_num_channels(WAV* wav, short channels) {

	// assuming need to add channels for now...
	short intial_channels = *wav->header_->num_channels_;
	int intial_bytes = *wav->header_->data_length_;
	int final_bytes = (intial_bytes * channels) / intial_channels;
	int bytes_per_sample = *wav->header_->bits_per_sample_ / BITS_PER_BYTE;
	int samples = intial_bytes / bytes_per_sample;
	char* buffer = create_buffer(final_bytes);

	int c_i = intial_channels;
	int c_f = channels;
	for (int s_i = 0, s_f = 0; s_i < samples && s_f < c_f * samples; s_i += c_i, s_f += c_f) {
		int b_i = bytes_per_sample * s_i;
		int b_f = bytes_per_sample * s_f;
		for (int i = 0; i < bytes_per_sample; i++) {
			for (int c = 0; c < c_f; ++c) {
				int d_i = c * bytes_per_sample;
				buffer[b_f+d_i+i] = wav->body_->data_[b_i+i];
			}
		}
	}

	delete[] wav->body_->data_;
	wav->body_->data_ = buffer;

	*wav->header_->num_channels_ = channels;
	*wav->header_->byte_rate_ = (*wav->header_->byte_rate_ * channels) / intial_channels;
	*wav->header_->block_align_ = (*wav->header_->block_align_ * channels) / intial_channels;
	*wav->header_->data_length_ = (*wav->header_->data_length_ * channels) / intial_channels;
	*wav->header_->riff_length_ = *wav->header_->data_length_ + 36;
}








char* Converter::create_buffer(int bytes) {
	char* buffer = new char[bytes+1];
	buffer[bytes] = '\0';
	for (int i = 0; i < bytes; ++i)
		buffer[i] = 0;
	return buffer;
}


void Converter::clean_up(WAV* wav, short channels, short prev_channels) {

}


WAV* Converter::test_irreconcilables(WAV* converted, WAV* prototype) {
	if (*converted->header_->fmt_length_ != *prototype->header_->fmt_length_)
		return nullptr;
	if (*converted->header_->audio_format_ != *prototype->header_->audio_format_)
		return nullptr;
	return converted;
}

