# This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


add_library(readline INTERFACE)

if( UNIX )
  find_package(Readline REQUIRED)

  target_link_libraries(readline
    INTERFACE
      Readline::Readline)
endif()