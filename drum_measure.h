#ifndef DRUM_VERSE_H_
#define DRUM_VERSE_H_
#include <vector>
#include <memory>
#include <string>
#include <map>
class Beat;


class DrumMeasure {


public:
	DrumMeasure(const std::string& key, int col);
	~DrumMeasure();

	void reset(int cols);

	void resize(int cols);
	const std::string& key() const;
	Beat& operator[](int i);
	size_t size();
	void clear();


private:
	std::vector<std::shared_ptr<Beat> > verse_;
	std::string wav_key_;

	//std::map<std::string, std::vector<std::shared_ptr<Beat> > > verse_;

};


#endif
