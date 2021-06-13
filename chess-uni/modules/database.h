#pragma once

#include<string>
#include<vector>

#include "json.hpp"
#include "../utils/fileio.h"

using namespace std;
using json = nlohmann::json;

struct AppStates
{
	bool
		canUndo = false,
		showMovePreview = true,
		showTimer = true
		;

	string
		selectedMusic = "",
		selectedTheme = "",
		
		host_name = "",
		client_name = ""
		;

	void serialize(json Data) {
		canUndo = Data["canUndo"].get<bool>();
		showMovePreview = Data["showMovePreview"].get<bool>();
		showTimer = Data["showTimer"].get<bool>();
		
		selectedMusic = Data["selectedMusic"].get<string>();
		selectedTheme = Data["selectedTheme"].get<string>();
		
		host_name = Data["host_name"].get<string>();
		client_name = Data["client_name"].get<string>();
	}
	json deserialize() {
		json result = {
			{"canUndo" 		  , canUndo},
			{"showMovePreview", showMovePreview},
			{"showTimer" 	  , showTimer},

			{"selectedMusic", selectedMusic},
			{"selectedTheme", selectedTheme},

			{"host_name", host_name		   },
			{"client_name", client_name	   }
		};

		return result;
	}
};
struct ClientPermissions
{
	bool
		canControlMusic = false, // upload, play, pause, ...
		canControlTimer = false
		;

	void serialize(json Data) {
		canControlMusic = Data["canControlMusic"].get<bool>();
		canControlTimer = Data["canControlTimer"].get<bool>();
	}
	json deserialize() {
		json result = {
			{"canControlMusic",canControlMusic},
			{"canControlTimer", canControlTimer}
		};
		return result;
	}
};
struct GameStates
{
	int board[8][8] = { {0} }; // TODO: replace with ChessPieces

	bool
		IsMusicPlaying = false,
		isUndoEnabled = true
		;

	void serialize(json Data) {
		IsMusicPlaying = Data["IsMusicPlaying"].get<bool>();
		isUndoEnabled = Data["isUndoEnabled"].get<bool>();
	}
	json deserialize() {
		// convert array[8][8] to vector[8][8] to use in json
		vector<vector<int>> vboard;
		for (int y = 0; y < 8; y++)
		{
			vector<int> row;
			for (int x = 0; x < 8; x++)
				row.push_back(board[y][x]);

			vboard.push_back(row);
		}

		json result = {
			{"board", vboard},
			{"IsMusicPlaying", IsMusicPlaying },
			{"isUndoEnabled", isUndoEnabled},
		};
		return result;
	}
};

void saveData(string path, AppStates as, ClientPermissions cp, GameStates gs) {
	json result = {
		{"AppStates", as.deserialize()},
		{"ClientPermissions", cp.deserialize()},
		{"GameStates", gs.deserialize()},
	};

	writeFile(path, result.dump());
}
void laodData(string path, AppStates* as, ClientPermissions* cp, GameStates* gs) {
	auto jsData = json::parse(readFile(path));

	as->serialize(jsData["AppStates"]);
	cp->serialize(jsData["ClientPermissions"]);
	gs->serialize(jsData["GameStates"]);
}