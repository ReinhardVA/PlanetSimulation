# 1. Uygulama dosyamızı oluşturuyoruz (Dosyada SADECE BİR KERE olmalı)
add_executable(App 
    Main.cpp
)

# 2. Kendi yazdığımız Core motorunu uygulamaya bağlıyoruz
target_link_libraries(App PRIVATE Core)

# --- DLL OTOMASYON KISMI ---

# 3. SFML 3.0.2'nin doğru klasör yolu (Bulduğumuz yola göre güncelledim)
set(SFML_BIN_DIR "C:/Libraries/SFML-3.0.2/bin") 

# 4. O klasördeki tüm DLL'leri bul
file(GLOB SFML_DLLS "${SFML_BIN_DIR}/*.dll")

# 5. Derleme sonrası DLL'leri exe'nin yanına kopyala
if(SFML_DLLS)
    add_custom_command(TARGET App POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_DLLS}
        $<TARGET_FILE_DIR:App>
    )
else()
    message(WARNING "DİKKAT: ${SFML_BIN_DIR} yolunda hic DLL bulunamadi!")
endif()