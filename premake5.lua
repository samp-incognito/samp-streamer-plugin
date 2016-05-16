solution "streamer"
	configurations { "Release", "Debug" }
	language "C++"

	project "streamer"
		includedirs { "include", "lib", "lib/**" }
		kind "SharedLib"
		targetprefix ""
		if _ACTION == "gmake" then
			files { "**.c", "**.cpp" }
			links "rt"
			targetextension ".so"
		elseif string.startswith(_ACTION, "vs") then
			files { "**.c", "**.cpp", "**.def", "**.rc", "lib/**.h", "src/**.h" }
			targetextension ".dll"
		end

	configuration "Release"
		if _ACTION == "gmake" then
			buildoptions { "-fno-strict-aliasing", "-fPIC", "-m32", "-O3", "-Wall" }
			defines { "BOOST_CHRONO_HEADER_ONLY", "LINUX", "NDEBUG", "SAMPGDK_AMALGAMATION", "SAMPGDK_CPP_WRAPPERS" }
			flags "NoImportLib"
			linkoptions "-m32"
			objdir "obj/linux/Release"
			targetdir "bin/linux/Release"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "NDEBUG", "NOMINMAX", "SAMPGDK_AMALGAMATION", "SAMPGDK_CPP_WRAPPERS", "WIN32" }
			flags { "FatalWarnings", "LinkTimeOptimization", "NoBufferSecurityCheck" }
			objdir "obj/win32/Release"
			optimize "Speed"
			targetdir "bin/win32/Release"
		end

	configuration "Debug"
		if _ACTION == "gmake" then
			defines { "BOOST_CHRONO_HEADER_ONLY", "LINUX", "SAMPGDK_AMALGAMATION", "SAMPGDK_CPP_WRAPPERS" }
			buildoptions { "-fPIC", "-m32", "-O0", "-Wall" }
			flags { "NoImportLib", "Symbols" }
			linkoptions { "-m32", "-rdynamic" }
			objdir "obj/linux/Debug"
			targetdir "bin/linux/Debug"
		elseif string.startswith(_ACTION, "vs") then
			defines { "BOOST_ALL_NO_LIB", "BOOST_CHRONO_HEADER_ONLY", "NOMINMAX", "SAMPGDK_AMALGAMATION", "SAMPGDK_CPP_WRAPPERS", "WIN32" }
			flags { "FatalWarnings", "Symbols" }
			objdir "obj/win32/Debug"
			targetdir "bin/win32/Debug"
		end
