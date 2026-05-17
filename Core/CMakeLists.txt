### CORE

# Source/Core altındaki tüm .cpp ve .h dosyalarını bulup CORE_SOURCES değişkenine atar
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "Source/Core/*.cpp" "Source/Core/*.h")

# Kütüphaneyi bulunan tüm bu dosyalarla oluşturur
add_library(Core STATIC ${CORE_SOURCES})

# App klasörünün bu dosyalara erişebilmesi için yolu gösteriyoruz
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
# Yolların tam olarak doğru olduğundan (ve dosyaların orada olduğundan) emin ol!
set(SFML_ROOT "C:/Libraries/SFML-3.0.2")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)

# SFML 3.0'ın modern isim uzayı (namespace) formatıyla bağlıyoruz
target_link_libraries(Core PUBLIC SFML::Graphics SFML::Window SFML::System)