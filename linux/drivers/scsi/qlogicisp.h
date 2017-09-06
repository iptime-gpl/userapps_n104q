/*
 * QLogic ISP1020 Intelligent SCSI Processor Driver (PCI)
 * Written by Erik H. Moe, ehm@cris.com
 * Copyright 1995, Erik H. Moe
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

/* Renamed and updated to 1.3.x by Michael Griffith <grif@cs.ucr.edu> */

/*
 * $Date: 2010/06/15 01:48:50 $
 * $Revision: 1.1.1.1 $
 *
 * $Log: qlogicisp.h,v $
 * Revision 1.1.1.1  2010/06/15 01:48:50  ysyoo
 * RTL8196C
 *
 * Revision 1.1.1.1  2007/08/06 10:04:53  root
 * Initial import source to CVS
 *
 * Revision 1.1.1.1  2004/07/28 06:27:28  ysc
 *
 * Initial version
 *
 * Revision 1.1.1.1  2004/07/14 13:34:20  ysy
 *
 *
 * Revision 1.1.1.1  2004/07/13 21:58:27  ysy
 *
 *
 * Revision 1.1.1.1  2004/07/13 15:57:45  ysy
 * no message
 *
 * Revision 1.1.1.2  2003/04/04 01:16:22  david
 * rtl8181 project
 *
 * Revision 1.1.1.1  2003/03/13 07:57:15  david
 *
 * :
 * VS: ----------------------------------------------------------------------
 *
 * Revision 1.1.1.1  2003/03/13 07:57:15  john
 * rtl8181_prj initially build_up
 *
 * Revision 1.1.1.1  2003/03/12 06:25:12  john
 * rtl8181_prj initially build_up
 *
 * Revision 1.1.1.1  2003/03/12 06:19:21  john
 * rtl8181_prj initially build_up
 *
 * Revision 1.1.1.1  2003/03/11 06:59:05  john
 * RTL8181 Initical Check In
 *
 * Revision 1.1.1.1  2002/03/04 11:13:01  carstenl
 * Linux kernel version 2.4.18 from cvs@oss.sgi.com, 4 March, 2002
 *
 * Revision 0.5  1995/09/22  02:32:56  root
 * do auto request sense
 *
 * Revision 0.4  1995/08/07  04:48:28  root
 * supply firmware with driver.
 * numerous bug fixes/general cleanup of code.
 *
 * Revision 0.3  1995/07/16  16:17:16  root
 * added reset/abort code.
 *
 * Revision 0.2  1995/06/29  03:19:43  root
 * fixed biosparam.
 * added queue protocol.
 *
 * Revision 0.1  1995/06/25  01:56:13  root
 * Initial release.
 *
 */

#ifndef _QLOGICISP_H
#define _QLOGICISP_H

/*
 * With the qlogic interface, every queue slot can hold a SCSI
 * command with up to 4 scatter/gather entries.  If we need more
 * than 4 entries, continuation entries can be used that hold
 * another 7 entries each.  Unlike for other drivers, this means
 * that the maximum number of scatter/gather entries we can
 * support at any given time is a function of the number of queue
 * slots available.  That is, host->can_queue and host->sg_tablesize
 * are dynamic and _not_ independent.  This all works fine because
 * requests are queued serially and the scatter/gather limit is
 * determined for each queue request anew.
 */
#define QLOGICISP_REQ_QUEUE_LEN	63	/* must be power of two - 1 */
#define QLOGICISP_MAX_SG(ql)	(4 + ((ql) > 0) ? 7*((ql) - 1) : 0)

int isp1020_detect(Scsi_Host_Template *);
int isp1020_release(struct Scsi_Host *);
const char * isp1020_info(struct Scsi_Host *);
int isp1020_queuecommand(Scsi_Cmnd *, void (* done)(Scsi_Cmnd *));
int isp1020_abort(Scsi_Cmnd *);
int isp1020_reset(Scsi_Cmnd *, unsigned int);
int isp1020_biosparam(Disk *, kdev_t, int[]);

#ifndef NULL
#define NULL (0)
#endif

#define QLOGICISP {							   \
	detect:			isp1020_detect,				   \
	release:		isp1020_release,			   \
	info:			isp1020_info,				   \
	queuecommand:		isp1020_queuecommand,			   \
	abort:			isp1020_abort,				   \
	reset:			isp1020_reset,				   \
	bios_param:		isp1020_biosparam,			   \
	can_queue:		QLOGICISP_REQ_QUEUE_LEN,		   \
	this_id:		-1,					   \
	sg_tablesize:		QLOGICISP_MAX_SG(QLOGICISP_REQ_QUEUE_LEN), \
	cmd_per_lun:		1,					   \
	present:		0,					   \
	unchecked_isa_dma:	0,					   \
	use_clustering:		DISABLE_CLUSTERING			   \
}

#endif /* _QLOGICISP_H */
