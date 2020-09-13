workspace "Delilah"
    platforms { "x86", "x86_64" }
    startproject "Game"

    configurations
	{
		"Debug",
		"Release",
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- our include dir
IncludeDir = {}
IncludeDir["glm"] = "vendor/glm"
IncludeDir["GLFW"] = "vendor/glfw/include"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["freetype2"] = "vendor/freetype2/include"
IncludeDir["entt"] = "vendor/entt/include"

group "Dependencies"
	include "vendor/glfw"
	include "vendor/glm"
	include "vendor/freetype2"
group ""

project "engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	characterset "MBCS"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"game/src",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.freetype2}",
		"%{IncludeDir.entt}",
		"$(VULKAN_SDK)/include"
	}

	links 
	{ 
		"GLFW",
		"freetype2"
	}

	filter "system:windows"
		systemversion "latest"
		defines "ENGINE_WIN32"

		defines
		{
		}

	filter "configurations:Debug"
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines { "ENGINE_DEBUG", "DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines { "ENGINE_RELEASE", "NDEBUG" }
		runtime "Release"
		optimize "on"
		symbols "off"

	filter "platforms:x86"
        architecture "x86"
        links 
		{
			"$(VULKAN_SDK)/lib32/vulkan-1.lib"
		}

    filter "platforms:x64"
        architecture "x86_64"
        links 
		{
			"$(VULKAN_SDK)/lib/vulkan-1.lib"
		}

project "game"
	location "game"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	characterset "MBCS"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	postbuildcommands {
		"IF NOT EXIST \"../game_content\" (mkdir \"../game_content\")",
		"del /f ..\\bin\\" .. outputdir .. "\\%{prj.name}\\**.lib",
		"del /f ..\\bin\\" .. outputdir .. "\\%{prj.name}\\**.exp",
		"xcopy \"../game_content\" \"../bin/" .. outputdir .. "/%{prj.name}\" /h /i /c /k /e /r /y "
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"engine/src",
		"%{prj.name}/src",
		"vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.freetype2}",
		"$(VULKAN_SDK)/include"
	}

	links
	{
		"engine",
		"freetype2"
	}

	filter "system:windows"
		systemversion "latest"
		defines "ENGINE_WIN32"

	filter "configurations:Debug"	
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines { "ENGINE_DEBUG", "DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines { "ENGINE_RELEASE", "NDEBUG" }
		runtime "Release"
		optimize "on"
		symbols "off"

	filter "platforms:x86"
        architecture "x86"
        links 
		{
			"$(VULKAN_SDK)/lib32/vulkan-1.lib"
		}

    filter "platforms:x64"
        architecture "x86_64"
        links 
		{
			"$(VULKAN_SDK)/lib/vulkan-1.lib"
		}