#pragma once

#include<string>
#include<vector>

#include "json.hpp"
#include "../utils/fileio.h"
#include "../UI/ChessBoard.h"
#include "../utils/utils.h"

using namespace std;
using json = nlohmann::json;
using namespace System;

ref struct AppStates
{
	bool
		showMovePreview = true,
		showTimer = true;

	String^ selectedMusic = gcnew String("");
	String^ selectedTheme = gcnew String("");

	void serialize(json Data) {
		showMovePreview = Data["showMovePreview"].get<bool>();
		showTimer = Data["showTimer"].get<bool>();

		selectedMusic = gcnew String(Data["selectedMusic"].get<string>().c_str());
		selectedTheme = gcnew String(Data["selectedTheme"].get<string>().c_str());
	}
	json deserialize() {
		json result = {
			{"showMovePreview", json::boolean_t(showMovePreview)},
			{"showTimer" 	  , json::boolean_t(showTimer)},

			{"selectedMusic", toStdString(selectedMusic)},
			{"selectedTheme", toStdString(selectedTheme)},
		};

		return result;
	}
};

ref struct GameStates
{
	UI::BoardClass^ boardc;

	bool IsMusicPlaying = false;

	void serialize(json Data) {
		IsMusicPlaying = Data["IsMusicPlaying"].get<bool>();
	}
	json deserialize() {
		// convert array[8][8] to vector[8][8] to use in json
		vector<vector<int>> vboard;
		for (int y = 0; y < 8; y++)
		{
			vector<int> row;
			for (int x = 0; x < 8; x++)
				row.push_back(int(boardc->board[y, x]));

			vboard.push_back(row);
		}

		json result = {
			{"board", vboard},
			{"IsMusicPlaying", json::boolean_t(IsMusicPlaying) },
		};
		return result;
	}
};

void saveData(string path, AppStates^ as, GameStates^ gs) {
	json result = {
		{"AppStates", as->deserialize()},
		{"GameStates", gs->deserialize()},
	};

	writeFile(path, result.dump());
}
void laodData(string path, AppStates^ as, GameStates^ gs) {
	auto jsData = json::parse(readFile(path));

	as->serialize(jsData["AppStates"]);
	gs->serialize(jsData["GameStates"]);
}