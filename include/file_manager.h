#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "scene.h"
#include <fstream>
#include <string>

class File_Manager
{
public:
	static bool saveScene(const Scene& scene, const std::string& filename);
	static bool loadScene(Scene& scene, const std::string& filename);
};

#endif
