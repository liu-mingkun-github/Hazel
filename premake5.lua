workspace "Hazel"
	-- Actually x64 or x86 are the architecture name,
	-- which correspond to 32-bit and 64-bit
	architecture "x64"

	configurations
	{
		"Debug",
		-- "Release" is a stripped version of Debug, faster, but will do less
		"Release",
		-- Distribution, no login, just the basic things.
		"Dist"
	}

	-- Set Sandbox as the start project
	startproject "Sandbox"

-- Define a path variable
-- The tokens (e.g., cfg.buildcfg) can be looked up in the wiki tokens
-- The actual output is Debug-Windows-x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"

group "Dependencies"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"

group ""

project "Hazel"
	-- Because we want to put part of the things into the Hazel file inside the outer Hazel file.
	-- So the location Hazel here means the Hazel file in the same directory as the .lua file
	location "Hazel"
	-- SharedLib means this is a DLL file
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	-- Specify where is this going to be output to
	-- .. means appending
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- objdir is for intermediate codes
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- pchheader here means precompiled headers
	pchheader "hzpch.h"
	-- pchsource is only needed on vs, but we don't need to add to the 
	-- platform explicit scope, because other platform will automatically ignore it. 
	pchsource "Hazel/src/hzpch.cpp"

	-- files define the file patterns we want to include in the sln file
	files
	{
		"%{prj.name}/src/**.h",	-- include every .h files in the source file
		"%{prj.name}/src/**.cpp",	-- include every .cpp files in the source files
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	-- This defines all the files we want to include
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	-- Filter includes variables that only can be applied to a certain platform
	filter "system:windows"
		cppdialect "C++17"
		-- To link the libraries statically
		-- staticruntime "On"
		systemversion "10.0.22000.0"	-- or you can just use "latest"

		-- Here are the preprocessor variables we defined that can be used by macros
		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- Here you can add commands which will automatically be done after being built
		-- Like here we initially need to copy the dll every time from Hazel to Sandbox, now we can add the step to here.
		postbuildcommands
		{
			-- The command below is going to copy the dll from Hazel into Sandbox so we don't need to manual do it
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"")
		}

	filter "configurations:Debug"
		-- Define a preprocessor variable
		defines "HZ_DEBUG"
		-- buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"


	-- filter { "system:windows", "configurations:Release" }
	-- 	buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",	-- include every .h files in the source file
		"%{prj.name}/src/**.cpp"	-- include every .cpp files in the source files
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		"%{IncludeDir.glm}"
	}

	-- Sandbox needs to link in Hazel
	links
	{
		"Hazel"
	}

	-- Filter includes variables that only can be applied to a certain platform
	filter "system:windows"
		cppdialect "C++17"
		-- staticruntime "On"
		systemversion "10.0.22621.0"	-- or you can just use "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		-- buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"
