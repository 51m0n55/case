# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(MyAddin)

include(GenerateG1A)
include(GenerateG3A)
include(GenerateHH2Bin)
include(Fxconv)
find_package(Gint 2.9 REQUIRED)

set(SOURCES
  src/main.c
  src/cases.c
  src/cases.h
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  assets-fx/font.png
  assets-fx/CZ75.png
  assets-fx/DESERT_EAGLE.png 
  assets-fx/DUAL_BARRETAS.png
  assets-fx/FIVE_SEVEN.png   
  assets-fx/GLOCK_18.png     
  assets-fx/P2000.png        
  assets-fx/P250.png
  assets-fx/R8_REVOLVER.png  
  assets-fx/TEC_9.png        
  assets-fx/USP_S.png        
  assets-fx/AK_47.png        
  assets-fx/AUG.png
  assets-fx/AWP.png
  assets-fx/FAMAS.png        
  assets-fx/G3SG1.png        
  assets-fx/GALIL_AR.png     
  assets-fx/M4A1_S.png       
  assets-fx/M4A4.png
  assets-fx/SCAR_20.png      
  assets-fx/SG553.png        
  assets-fx/SSG_08.png       
  assets-fx/MAC_10.png       
  assets-fx/MPS_SD.png       
  assets-fx/MP7.png
  assets-fx/MP9.png
  assets-fx/PP_BIZON.png     
  assets-fx/P90.png
  assets-fx/UMP_45.png       
  assets-fx/MAG_7.png        
  assets-fx/NOVA.png
  assets-fx/SAWED_OFF.png    
  assets-fx/XM1014.png       
  assets-fx/M249.png
  assets-fx/NEGEV.png
  assets-fx/BAYONET.png
  assets-fx/BOWIE_KNIFE.png
  assets-fx/BUTTERFLY_KNIFE.png
  assets-fx/CLASSIC_KNIFE.png
  assets-fx/FALCHION_KNIFE.png
  assets-fx/FLIP_KNIFE.png
  assets-fx/GUT_KNIFE.png
  assets-fx/HUNTSMAN_KNIFE.png
  assets-fx/KARAMBIT.png
  assets-fx/KUKRI_KNIFE.png
  assets-fx/M9_BAYONET.png
  assets-fx/NAVAJA_KNIFE.png
  assets-fx/NOMAD_KNIFE.png
  assets-fx/PARACORD_KNIFE.png
  assets-fx/SHADOW_DAGGERS.png
  assets-fx/SKELETON_KNIFE.png
  assets-fx/STILLETO_KNIFE.png
  assets-fx/SURVIVAL_KNIFE.png
  assets-fx/TALON_KNIFE.png
  assets-fx/URSUS_KNIFE.png
)
set(ASSETS_cg
  assets-cg/example.png
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -Wall -Wextra -Os -g -flto)
target_link_libraries(myaddin Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET myaddin OUTPUT "Case.g1a"
    NAME "Case" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET myaddin OUTPUT "MyAddin.g3a"
    NAME "MyAddin" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G_G3A)
  generate_g3a(TARGET myaddin OUTPUT "MyAddin-fx.g3a"
    NAME "MyAddin-fx" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCP)
  generate_hh2_bin(TARGET myaddin OUTPUT "MyAddin-hh2.bin")
endif()
