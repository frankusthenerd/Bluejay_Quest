#ifndef MACROS_HEADER
#define MACROS_HEADER 1

#include <allegro.h>
#include <cstring>
#include "character.hpp"
#include "platform.hpp"

using namespace std;

inline void Load_Bitmap_File(int id,
                             const char* bitmap_name,
                             BITMAP** bitmaps)
{

    char file_name[50+1];

    strcpy(file_name, bitmap_name);
    fix_filename_slashes(file_name);
    bitmaps[id] = load_bitmap(file_name, NULL);
    
}

inline void Load_Music_Track_File(int id,
                                  const char* music_track_name,
                                  MIDI** music_tracks)
{

    char file_name[50+1];

    strcpy(file_name, music_track_name);
    fix_filename_slashes(file_name);
    music_tracks[id] = load_midi(file_name);
    
}

inline void Load_Sound_Effect_File(int id,
                                   const char* sound_effect_name,
                                   SAMPLE** sound_effects)
{

    char file_name[50+1];

    strcpy(file_name, sound_effect_name);
    fix_filename_slashes(file_name);
    sound_effects[id] = load_sample(file_name);
    
}

inline void Load_Bump_Map_For_Character(const char* bump_map,
                                        Character** characters,
                                        int number_of_characters)
{

    char bump_map_name[50+1];

    strcpy(bump_map_name, bump_map);
    fix_filename_slashes(bump_map_name); 
    characters[number_of_characters]->Load_Bump_Maps(bump_map_name);
    
}

inline void Load_Bump_Map_For_Platform(const char* bump_map,
                                       Platform** platforms,
                                       int number_of_platforms)
{

    char bump_map_name[50+1];

    strcpy(bump_map_name, bump_map);
    fix_filename_slashes(bump_map_name);
    platforms[number_of_platforms]->Load_Bump_Map(bump_map_name);
    
}

#endif
