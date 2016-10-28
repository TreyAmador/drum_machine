#ifndef BEAT_H_
#define BEAT_H_
#include <iostream>


class Beat {

public:
	Beat();
	~Beat();

	void change_magnitude();
	void play();
	const int magnitude() const;


private:
	int magnitude_;


};


#endif
