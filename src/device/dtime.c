/*
 * Simple host time device
 * Copyright (c) 2003-2007 Viliam Holub
 */

/** \file dtime.c
 *
 * Device: Host time
 */

#ifdef HAVE_CONFIG_H
#	include "../config.h"
#endif

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#include "dtime.h"

#include "device.h"
#include "../output.h"
#include "../utils.h"

/** \{ \name Register offsets */
#define REGISTER_SEC	0
#define REGISTER_USEC	4
#define REGISTER_LIMIT	8
/* \} */


/*
 * Device commands
*/

static bool dtime_init( parm_link_s *parm, device_s *dev);
static bool dtime_info( parm_link_s *parm, device_s *dev);
static bool dtime_stat( parm_link_s *parm, device_s *dev);

/** Dtime command-line commands and parameters. */
cmd_s dtime_cmds[] =
{
	{ "init", (cmd_f)dtime_init,
		DEFAULT,
		DEFAULT,
		"Inicialization",
		"Inicialization",
		REQ STR "time/timer name" NEXT
		REQ INT "arrd/timer register address" END},
	{ "help", (cmd_f)dev_generic_help,
		DEFAULT,
		DEFAULT,
		"Displays help",
		"Displays help",
		OPT STR "cmd/command name" END},
	{ "info", (cmd_f)dtime_info,
		DEFAULT,
		DEFAULT,
		"Displays device configuration",
		"Displays device configuration",
		NOCMD},
	{ "stat", (cmd_f)dtime_stat,
		DEFAULT,
		DEFAULT,
		"Displays device statictics",
		"displays device statictics",
		NOCMD},
	LAST_CMD
};

/** Name of the dtime as presented to the user */
const char id_dtime[] = "dtime";

static void dtime_done( device_s *d);
static void dtime_read( device_s *d, uint32_t addr, uint32_t *val);

/** Dtime object structure */
device_type_s DTime =
{
	/* Type name and description */
	.name = id_dtime,
	.brief = "Real time",
	.full = "The time device brings the host real time to the simulated "
		"environment. One memory-mapped register allows programs"
		"to read hosts time since the Epoch as specified in the"
		"POSIX.",
	
	/* Functions */
	.done = dtime_done,
	.read = dtime_read,
	
	/* Commands */
	.cmds = dtime_cmds
};


/** Dtime instance data structure */
struct dtime_data_struct
{
	uint32_t addr;	/**< Dtime memory location */
};


/** Init command implementation.
 *
 * \param parm	Command-line parameters
 * \param dev	Device instance structure
 * \return True if successful
 */
static bool
dtime_init( parm_link_s *parm, device_s *dev)
{
	struct dtime_data_struct *td;
	
	/* Alloc the dtime structure. */
	td = XXMALLOC( struct dtime_data_struct);
	dev->data = td;
	
	/* Inicialization */
	parm_next( &parm);
	td->addr = parm_next_int( &parm);
	
	/* Check */

	/* Address alignment */
	if (!addr_word_aligned( td->addr))
	{
		mprintf( "Dtime address must be 4-byte aligned.\n");
		free( td);
		return false;
	}

	/* Address limit */
	if ((long long)td->addr +(long long)REGISTER_LIMIT > 0x100000000ull)
	{
		mprintf( "Invalid address; registers would exceed the 4GB limit.\n");
		return false;
	}

	
	return true;
}


/** Info command implementation
 *
 * \param parm	Command-line parameters
 * \param dev	Device instance structure
 * \return True; always successful
 */
static bool
dtime_info( parm_link_s *parm, device_s *dev)
{
	struct dtime_data_struct *td = dev->data;
	
	mprintf_btag( INFO_SPC, "address:0x%08x\n", td->addr);
	
	return true;
}


/** Stat command implementation
 *
 * \param parm	Command-line parameters
 * \param dev	Device instance structure
 * \return True; always successful
 */
static bool
dtime_stat( parm_link_s *parm, device_s *dev)
{
	mprintf_btag( INFO_SPC, "no statistics\n");
	return true;
}



/*
 *
 * Implicit commands
 *
 */

/** Disposing dtime.
 *
 * \param d	Device pointer
 */
static void
dtime_done( device_s *d)
{
	XFREE( d->name);
	XFREE( d->data);
}


/** Read command implementation.
 *
 * Reads host time via gettimeofday().
 *
 * \param d	Ddisk device pointer
 * \param addr	Address of the read operation
 * \param val	Readed (returned) value
 */
static void
dtime_read( device_s *d, uint32_t addr, uint32_t *val)
{
	struct dtime_data_struct *od = d->data;
	
	if (addr == od->addr +REGISTER_SEC || addr == od->addr +REGISTER_USEC)
	{
		/* Get actual time. */
		struct timeval t;
		gettimeofday( &t, NULL);
		*val = (addr == od->addr) ? (uint32_t)t.tv_sec : (uint32_t)t.tv_usec;
	}
}