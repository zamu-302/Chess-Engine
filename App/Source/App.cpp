#include "Core/Board.h"
#include "Core/MoveGen.h"
#include "Core/lookuptabel.h"
#include "Core/Evaluation.h"
#include "Core/Search.h"


#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

static const std::string StartFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

static char promotionChar(PieceType piece)
{
	switch (piece)
	{
	case PieceType::Queen: return 'q';
	case PieceType::Rook: return 'r';
	case PieceType::Bishop: return 'b';
	case PieceType::Knight: return 'n';
	default: return '\0';
	}
}

static std::string moveToUci(const Move& move)
{
	std::string text;
	int fromCol=move.from%8;
	int fromRow=move.from/8;
	int toCol=move.to%8;
	int toRow=move.to/8;
	text += static_cast<char>('a' + fromCol);
	text += static_cast<char>('8' - fromRow);
	text += static_cast<char>('a' + toCol);
	text += static_cast<char>('8' - toRow);

	char promo = promotionChar(move.PromotionPiece);
	if (promo != '\0')
		text += promo;

	return text;
}

static bool sameUciMove(const Move& move, const std::string& text)
{
	return moveToUci(move) == text;
}

static bool playUciMove(GameState& state, const std::string& text)
{
	std::vector<Move> moves = generateLegalMoves(state);

	auto it = std::find_if(moves.begin(), moves.end(), [&](const Move& move) {
		return sameUciMove(move, text);
	});

	if (it == moves.end())
	{
		moves = generateLegalMoves(state);
		it = std::find_if(moves.begin(), moves.end(), [&](const Move& move) {
			return sameUciMove(move, text);
		});
	}

	if (it == moves.end())
		return false;

	state.Makemove(*it);
	return true;
}

static void setPosition(GameState& state, const std::string& line)
{
	std::istringstream stream(line);
	std::string token;
	stream >> token; // position
	stream >> token;

	if (token == "startpos")
	{
		state.LoadFEN(StartFen);
		stream >> token;
	}
	else if (token == "fen")
	{
		std::string fen;
		for (int i = 0; i < 6 && stream >> token; ++i)
		{
			if (i > 0)
				fen += ' ';
			fen += token;
		}
		state.LoadFEN(fen);
		stream >> token;
	}

	if (token != "moves")
		return;

	while (stream >> token)
		playUciMove(state, token);
}



int main()
{
	initMagicTables();
	GameState state;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line == "uci")
		{
			std::cout << "id name StockFishofOurHeart\n";
			std::cout << "id author AFROCHEM\n";
			std::cout << "uciok\n";
		}
		else if (line == "isready")
		{
			std::cout << "readyok\n";
		}
		else if (line == "ucinewgame")
		{
			state.LoadFEN(StartFen);
		}
		else if (line.rfind("position", 0) == 0)
		{
			setPosition(state, line);
		}
		else if (line.rfind("go", 0) == 0)
		{
			Move move = selectBestMove(state,3);

			if (move.from == -1)
			{
				std::cout << "bestmove 0000\n";
			}
			else
			{
				std::cout << "bestmove " << moveToUci(move) << "\n";
			}
		}
		else if (line == "quit")
		{
			break;
		}

		std::cout.flush();
	}
}
