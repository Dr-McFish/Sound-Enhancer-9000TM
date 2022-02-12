cmake_minimum_required(VERSION 3.14.0)

set(vst3sdk_SOURCE_DIR C:/Users/woosi/source/libs/VST_SDK/vst3sdk)
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(Placebo_Plugin)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(Placebo_Plugin
    source/version.h
    source/myplugincids.h
    source/mypluginprocessor.h
    source/mypluginprocessor.cpp
    source/myplugincontroller.h
    source/myplugincontroller.cpp
    source/mypluginentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(Placebo_Plugin
        PRIVATE
            resource/myplugineditor.uidesc
    )
    target_link_libraries(Placebo_Plugin
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(Placebo_Plugin
        RESOURCES
            "resource/myplugineditor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (Placebo_Plugin
    RESOURCES
        resource/70B0E0A5BFE15E808B1969D248F2D461_snapshot.png
        resource/70B0E0A5BFE15E808B1969D248F2D461_snapshot_2.0x.png
)

target_link_libraries(Placebo_Plugin
    PRIVATE
        sdk
)

if(SMTG_MAC)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)
    smtg_target_set_bundle(Placebo_Plugin
        BUNDLE_IDENTIFIER drmcfish.plugins.placebo
        INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS
    )
    smtg_target_set_debug_executable(Placebo_Plugin
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(Placebo_Plugin PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Placebo_Plugin)

        smtg_target_set_debug_executable(Placebo_Plugin
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
