solution "streamer"
	configurations { "Release", "Debug" }
	language "C++"

	project "streamer"
		includedirs { "include" }
		kind "SharedLib"
		if _ACTION == "gmake" then
			files { "**.cpp" }
			libdirs { "lib/sampgdk/linux" }
			targetextension ".so"
		elseif string.startswith(_ACTION, "vs") then
			files { "**.cpp", "**.def", "**.rc", "src/**.h" }
			libdirs { "lib/sampgdk/win32" }
			targetextension ".dll"
		end

	configuration "Release"
		if _ACTION == "gmake" then
			buildoptions { "-ffast-math", "-fmerge-all-constants", "-fno-strict-aliasing", "-fvisibility=hidden", "-fvisibility-inlines-hidden", "-O3", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "NDEBUG", "SAMPGDK_STATIC", "SAMPGDK_AMALGAMATION" }
			flags { "NoImportLib" }
			links { "rt", "sampgdk" }
			objdir "obj/linux/Release"
			targetdir "bin/linux/Release"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "NDEBUG", "SAMPGDK_STATIC", "SAMPGDK_AMALGAMATION", "_CRT_SECURE_NO_WARNINGS" }
			flags { "FatalWarnings", "LinkTimeOptimization", "NoBufferSecurityCheck" }
			links { "sampgdk4" }
			objdir "obj/win32/Release"
			optimize "Speed"
			targetdir "bin/win32/Release"
		end

	configuration "Debug"
		if _ACTION == "gmake" then
			buildoptions { "-O0", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "SAMPGDK_STATIC", "SAMPGDK_AMALGAMATION" }
			flags { "NoImportLib", "Symbols" }
			linkoptions { "-rdynamic" }
			links { "rt", "sampgdk" }
			objdir "obj/linux/Debug"
			targetdir "bin/linux/Debug"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "SAMPGDK_STATIC", "SAMPGDK_AMALGAMATION" }
			flags { "FatalWarnings", "Symbols" }
			links { "sampgdk4" }
			objdir "obj/win32/Debug"
			targetdir "bin/win32/Debug"
		end
