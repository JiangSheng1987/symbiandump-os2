/* -*- mode: C; c-file-style: "gnu" -*- */
/* test.h  unit test routines
 *
 * Copyright (C) 2003 Red Hat, Inc.
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

#ifndef BUS_TEST_H
#define BUS_TEST_H

#ifndef __SYMBIAN32__
#include <config.h>
#else
#include "config.h"
#endif //__SYMBIAN32__

#ifdef DBUS_BUILD_TESTS

#include <dbus/dbus.h>
#ifndef __SYMBIAN32__
#include <dbus/dbus-string.h>
#else
#include "dbus-string.h"
#endif //__SYMBIAN32__
#include "connection.h"

dbus_bool_t bus_dispatch_test         (const DBusString             *test_data_dir);
dbus_bool_t bus_dispatch_sha1_test    (const DBusString             *test_data_dir);
dbus_bool_t bus_policy_test           (const DBusString             *test_data_dir);
dbus_bool_t bus_config_parser_test    (const DBusString             *test_data_dir);
dbus_bool_t bus_signals_test          (const DBusString             *test_data_dir);
dbus_bool_t bus_expire_list_test      (const DBusString             *test_data_dir);
dbus_bool_t bus_activation_service_reload_test (const DBusString    *test_data_dir);
dbus_bool_t bus_setup_debug_client    (DBusConnection               *connection);
void        bus_test_clients_foreach  (BusConnectionForeachFunction  function,
                                       void                         *data);
dbus_bool_t bus_test_client_listed    (DBusConnection               *connection);
void        bus_test_run_bus_loop     (BusContext                   *context,
                                       dbus_bool_t                   block);
void        bus_test_run_clients_loop (dbus_bool_t                   block);
void        bus_test_run_everything   (BusContext                   *context);
BusContext* bus_context_new_test      (const DBusString             *test_data_dir,
                                       const char                   *filename);



#endif

#endif /* BUS_TEST_H */
