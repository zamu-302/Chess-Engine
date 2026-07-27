#include "Core/Board.h"
#include "Core/MoveGen.h"
#include "Core/Preft.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

int main(){
	GameState state;
	std::cout<<preft(state,1)<<'\n';
	std::cout<<preft(state,2)<<'\n';
	std::cout<<preft(state,3)<<'\n';
	std::cout<<preft(state,4)<<'\n';

	return 0;
}