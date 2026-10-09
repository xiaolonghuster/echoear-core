# Optional integration, compiled in the owning firmware's main component.
# The standalone core component never depends on main/Application/Board.
get_filename_component(ECHOEAR_CORE_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(ECHOEAR_XIAOZHI_SOURCES
    "${ECHOEAR_CORE_ROOT}/adapters/xiaozhi/echoear_display.cc"
    "${ECHOEAR_CORE_ROOT}/adapters/xiaozhi/echoear_extras.cc"
    "${ECHOEAR_CORE_ROOT}/adapters/xiaozhi/original_ui.cc")
set(ECHOEAR_XIAOZHI_INCLUDE_DIR "${ECHOEAR_CORE_ROOT}/adapters/xiaozhi")
