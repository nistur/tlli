solution "tlli"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

if os.is("windows") then
	defines { "TLLI_BUILD", "WIN32" }
else
	defines { "TLLI_BUILD" }
end

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
files { "src/**.c" }
excludes { "src/tlli-repl.c" }

project "tlli-dynamic"
kind "SharedLib"
files { "src/**.c" }
excludes { "src/tlli-repl.c" }
targetname "tlli"

project "tlli-repl"
kind "ConsoleApp"
files { "src/tlli-repl.c" }
targetname "tlli"
links { "tlli", "readline" }

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
-- this causes the testsuite to link with the dynamic library
-- which it can't find because it's not in the library search
-- path, so for now, we add the source files manually
--links { "tlli" }
files { "src/**.c" }
excludes { "src/tlli-repl.c" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
