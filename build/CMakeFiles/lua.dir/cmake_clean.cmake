file(REMOVE_RECURSE
  "liblua.a"
  "liblua.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/lua.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
