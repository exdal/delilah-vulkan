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
IncludeDir["glad"] = "vendor/glad/include"
IncludeDir["GLFW"] = "vendor/glfw/include"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["entt"] = "vendor/entt/include"

group "Dependencies"
	include "vendor/glfw"
	include "vendor/glad"
	include "vendor/glm"
group ""

project "engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links 
	{ 
		"GLFW",
		"glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		defines "ENGINE_WIN32"

		defines
		{
		}

	filter "configurations:Debug"
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines "ENGINE_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "off"

	filter "platforms:x86"
        architecture "x86"

    filter "platforms:x64"
        architecture "x86_64"

project "game"
	location "game"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	postbuildcommands {
		"IF NOT EXIST \"../assets\" (mkdir \"../assets\")",
		"IF NOT EXIST \"../bin/" .. outputdir .. "/%{prj.name}/assets\" (mkdir \"../bin/" .. outputdir .. "/%{prj.name}/assets\")",
		"xcopy \"../assets\" \"../bin/" .. outputdir .. "/%{prj.name}/assets\" /h /i /c /k /e /r /y "
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"engine/src",
		"vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"
		defines "ENGINE_WIN32"

	filter "configurations:Debug"	
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}/"
		defines "ENGINE_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "off"

	filter "platforms:x86"
        architecture "x86"

    filter "platforms:x64"
        architecture "x86_64"