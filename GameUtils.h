#pragma once
#include <string>

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
#define my_rog_debug1(fmt_str, ...) do {} while (0)
#else
void my_rog_debug1_impl(const std::string & file, int line, const std::string & function, const std::string fmt_str, ...);
#define my_rog_debug1(fmt_str, ...) my_rog_debug1_impl(__FILE__, __LINE__, __FUNCTION__, fmt_str, ##__VA_ARGS__)
//void my_rog_debug1(const std::string fmt_str, ...);
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