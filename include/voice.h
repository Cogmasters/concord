/**
 * @file voice.h
 * @author Cogmasters
 * @brief Voice public functions and datatypes
 */

#ifndef DISCORD_VOICE_H
#define DISCORD_VOICE_H

#include "discord-templates.h"

DISCORDT_RETURN(voice_regions);

/**
 * @brief Get voice regions that can be used when setting a
 *        voice or stage channel's `rtc_region`
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret,voice_regions}
 * @CCORD_return
 */
CCORDcode discord_list_voice_regions(struct discord *client,
                                     struct discord_ret_voice_regions *ret);

#endif /* DISCORD_VOICE_H */
