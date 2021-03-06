/*
 * Copyright (c) 2013, Novell Inc.
 *
 * This program is licensed under the BSD license, read LICENSE.BSD
 * for further information
 */

#include "repo.h"

#define ADD_KEYDIR_WITH_DOTFILES	(1 << 8)
#define ADD_WITH_SUBKEYS		(1 << 9)
#define ADD_MULTIPLE_PUBKEYS		(1 << 10)
#define ADD_WITH_KEYSIGNATURES		(1 << 11)

extern int repo_add_rpmdb_pubkeys(Repo *repo, int flags);
extern Id repo_add_pubkey(Repo *repo, const char *keyfile, int flags);
extern int repo_add_keyring(Repo *repo, FILE *fp, int flags);
extern int repo_add_keydir(Repo *repo, const char *keydir, const char *suffix, int flags);

/* signature parsing */
typedef struct _solvsig {
  unsigned char *sigpkt;
  int sigpktl;
  Id htype;
  unsigned int created;
  unsigned int expires;
  char keyid[17];
} Solvsig;

Solvsig *solvsig_create(FILE *fp);
void solvsig_free(Solvsig *ss);
Id solvsig_verify(Solvsig *ss, Repo *repo, void *chk);

Id repo_verify_sigdata(Repo *repo, unsigned char *sigdata, int sigdatal, const char *keyid);

