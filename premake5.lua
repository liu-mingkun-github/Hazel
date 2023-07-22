workspace "Hazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

-- Define a path variable
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",	-- include every .h files in the source file
		"%{prj.name}/src/**.cpp"	-- include every .cpp files in the source files
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	-- Filter includes variables that only can be applied to a certain platform
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22000.0"	-- or you can just use "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

		postbuildcommands
		{
			-- The command below is going to copy the dll from Hazel into Sandbox so we don't need to manual do it
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"


	-- filter { "system:windows", "configurations:Release" }
	-- 	buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Hazel/src"
	}

	-- Sandbox needs to link in Hazel
	links
	{
		"Hazel"
	}

	-- Filter includes variables that only can be applied to a certain platform
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22000.0"	-- or you can just use "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"
