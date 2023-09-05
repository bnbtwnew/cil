#pragma once
#include <string>
#include "InGamePlaying.h"

// https://stackoverflow.com/questions/44317362/remove-debug-strings-in-release-build
//#ifdef _DEBUG
//#define my_rog_debug1(str) do { printf("[D][%s:%d %s] ", \
//                               __FILE__, \
//                               __LINE__, \
//                               __FUNCTION__); \
//                            puts(#str); } while(0)
//#else
//#define my_rog_debug1(str)
//#endif

#ifdef LICENSE_BUILD
// Define log_debug as an empty macro in release builds
void my_rog_debug1_impl(const std::string& file, int line, const std::string& function, const std::string fmt_str, ...);
#define my_rog_debug1(fmt_str, ...) my_rog_debug1_impl(__FILE__, __LINE__, __FUNCTION__, fmt_str, ##__VA_ARGS__)
//#define my_rog_debug1(fmt_str, ...) do {} while (0)
#else
void my_rog_debug1_impl(const std::string & file, int line, const std::string & function, const std::string fmt_str, ...);
#define my_rog_debug1(fmt_str, ...) my_rog_debug1_impl(__FILE__, __LINE__, __FUNCTION__, fmt_str, ##__VA_ARGS__)
#endif // !LICENSE_BUILD

namespace GameUtils {
	typedef struct MapPoint {
		int column;
		int row;

		MapPoint() {
			column = -1;
			row = -1;
		}

		MapPoint(int c, int r) {
			column = c;
			row = r;
		}

	} MapPoint;

	enum GameState {
		GAME_STATE_NOT_LAUNCHED = 0,
		GAME_STATE_LOGIN_SCREEN = 1,
		GAME_STATE_LOGIN_LOADING = 0x17,
		GAME_STATE_WAITING_AT_LOBBY = 0xB,
		GAME_STATE_WAITING_INSIDE_ROOM = 0xC,
		GAME_STATE_PLAYING = 0xD,
		GAME_STATE_SHOPPING = 0xE
	};
	/*
	* To store state of last previous game state for further actions
	*/
	extern int previousGameState;
	void GetLastErrorHumanReadable();
	void AllocateAndResizeConsole(int width, int height);
	void ClearConsole();
	void PrintCurrentFeatureStatesOnConsole(InGamePlaying _inGamePlaying);
	int GetTargetModuleDllBase();
	int GetGameState();
	bool isGamePlaying();
	bool isShopping();
	int sub_658a2c_Retrieve_Object_Address_When_GameIsPlaying();
	bool HasItemAtTile(int targetDllASLR, MapPoint point);
	int GetItemID(int targetDllASLR, MapPoint point);
	int GetMysteriousNumber(int targetDllASLR, MapPoint, int itemID);
	bool IsSkillItemIDValid(int itemID);
	void EnumerateProperties();
	int GetYourPlayerPositionWhenJoinGame();
	std::string FormatString(const std::string fmt_str, ...);
	//void log_debug(const std::string fmt_str, ...);

//#ifdef LICENSE_BUILD
//// Define log_debug as an empty macro in release builds
//#define my_rog_debug1(fmt_str, ...) do {} while (0)
//#else
//	void my_rog_debug1(const std::string fmt_str, ...) {
//		//#ifndef LICENSE_BUILD
//		int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
//		std::unique_ptr<char[]> formatted;
//		va_list ap;
//		while (1) {
//			formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
//			strcpy(&formatted[0], fmt_str.c_str());
//			va_start(ap, fmt_str);
//			final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
//			va_end(ap);
//			if (final_n < 0 || final_n >= n)
//				n += abs(final_n - n + 1);
//			else
//				break;
//		}
//
//		cout << formatted.get();
//
//
//
//
//		// FIXME: << is not working here, compiler error
//		string s = std::string(formatted.get());
//		std::ofstream logFile("my_log.txt", std::ios_base::app);
//		logFile << s; //std::string(formatted.get());
//		logFile.close();
//		//#endif // !LICENSE_BUILD
//	}
//#endif // !LICENSE_BUILD
};