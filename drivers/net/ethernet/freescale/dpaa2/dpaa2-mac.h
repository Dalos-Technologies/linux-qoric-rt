/* SPDX-License-Identifier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2019, 2024 NXP */
#ifndef DPAA2_MAC_H
#define DPAA2_MAC_H

#include <linux/of.h>
#include <linux/of_mdio.h>
#include <linux/of_net.h>
#include <linux/phylink.h>
#include "dpmac.h"
#include "dpmac-cmd.h"

struct dpaa2_mac {
	struct fsl_mc_device *mc_dev;
	struct dpmac_link_state state;
	struct net_device *net_dev;
	struct fsl_mc_io *mc_io;
	struct dpmac_attr attr;
	u16 ver_major, ver_minor;
	unsigned long features;

	struct phylink_config phylink_config;
	struct phylink *phylink;
	struct ethtool_link_ksettings kset;
	phy_interface_t if_mode;
	enum dpmac_link_type if_link_type;
	struct phylink_pcs *pcs;
	struct fwnode_handle *fw_node;

	struct phy **phys;
	size_t num_phys;
	size_t num_lanes;

	int phy_req_state;
	u32 *cnt_idx_dma_mem;
	u64 *cnt_values_dma_mem;
	dma_addr_t cnt_idx_iova, cnt_values_iova;
};

static inline bool dpaa2_mac_is_type_phy(struct dpaa2_mac *mac)
{
	if (!mac)
		return false;

	return mac->attr.link_type == DPMAC_LINK_TYPE_PHY ||
	       mac->attr.link_type == DPMAC_LINK_TYPE_BACKPLANE;
}

int dpaa2_mac_open(struct dpaa2_mac *mac);

void dpaa2_mac_close(struct dpaa2_mac *mac);

int dpaa2_mac_connect(struct dpaa2_mac *mac);

void dpaa2_mac_disconnect(struct dpaa2_mac *mac);

int dpaa2_mac_get_sset_count(void);

void dpaa2_mac_get_strings(u8 *data);

void dpaa2_mac_get_ethtool_stats(struct dpaa2_mac *mac, u64 *data);

void dpaa2_mac_start(struct dpaa2_mac *mac);

void dpaa2_mac_stop(struct dpaa2_mac *mac);

void dpaa2_mac_driver_attach(struct fsl_mc_device *dpmac_dev);

void dpaa2_mac_driver_detach(struct fsl_mc_device *dpmac_dev);

#endif /* DPAA2_MAC_H */
