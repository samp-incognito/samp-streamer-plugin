solution "streamer"
	configurations { "Release", "Debug" }
	language "C++"

	project "streamer"
		includedirs { "include", "lib", "lib/sdk" }
		kind "SharedLib"
		targetprefix ""
		if _ACTION == "gmake" then
			files { "**.c", "**.cpp" }
			links "rt"
			targetextension ".so"
		elseif string.startswith(_ACTION, "vs") then
			files { "**.c", "**.cpp", "**.def", "**.rc", "src/**.h" }
			targetextension ".dll"
		end

	configuration "Release"
		if _ACTION == "gmake" then
			buildoptions { "-ffast-math", "-fmerge-all-constants", "-fno-strict-aliasing", "-fPIC", "-fvisibility=hidden", "-fvisibility-inlines-hidden", "-m32", "-O3", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "_GNU_SOURCE", "NDEBUG", "SAMPGDK_AMALGAMATION" }
			flags "NoImportLib"
			linkoptions "-m32"
			objdir "obj/linux/Release"
			targetdir "bin/linux/Release"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "_CRT_SECURE_NO_WARNINGS", "NDEBUG", "SAMPGDK_AMALGAMATION" }
			flags { "FatalWarnings", "LinkTimeOptimization", "NoBufferSecurityCheck" }
			objdir "obj/win32/Release"
			optimize "Speed"
			targetdir "bin/win32/Release"
		end

	configuration "Debug"
		if _ACTION == "gmake" then
			buildoptions { "-fPIC", "-m32", "-O0", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "_GNU_SOURCE", "SAMPGDK_AMALGAMATION" }
			flags { "NoImportLib", "Symbols" }
			linkoptions { "-m32", "-rdynamic" }
			objdir "obj/linux/Debug"
			targetdir "bin/linux/Debug"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "_CRT_SECURE_NO_WARNINGS", "SAMPGDK_AMALGAMATION" }
			flags { "FatalWarnings", "Symbols" }
			objdir "obj/win32/Debug"
			targetdir "bin/win32/Debug"
		end
