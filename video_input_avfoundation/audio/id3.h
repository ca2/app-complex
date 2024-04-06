#pragma once

#include "id3.h"
#include "id3/tag.h"
#include "id3/readers.h"


CLASS_DECL_APP_CORE_AUDIO int id3_cp(ID3_TextEnc enc);
CLASS_DECL_APP_CORE_AUDIO string id3_field_text(ID3_Field * pfield);
CLASS_DECL_APP_CORE_AUDIO string id3_frame_text(ID3_Frame * pframe);
CLASS_DECL_APP_CORE_AUDIO property_set id3_set(file_pointer file);
