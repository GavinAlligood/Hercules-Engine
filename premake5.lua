workspace "Hercules0.1"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hercules0.1/vendor/GLFW/include"
IncludeDir["Glad"] = "Hercules0.1/vendor/Glad/include"
IncludeDir["imgui"] = "Hercules0.1/vendor/imgui"

include "Hercules0.1/vendor/GLFW"
include "Hercules0.1/vendor/Glad"
include "Hercules0.1/vendor/imgui"

project "Hercules0.1"
    location "Hercules0.1"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    -- precompiled header
    pchheader "hcpch.h"
    pchsource "Hercules0.1/src/hcpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.shader",
        "%{prj.name}/vendor/stbi/**.h",
        "%{prj.name}/vendor/stbi/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{prj.name}/src/Hercules/Renderer/stbi",
        "%{prj.name}/src/Hercules/Core/Math/glm",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "imgui"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HC_PLATFORM_WINDOWS",
            "HC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "HC_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "HC_RELEASE"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Assets/Shaders/**.shader"
    }

    includedirs
    {
        "Hercules0.1/vendor/spdlog/include",
        "Hercules0.1/src/Hercules",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
        "Hercules0.1"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "HC_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "HC_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "HC_RELEASE"
        runtime "Release"
        optimize "on"