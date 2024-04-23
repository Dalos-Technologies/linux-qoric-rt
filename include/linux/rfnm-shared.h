// SPDX-License-Identifier: GPL-2.0+

#ifndef INCLUDE_LINUX_RFNM_SHARED_H_
#define INCLUDE_LINUX_RFNM_SHARED_H_

#define RFNM_DAUGHTERBOARD_BREAKOUT (1)
#define RFNM_DAUGHTERBOARD_GRANITA (2)
#define RFNM_DAUGHTERBOARD_LIME (3)

#define RFNM_SLOT_PRIMARY (0)
#define RFNM_SLOT_SECONDARY (1)

#define RFNM_DAUGHTERBOARD_PRESENT (0x10)
#define RFNM_DAUGHTERBOARD_NOT_FOUND (0x20)
#define RFNM_DAUGHTERBOARD_NOT_CHECKED_YET (0xff)
#define RFNM_DTB_NODE_NOT_FOUND (-1)

extern int la9310_read_dtb_node_mem_region(const char *node_name, struct resource *get_mem_res);

/**
 * Force a structure to be packed
 */
#define __rfnm_packed __attribute__((__packed__))

#define RFNM_LA_BAR0_PHY_ADDR (0x18000000)
#define RFNM_LA_DCS_PHY_ADDR (RFNM_LA_BAR0_PHY_ADDR + 0x1040000)
#define RFNM_LA_GPOUT_PHY_ADDR (RFNM_LA_BAR0_PHY_ADDR + 0x1000580)

#define HSDAC_CFGCTL1 ( 0x210 >> 2 )

#define GP_OUT_4 ( 4 )
#define GP_OUT_7 ( 7 )

#define RFNM_ADC_MAP (int[]){0x2, 0x4, 0x1, 0x3}

#define RFNM_TX (0)
#define RFNM_RX (1)


#define MHZ_TO_HZ * 1000 * 1000ul
#define HZ_TO_MHZ(Hz) (Hz / (1000ul * 1000ul))
#define HZ_TO_KHZ(Hz) (Hz / 1000ul)

/*
struct rfnm_dgb_tx_ch {
	int freq;
	int freq_max;
	int freq_min;
	int power;
	int dac_id;
	int ch_id;
	
	void * ch_get;
	void * ch_set;
};

struct rfnm_dgb_rx_ch {
	int freq;
	int freq_max;
	int freq_min;
	int gain;
	int adc_id;
	int ch_id;
	
	void * ch_get;
	void * ch_set;
};

struct rfnm_dgb {
	struct rfnm_dgb_rx_ch rx_ch[4];
	struct rfnm_dgb_tx_ch tx_ch[4];
	int rx_ch_cnt;
	int tx_ch_cnt;
	uint8_t board_id;
	uint8_t board_revision_id;
	uint8_t serial_number[9];
	struct rfnm_dgb_dt *rfnm_dgb_dt;
};
*/

struct rfnm_eeprom_data {
	uint8_t magic_header[4];
	uint8_t pad1[12];
	uint8_t board_id;
	uint8_t board_revision_id;
	uint8_t pad2[5];
	uint8_t serial_number[9];
	uint32_t crc;
} __rfnm_packed;

// 0xff initial status is only guaranteed by uboot mod in the first 4kB
struct rfnm_bootconfig {
	uint8_t daughterboard_present[2];
	uint8_t pcie_clock_ready;
	uint8_t usb_pd_negotiation_in_progress;
	struct rfnm_eeprom_data motherboard_eeprom;
	struct rfnm_eeprom_data daughterboard_eeprom[2];
} __rfnm_packed;

//#define RFNM_MAX_TRX_CH_CNT (8)


enum rfnm_ch_data_type {
	RFNM_CH_DATA_TYPE_COMPLEX,
	RFNM_CH_DATA_TYPE_REAL
};

enum rfnm_agc_type {
    RFNM_AGC_OFF,
    RFNM_AGC_DEFAULT
};

enum rfnm_bias_tee {
    RFNM_BIAS_TEE_OFF,
    RFNM_BIAS_TEE_ON
};

enum rfnm_rf_path {
	RFNM_PATH_SMA_A,
	RFNM_PATH_SMA_B,
	RFNM_PATH_SMA_C,
	RFNM_PATH_SMA_D,
	RFNM_PATH_SMA_E,
	RFNM_PATH_SMA_F,
	RFNM_PATH_SMA_G,
	RFNM_PATH_SMA_H,
	RFNM_PATH_EMBED_ANT,
	RFNM_PATH_LOOPBACK,
	RFNM_PATH_NULL
};

enum rfnm_ch_enable {
	RFNM_CH_OFF,
	RFNM_CH_ON,
	RFNM_CH_ON_TDD
};

struct rfnm_api_tx_ch {
	int8_t abs_id;
	int8_t dgb_ch_id;
	int8_t dgb_id;
	int8_t dac_id;
        int64_t freq_min;
        int64_t freq_max;
        int64_t freq;
	int16_t iq_lpf_bw;
        int16_t samp_freq_div_m;
        int16_t samp_freq_div_n;
        int8_t avail;
        int8_t power;
	enum rfnm_ch_enable enable;
	enum rfnm_bias_tee bias_tee;
	enum rfnm_rf_path path;
	enum rfnm_rf_path path_possible[10];
	enum rfnm_ch_data_type data_type;
} __rfnm_packed;

struct rfnm_api_rx_ch {
	int8_t abs_id;
	int8_t dgb_ch_id;
	int8_t dgb_id;
	int8_t adc_id;
        int64_t freq_min;
        int64_t freq_max;
        int64_t freq;
	int16_t iq_lpf_bw;
        int16_t samp_freq_div_m;
        int16_t samp_freq_div_n;
        int8_t avail;
        int8_t gain;
        enum rfnm_ch_enable enable;
	enum rfnm_agc_type agc;
	enum rfnm_bias_tee bias_tee;
        enum rfnm_rf_path path;
	enum rfnm_rf_path path_possible[10];
	enum rfnm_ch_data_type data_type;
} __rfnm_packed;

struct rfnm_dev_hwinfo_bit {
	uint8_t board_id;
	uint8_t board_revision_id;
	uint8_t serial_number[9];
	char user_readable_name[30];
	uint8_t mac_addr[6];
	uint8_t tx_ch_cnt;
	uint8_t rx_ch_cnt;
	int16_t temperature;
} __rfnm_packed;

struct rfnm_dev_hwinfo {
	struct rfnm_dev_hwinfo_bit motherboard;
	struct rfnm_dev_hwinfo_bit daughterboard[2];
	//struct rfnm_dev_hwinfo_clockgen clock;
} __rfnm_packed;

struct rfnm_dev_tx_ch_list {
	int cnt;
	struct rfnm_api_tx_ch tx_ch[8];
} __rfnm_packed;

struct rfnm_dev_rx_ch_list {
	int cnt;
	struct rfnm_api_rx_ch rx_ch[8];
} __rfnm_packed;

enum rfnm_control_ep {
	RFNM_GET_DEV_HWINFO = 0xf00,
	RFNM_GET_TX_CH_LIST,
	RFNM_SET_TX_CH_LIST,
	RFNM_GET_RX_CH_LIST,
	RFNM_SET_RX_CH_LIST
};

struct fe_s {
	uint32_t latch_val[6];
	uint32_t latch_val_last_written[6];
	uint32_t num_latches[7];
	uint32_t align[1];
	uint32_t load_order[8];
} __rfnm_packed;

struct rfnm_dgb {
	struct rfnm_api_rx_ch *rx_ch[4];
	struct rfnm_api_tx_ch *tx_ch[4];
	struct rfnm_api_rx_ch *rx_s[4];
	struct rfnm_api_tx_ch *tx_s[4];
	int rx_ch_cnt;
	int tx_ch_cnt;

	uint8_t board_id;
	uint8_t board_revision_id;
	uint8_t serial_number[9];
	//struct rfnm_dgb_dt *rfnm_dgb_dt;

	struct device dev;
	//void *priv;
	int dgb_id;
	void *priv_drv;
	//void *priv_fe;
	struct fe_s fe;
	struct fe_s fe_tdd[2];
	void * rx_ch_set;
	void * rx_ch_get;
	void * tx_ch_set;
	void * tx_ch_get;

	uint8_t dac_ifs;
	uint8_t adc_iqswap[2];
	uint8_t dac_iqswap[2];
};

struct rfnm_m7_dgb {
	struct fe_s fe;
	struct fe_s fe_tdd[2];
	uint32_t m7_tdd_initialized;
        uint32_t dgb_id;
        uint32_t tdd_available;
} __rfnm_packed;

void rfnm_dgb_reg_rx_ch(struct rfnm_dgb *dgb_dt, struct rfnm_api_rx_ch * rx_ch, struct rfnm_api_rx_ch * rx_s);
void rfnm_dgb_reg_tx_ch(struct rfnm_dgb *dgb_dt, struct rfnm_api_tx_ch * tx_ch, struct rfnm_api_tx_ch * tx_s);
void rfnm_dgb_reg(struct rfnm_dgb *dgb_dt);
void rfnm_dgb_unreg(struct rfnm_dgb *dgb_dt);
void rfnm_dgb_en_tdd(struct rfnm_dgb *dgb_dt, struct rfnm_api_tx_ch * tx_ch, struct rfnm_api_rx_ch * rx_ch);

void rfnm_populate_dev_hwinfo(struct rfnm_dev_hwinfo *r_hwinfo);
#endif
