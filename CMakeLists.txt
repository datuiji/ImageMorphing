cmake_minimum_required(VERSION 3.15)

project(ImageMorphing VERSION 0.0.1)

set (TargetName ${PROJECT_NAME})

add_subdirectory(JUCE)

juce_add_gui_app(${TargetName} PRODUCT_NAME "ImageMorphing")
juce_generate_juce_header(${TargetName})


target_sources(${TargetName} PRIVATE
        Source/Main.cpp
        Source/MainComponent.cpp
        Source/WarpingImageComponent.cpp
	Source/BlendingImageComponent.cpp
	Source/MorphingAnimationComponent.cpp
	Source/PaintImageComponent.cpp
	Source/SliderWithLabel.cpp
	)

target_compile_definitions(${TargetName} PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_PROJECT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_VERSION>")

target_link_libraries(${TargetName} PRIVATE
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        juce::juce_gui_extra)
