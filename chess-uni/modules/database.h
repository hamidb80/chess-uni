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
	bool IsMusicPlaying = false;
	String^ selectedMusic = gcnew String("");
	cli::array<ChessPieces, 2>^ board;
	List<MyFileInfo^>^ musicList; // (name, path)

	void deserialize(json Data) {
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

			{"selectedMusic", toStdString(selectedMusic)},
			{"showTimer", selfGet(showTimer)},
			{"IsMusicPlaying", selfGet(this->IsMusicPlaying)},

			{"showMovePreview", selfGet(selectedTheme->showMovePreview) },
			{"theme-style", selfGet(int(selectedTheme->pieciesThemeStyle)) },
			{"theme-color", selfGet(int(selectedTheme->pieciesThemeColor)) },
			{"theme-bg", selfGet(int(selectedTheme->boardBackTheme))},
		};
	}
};

void saveData(string path, AppStates^ as) {
	json result = as->serialize();
	writeFile(path, result.dump());
}
void laodData(string path, AppStates^ as) {
	auto jsData = json::parse(readFile(path));
	as->deserialize(jsData);
}