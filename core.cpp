#include <vector>
#include <string>
#include "core.h"
#include "util.h"
#include "rhythm_generator.h"


Core::Core() {}


Core::~Core() {}


void Core::initialize() {
	
	RhythmGenerator generator;
	
	// practice generation
	generator.change_magnitude({ 0,0 });
	generator.change_magnitude({ 0,4 });
	generator.change_magnitude({ 0,5 });
	generator.change_magnitude({ 0,8 });
	generator.change_magnitude({ 0,12 });
	generator.change_magnitude({ 0,13 });


	generator.change_magnitude({ 1,0 });
	generator.change_magnitude({ 1,1 });
	generator.change_magnitude({ 1,2 });
	generator.change_magnitude({ 1,3 });
	generator.change_magnitude({ 1,4 });
	generator.change_magnitude({ 1,5 });
	generator.change_magnitude({ 1,6 });
	generator.change_magnitude({ 1,7 });
	generator.change_magnitude({ 1,8 });
	generator.change_magnitude({ 1,9 });
	generator.change_magnitude({ 1,10 });
	generator.change_magnitude({ 1,11 });
	generator.change_magnitude({ 1,12 });
	generator.change_magnitude({ 1,13 });
	generator.change_magnitude({ 1,14 });
	generator.change_magnitude({ 1,15 });

	generator.change_magnitude({ 2,0 });
	generator.change_magnitude({ 2,1 });
	generator.change_magnitude({ 2,2 });
	generator.change_magnitude({ 2,4 });
	generator.change_magnitude({ 2,6 });
	generator.change_magnitude({ 2,8 });
	generator.change_magnitude({ 2,9 });
	generator.change_magnitude({ 2,10 });
	generator.change_magnitude({ 2,12 });
	generator.change_magnitude({ 2,14 });

	generator.update();

}

