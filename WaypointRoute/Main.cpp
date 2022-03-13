#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct VecI
{
	int x;
	int y;
};

static constexpr int MaxLoopCounter = 2;
static int loopCounter = 0;

std::vector<std::string> SpiltString(std::string s, std::string delimiter, bool removeEmptyEntries = false)
{
	std::vector<std::string> result;
	size_t start = 0u;
	size_t end = s.find(delimiter);
	size_t totalTokenLength = 0u;
	while (end != std::string::npos)
	{
		std::string token = s.substr(start, end - start);
		result.push_back(token);
		totalTokenLength += token.size();
		start = totalTokenLength + delimiter.size() * result.size();
		end = s.substr(start).find(delimiter);
		if (end != std::string::npos)
			end += start;
		else
			result.push_back(s.substr(start, end - start));
	}
	if (removeEmptyEntries)
	{
		std::vector<std::string>::iterator it = std::remove_if(result.begin(), result.end(),
			[&](const std::string& item) { return item == ""; });
		result.erase(it, result.end());
	}
	return result;
}

void Output(const VecI& startPoint, const VecI& endPoint)
{
	std::cout << "start: (" << startPoint.x << "," << startPoint.y << ")" << std::endl;
	std::cout << "end: (" << endPoint.x << "," << endPoint.y << ")" << std::endl;
}

void MoveFollowByWaypoints(VecI startPoint, std::vector<VecI> waypoints, bool repeat = true)
{
	std::vector<VecI>::iterator start;
	std::vector<VecI>::iterator end = waypoints.begin();
	while (end != waypoints.end())
	{
		if (end == waypoints.begin())
		{
			Output(startPoint, *end);
			//Increment
			start = waypoints.begin();
			std::advance(end, 1);
		}
		else
		{
			Output(*start, *end);
			//Increment
			std::advance(start, 1);
			std::advance(end, 1);
		}
		if (end != waypoints.end())
		{
			std::cout << "======================================" << std::endl;
		}
		else
		{
			std::cout << "=================END==================" << std::endl;
			if (repeat)
			{
				if (loopCounter < MaxLoopCounter)
				{
					start = waypoints.begin();
					end = start;
					std::advance(end, 1);
					std::cout << "repeat:" << ++loopCounter << std::endl;
				}
			}
		}
	}
}

int main()
{
	VecI waypoint;
	std::vector<VecI> waypoints;
	std::string file("waypoints.txt");
	std::ifstream fileStream(file);
	std::string line;
	if (!fileStream.is_open())
	{
		return -1;
	}

	while (std::getline(fileStream, line))
	{
		std::vector<std::string> result = SpiltString(line, ",");
		try
		{
			waypoint = { std::stoi(result[0]), std::stoi(result[1]) };
		}
		catch (std::invalid_argument e)
		{
			std::cout << e.what();
		}
		waypoints.push_back(waypoint);
	}
	MoveFollowByWaypoints(VecI(100, 200), waypoints, true);
	return 0;
}