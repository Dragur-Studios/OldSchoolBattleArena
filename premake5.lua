-- premake5.lua
workspace "Old School Battle Arena"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }

   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Server/Build_Server.lua"
include "Client/Build_Client.lua" 
