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
externaldir["SDL2_image"] = "vendor/SDL2_image/lib/%{cfg.system}-%{cfg.architecture}"
externalinc["SDL2_image"] = "vendor/SDL2_image/include"

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
        externalinc["SDL2_image"]
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
        externalinc["SDL2_image"],
        "S2DE/include"
    }
	
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

        libdirs {
            externaldir["SDL2"],
            externaldir["SDL2_image"]
        }

        links {
            "SDL2",
            "SDL2_image",
            "S2DE"
        }

        postbuildcommands {
			("{COPY} ../" .. externaldir["SDL2"] .. " ../bin/" .. outputdir .. "/%{prj.name}"),
			("{COPY} ../" .. externaldir["SDL2_image"] .. " ../bin/" .. outputdir .. "/%{prj.name}"),
		}
	
	
	filter "system:macosx"
        buildoptions {
            "-F ../" .. externaldir["SDL2"],
            "-F ../" .. externaldir["SDL2_image"],
        }
        linkoptions {
            "-F ../" .. externaldir["SDL2"],
            "-F ../" .. externaldir["SDL2_image"],
        }

        links {
            "SDL2.framework",
            "SDL2_image.framework",
            "S2DE"
        }
	
	
	filter "system:linux"
		links {
            "SDL2",
            "SDL2_image",
            "S2DE"
        }
	

    filter "configurations:debug"
        symbols "On"
    
    filter "configurations:release"
        optimize "On"