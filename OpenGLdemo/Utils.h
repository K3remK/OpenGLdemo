#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Util
{
	 inline std::string vector_to_string(glm::vec3 vec)
     {
		 return std::string("x: " + std::to_string(vec.x) + ", y: " + std::to_string(vec.y) + ", z: " + std::to_string(vec.z));
     }
}