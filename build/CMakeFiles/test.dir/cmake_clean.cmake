file(REMOVE_RECURSE
  "libtest.a"
  "libtest.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/test.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
