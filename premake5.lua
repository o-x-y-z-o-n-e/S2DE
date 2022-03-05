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
externalinc["stb_image"] = "S2DE/vendor/stb_image/include"
externalinc["spdlog"] = "S2DE/vendor/spdlog/include"


project "S2DE"
    location "S2DE"
    kind "StaticLib"
    language "C++"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("tmp/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.name}/source/**.cpp"
    }


    includedirs {
        "%{prj.name}/include",
        "%{prj.name}/include/**",
        "%{prj.name}/source",
        "%{prj.name}/source/**",
        
        externalinc["SDL2"],
		externalinc["stb_image"],
		externalinc["spdlog"]
    }
	
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines "S2DE_WINDOWS"
	
	
	filter "system:macosx"
        buildoptions "-std=c++17"
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
			("{COPY} ../" .. externaldir["SDL2"] .. "/SDL2.dll" .. " ../bin/" .. outputdir .. "/%{prj.name}")
		}
	
	
	filter "system:macosx"
        buildoptions {
            "-std=c++17",
            "-F /Library/Frameworks"
        }
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