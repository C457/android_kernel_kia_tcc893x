/* ==========================================================================
 * $File: //dwh/usb_iip/dev/software/otg/linux/drivers/dwc_otg_driver.h $
 * $Revision: #15 $
 * $Date: 2008/12/24 $
 * $Change: 1158473 $
 *
 * Synopsys HS OTG Linux Software Driver and documentation (hereinafter,
 * "Software") is an Unsupported proprietary work of Synopsys, Inc. unless
 * otherwise expressly agreed to in writing between Synopsys and you.
 * 
 * The Software IS NOT an item of Licensed Software or Licensed Product under
 * any End User Software License Agreement or Agreement for Licensed Product
 * with Synopsys or any supplement thereto. You are permitted to use and
 * redistribute this Software in source and binary forms, with or without
 * modification, provided that redistributions of source code must retain this
 * notice. You may not view, use, disclose, copy or distribute this file or
 * any information contained herein except pursuant to this license grant from
 * Synopsys. If you do not agree with this notice, including the disclaimer
 * below, then you are not authorized to use the Software.
 * 
 * THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS" BASIS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * ========================================================================== */

#ifndef __DWC_OTG_DRIVER_H__
#define __DWC_OTG_DRIVER_H__
#include <linux/semaphore.h>

/** @file
 * This file contains the interface to the Linux driver.
 */
#include "dwc_otg_core_if.h"

/* Type declarations */
struct dwc_otg_pcd;
struct dwc_otg_hcd;


/**
 * This structure is a wrapper that encapsulates the driver components used to
 * manage a single DWC_otg controller.
 */
typedef struct dwc_otg_device {
	/** Base address returned from ioremap() */
	void *base;

	/** Pointer to the core interface structure. */
	dwc_otg_core_if_t *core_if;

	/** Register offset for Diagnostic API. */
	uint32_t reg_offset;

	/** Pointer to the PCD structure. */
	struct dwc_otg_pcd *pcd;

	/** Pointer to the HCD structure. */
	struct dwc_otg_hcd *hcd;

	/* clock control */
	struct clk *clk[2];
	
	/** Flag to indicate whether the common IRQ handler is installed. */
	uint8_t common_irq_installed;

	/** For tcc_vbus_thread */
	uint8_t flagID;
	int8_t flagDeviceVBUS;
	uint8_t flagDeviceAttach;
	uint8_t flagMode, flagMode_backup;
	struct task_struct *vbus_usb_task;
	struct semaphore vbus_usb_task_lock;
#if defined(CONFIG_REGULATOR)
	struct regulator *vdd_usb33;
	struct regulator *vdd_usb12;
#endif
} dwc_otg_device_t;

#endif