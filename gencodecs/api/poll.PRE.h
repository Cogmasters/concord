/*****************************************************************************
 * Pool Datatypes
 * **************************************************************************/

/** Discord polls
 * @see https://discord.com/developers/docs/resources/poll */

/** @CCORD_pub_struct{discord_poll_question} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_poll_question)
  /** the text of the field */
  COND_WRITE(self->text != NULL)
    FIELD_PTR(text, char, *)
  COND_END
  /** the emoji of the field */
  COND_WRITE(self->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_poll} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_poll)
  /** the poll question payload (text + emoji) */
    FIELD_STRUCT_PTR(question, discord_poll_question, *)
  /** list of available answers */
    FIELD_STRUCT_PTR(answers, discord_poll_answers, *)
  /** expiration timestamp */
    FIELD_TIMESTAMP(expiry)
  /** whether multiple answers are allowed */
    FIELD(allow_multiselect, bool, false)
  /** layout type for the poll (integer) */
    FIELD(layout_type, int, 0)
  /** poll results */
    FIELD_STRUCT_PTR(results, discord_poll_results, *)
STRUCT_END
#endif


/** @CCORD_pub_struct{discord_poll_answer} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_poll_answer)
  /** numeric answer id */
    FIELD(answer_id, int, 0)
  /** poll media (text + emoji) */
    FIELD_STRUCT_PTR(poll_media, discord_poll_question, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_poll_answers)
    LISTTYPE_STRUCT(discord_poll_answer)
LIST_END
#endif


/** @CCORD_pub_struct{discord_poll_results_entry} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_poll_results_entry)
  /** answer id */
    FIELD(id, int, 0)
  /** vote count */
    FIELD(count, int, 0)
  /** whether current user voted */
    FIELD(me_voted, bool, false)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_poll_results_entries)
    LISTTYPE_STRUCT(discord_poll_results_entry)
LIST_END
#endif


/** @CCORD_pub_struct{discord_poll_results} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_poll_results)
  /** array of answer counts */
    FIELD_STRUCT_PTR(answer_counts, discord_poll_results_entries, *)
  /** whether results are final */
    FIELD(is_finalized, bool, false)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_poll_answer_voters} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_poll_answer_voters)
  /** users who voted for this answer */
    FIELD_STRUCT_PTR(users, discord_user, *)
STRUCT_END
#endif
