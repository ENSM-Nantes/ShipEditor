; --------------------------------
; ShipEditor Installer
; --------------------------------

!define APPNAME "ShipEditor"

RequestExecutionLevel admin

Icon "..\res\ShipEditor.ico"	
Name "${APPNAME}"

OutFile "ShipEditor-Setup.exe"
InstallDir "$PROGRAMFILES64\ShipEditor"

VIProductVersion "1.0.0.0"
VIAddVersionKey "ProductName" "${APPNAME}"
VIAddVersionKey "ProductVersion" "2.2"
VIAddVersionKey "CompanyName" "ENSM-Nantes"
VIAddVersionKey "FileDescription" "Tool to edit boat parameters"
VIAddVersionKey "LegalCopyright" "2026 ENSM Nantes"
VIAddVersionKey "FileVersion" "1.0"

SetCompressor /SOLID lzma

Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"

    SetOutPath "$INSTDIR"

    ; ---- Build folder ----
    SetOutPath "$INSTDIR\build"
    File /r "..\build\*.*"

    ; ---- Resources folder ----
    SetOutPath "$INSTDIR\res"
    File /r "..\res\*.*"

    ; ---- Uninstaller ----
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    ; ---- Start Menu shortcut ----
    CreateDirectory "$SMPROGRAMS\ShipEditor"
    CreateShortcut "$SMPROGRAMS\ShipEditor\ShipEditor.lnk" \
        "$INSTDIR\build\ShipEditor.exe" "" \
        "$INSTDIR\build\ShipEditor.exe" 0 \
        SW_SHOWNORMAL "" "$INSTDIR"
		
	CreateShortcut "$SMPROGRAMS\ShipEditor\Uninstall ShipEditor.lnk" \
        "$INSTDIR\Uninstall.exe" "" \
        "$INSTDIR\Uninstall.exe" 0 \
        SW_SHOWNORMAL "" "$INSTDIR"

    ; ---- Desktop shortcut ----
    CreateShortcut "$DESKTOP\ShipEditor.lnk" \
        "$INSTDIR\build\ShipEditor.exe" "" \
        "$INSTDIR\build\ShipEditor.exe" 0 \
        SW_SHOWNORMAL "" "$INSTDIR"

SectionEnd


Section "Uninstall"

    Delete "$DESKTOP\ShipEditor.lnk"
    Delete "$SMPROGRAMS\ShipEditor\ShipEditor.lnk"
    RMDir "$SMPROGRAMS\ShipEditor"

    RMDir /r "$INSTDIR"

SectionEnd