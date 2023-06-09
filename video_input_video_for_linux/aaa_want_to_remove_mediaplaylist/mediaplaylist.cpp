//
//  mediaplaylist.cpp
//  multimedia
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 03/06/19.
//  Copyright (c) 2019 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//


#include "framework.h"

#include "base/update.h"


namespace mediaplaylist
{

   static ::u64 g_usedid[] =
   {

      id_do_play,
      id_play_if_not_playing,
      id_play_and_fail_if_playing,
      id_playlists_changed,
      id_songs_changed,
      INVALID_ID

   };

   
   ::u64* usedid()
   {

      return g_usedid;

   }

   

} // namespace mediaplaylist



