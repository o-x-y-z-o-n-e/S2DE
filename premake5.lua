workspace "S2DE"
    configurations {
        "debug",
        "release"
    }
	
	filter "system:windows"
		architecture "x86_64"
	
	filter "system:macosx"
		architecture "arm64"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
externaldir = {}
externalinc = {}

externaldir["SDL2"] = "vendor/SDL2/lib/%{cfg.system}-%{cfg.architecture}"
externalinc["SDL2"] = "vendor/SDL2/include"

externalinc["stb_image"] = "vendor/stb_image/include"


project "S2DE"
    location "S2DE"
    kind "StaticLib"
    language "C++"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.name}/include/**.h",
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }


    includedirs {
        "%{prj.name}/include",
        externalinc["SDL2"],
		externalinc["stb_image"]
    }
	
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines "S2DE_WINDOWS"
	
	
	filter "system:macosx"
		defines "S2DE_MACOSX"
	
	
	filter "system:linux"
		defines "S2DE_LINUX"
		

    filter "configurations:debug"
        defines "S2DE_DEBUG"
        symbols "On"
    
    filter "configurations:release"
        defines "S2DE_RELEASE"
        optimize "On"
	
	


project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }


    includedirs {
        externalinc["SDL2"],
        "S2DE/include"
    }
	
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

        libdirs {
            externaldir["SDL2"]
        }

        links {
            "SDL2",
            "S2DE"
        }

        postbuildcommands {
			("{COPY} ../" .. externaldir["SDL2"] .. " ../bin/" .. outputdir .. "/%{prj.name}")
		}
	
	
	filter "system:macosx"
        buildoptions {"-F /Library/Frameworks"}
        linkoptions {"-F /Library/Frameworks"}

        links {
            "SDL2.framework",
            "S2DE"
        }
	
	
	filter "system:linux"
		links {
            "SDL2",
            "S2DE"
        }
	

    filter "configurations:debug"
        symbols "On"
    
    filter "configurations:release"
        optimize "On"