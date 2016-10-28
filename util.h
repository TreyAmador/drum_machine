#ifndef UTIL_H_
#define UTIL_H_


struct Position {
	int r_, c_;
	Position(const Position& position) :
		r_(position.r_), c_(position.c_)
	{}
	Position(int r, int c) : 
		r_(r), c_(c)
	{}
};


struct Dimensions {
	int r_, c_;
	Dimensions(const Dimensions& dimension) :
		r_(dimension.r_), c_(dimension.c_)
	{}
	Dimensions(int r, int c) :
		r_(r), c_(c)
	{}
};

#endif
