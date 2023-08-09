#pragma once
#include <string>

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
	bool HasItemAtTile(int targetDllASLR, MapPoint point);
	int GetItemID(int targetDllASLR, MapPoint point);
	int GetMysteriousNumber(int targetDllASLR, MapPoint, int itemID);
	std::string FormatString(const std::string fmt_str, ...);
	void log_debug(const std::string fmt_str, ...);
};