/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-userdb.c User database abstraction
 * 
 * Copyright (C) 2003, 2004  Red Hat, Inc.
 * Portion Copyright � 2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#define DBUS_USERDB_INCLUDES_PRIVATE 1
#include "dbus-userdb.h"
#include "dbus-hash.h"
#include "dbus-test.h"
#include "dbus-internals.h"
#include "dbus-protocol.h"
#include <string.h>
#ifdef __SYMBIAN32__
#include "libdbus_wsd_solution.h"
#endif


/**
 * @addtogroup DBusInternalsUtils
 * @{
 */

/**
 * Frees the given #DBusUserInfo's members with _dbus_user_info_free()
 * and also calls dbus_free() on the block itself
 *
 * @param info the info
 */

void
_dbus_user_info_free_allocated (DBusUserInfo *info)
{
  if (info == NULL) /* hash table will pass NULL */
    return;

  _dbus_user_info_free (info);
  dbus_free (info);
}

/**
 * Frees the given #DBusGroupInfo's members with _dbus_group_info_free()
 * and also calls dbus_free() on the block itself
 *
 * @param info the info
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
void
_dbus_group_info_free_allocated (DBusGroupInfo *info)
{
  if (info == NULL) /* hash table will pass NULL */
    return;

  _dbus_group_info_free (info);
  dbus_free (info);
}

/**
 * Checks if a given string is actually a number 
 * and converts it if it is 
 *
 * @param str the string to check
 * @param num the memory location of the unsigned long to fill in
 * @returns TRUE if str is a number and num is filled in 
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_is_a_number (const DBusString *str,
                   unsigned long    *num)
{
  int end;

  #ifdef __SYMBIAN32__
  if (_dbus_string_parse_int (str, 0, (long *) num, &end) &&
      end == _dbus_string_get_length (str))
#else
  if (_dbus_string_parse_int (str, 0, num, &end) &&
      end == _dbus_string_get_length (str))
#endif
   return TRUE;
  else
    return FALSE;
}

/**
 * Looks up a uid or username in the user database.  Only one of name
 * or UID can be provided. There are wrapper functions for this that
 * are better to use, this one does no locking or anything on the
 * database and otherwise sort of sucks.
 *
 * @param db the database
 * @param uid the user ID or #DBUS_UID_UNSET
 * @param username username or #NULL 
 * @param error error to fill in
 * @returns the entry in the database
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
DBusUserInfo*
_dbus_user_database_lookup (DBusUserDatabase *db,
                            dbus_uid_t        uid,
                            const DBusString *username,
                            DBusError        *error)
{
  DBusUserInfo *info;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  _dbus_assert (uid != DBUS_UID_UNSET || username != NULL);

  /* See if the username is really a number */
  if (uid == DBUS_UID_UNSET)
    {
      unsigned long n;

      if (_dbus_is_a_number (username, &n))
        uid = n;
    }

  if (uid != DBUS_UID_UNSET)
    info = _dbus_hash_table_lookup_ulong (db->users, uid);
  else
    info = _dbus_hash_table_lookup_string (db->users_by_name, _dbus_string_get_const_data (username));
  
  if (info)
    {
      _dbus_verbose ("Using cache for UID "DBUS_UID_FORMAT" information\n",
                     info->uid);
      return info;
    }
  else
    {
      if (uid != DBUS_UID_UNSET)
	_dbus_verbose ("No cache for UID "DBUS_UID_FORMAT"\n",
		       uid);
      else
	_dbus_verbose ("No cache for user \"%s\"\n",
		       _dbus_string_get_const_data (username));
      
      info = dbus_new0 (DBusUserInfo, 1);
      if (info == NULL)
        {
          dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
          return NULL;
        }

      if (uid != DBUS_UID_UNSET)
        {
          if (!_dbus_user_info_fill_uid (info, uid, error))
            {
              _DBUS_ASSERT_ERROR_IS_SET (error);
              _dbus_user_info_free_allocated (info);
              return NULL;
            }
        }
      else
        {
          if (!_dbus_user_info_fill (info, username, error))
            {
              _DBUS_ASSERT_ERROR_IS_SET (error);
              _dbus_user_info_free_allocated (info);
              return NULL;
            }
        }

      /* be sure we don't use these after here */
      uid = DBUS_UID_UNSET;
      username = NULL;

      /* insert into hash */
      if (!_dbus_hash_table_insert_ulong (db->users, info->uid, info))
        {
          dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
          _dbus_user_info_free_allocated (info);
          return NULL;
        }

      if (!_dbus_hash_table_insert_string (db->users_by_name,
                                           info->username,
                                           info))
        {
          _dbus_hash_table_remove_ulong (db->users, info->uid);
          dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
          return NULL;
        }
      
      return info;
    }
}
#if EMULATOR
GET_GLOBAL_VAR_FROM_TLS(_dbus_lock_system_users,dbus_userdb,DBusMutex *)
#define _dbus_lock_system_users (*GET_DBUS_WSD_VAR_NAME(_dbus_lock_system_users,dbus_userdb,g)())
#else
_DBUS_DEFINE_GLOBAL_LOCK(system_users);
#endif
#if EMULATOR
GET_STATIC_VAR_FROM_TLS(database_locked,dbus_userdb,dbus_bool_t)
#define database_locked (*GET_DBUS_WSD_VAR_NAME(database_locked,dbus_userdb,s)())

GET_STATIC_VAR_FROM_TLS(system_db,dbus_userdb,DBusUserDatabase*)
#define system_db (*GET_DBUS_WSD_VAR_NAME(system_db,dbus_userdb,s)())

GET_STATIC_VAR_FROM_TLS(process_username,dbus_userdb,DBusString)
#define process_username (*GET_DBUS_WSD_VAR_NAME(process_username,dbus_userdb,s)())

GET_STATIC_VAR_FROM_TLS(process_homedir,dbus_userdb,DBusString)
#define process_homedir (*GET_DBUS_WSD_VAR_NAME(process_homedir,dbus_userdb,s)())

#else
static dbus_bool_t database_locked = FALSE;
static DBusUserDatabase *system_db = NULL;
static DBusString process_username;
static DBusString process_homedir;
#endif
      
static void
shutdown_system_db (void *data)
{
  _dbus_user_database_unref (system_db);
  system_db = NULL;
  _dbus_string_free (&process_username);
  _dbus_string_free (&process_homedir);
}

static dbus_bool_t
init_system_db (void)
{
  _dbus_assert (database_locked);
    
  if (system_db == NULL)
    {
      DBusError error;
      const DBusUserInfo *info;
      
      system_db = _dbus_user_database_new ();
      if (system_db == NULL)
        return FALSE;

      dbus_error_init (&error);

      if (!_dbus_user_database_get_uid (system_db,
                                        _dbus_getuid (),
                                        &info,
                                        &error))
        {
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          
          if (dbus_error_has_name (&error, DBUS_ERROR_NO_MEMORY))
            {
              dbus_error_free (&error);
              return FALSE;
            }
          else
            {
              /* This really should not happen. */
              _dbus_warn ("Could not get password database information for UID of current process: %s\n",
                          error.message);
              dbus_error_free (&error);
              return FALSE;
            }
        }

      if (!_dbus_string_init (&process_username))
        {
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          return FALSE;
        }

      if (!_dbus_string_init (&process_homedir))
        {
          _dbus_string_free (&process_username);
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          return FALSE;
        }

      if (!_dbus_string_append (&process_username,
                                info->username) ||
          !_dbus_string_append (&process_homedir,
                                info->homedir) ||
          !_dbus_register_shutdown_func (shutdown_system_db, NULL))
        {
          _dbus_string_free (&process_username);
          _dbus_string_free (&process_homedir);
          _dbus_user_database_unref (system_db);
          system_db = NULL;
          return FALSE;
        }
    }

  return TRUE;
}

/**
 * Locks global system user database.
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
void
_dbus_user_database_lock_system (void)
{
  _DBUS_LOCK (system_users);
  database_locked = TRUE;
}

/**
 * Unlocks global system user database.
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
void
_dbus_user_database_unlock_system (void)
{
  database_locked = FALSE;
  _DBUS_UNLOCK (system_users);
}

/**
 * Gets the system global user database;
 * must be called with lock held (_dbus_user_database_lock_system()).
 *
 * @returns the database or #NULL if no memory
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
DBusUserDatabase*
_dbus_user_database_get_system (void)
{
  _dbus_assert (database_locked);

  init_system_db ();
  
  return system_db;
}

/**
 * Gets username of user owning current process.  The returned string
 * is valid until dbus_shutdown() is called.
 *
 * @param username place to store pointer to username
 * @returns #FALSE if no memory
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_username_from_current_process (const DBusString **username)
{
  _dbus_user_database_lock_system ();
  if (!init_system_db ())
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }
  *username = &process_username;
  _dbus_user_database_unlock_system ();  

  return TRUE;
}

/**
 * Gets homedir of user owning current process.  The returned string
 * is valid until dbus_shutdown() is called.
 *
 * @param homedir place to store pointer to homedir
 * @returns #FALSE if no memory
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_homedir_from_current_process (const DBusString  **homedir)
{
  _dbus_user_database_lock_system ();
  if (!init_system_db ())
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }
  *homedir = &process_homedir;
  _dbus_user_database_unlock_system ();

  return TRUE;
}

/**
 * Gets the home directory for the given user.
 *
 * @param username the username
 * @param homedir string to append home directory to
 * @returns #TRUE if user existed and we appended their homedir
 */

dbus_bool_t
_dbus_homedir_from_username (const DBusString *username,
                             DBusString       *homedir)
{
  DBusUserDatabase *db;
  const DBusUserInfo *info;
  _dbus_user_database_lock_system ();

  db = _dbus_user_database_get_system ();
  if (db == NULL)
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }

  if (!_dbus_user_database_get_username (db, username,
                                         &info, NULL))
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }

  if (!_dbus_string_append (homedir, info->homedir))
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }
  
  _dbus_user_database_unlock_system ();
  return TRUE;
}

/**
 * Gets the credentials corresponding to the given username.
 *
 * @param username the username
 * @param credentials credentials to fill in
 * @returns #TRUE if the username existed and we got some credentials
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_credentials_from_username (const DBusString *username,
                                 DBusCredentials  *credentials)
{
  DBusUserDatabase *db;
  const DBusUserInfo *info;
  _dbus_user_database_lock_system ();

  db = _dbus_user_database_get_system ();
  if (db == NULL)
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }

  if (!_dbus_user_database_get_username (db, username,
                                         &info, NULL))
    {
      _dbus_user_database_unlock_system ();
      return FALSE;
    }

  credentials->pid = DBUS_PID_UNSET;
  credentials->uid = info->uid;
  credentials->gid = info->primary_gid;
  
  _dbus_user_database_unlock_system ();
  return TRUE;
}

/**
 * Creates a new user database object used to look up and
 * cache user information.
 * @returns new database, or #NULL on out of memory
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
DBusUserDatabase*
_dbus_user_database_new (void)
{
  DBusUserDatabase *db;
  
  db = dbus_new0 (DBusUserDatabase, 1);
  if (db == NULL)
    return NULL;

  db->refcount = 1;

  db->users = _dbus_hash_table_new (DBUS_HASH_ULONG,
                                    NULL, (DBusFreeFunction) _dbus_user_info_free_allocated);
  
  if (db->users == NULL)
    goto failed;

  db->groups = _dbus_hash_table_new (DBUS_HASH_ULONG,
                                     NULL, (DBusFreeFunction) _dbus_group_info_free_allocated);
  
  if (db->groups == NULL)
    goto failed;

  db->users_by_name = _dbus_hash_table_new (DBUS_HASH_STRING,
                                            NULL, NULL);
  if (db->users_by_name == NULL)
    goto failed;
  
  db->groups_by_name = _dbus_hash_table_new (DBUS_HASH_STRING,
                                             NULL, NULL);
  if (db->groups_by_name == NULL)
    goto failed;
  
  return db;
  
 failed:
  _dbus_user_database_unref (db);
  return NULL;
}

/**
 * Flush all information out of the user database. 
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
void
_dbus_user_database_flush (DBusUserDatabase *db) 
{
  _dbus_hash_table_remove_all(db->users_by_name);
  _dbus_hash_table_remove_all(db->groups_by_name);
  _dbus_hash_table_remove_all(db->users);
  _dbus_hash_table_remove_all(db->groups);
}

#ifdef DBUS_BUILD_TESTS
/**
 * Increments refcount of user database.
 * @param db the database
 * @returns the database
 */
DBusUserDatabase *
_dbus_user_database_ref (DBusUserDatabase  *db)
{
  _dbus_assert (db->refcount > 0);

  db->refcount += 1;

  return db;
}
#endif /* DBUS_BUILD_TESTS */

/**
 * Decrements refcount of user database.
 * @param db the database
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
void
_dbus_user_database_unref (DBusUserDatabase  *db)
{
  _dbus_assert (db->refcount > 0);

  db->refcount -= 1;
  if (db->refcount == 0)
    {
      if (db->users)
        _dbus_hash_table_unref (db->users);

      if (db->groups)
        _dbus_hash_table_unref (db->groups);

      if (db->users_by_name)
        _dbus_hash_table_unref (db->users_by_name);

      if (db->groups_by_name)
        _dbus_hash_table_unref (db->groups_by_name);
      
      dbus_free (db);
    }
}

/**
 * Gets the user information for the given UID,
 * returned user info should not be freed. 
 *
 * @param db user database
 * @param uid the user ID
 * @param info return location for const ref to user info
 * @param error error location
 * @returns #FALSE if error is set
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_user_database_get_uid (DBusUserDatabase    *db,
                             dbus_uid_t           uid,
                             const DBusUserInfo **info,
                             DBusError           *error)
{
  *info = _dbus_user_database_lookup (db, uid, NULL, error);
  return *info != NULL;
}

/**
 * Gets the user information for the given username.
 *
 * @param db user database
 * @param username the user name
 * @param info return location for const ref to user info
 * @param error error location
 * @returns #FALSE if error is set
 */

dbus_bool_t
_dbus_user_database_get_username  (DBusUserDatabase     *db,
                                   const DBusString     *username,
                                   const DBusUserInfo  **info,
                                   DBusError            *error)
{
  *info = _dbus_user_database_lookup (db, DBUS_UID_UNSET, username, error);
  return *info != NULL;
}

/** @} */

/* Tests in dbus-userdb-util.c */