FILE(REMOVE_RECURSE
"libcore.pdb"
"libcore.a"
"libcore.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/core.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
