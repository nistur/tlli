solution "tlli"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TLLI_BUILD" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSpeed",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "tlli"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

--[[
project "tlli-dynamic"
kind "SharedLib"
files { "src/**.c", "src/**.cpp" }
targetname "tlli"
--]]
project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "tlli" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
