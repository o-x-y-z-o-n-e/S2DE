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
        "vendor/SDL2/include",
        "vendor/SDL2_image/include"
    }
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		postbuildcommands {
			("{COPY} ../vendor/SDL2/lib/windows-x86_64 ../bin/" .. outputdir .. "/Example"),
			("{COPY} ../vendor/SDL2_image/lib/%{cfg.system}-%{cfg.architecture} ../bin/" .. outputdir .. "/Example")
		}

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
        "vendor/SDL2/include",
        "vendor/SDL2_image/include",
        "S2DE/include"
    }

    libdirs {
        "vendor/SDL2/lib/%{cfg.system}-%{cfg.architecture}",
        "vendor/SDL2_image/lib/%{cfg.system}-%{cfg.architecture}"
    }

    filter "system:macosx"
        libdirs {"bin/" .. outputdir .. "/S2DE"}

        buildoptions {"-F ../vendor/SDL2/lib/%{cfg.system}-%{cfg.architecture}/"}
        linkoptions {"-F ../vendor/SDL2/lib/%{cfg.system}-%{cfg.architecture}/"}

        links { "SDL2.framework" }
    
    
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

        links { "SDL2" }
    
    links {
        "SDL2_image",
        "S2DE"
    }

    filter "configurations:debug"
        symbols "On"
    
    filter "configurations:release"
        optimize "On"