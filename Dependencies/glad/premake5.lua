project "GLAD"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"include"
	}

	files {
		"src/glad.c"
	}

	filter "system:windows"
		defines {
			"_GLAD_WIN32"
		}

	filter "system:linux"
		pic "On"
		staticruntime "On"
		defines {
			"_GLAD_X11"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "on"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "on"
