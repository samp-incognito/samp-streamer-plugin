solution "streamer"
	configurations { "Release", "Debug" }
	language "C++"

	project "streamer"
		includedirs { "include" }
		kind "SharedLib"
		if _ACTION == "gmake" then
			files { "**.cpp" }
			libdirs { "lib/sampgdk/linux", "lib/subhook/linux" }
			targetextension ".so"
		elseif string.startswith(_ACTION, "vs") then
			files { "**.cpp", "**.def", "**.rc", "src/**.h" }
			libdirs { "lib/sampgdk/win32", "lib/subhook/win32" }
			targetextension ".dll"
		end

	configuration "Release"
		if _ACTION == "gmake" then
			buildoptions { "-ffast-math", "-fmerge-all-constants", "-fno-strict-aliasing", "-fvisibility=hidden", "-fvisibility-inlines-hidden", "-O3", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "NDEBUG", "SAMPGDK_STATIC" }
			flags { "NoImportLib" }
			links { "rt", "sampgdk", "subhook" }
			objdir "obj/linux/Release"
			targetdir "bin/linux/Release"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "NDEBUG", "SAMPGDK_STATIC" }
			flags { "FatalWarnings", "LinkTimeOptimization", "NoBufferSecurityCheck" }
			links { "sampgdk3", "subhook" }
			objdir "obj/win32/Release"
			optimize "Speed"
			targetdir "bin/win32/Release"
		end

	configuration "Debug"
		if _ACTION == "gmake" then
			buildoptions { "-O0", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "SAMPGDK_STATIC" }
			flags { "NoImportLib", "Symbols" }
			linkoptions { "-rdynamic" }
			links { "rt", "sampgdkd", "subhookd" }
			objdir "obj/linux/Debug"
			targetdir "bin/linux/Debug"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "SAMPGDK_STATIC" }
			flags { "FatalWarnings", "Symbols" }
			links { "sampgdk3d", "subhookd" }
			objdir "obj/win32/Debug"
			targetdir "bin/win32/Debug"
		end
