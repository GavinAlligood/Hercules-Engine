workspace "Hercules0.1"
    architecture "x64"
    startproject("HerculesEditor")

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hercules0.1/vendor/GLFW/include"
IncludeDir["Glad"] = "Hercules0.1/vendor/Glad/include"
IncludeDir["ImGui"] = "Hercules0.1/vendor/imgui"
IncludeDir["assimp"] = "Hercules0.1/vendor/assimp/include"

include "Hercules0.1/vendor/GLFW"
include "Hercules0.1/vendor/Glad"
include "Hercules0.1/vendor/imgui"
include "Hercules0.1/vendor/assimp"

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
        "%{prj.name}/vendor/stbi/**.h",
        "%{prj.name}/vendor/stbi/**.cpp",
        "%{prj.name}/vendor/glm/**.hpp",
        "%{prj.name}/vendor/assimp/include/assimp/**.h",
        "%{prj.name}/vendor/assimp/include/assimp/**.hpp",
        "%{prj.name}/vendor/assimp/include/assimp/**.inl"
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
        "%{IncludeDir.ImGui}",
        ---"Hercules0.1/vendor/assimp/include",
        "%{IncludeDir.assimp}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "ImGui",
        --"Hercules0.1/vendor/assimp/bin/assimp.lib"
        "assimp"
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

project "HerculesEditor"
    location "HerculesEditor"
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
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "Hercules0.1/vendor/assimp/include",
        "Hercules0.1/vendor"
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
            "HC_PLATFORM_WINDOWS",
            "HC_PROJECT_HUB"
        }
        
    filter "configurations:Debug"
        defines "HC_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "HC_RELEASE"
        runtime "Release"
        optimize "on"