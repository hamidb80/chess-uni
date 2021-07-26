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
using namespace System::Collections::Generic;
using namespace UI;

ref struct AppStates
{
	ThemeOptions^ selectedTheme;
	
	bool showTimer = true;
	int restTime = 0;

	bool IsMusicPlaying = false;
	String^ selectedMusic = gcnew String("");
	List<MyFileInfo^>^ musicList; // todo
	
	cli::array<ChessPieces, 2>^ board;
	
	void deserialize(json Data) {
		restTime = Data["restTime"].get<int>();
		showTimer = Data["showTimer"].get<bool>();
		IsMusicPlaying = Data["IsMusicPlaying"].get<bool>();
		selectedMusic = gcnew String(Data["selectedMusic"].get<string>().c_str());

		selectedTheme->pieciesThemeStyle = PieciesThemeStyle(Data["theme-style"].get<int>());
		selectedTheme->pieciesThemeColor = PieciesThemeColor(Data["theme-color"].get<int>());
		selectedTheme->boardBackTheme = BoardBackTheme(Data["theme-bg"].get<int>());
		selectedTheme->showMovePreview = Data["showMovePreview"].get<bool>();

		for (int y = 0; y < 8; y++)
			for (int x = 0; x < 8; x++)
				board[y, x] = ChessPieces(Data["board"][y][x].get<int>());
	}
	json serialize() {
		vector<vector<int>> vboard;
		for (int y = 0; y < 8; y++)
		{
			vector<int> row; for (int x = 0; x < 8; x++)
				row.push_back(int(board[y, x]));

			vboard.push_back(row);
		}

		return json{
			{"board", vboard},

			{"showTimer", selfGet(showTimer)},
			{"restTime", selfGet(restTime) },

			{"selectedMusic", toStdString(selectedMusic)},
			{"IsMusicPlaying", selfGet(this->IsMusicPlaying)},

			{"showMovePreview", selfGet(selectedTheme->showMovePreview) },
			{"theme-style", selfGet(int(selectedTheme->pieciesThemeStyle)) },
			{"theme-color", selfGet(int(selectedTheme->pieciesThemeColor)) },
			{"theme-bg", selfGet(int(selectedTheme->boardBackTheme))},
		};
	}
};

void saveData(string path, AppStates^ dest) {
	json result = dest->serialize();
	writeFile(path, result.dump());
}
void laodData(string path, AppStates^ dest) {
	auto jsData = json::parse(readFile(path));
	dest->deserialize(jsData);
}