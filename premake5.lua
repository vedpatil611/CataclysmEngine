workspace "Meow"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies/glad"

IncludeDirs = {}
IncludeDirs["GLAD"] = "Dependencies/glad/include"

project "CataclysmEngine"
	location "CataclysmEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	inlining "Auto"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")
		
	includedirs {
		"%{prj.name}/Includes/",
		"%{IncludeDirs.GLAD}",
	}

	links {
		"glfw",
		"glad",
		"spdlog",
		"fmt",
		"pthread"
	}

	defines {
		"SPDLOG_SHARED_LIB", "SPDLOG_COMPILED_LIB", "SPDLOG_FMT_EXTERNAL"
	}

	files { 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/Core/**.cpp",
		"%{prj.name}/src/Renderer/**.cpp",
	}

	filter "system:windows"		
		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		pic "On"
		staticruntime "On"
		links {
			"dl",
			"pthread",
        }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"
		buildoptions "/MD"
