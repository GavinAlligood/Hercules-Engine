project "assimp"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"**"
	}

	includedirs
	{
		"include/",
		"include/assimp",
		"include/contrib",
		"build/include",
		"build/",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
